// $Id$

#include "Testing_App_Server.h"
#include "TestManager_i.h"
#include "tao/IORTable/IORTable.h"
#include "ace/Thread_Manager.h"

#define VERBOSE_MSG(msg) \
  if (this->verbose_) \
  { \
    ACE_DEBUG (msg); \
  }

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
  try
  {
    if (this->parse_args (argc, argv) == -1)
      return -1;

    // Get a reference to the <RootPOA>
    VERBOSE_MSG ((LM_DEBUG, 
                  "*** debug: resolving initial reference to RootPOA\n"));
    CORBA::Object_var obj = this->orb_->resolve_initial_references ("RootPOA");
    PortableServer::POA_var root_poa = PortableServer::POA::_narrow (obj.in ());

    try
    {
      // Activate the RootPOA's manager.
      VERBOSE_MSG ((LM_DEBUG, 
                    "*** debug: getting reference to POAManager\n"));
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
                    "*** error : failed to register with IOR table\n"));
      }

      // Spawn the server's service thread.
      int grp_id =
        ACE_Thread_Manager::instance ()->spawn (
          CUTS_Testing_App_Server::svc_run,
          this);

      if (grp_id == -1)
      {
        ACE_ERROR ((LM_ERROR, 
                    "*** error: failed to start test manger server\n"));
      }
      
      // Pass control to the base class. This method does not return until
      // the testing application is shutdown.
      this->run_main_i ();
   
      // Wait for the thread to exit.
      if (grp_id != -1)
        ACE_Thread_Manager::instance ()->wait_grp (grp_id);
    }
    catch (const CORBA::Exception & ex)
    {
      ACE_ERROR ((LM_ERROR, 
                  "*** error: %s\n", 
                  ex._info ().c_str ()));
    }
    catch (...)
    {
      ACE_ERROR ((LM_ERROR, 
                  "*** error: caught unknown exception\n"));
    }

    // Destroy the RootPOA.
    VERBOSE_MSG ((LM_DEBUG,
                  "*** debug: destroying the RootPOA\n"));
    root_poa->destroy (true, true);

    // Destroy the ORB.
    VERBOSE_MSG ((LM_DEBUG,
                  "*** debug: destroying the ORB\n"));
    this->orb_->destroy ();

  }
  catch (const CORBA::Exception & ex)
  {
    ACE_ERROR ((LM_ERROR,
                "*** error: %s\n",
                ex._info ().c_str ()));
  }
  catch (...)
  {
    ACE_ERROR ((LM_ERROR,
                "*** error: caught unknown exception\n"));
  }

  return -1;
}

//
// parse_args
//
int CUTS_Testing_App_Server::parse_args (int argc, char * argv [])
{
  this->orb_ = CORBA::ORB_init (argc, argv);
  return CUTS_Testing_App::parse_args (argc, argv);
}

//
// svc_run
//
ACE_THR_FUNC_RETURN CUTS_Testing_App_Server::svc_run (void * param)
{
  // Get the server from the thread's parameter.
  CUTS_Testing_App_Server * server = 
    reinterpret_cast <CUTS_Testing_App_Server *> (param);

  // Run the ORB's main event loop.
  server->orb_->run ();
  return 0;
}

//
// shutdown
//
int CUTS_Testing_App_Server::shutdown (void)
{
  try
  {
    // First, pass control to the base class.
    CUTS_Testing_App::shutdown ();

    // Stop the main event loop for the ORB.
    VERBOSE_MSG ((LM_DEBUG,
                  "*** debug: shutting down the ORB\n"));

    this->orb_->shutdown (true);
  }
  catch (const CORBA::Exception & ex)
  {
    ACE_ERROR ((LM_ERROR, 
                "*** error: %s\n", 
                ex._info ().c_str ()));
  }
  catch (...)
  {
    ACE_ERROR ((LM_ERROR, "*** error: caught unknown exception\n"));
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
                         "*** error : failed to resolve IOR table\n"),
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
                "*** info: registering test manager with the IOR table [%s]\n",
                manager_name.c_str ()));

    ior_table->bind (name_str.in (), obj_str.in ());
    return 0;
  }
  catch (const CORBA::Exception & ex)
  {
    ACE_ERROR ((LM_ERROR,
                "*** error: %s\n",
                ex._info ().c_str ()));
  }

  return -1;
}


