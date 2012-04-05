// $Id:

#include "Tron_Deployment_Handler.h"
#include <cstddef>
#include "ace/ARGV.h"

//
// adapter_new
//
TestAdapter * adapter_new (Reporter * r, int argc, const char * argv[])
{
  try
  {
    // Create the deployment singleton and initialize it.
    Tron_Deployment_Handler::create_singleton (r);
    if (0 != Tron_Deployment_Handler::singleton ()->init (argc, argv))
      ACE_ERROR_RETURN((LM_ERROR,
                        ACE_TEXT ("%T (%t) - %M - adapter initializtion failed\n")),
                        0);

    return Tron_Deployment_Handler::singleton ();
  }
  catch (...)
  {
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - caught unknown exception [%N:%l]\n")));
  }
  return 0;
}

//
// adapter_delete
//
void adapter_delete (TestAdapter * adapter)
{
  if (adapter != Tron_Deployment_Handler::singleton ())
    return;

  Tron_Deployment_Handler::destroy_singleton ();
}

//
// adapter_start
//
void adapter_start (TestAdapter * adapter)
{
  Tron_Deployment_Handler * handler = 0;
  handler = dynamic_cast <Tron_Deployment_Handler *> (adapter);
  handler->adapter_start ();
}

//
// adapter_perform
//
void adapter_perform (TestAdapter * adapter, int32_t chan, uint16_t n, const int32_t data[])
{
  Tron_Deployment_Handler * handler = 0;
  handler = dynamic_cast <Tron_Deployment_Handler *> (adapter);
  if (handler != 0)
    handler->adapter_perform (chan, n, data);
}

//
// singleton_
//
Tron_Deployment_Handler * Tron_Deployment_Handler::singleton_ = 0;

//
// create_singleton
//
void Tron_Deployment_Handler::create_singleton (Reporter * r)
{
  if (0 == Tron_Deployment_Handler::singleton_)
    Tron_Deployment_Handler::singleton_ = new Tron_Deployment_Handler (r);
}

//
// destroy_singleton
//
void Tron_Deployment_Handler::destroy_singleton (void)
{
  if (0 != Tron_Deployment_Handler::singleton_)
  {
    delete Tron_Deployment_Handler::singleton_;
    Tron_Deployment_Handler::singleton_ = 0;
  }
}

//
// singleton
//
inline
Tron_Deployment_Handler * Tron_Deployment_Handler::singleton (void)
{
  return Tron_Deployment_Handler::singleton_;
}

//
// Tron_Deployment_Handler
//
Tron_Deployment_Handler::Tron_Deployment_Handler (Reporter * r)
: TestAdapter (r),
  ta_mgr_ (&ta_, false)
{
  // Set the start and perform methods
  this->start = &(::adapter_start);
  this->perform = &(::adapter_perform);
}

//
// ~Tron_Deployment_Handler
//
Tron_Deployment_Handler::~Tron_Deployment_Handler (void)
{

}

//
// init
//
int Tron_Deployment_Handler::init (int argc, const char * argv[])
{
  try
  {
    ACE_ARGV_T <char> dup_args (argc, const_cast <char **> (argv));

    ACE_DEBUG  ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - initializing test adapter orb with [%s]\n"),
                dup_args.buf ()));

    this->orb_ = ::CORBA::ORB_init (argc, dup_args.argv ());

    ::CORBA::Object_var obj = this->orb_->resolve_initial_references ("TestAdapterCallback");

    if (::CORBA::is_nil (obj.in ()))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to resolve TestAdapterCallback\n")),
                         -1);

    this->callback_ = ::Tron::TestAdapterCallback::_narrow (obj.in ());

    if (::CORBA::is_nil (obj.in ()))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - object is not a TestAdapterCallback\n")),
                         -1);

    // Activate the TestAdapter implementation.
    this->activate_test_adapter ();

    // Run the ORB in another thread (i.e., task).
    ACE_ERROR ((LM_DEBUG,
              ACE_TEXT ("%T (%t) - %M - running ORB in another thread\n")));
    this->task_.reset (this->orb_.in ());
    this->task_.activate ();

    // Setup reporter
    this->rep->setTimeUnit (this->rep, 10000);
    this->rep->setTimeout (this->rep, 100000);

    // Block until tron servants are initialized
    this->ta_.wait_for_initialization_complete ();

    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - initialization is complete\n")));

    // Setup input channels
/*    int r;
    r = this->rep->getInputEncoding (this->rep, "Click");

    // Setup output channels
    r = this->rep->getOutputEncoding (this->rep, "SingleClick");
    r = this->rep->getOutputEncoding (this->rep, "DoubleClick");
*/
    return 0;
  }
  catch (const ::CORBA::Exception & ex)
  {
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - %s\n"),
                ex._info ().c_str ()));
  }
  return -1;
}

//
// activate_test_adapter
//
void Tron_Deployment_Handler::activate_test_adapter (void)
{
  // Get a reference to the <RootPOA>
  ::CORBA::Object_var obj = this->orb_->resolve_initial_references ("RootPOA");
  ::PortableServer::POA_var root_poa = ::PortableServer::POA::_narrow (obj.in ());

  // Activate the RootPOA's manager.
  ::PortableServer::POAManager_var mgr = root_poa->the_POAManager ();
  mgr->activate ();

  this->ta_mgr_.activate (root_poa.in ());

  ACE_ERROR ((LM_DEBUG,
            ACE_TEXT ("%T (%t) - %M - TestAdapter is activated\n")));

  // Register TestAdapter with the callback
  obj = this->ta_mgr_.get_reference ();
  ::Tron::TestAdapter_var ta = ::Tron::TestAdapter::_narrow (obj.in ());

  ACE_ERROR ((LM_DEBUG,
            ACE_TEXT ("%T (%t) - %M - setting test adapter callback\n")));

  this->callback_->set_test_adapter (ta.in ());

  ACE_ERROR ((LM_DEBUG,
            ACE_TEXT ("%T (%t) - %M - test adapter is registered\n")));
}

//
// adapter_start
//
void Tron_Deployment_Handler::adapter_start (void)
{
  // Block for TA_Impl.is_configuration_complete ()
  ACE_ERROR ((LM_DEBUG,
              ACE_TEXT ("%T (%t) - %M - waiting for components to be activated\n")));

  this->ta_.wait_for_activate_complete ();

  ACE_ERROR ((LM_DEBUG,
              ACE_TEXT ("%T (%t) - %M - all components are now activated\n")));
}

//
// adapter_perform
//
void Tron_Deployment_Handler::adapter_perform (int32_t channel,
                                               uint16_t size, const int32_t data[])
{
  this->rep->report_now (this->rep, 4, 0, NULL);
}
