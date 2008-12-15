// $Id$

#include "Logging_Server.h"

#if !defined (__CUTS_INLINE__)
#include "Logging_Server.inl"
#endif

#include "TestLoggerServer_i.h"
#include "Logging_Server_File.h"
#include "cuts/UUID.h"
#include "cuts/utils/logging/server/callbacks/testing/Test_Logging_Callback.h"
#include "tao/IORTable/IORTable.h"
#include "ace/Get_Opt.h"
#include "ace/Env_Value_T.h"
#include "ace/streams.h"
#include "XSCRT/utils/Console_Error_Handler.h"
#include "boost/bind.hpp"
#include <sstream>
#include <algorithm>

static const char * __HELP__ =
"Logging server daemon for collecting log messages\n"
"\n"
"General options:\n"
"  --clients=FILE        register server with clients in FILE\n"
"  --thread-count=N      execute N threads in server (default: N=1)\n"
"  --uuid=UUID           associate log message with test UUID\n"
"\n"
"Printing options:\n"
"  -h, --help            print this help message\n"
"  -v, --verbose         print verbose infomration\n"
"  --debug               print debugging information\n"
"  --trace               print tracing information\n";

//
// CUTS_Test_Logging_Server
//
CUTS_Test_Logging_Server::CUTS_Test_Logging_Server (void)
{
  this->uuid_ <<= ACE_Utils::UUID::NIL_UUID;
}

//
// CUTS_Test_Logging_Server
//
CUTS_Test_Logging_Server::CUTS_Test_Logging_Server (CORBA::ORB_ptr orb)
: orb_ (::CORBA::ORB::_duplicate (orb))
{
  this->uuid_ <<= ACE_Utils::UUID::NIL_UUID;
}

//
// run_main
//
int CUTS_Test_Logging_Server::run_main (int argc, char * argv [])
{
  // Spawn a new instance of the server.
  int retval = this->spawn_main (argc, argv);

  if (retval == 0)
  {
    // Wait for the server to exit.
    ACE_DEBUG ((LM_DEBUG,
                "%T (%t) - %M - waiting for logging server to exit\n"));

    this->task_.wait ();
  }

  return retval;
}

//
// spawn_main
//
int CUTS_Test_Logging_Server::spawn_main (int argc, char * argv [])
{
  try
  {
    // Parse the command-line arguments.
    if (this->parse_args (argc, argv) == -1)
      return -1;

    if (this->init_test_database () != 0)
    {
      ACE_ERROR ((LM_ERROR,
                  "%T (%t) - %M - failed to initialize test database\n"));
    }

    // Get a reference to the <RootPOA>
    ACE_DEBUG ((LM_DEBUG,
                "%T (%t) - %M - resolving initial reference to RootPOA\n"));

    CORBA::Object_var obj = this->orb_->resolve_initial_references ("RootPOA");
    this->root_poa_ = PortableServer::POA::_narrow (obj.in ());

    // Activate the RootPOA's manager.
    ACE_DEBUG ((LM_DEBUG,
                "%T (%t) - %M - getting reference to POAManager\n"));
    PortableServer::POAManager_var mgr = this->root_poa_->the_POAManager ();
    mgr->activate ();

    // Activate the servant.
    PortableServer::ObjectId_var id =
      this->root_poa_->activate_object (&this->server_);

    // Activate the server's task.
    ACE_DEBUG ((LM_DEBUG,
                "%T (%t) - %M - activating server task\n"));
    this->task_.reset (this->orb_.in ());

    int flags = THR_NEW_LWP | THR_JOINABLE | THR_INHERIT_SCHED;
    if (this->task_.activate (flags, this->opts_.thread_count_) == -1)
    {
      ACE_ERROR_RETURN ((LM_ERROR,
                         "%T (%t) - %M - failed to activate server task\n"),
                         -1);
    }

    // Register the server with the logging clients.
    if (!this->opts_.clients_file_.empty ())
      this->register_with_clients ();

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
// parse_args
//
int CUTS_Test_Logging_Server::parse_args (int argc, char * argv[])
{
  // Initailize the ORB.
  if (::CORBA::is_nil (this->orb_.in ()))
    this->orb_ = ::CORBA::ORB_init (argc, argv, "cuts.logging.server");

  const char * optstr = "hv";
  ACE_Get_Opt get_opt (argc, argv, optstr);

  get_opt.long_option ("clients", ACE_Get_Opt::ARG_REQUIRED);
  get_opt.long_option ("thread-count", ACE_Get_Opt::ARG_REQUIRED);
  get_opt.long_option ("uuid", ACE_Get_Opt::ARG_REQUIRED);

  get_opt.long_option ("debug", ACE_Get_Opt::NO_ARG);
  get_opt.long_option ("verbose", 'v', ACE_Get_Opt::NO_ARG);
  get_opt.long_option ("help", 'h', ACE_Get_Opt::NO_ARG);

  char ch;

  while ((ch = get_opt ()) != EOF)
  {
    switch (ch)
    {
    case 0:
      if (ACE_OS::strcmp ("verbose", get_opt.long_option ()) == 0)
      {
        u_long mask =
          ACE_Log_Msg::instance ()->priority_mask (ACE_Log_Msg::PROCESS);

        mask |= LM_INFO;

        ACE_Log_Msg::instance ()->priority_mask (mask, ACE_Log_Msg::PROCESS);
      }
      else if (ACE_OS::strcmp ("debug", get_opt.long_option ()) == 0)
      {
        u_long mask =
          ACE_Log_Msg::instance ()->priority_mask (ACE_Log_Msg::PROCESS);

        mask |= LM_DEBUG;

        ACE_Log_Msg::instance ()->priority_mask (mask, ACE_Log_Msg::PROCESS);
      }
      else if (ACE_OS::strcmp ("uuid", get_opt.long_option ()) == 0)
      {
        ACE_Utils::UUID uuid (get_opt.opt_arg ());
        this->uuid_ <<= uuid;
      }
      else if (ACE_OS::strcmp ("help", get_opt.long_option ()) == 0)
      {
        this->print_help ();
      }
      else if (ACE_OS::strcmp ("thread-count", get_opt.long_option ()) == 0)
      {
        std::istringstream istr (get_opt.opt_arg ());
        istr >> this->opts_.thread_count_;
      }
      else if (ACE_OS::strcmp ("clients", get_opt.long_option ()) == 0)
      {
        this->opts_.clients_file_ = get_opt.opt_arg ();
      }

      break;

    case 'v':
      {
        u_long mask =
          ACE_Log_Msg::instance ()->priority_mask (ACE_Log_Msg::PROCESS);

        mask |= LM_INFO;

        ACE_Log_Msg::instance ()->priority_mask (mask, ACE_Log_Msg::PROCESS);
      }
      break;

    case 'h':
      this->print_help ();
      break;
    }
  }

  return 0;
}

//
// shutdown
//
void CUTS_Test_Logging_Server::shutdown (void)
{
  try
  {
    // Shutdown the ORB.
    ACE_DEBUG ((LM_DEBUG,
                "%T (%t) - %M - shutting down the ORB\n"));

    this->unregister_with_clients ();

    if (!::CORBA::is_nil (this->orb_.in ()))
      this->orb_->shutdown (1);

    // Destroy the RootPOA.
    ACE_DEBUG ((LM_DEBUG,
                "%T (%t) - %M - destorying the RootPOA\n"));

    if (!CORBA::is_nil (this->root_poa_.in ()))
      this->root_poa_->destroy (1, 1);

    // Destroy the ORB.
    ACE_DEBUG ((LM_DEBUG,
                "%T (%t) - %M - destorying the ORB\n"));
    if (!CORBA::is_nil (this->orb_.in ()))
      this->orb_->destroy ();
  }
  catch (const CORBA::Exception & ex)
  {
    ACE_ERROR ((LM_ERROR,
                "%T (%t) - %M - %s\n",
                ex._info ().c_str ()));
  }
}

//
// print_help
//
void CUTS_Test_Logging_Server::print_help (void)
{
  std::cout << __HELP__ << std::endl;
  ACE_OS::exit (0);
}

//
// register_with_client
//
void CUTS_Test_Logging_Server::register_with_clients (void)
{
  CUTS_Logging_Server_File reader;

  // Set the error handler for the console.
  reader.parser ()->setErrorHandler (new XSCRT::utils::Console_Error_Handler ());

  ACE_DEBUG ((LM_DEBUG,
              "%T (%t) - %M - loading configuration file %s\n",
              this->opts_.clients_file_.c_str ()));

  // Load the client file into memory.
  if (reader.read (this->opts_.clients_file_.c_str ()))
  {
    // Transform the file contents into an object.
    CUTS::loggingClients clients;
    reader >>= clients;

    // Get a reference to the server servant.
    CORBA::Object_var obj =
      this->root_poa_->servant_to_reference (&this->server_);

    if (::CORBA::is_nil (obj.in ()))
    {
      ACE_ERROR ((LM_ERROR,
                  "%T (%t) - %M - server reference is NIL\n"));
      return;
    }

    CUTS::TestLoggerServer_var server =
      CUTS::TestLoggerServer::_narrow (obj.in ());

    if (!::CORBA::is_nil (server.in ()))
    {
      // Load each of the clients.
      std::for_each (clients.begin_client (),
                     clients.end_client (),
                     boost::bind (&CUTS_Test_Logging_Server::register_with_client,
                                  this,
                                  _1,
                                  server.in ()));
    }
    else
    {
      ACE_ERROR ((LM_ERROR,
                  "%T - %M - reference is not a logging server\n"));
    }
  }
  else
  {
    ACE_ERROR ((LM_ERROR,
                "%T (%t) - %M - failed to read configration file %s\n",
                this->opts_.clients_file_.c_str ()));
  }
}

//
// register_with_client
//
void CUTS_Test_Logging_Server::
register_with_client (const std::string & str,
                      CUTS::TestLoggerServer_ptr server)
{
  try
  {
    // Resolve the logger's client reference.
    ::CORBA::Object_var obj = this->orb_->string_to_object (str.c_str ());

    if (::CORBA::is_nil (obj.in ()))
    {
      ACE_ERROR ((LM_ERROR,
                  "%T (%t) - %M - failed to locate object in "
                  "naming service\n"));
      return;
    }

    // Extract the logger client from the object.
    CUTS::TestLoggerClient_var client =
      CUTS::TestLoggerClient::_narrow (obj.in ());

    // Make sure the client exist.
    if (::CORBA::is_nil (client.in ()))
    {
      ACE_ERROR ((LM_ERROR,
                  "%T (%t) - %M - reference is not a "
                  "CUTS::TestLoggerClient [%s]\n",
                  obj->_repository_id ()));
      return;
    }

    // Register the server w/ the logging client.
    ACE_DEBUG ((LM_INFO,
                "%T (%t) - %M - registering server with client %s\n",
                str.c_str ()));

    client->register_server (this->uuid_, server);

    if (this->clients_.insert (client) == -1)
    {
      ACE_ERROR ((LM_WARNING,
                  "%T (%t) - %M - failed to cache logging client [%s]\n",
                  str.c_str ()));
    }
  }
  catch (const CORBA::Exception & ex)
  {
    ACE_ERROR ((LM_ERROR,
                "%T (%t) - %M - %s\n",
                ex._info ().c_str ()));
  }
}

//
// uuid
//
void CUTS_Test_Logging_Server::uuid (const ACE_Utils::UUID & uuid)
{
  this->uuid_ <<= uuid;
}

//
// unregister_with_clients
//
void CUTS_Test_Logging_Server::unregister_with_clients (void)
{
  try
  {
    ACE_DEBUG ((LM_DEBUG,
                "%T (%t) - %M - unregistering server with clients\n"));

    clients_set_type::ITERATOR iter (this->clients_);

    for ( ; !iter.done (); ++ iter)
      (*iter)->unregister_server (this->uuid_);

    // Reset the set.
    this->clients_.reset ();
  }
  catch (const CORBA::Exception & ex)
  {
    ACE_ERROR ((LM_ERROR,
                "%T (%t) - %M - %s\n",
                ex._info ().c_str ()));
  }
}

//
// init_test_database
//
int CUTS_Test_Logging_Server::init_test_database (void)
{
  // This is temporary hack until we figure out how to resolve
  // the BUGS in TAO for loading servants in shared libraries.
  ACE_Utils::UUID uuid;
  this->uuid_ >>= uuid;

  ACE_Env_Value <char *> CUTS_ROOT ("CUTS_ROOT", "");
  std::ostringstream ostr;
  ostr << CUTS_ROOT << "/etc/tests/"
       << uuid.to_string ()->c_str () << ".cdb";

  if (!this->db_.create (ostr.str ().c_str (), uuid))
    return -1;

  CUTS_Test_Logging_Callback * callback = 0;

  ACE_NEW_THROW_EX (callback,
                    CUTS_Test_Logging_Callback (this->db_),
                    CORBA::NO_MEMORY ());

  ACE_Auto_Ptr <CUTS_Test_Logging_Callback> auto_clean (callback);

  if (callback->init () == -1)
    return -1;

  this->install_callback (callback);
  auto_clean.release ();

  return 0;
}
