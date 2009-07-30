// $Id$

#include "NodeDaemon_Server_Impl.h"

#if !defined (__CUTS_INLINE__)
#include "NodeDaemon_Server_Impl.inl"
#endif

//
// init
//
int CUTS_NodeDaemon_Server_Impl::init (int argc, char * argv [])
{
  try
  {
    // Parse the command-line options.
    if (0 != this->parse_args (argc, argv))
      ACE_ERROR_RETURN ((LM_ERROR,
                          ACE_TEXT ("%T (%t) - %M - failed to parse ")
                          ACE_TEXT ("command-line options\n")),
                          -1);

    // Update the task with the new ORB.
    this->task_.reset (this->orb_.in ());

    // Resolve the RootPOA.
    ACE_DEBUG ((LM_DEBUG,
                ACE_TEXT ("%T (%t) - %M - resolving RootPOA\n")));

    ::CORBA::Object_var obj = this->orb_->resolve_initial_references ("RootPOA");
    if (::CORBA::is_nil (obj.in ()))
      ACE_ERROR_RETURN ((LM_ERROR,
                          ACE_TEXT ("%T (%t) - %M - failed to resolve ")
                          ACE_TEXT ("the RootPOA\n")),
                          -1);

    this->root_poa_ = ::PortableServer::POA::_narrow (obj.in ());
    if (::CORBA::is_nil (this->root_poa_.in ()))
      ACE_ERROR_RETURN ((LM_ERROR,
                          ACE_TEXT ("%T (%t) - %M - object is not a ")
                          ACE_TEXT ("::PortableServer::POA\n")),
                          -1);

    // Activate the RootPOA's POA manager.
    ACE_DEBUG ((LM_DEBUG,
                ACE_TEXT ("%T (%t) - %M - activating RootPOA manager\n")));

    ::PortableServer::POAManager_var mgr = this->root_poa_->the_POAManager ();
    mgr->activate ();

    // Activate the server's daemon object.
    ACE_DEBUG ((LM_DEBUG,
                ACE_TEXT ("%T (%t) - %M - activating NodeDaemon servant\n")));
    PortableServer::ObjectId_var oid = this->root_poa_->activate_object (&this->daemon_);

    // Activate the task that runs the ORB's event loop.
    if (0 != this->task_.activate ())
      ACE_ERROR_RETURN ((LM_ERROR,
                          ACE_TEXT ("%T (%t) - %M - failed to activate ")
                          ACE_TEXT ("logging server's ORB task\n")),
                          -1);

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
// fini
//
int CUTS_NodeDaemon_Server_Impl::fini (void)
{
  try
  {
    // Deactivate the servant.
    ACE_DEBUG ((LM_DEBUG,
                ACE_TEXT ("%T (%t) - %M - deactivating NodeDaemon servant\n")));
    ::PortableServer::ObjectId_var oid = this->root_poa_->servant_to_id (&this->daemon_);
    this->root_poa_->deactivate_object (oid.in ());

    // Shutdown ORB and wait for all threads to exit.
    ACE_DEBUG ((LM_DEBUG,
                ACE_TEXT ("%T (%t) - %M - shutting down the ORB\n")));

    this->orb_->shutdown ();
    this->task_.wait ();

    // Destroy the remaining resources.
    ACE_DEBUG ((LM_DEBUG,
                ACE_TEXT ("%T (%t) - %M - release ORB resources\n")));
    this->root_poa_->destroy (0, 0);
    this->orb_->destroy ();

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
// parse_args
//
int CUTS_NodeDaemon_Server_Impl::parse_args (int argc, char * argv [])
{
  this->orb_ = ::CORBA::ORB_init (argc, argv);
  return 0;
}

