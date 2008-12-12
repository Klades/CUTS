// $Id$

#include "Logging_Server.h"

#if !defined (__CUTS_INLINE__)
#include "Logging_Server.inl"
#endif

#include "TestLoggerServer_i.h"
#include "Logging_Server_File.h"
#include "cuts/UUID.h"
#include "tao/IORTable/IORTable.h"
#include "ace/Get_Opt.h"
#include "ace/streams.h"
#include "XSCRT/utils/Console_Error_Handler.h"
#include "boost/bind.hpp"
#include <sstream>
#include <algorithm>

static const char * __HELP__ =
"Logging server daemon for collecting log messages\n"
"\n"
"Options:\n"
"  --clients=FILE        file containing logging client addresses\n"
"  --thread-count=N      size of the server's thread pool for receiving\n"
"                        log messages from client applications (default N=1)\n"
"\n"
"  -h, --help            print this help message\n"
"  -v, --verbose         print verbose infomration\n"
"  --debug               print debugging information\n"
"  --trace               print tracing information\n";

//
// CUTS_Test_Logging_Server
//
CUTS_Test_Logging_Server::CUTS_Test_Logging_Server (void)
: task_ (*this)
{
  this->uuid_ <<= ACE_Utils::UUID::NIL_UUID;
}

//
// CUTS_Test_Logging_Server
//
CUTS_Test_Logging_Server::CUTS_Test_Logging_Server (CORBA::ORB_ptr orb)
: task_ (*this),
  orb_ (CORBA::ORB::_duplicate (orb))
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

    // Get a reference to the <RootPOA>
    ACE_DEBUG ((LM_DEBUG,
                "%T (%t) - %M - resolving initial reference to RootPOA\n"));

    CORBA::Object_var obj = this->orb_->resolve_initial_references ("RootPOA");
    this->root_poa_ = PortableServer::POA::_narrow (obj.in ());

    // Activate the RootPOA's manager.
    ACE_DEBUG ((LM_DEBUG,
                "%T (%t) - %M - getting reference to POAManager\n"));
    PortableServer::POAManager_var poa_mgr = this->root_poa_->the_POAManager ();
    poa_mgr->activate ();

    // Activate the servant.
    PortableServer::ObjectId_var id =
      this->root_poa_->activate_object (&this->server_);

    // Convert the object id into a string.
    obj = this->root_poa_->id_to_reference (id.in ());
    CORBA::String_var objstr = this->orb_->object_to_string (obj.in ());

    // Activate the task, and wait for all threads to exit.
    ACE_DEBUG ((LM_DEBUG,
                "%T (%t) - %M - activating server task\n"));
    this->task_.activate (this->opts_.thread_count_);

    // Register the server with the logging clients.
    //if (!this->opts_.clients_file_.empty ())
    //  this->register_with_clients ();

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
  else
    ACE_DEBUG ((LM_DEBUG, "ORB already initialized\n"));

  const char * optstr = "hv";
  ACE_Get_Opt get_opt (argc, argv, optstr);

  get_opt.long_option ("clients", ACE_Get_Opt::ARG_REQUIRED);
  get_opt.long_option ("thread-count", ACE_Get_Opt::ARG_REQUIRED);

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
      return;

    CUTS::TestLoggerServer_var server =
      CUTS::TestLoggerServer::_narrow (obj.in ());

    if (::CORBA::is_nil (server.in ()))
      return;

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
      return;

    // Extract the logger client from the object.
    CUTS::TestLoggerClient_var client =
      CUTS::TestLoggerClient::_narrow (obj.in ());

    // Make sure the client exist.
    if (::CORBA::is_nil (client.in ()))
      return;

    // Register the server w/ the logging client.
    ACE_DEBUG ((LM_DEBUG,
                "%T (%t) - %M - registering server with client %s\n",
                str.c_str ()));

    client->register_server (this->uuid_, server);

    if (this->clients_.insert (client.in ()) == 0)
    {
      client._retn ();
    }
    else
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
    // Get a reference to the server servant.
    CORBA::Object_var obj =
      this->root_poa_->servant_to_reference (&this->server_);

    if (::CORBA::is_nil (obj.in ()))
      return;

    CUTS::TestLoggerServer_var server =
      CUTS::TestLoggerServer::_narrow (obj.in ());

    if (::CORBA::is_nil (server.in ()))
      return;

    ACE_DEBUG ((LM_DEBUG,
                "%T (%t) - %M - unregistering server with clients\n"));

    clients_set_type::ITERATOR iter (this->clients_);

    for ( ; !iter.done (); ++ iter)
    {
      // Unregister the server with the client.
      (*iter)->unregister_server (this->uuid_, server.in ());

      // Release this reference to the object.
      CORBA::release (*iter);
    }

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
