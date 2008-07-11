// $Id$

#include "Testing_App_Server.h"
#include "TestManager_i.h"
#include "tao/IORTable/IORTable.h"
#include "ace/Thread_Manager.h"
#include "ace/Get_Opt.h"
#include "ace/Guard_T.h"

//
// CUTS_Testing_App_Server
//
CUTS_Testing_App_Server::CUTS_Testing_App_Server (void)
{

}

//
// CUTS_Testing_App_Server
//
CUTS_Testing_App_Server::~CUTS_Testing_App_Server (void)
{

}

//
// run_main
//
int CUTS_Testing_App_Server::run_main (int argc, char * argv [])
{ 
  if (this->parse_args (argc, argv) == -1)
    return -1;

  // Spawn the server's service thread.
  int grp_id =
    ACE_Thread_Manager::instance ()->spawn (
      CUTS_Testing_App_Server::svc_run,
      this);

  if (grp_id == -1)
  {
    ACE_ERROR ((LM_ERROR, 
                "%T - [%M] - failed to start test manger server\n"));
  }
  
  // Pass control to the base class. This method does not return until
  // the testing application is shutdown.

  ACE_DEBUG ((LM_DEBUG, 
              "%T - [%M] - passing control to base class\n"));

  this->run_main_i ();

  // Wait for the server thread to exit.
  if (grp_id != -1)
    ACE_Thread_Manager::instance ()->wait_grp (grp_id);

  return 0;
}

//
// parse_args
//
int CUTS_Testing_App_Server::parse_args (int argc, char * argv [])
{
  this->orb_ = CORBA::ORB_init (argc, argv);

  // Pass control to the base class.
  if (CUTS_Testing_App::parse_args (argc, argv) == -1)
    return -1;

  // Parse the remainder of the command-line options.
  const ACE_TCHAR * opts = ACE_TEXT ("");
  ACE_Get_Opt get_opt (argc, argv, opts);

  get_opt.long_option ("regiser-with-ns");

  char ch;

  while ((ch = get_opt ()) != EOF)
  {
    switch (ch)
    {
    case 0:
      if (ACE_OS::strcmp ("register-with-ns", get_opt.long_option ()) == 0)
        this->regiser_with_ns_ = true;

      break;
    };
  }

  return 0;
}

//
// svc_run
//
ACE_THR_FUNC_RETURN CUTS_Testing_App_Server::svc_run (void * param)
{
  // Get the server from the thread's parameter.
  CUTS_Testing_App_Server * server = 
    reinterpret_cast <CUTS_Testing_App_Server *> (param);

  return server->orb_svc ();
}

//
// shutdown
//
int CUTS_Testing_App_Server::shutdown (void)
{
  try
  {
    // We need to unregister the object with the naming service before we 
    // shutdown the ORB.
    if (this->regiser_with_ns_)
      this->unregister_with_name_service ();

    // Stop the main event loop for the ORB.
    ACE_DEBUG ((LM_DEBUG,
                  "%T - [%M] - shutting down the ORB\n"));

    this->orb_->shutdown (true);

    // Now, pass control to the base class.
    CUTS_Testing_App::shutdown ();
  }
  catch (const CORBA::Exception & ex)
  {
    ACE_ERROR ((LM_ERROR, 
                "%T - [%M] - %s\n", 
                ex._info ().c_str ()));
  }
  catch (...)
  {
    ACE_ERROR ((LM_ERROR, 
                "%T - [%M] - caught unknown exception\n"));
  }

  return -1;
}

//
// register_with_iortable
//
int CUTS_Testing_App_Server::register_with_iortable (void)
{
  try
  {
    // Locate the IORTable for the application.
    CORBA::Object_var obj = this->orb_->resolve_initial_references ("IORTable");
    IORTable::Table_var ior_table = IORTable::Table::_narrow (obj.in ());

    if (::CORBA::is_nil (ior_table.in ()))
    {
      ACE_ERROR_RETURN ((LM_ERROR,
                         "%T - [%M] - failed to resolve IOR table\n"),
                         -1);
    }

    // Construct the name for the test manager.
    ACE_CString manager_name = "CUTS/TestManager/";
    manager_name += this->name ();

    // Get the IOR string for the test manager.
    CUTS::TestManager_var test_mgr = this->test_manager_->_this ();
    CORBA::String_var obj_str  = this->orb_->object_to_string (test_mgr.in ());
    CORBA::String_var name_str = CORBA::string_dup (manager_name.c_str ());

    // Bind the object to the IOR table.
    ACE_DEBUG ((LM_DEBUG, 
                "%T - [%M] - registering test manager with the IOR table [%s]\n",
                manager_name.c_str ()));

    ior_table->bind (name_str.in (), obj_str.in ());
    return 0;
  }
  catch (const CORBA::Exception & ex)
  {
    ACE_ERROR ((LM_ERROR,
                "%T - [%M] - %s\n",
                ex._info ().c_str ()));
  }

  return -1;
}

//
// register_with_name_service
//
int CUTS_Testing_App_Server::register_with_name_service (void)
{
  try
  {
    // Get the root context of the naming service.
    CORBA::Object_var obj = 
      this->orb_->resolve_initial_references ("NameService");

    this->root_ctx_ = CosNaming::NamingContextExt::_narrow (obj.in ());

    // Construct all the context we would like to create, then contact
    // the naming service to ensure they all exist.
    const char * ctx_names [] = {"CUTS", "TestManager"};

    CosNaming::Name ns_name (3);
    CosNaming::NamingContext_var ctx;

    for (int i = 0; i < 2; ++ i)
    {
      // Initialize the next id in the name.
      ns_name.length (i + 1);
      ns_name[i].id = CORBA::string_dup (ctx_names[i]);

      try
      {
        ctx = this->root_ctx_->bind_new_context (ns_name);
      }
      catch (const CosNaming::NamingContext::AlreadyBound &)
      {
        // do nothing
      }
    }

    // Update the length so that the test manager's name is visible
    // to the naming service.
    ns_name.length (3);
    ns_name[2].id = CORBA::string_dup (this->name ().c_str ());

    // Bind the actual test manger to the naming service.
    ACE_DEBUG ((LM_DEBUG, 
                "%T - [%M] - binding testing manager to naming service as %s\n",
                this->name ().c_str ()));

    CUTS::TestManager_var tm = this->test_manager_->_this ();
    this->root_ctx_->bind (ns_name, tm);
    return 0;
  }
  catch (const CosNaming::NamingContext::AlreadyBound & ex)
  {
    ACE_ERROR ((LM_ERROR,
                "%T - [%M] - %s already registered with naming service (%s)\n",
                this->name ().c_str (),
                ex._info ().c_str ()));
  }
  catch (const CORBA::Exception & ex)
  {
    ACE_ERROR ((LM_ERROR, 
                "%T - [%M] - %s\n", 
                ex._info ().c_str ()));
  }
  catch (...)
  {
    
  }

  return -1;
}

//
// register_with_name_service
//
int CUTS_Testing_App_Server::unregister_with_name_service (void)
{
  if (CORBA::is_nil (this->root_ctx_))
    return 0;

  try
  {
    // Construct the fully qualified name of the test manger for 
    // within the naming service.
    CosNaming::Name ns_name (3);
    ns_name.length (3);

    ns_name[0].id = CORBA::string_dup ("CUTS");
    ns_name[1].id = CORBA::string_dup ("TestManager");
    ns_name[2].id = CORBA::string_dup (this->name ().c_str ());

    // Unregister the TestManger with the naming service.
    ACE_DEBUG ((LM_INFO, 
                "%T - [%M] - unregistering test manager with naming service\n"));

    this->root_ctx_->unbind (ns_name);
  }
  catch (const CORBA::Exception & ex)
  {
    ACE_ERROR ((LM_ERROR,
                "%T - [%M] - %s\n",
                ex._info ().c_str ()));
  }
  catch (...)
  {
    ACE_ERROR ((LM_ERROR,
                "%T - [%M] - caught unknown exception\n"));
  }

  return -1;
}

//
// svc
//
int CUTS_Testing_App_Server::orb_svc (void)
{
  try
  {
    // Get a reference to the <RootPOA>
    ACE_DEBUG ((LM_DEBUG, 
                "%T - [%M] - resolving initial reference to RootPOA\n"));
    CORBA::Object_var obj = this->orb_->resolve_initial_references ("RootPOA");
    PortableServer::POA_var root_poa = PortableServer::POA::_narrow (obj.in ());

    // Activate the RootPOA's manager.
    ACE_DEBUG ((LM_DEBUG, 
                "%T - [%M] - getting reference to POAManager\n"));
    PortableServer::POAManager_var mgr = root_poa->the_POAManager ();
    mgr->activate ();

    // Create a new test manager.
    ACE_NEW_THROW_EX (this->test_manager_, 
                      CUTS_TestManager_i (*this), 
                      CORBA::NO_MEMORY ());

    // Activate the manager and transfer ownership.
    CUTS::TestManager_var manager = this->test_manager_->_this ();
    this->servant_ = this->test_manager_;

    // Register the test manager with the IORTable for the ORB.
    if (this->register_with_iortable () == -1)
    {
      ACE_ERROR ((LM_ERROR,
                  "%T - [%M] - failed to register with IOR table\n"));
    }

    // Register the test manager with the naming service, if applicable.
    if (this->regiser_with_ns_)
    {
      if (this->register_with_name_service () == -1)
      {
        ACE_ERROR ((LM_ERROR, 
                    "%T - [%M] - failed to register %s with naming service",
                    this->name ().c_str ()));
      }
    }

    // Run the ORB's main event loop.
    ACE_DEBUG ((LM_DEBUG,
                "%T - [%M] - running the server's main event loop\n"));
    this->orb_->run ();

    // Destroy the RootPOA.
    ACE_DEBUG ((LM_DEBUG, "%T - [%M] - destroying the RootPOA\n"));
    root_poa->destroy (true, true);

    // Destroy the ORB.
    ACE_DEBUG ((LM_DEBUG, "%T - [%M] - destroying the ORB\n"));
    this->orb_->destroy ();
    return 0;
  }
  catch (const CORBA::Exception & ex)
  {
    ACE_ERROR ((LM_ERROR,
                "%T - [%M] - : %s\n",
                ex._info ().c_str ()));
  }
  catch (...)
  {
    ACE_ERROR ((LM_ERROR,
                "%T - [%M] - : caught unknown exception\n"));
  }

  return -1;
}
