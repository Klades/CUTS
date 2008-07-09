// $Id$

#include "Testing_App_Server.h"
#include "Testing_App.h"
#include "tao/IORTable/IORTable.h"
#include "ace/Thread_Manager.h"

//
// CUTS_Testing_App_Server
//
CUTS_Testing_App_Server::CUTS_Testing_App_Server (CUTS_Testing_App & parent)
: parent_ (parent),
  thr_grp_id_ (-1)
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
  // Initialize the CORBA ORB.
  try
  {
    this->orb_ = CORBA::ORB_init (argc, argv);

    // Get a reference to the <RootPOA>
    ACE_DEBUG ((LM_DEBUG, "resolving initial reference to RootPOA\n"));
    CORBA::Object_var obj = this->orb_->resolve_initial_references ("RootPOA");
    this->root_poa_ = PortableServer::POA::_narrow (obj.in ());

    // Activate the RootPOA's manager.
    ACE_DEBUG ((LM_DEBUG, "getting reference to POAManager\n"));
    PortableServer::POAManager_var mgr = this->root_poa_->the_POAManager ();
    mgr->activate ();

    // Create a new test manager.
    CUTS_TestManager_i * test_manager = 0;

    ACE_NEW_THROW_EX (test_manager, 
                      CUTS_TestManager_i (this->parent_), 
                      CORBA::NO_MEMORY ());

    this->test_manager_.reset (test_manager);

    // Activate the manager and transfer ownership.
    CUTS::TestManager_var manager = this->test_manager_->_this ();
    this->servant_ = this->test_manager_.get ();

    // Register the test manager with the IORTable for the ORB.
    if (this->register_with_iortable () == -1)
    {
      ACE_ERROR ((LM_ERROR,
                  "*** error : failed to register with IOR table\n"));
    }

    // Spawn the server's service thread.
    this->thr_grp_id_ =
      ACE_Thread_Manager::instance ()->spawn (CUTS_Testing_App_Server::svc_run,
                                              this);

    if (this->thr_grp_id_ == -1)
    {
      ACE_ERROR ((LM_ERROR, 
                  "*** error: failed to start test manger server\n"));
    }
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

  return this->thr_grp_id_ != -1 ? 0 : -1;
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
    // Stop the main event loop for the ORB.
    this->orb_->shutdown (true);

    if (this->thr_grp_id_ != -1)
      ACE_Thread_Manager::instance ()->wait_grp (this->thr_grp_id_);

    // Destroy the RootPOA.
    ACE_DEBUG ((LM_DEBUG, "destroying the RootPOA\n"));
    this->root_poa_->destroy (true, true);

    // Destroy the ORB.
    ACE_DEBUG ((LM_DEBUG, "**destroying the ORB\n"));
    this->orb_->destroy ();
    return 0;
  }
  catch (const CORBA::Exception & ex)
  {
    ACE_ERROR ((LM_ERROR, "*** error: %s\n", ex._info ().c_str ()));
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
    manager_name += this->parent_.name ();

    // Get the IOR string for the test manager.
    CUTS::TestManager_var test_mgr = this->test_manager_->_this ();
    CORBA::String_var obj_str  = this->orb_->object_to_string (test_mgr.in ());
    CORBA::String_var name_str = CORBA::string_dup (manager_name.c_str ());

    // Bind the object to the IOR table.
    ACE_DEBUG ((LM_DEBUG, 
                "registering test manager with the IOR table [%s]\n",
                manager_name.c_str ()));
    ior_table->bind (name_str.in (), obj_str.in ());
    return 0;
  }
  catch (const CORBA::Exception & ex)
  {
    ACE_ERROR ((LM_ERROR,
                "%s\n",
                ex._info ().c_str ()));
  }

  return -1;
}


