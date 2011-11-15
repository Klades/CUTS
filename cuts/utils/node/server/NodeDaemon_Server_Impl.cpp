// $Id$

#include "NodeDaemon_Server_Impl.h"

#if !defined (__CUTS_INLINE__)
#include "NodeDaemon_Server_Impl.inl"
#endif

#include "ace/Get_Opt.h"

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
    this->deamon_mgr_.activate (this->root_poa_.in ());

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
    this->deamon_mgr_.deactivate ();

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

  const char * optargs = ACE_TEXT ("o:");
  ACE_Get_Opt get_opt (argc, argv, optargs, 0);

  get_opt.long_option ("register-with-ns", ACE_Get_Opt::ARG_REQUIRED);
  get_opt.long_option ("register-with-iortable", ACE_Get_Opt::ARG_REQUIRED);

  char opt;

  while (EOF != (opt = get_opt ()))
  {
    switch (opt)
    {
    case 0:
      if (0 == ACE_OS::strcmp ("register-with-ns", get_opt.long_option ()))
      {
        this->opts_.ns_name_ = get_opt.opt_arg ();
      }
      else if (0 == ACE_OS::strcmp ("register-with-iortable", get_opt.long_option ()))
      {
        this->deamon_mgr_.set_trait_value (CUTS_IOR_Table_Trait (), get_opt.opt_arg ());
      }

      break;

    case 'o':
      this->deamon_mgr_.set_trait_value (CUTS_IOR_File_Trait (), get_opt.opt_arg ());
      break;
    }
  }

  return 0;
}
