// $Id$

#if !defined (__CUTS_INLINE__)
#include "CCM_ComponentServer_App_T.inl"
#endif

#include "CCM_Cookie.h"
#include "ace/Get_Opt.h"

//
// run
//
template <typename T, typename IMPL>
int CUTS_CCM_ComponentServer_App_T <T, IMPL>::run_main (int argc, char * argv[])
{
  try
  {
    // Parse the command-line options.
    this->parse_standard_args (argc, argv);

    // Instantiate a new ORB.
    this->orb_ = ::CORBA::ORB_init (argc, argv);
    this->task_.reset (this->orb_.in ());

    // Register the value types.
    this->register_valuetypes (this->orb_.in ());

    // Finish the initialization process, which mean create the
    // actual component server's implementation.
    IMPL * server = 0;
    T * self = dynamic_cast <T *> (this);

    ACE_NEW_THROW_EX (server,
                      IMPL (self),
                      ::CORBA::NO_MEMORY ());

    this->server_.reset (server);
    this->server_->init (argc, argv);

    // First, let's extract the server activator.
    ::CORBA::Object_var obj = this->orb_->string_to_object (this->callback_ior_.c_str ());

    if (::CORBA::is_nil (obj.in ()))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - IOR is not a valid object [%s]\n"),
                         this->callback_ior_.c_str ()),
                         -1);

    ::CIAO::Deployment::ServerActivator_var activator =
      ::CIAO::Deployment::ServerActivator::_narrow (obj.in ());

    if (::CORBA::is_nil (activator.in ()))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - object is not a ")
                         ACE_TEXT ("CIAO::Deployment::ServerActivator\n")),
                         -1);

    // Get the RootPOA.
    obj = this->orb_->resolve_initial_references ("RootPOA");

    if (::CORBA::is_nil (obj.in ()))
      return -1;

    this->root_ = PortableServer::POA::_narrow (obj.in ());
    if (::CORBA::is_nil (this->root_.in ()))
      return -1;

    // Activate the POA manager.
    ::PortableServer::POAManager_var mgr = this->root_->the_POAManager ();
    mgr->activate ();

    // Activate the server object with the RootPOA.
    this->root_->activate_object (this->server_.get ());

    // Activate the ORB's task. This will allow the component server to
    // receive commands from DAnCE.
    if (-1 == this->task_.activate ())
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to activate ORB task\n")),
                         -1);

    // Configure the component server.
    if (-1 == this->configure_component_server (activator.in ()))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to configure component server\n")),
                         -1);

    // Activate the TCP/IP server.
    if (-1 == this->server_->activate ())
       ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to activate TCP/IP ORB task\n")),
                         -1);

    // Wait for all threads to exit.
    this->task_.wait ();

    return 0;
  }
  catch (const CORBA::Exception & ex)
  {
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - %s\n"),
                ex._info ().c_str ()));
  }

  return -1;
}

//
// register_valuetypes
//
template <typename T, typename IMPL>
void CUTS_CCM_ComponentServer_App_T <T, IMPL>::
register_valuetypes (CORBA::ORB_ptr orb)
{
  ::CORBA::ValueFactory_var prev;

  prev = orb->register_value_factory (
    ::Components::PortDescription::_tao_obv_static_repository_id (),
    new ::Components::PortDescription_init ());

  prev = orb->register_value_factory (
    ::Components::FacetDescription::_tao_obv_static_repository_id (),
    new ::Components::FacetDescription_init ());

  prev = orb->register_value_factory (
    ::Components::FacetDescription::_tao_obv_static_repository_id (),
    new ::Components::ConnectionDescription_init ());

  prev = orb->register_value_factory (
    ::Components::ReceptacleDescription::_tao_obv_static_repository_id (),
    new ::Components::ReceptacleDescription_init ());

  prev = orb->register_value_factory (
    ::Components::ConsumerDescription::_tao_obv_static_repository_id (),
    new ::Components::ConsumerDescription_init ());

  prev = orb->register_value_factory (
    ::Components::EmitterDescription::_tao_obv_static_repository_id (),
    new ::Components::EmitterDescription_init ());

  prev = orb->register_value_factory (
    ::Components::SubscriberDescription::_tao_obv_static_repository_id (),
    new ::Components::SubscriberDescription_init ());

  prev = orb->register_value_factory (
    ::Components::PublisherDescription::_tao_obv_static_repository_id (),
    new ::Components::PublisherDescription_init ());

  prev = orb->register_value_factory (
    ::Components::ConfigValue::_tao_obv_static_repository_id (),
    new ::Components::ConfigValue_init ());

  prev = orb->register_value_factory (
    ::Components::ComponentPortDescription::_tao_obv_static_repository_id (),
    new ::Components::ComponentPortDescription_init ());

  prev = orb->register_value_factory (
    CUTS_CCM_Cookie::_tao_obv_static_repository_id (),
    new CUTS_CCM_Cookie_Factory ());
}

//
// configure_component_server
//
template <typename T, typename IMPL>
int CUTS_CCM_ComponentServer_App_T <T, IMPL>::
configure_component_server (::CIAO::Deployment::ServerActivator_ptr activator)
{
  // Register the component server with the server activator.
  ::CORBA::Object_var obj = this->root_->servant_to_reference (this->server_.get ());

  if (::CORBA::is_nil (obj.in ()))
    ACE_ERROR_RETURN ((LM_ERROR,
                        ACE_TEXT ("%T (%t) - %M - failed to get servant reference\n")),
                        -1);

  ::Components::ConfigValues_var config;
  ::Components::Deployment::ComponentServer_var server_ref =
    ::Components::Deployment::ComponentServer::_narrow (obj.in ());

  activator->component_server_callback (server_ref.in (),
                                        this->uuid_.c_str (),
                                        config.out ());

  this->server_->configure (activator,
                            config._retn (),
                            this->root_.in ());

  activator->configuration_complete (this->uuid_.c_str ());
  return 0;
}

//
// shutdown
//
template <typename T, typename IMPL>
void CUTS_CCM_ComponentServer_App_T <T, IMPL>::shutdown (bool notify)
{
  try
  {
    if (notify)
    {
      // Shutdown the application server.
      ACE_DEBUG ((LM_DEBUG,
                  ACE_TEXT ("%T (%t) - %M - shutdown the component server\n")));

      this->server_->shutdown ();
    }
    else
    {
      // Shutdown the ORB.
      ACE_DEBUG ((LM_DEBUG,
                  ACE_TEXT ("%T (%t) - %M - shutdown the ORB task\n")));

      this->orb_->shutdown ();
    }
  }
  catch (const CORBA::Exception & ex)
  {
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - %s\n"),
                ex._info ().c_str ()));
  }
}

//
// destroy
//
template <typename T, typename IMPL>
void CUTS_CCM_ComponentServer_App_T <T, IMPL>::destroy (void)
{
  try
  {
    if (!::CORBA::is_nil (this->root_.in ()))
    {
      this->root_->destroy (0, 0);
      this->root_ = ::PortableServer::POA::_nil ();
    }

    if (!::CORBA::is_nil (this->orb_.in ()))
    {
      this->orb_->destroy ();
      this->orb_ = ::CORBA::ORB::_nil ();
    }
  }
  catch (const CORBA::Exception & ex)
  {
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - %s\n"),
                ex._info ().c_str ()));
  }
}

//
// parse_args
//
template <typename T, typename IMPL>
int CUTS_CCM_ComponentServer_App_T <T, IMPL>::
parse_standard_args (int argc, char * argv [])
{
  const char * optargs = ACE_TEXT ("u:c:");
  ACE_Get_Opt get_opt (argc, argv, optargs);

  get_opt.long_option (ACE_TEXT("uuid"), 'u', ACE_Get_Opt::ARG_REQUIRED);
  get_opt.long_option (ACE_TEXT("callback-ior"), 'c', ACE_Get_Opt::ARG_REQUIRED);

  char opt;

  while (EOF != (opt = get_opt ()))
  {
    switch (opt)
    {
    case 0:
      if (0 == ACE_OS::strcmp (ACE_TEXT ("callback-ior"), get_opt.long_option ()))
      {
        this->callback_ior_ = get_opt.opt_arg ();
      }
      else if (0 == ACE_OS::strcmp (ACE_TEXT ("uuid"), get_opt.long_option ()))
      {
        this->uuid_ = get_opt.opt_arg ();
      }
      break;

    case 'c':
      this->callback_ior_ = get_opt.opt_arg ();
      break;

    case 'u':
      this->uuid_ = get_opt.opt_arg ();
      break;
    };
  }

  return 0;
}
