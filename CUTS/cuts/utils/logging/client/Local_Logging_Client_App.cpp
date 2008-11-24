// $Id$

#include "Local_Logging_Client_App.h"
#include "tao/IORTable/IORTable.h"
#include "ace/ARGV.h"
#include "ace/Argv_Type_Converter.h"
#include <sstream>

//
// CUTS_Local_Logging_Client_App
//
CUTS_Local_Logging_Client_App::
CUTS_Local_Logging_Client_App (const CUTS_TestLoggerClient_i & client)
: client_ (client)
{
  CUTS_TEST_LOGGING_CLIENT_TRACE ("CUTS_Local_Logging_Client_App::CUTS_Local_Logging_Client_App (void)");
}

//
// CUTS_Local_Logging_Client_App
//
CUTS_Local_Logging_Client_App::~CUTS_Local_Logging_Client_App (void)
{
  CUTS_TEST_LOGGING_CLIENT_TRACE ("CUTS_Local_Logging_Client_App::~CUTS_Local_Logging_Client_App (void)");
}

//
// run_main
//
int CUTS_Local_Logging_Client_App::run_main (u_short port, size_t threads)
{
  CUTS_TEST_LOGGING_CLIENT_TRACE ("CUTS_Local_Logging_Client_App::run_main (u_short, size_t)");

  try
  {
    // Construct the command-line parameters for this ORB.
    ACE_ARGV_T <char> args_list;
    args_list.add ("client");

    // Added the endpoint argument to the command-line.
    std::ostringstream endpoint;
    endpoint << "-ORBEndpoint iiop://localhost:" << port;

    ACE_ARGV_T <char> endpoint_arg (endpoint.str ().c_str ());
    args_list.add (endpoint_arg.argv ());

    // Let's not corrupt the original command-line.
    int argc = args_list.argc ();
    ACE_Argv_Type_Converter command_line (argc, args_list.argv ());

    // Initialize this ORB.
    this->orb_ = CORBA::ORB_init (command_line.get_argc (),
                                  command_line.get_ASCII_argv (),
                                  "cuts.logging.client.local");

    // Get a reference to the RootPOA.
    ACE_DEBUG ((LM_DEBUG,
                "%T (%t) - %M - resolving initial reference to RootPOA\n"));

    CORBA::Object_var obj = this->orb_->resolve_initial_references ("RootPOA");
    this->root_poa_ = PortableServer::POA::_narrow (obj.in ());

    // Activate the RootPOA's manager.
    ACE_DEBUG ((LM_DEBUG,
                "%T (%t) - %M - getting reference to POAManager\n"));
    PortableServer::POAManager_var mgr = this->root_poa_->the_POAManager ();
    mgr->activate ();

    // Allocate an instance of the local logger client.
    CUTS_LocalTestLoggerClient_i * servant = 0;

    ACE_NEW_THROW_EX (servant,
                      CUTS_LocalTestLoggerClient_i (this->client_),
                      CORBA::NO_MEMORY ());

    this->servant_.reset (servant);

    // Register the client with the IORTable
    if (this->register_with_iortable () == -1)
    {
      ACE_ERROR ((LM_ERROR,
                  "%T (%t) - %M - failed to register with IORTable\n"));
    }

    // Allocate a new task for the application.
    CUTS_Logging_Client_Task * task = 0;

    ACE_NEW_THROW_EX (task,
                      CUTS_Logging_Client_Task (this->orb_.in ()),
                      CORBA::NO_MEMORY ());

    this->task_.reset (task);

    // Activate the task.
    int flags = THR_NEW_LWP | THR_JOINABLE | THR_INHERIT_SCHED;
    return this->task_->activate (flags, threads);
  }
  catch (const CORBA::Exception & ex)
  {
    ACE_ERROR ((LM_ERROR,
                "%T (%t) - %M - %s\n",
                ex._info ().c_str ()));
  }

  return -1;
}

//
// shutdown
//
void CUTS_Local_Logging_Client_App::shutdown (void)
{
  CUTS_TEST_LOGGING_CLIENT_TRACE ("CUTS_Local_Logging_Client_App::shutdown (void)");

  try
  {
    this->orb_->shutdown (true);
  }
  catch (const CORBA::Exception & ex)
  {
    ACE_ERROR ((LM_ERROR,
                "%T (%t) - %M - %s\n",
                ex._info ().c_str ()));
  }
}

//
// destroy
//
int CUTS_Local_Logging_Client_App::destroy (void)
{
  CUTS_TEST_LOGGING_CLIENT_TRACE ("CUTS_Local_Logging_Client_App::destroy (void)");

  try
  {
    // Wait for all the threads to return.
    this->task_->wait ();

    // Destroy the RootPOA
    this->root_poa_->destroy (1, 1);

    // Destroy the ORB.
    this->orb_->destroy ();
    return 0;
  }
  catch (const CORBA::Exception & ex)
  {
    ACE_ERROR ((LM_ERROR,
                "%T (%t) - %M - %s\n",
                ex._info ().c_str ()));
  }

  return -1;
}

//
// register_with_iortable
//
int CUTS_Local_Logging_Client_App::register_with_iortable (void)
{
  CUTS_TEST_LOGGING_CLIENT_TRACE ("CUTS_Local_Logging_Client_App::register_with_iortable (void)");

  try
  {
    // Locate the IORTable for the application.
    CORBA::Object_var obj = this->orb_->resolve_initial_references ("IORTable");
    IORTable::Table_var ior_table = IORTable::Table::_narrow (obj.in ());

    if (::CORBA::is_nil (ior_table.in ()))
    {
      ACE_ERROR_RETURN ((LM_ERROR,
                         "%T (%t) - %M - failed to resolve IOR table\n"),
                         -1);
    }

    // Get the IOR string for the test manager.
    obj = this->root_poa_->servant_to_reference (this->servant_.get ());
    CORBA::String_var obj_str  = this->orb_->object_to_string (obj.in ());

    // Bind the object to the IOR table.
    ACE_DEBUG ((LM_DEBUG,
                "%T (%t) - %M - registering test logger client with localhost\n"));

    ior_table->bind ("CUTS/LocalTestLoggerClient", obj_str.in ());

    return 0;
  }
  catch (const CORBA::Exception & ex)
  {
    ACE_ERROR ((LM_ERROR,
                "%T (%t) - %M - %s\n",
                ex._info ().c_str ()));
  }

  return -1;
}
