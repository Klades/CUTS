// $Id$

#include "Logging_Server.h"

#if !defined (__CUTS_INLINE__)
#include "Logging_Server.inl"
#endif

#include "LoggingServer_i.h"
#include "cuts/ORB_Server_Task.h"
#include "cuts/UUID.h"
#include "ace/Get_Opt.h"
#include "ace/streams.h"
//#include "ace/OS_NS_unistd.h"
#include <sstream>

static const char * __HELP__ =
"Logging server daemon for collecting log messages\n"
"\n"
"General options:\n"
"  --thread-count=N                 execute N threads in server (default: N=1)\n"
"\n"
"  -o, --iorfile=FILE               write server IOR to FILE\n"
"  --register-with-iortable=NAME    register server with IORTable using NAME\n"
"\n"
"Printing options:\n"
"  -h, --help                       print this help message\n"
"  -v, --verbose                    print verbose infomration\n"
"  --debug                          print debugging information\n"
"  --trace                          print tracing information\n";

//
// run_main
//
int CUTS_Logging_Server::run_main (int argc, char * argv [])
{
  try
  {
    // Parse the command-line arguments.
    if (-1 == this->parse_args (argc, argv))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to parse command-line arguments\n")),
                         -1);

    ACE_DEBUG ((LM_DEBUG,
                ACE_TEXT ("%T (%t) - %M - resolving RootPOA\n")));

    ::CORBA::Object_var obj = this->orb_->resolve_initial_references ("RootPOA");
    this->root_poa_ = ::PortableServer::POA::_narrow (obj.in ());

    // Activate the RootPOA's manager.
    ::PortableServer::POAManager_var mgr = this->root_poa_->the_POAManager ();
    mgr->activate ();

    // Construct the policy list for the LoggingServerPOA.
    CORBA::PolicyList policies (6);
    policies.length (6);

    policies[0] = this->root_poa_->create_thread_policy (PortableServer::ORB_CTRL_MODEL);
    policies[1] = this->root_poa_->create_servant_retention_policy (PortableServer::RETAIN);
    policies[2] = this->root_poa_->create_id_assignment_policy (PortableServer::SYSTEM_ID);
    policies[3] = this->root_poa_->create_id_uniqueness_policy (PortableServer::UNIQUE_ID);
    policies[4] = this->root_poa_->create_lifespan_policy (PortableServer::TRANSIENT);
    policies[5] = this->root_poa_->create_request_processing_policy (PortableServer::USE_ACTIVE_OBJECT_MAP_ONLY);

    // Create the child POA for the test logger factory servants.
    ::PortableServer::POA_var child_poa =
      this->root_poa_->create_POA ("LoggingServerPOA",
                                   ::PortableServer::POAManager::_nil (),
                                   policies);

    // Destroy the POA policies
    for (::CORBA::ULong i = 0; i < policies.length (); ++ i)
      policies[i]->destroy ();

    mgr = child_poa->the_POAManager ();
    mgr->activate ();

    // Activate the servant.
    ACE_DEBUG ((LM_DEBUG,
                ACE_TEXT ("%T (%t) - %M - activating logger server servant\n")));

    this->servant_mgr_.activate (child_poa.in ());

    // Activate the server's task.
    CUTS_ORB_Server_Task task (this->orb_.in ());

    int flags = THR_NEW_LWP | THR_JOINABLE | THR_INHERIT_SCHED;
    if (task.activate (flags, this->opts_.thread_count_) == -1)
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to activate server task\n")),
                         -1);

    // Wait for the task to complete.
    ACE_DEBUG ((LM_DEBUG,
                ACE_TEXT ("%T (%t) - %M - waiting for ORB to shutdown\n")));

    task.wait ();

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
int CUTS_Logging_Server::parse_args (int argc, char * argv[])
{
  // Initailize the ORB.
  this->orb_ = ::CORBA::ORB_init (argc, argv, "cuts.logging.server");

  const char * optstr = "hvo:";
  ACE_Get_Opt get_opt (argc, argv, optstr);

  get_opt.long_option ("thread-count", ACE_Get_Opt::ARG_REQUIRED);

  get_opt.long_option ("iorfile", 'o', ACE_Get_Opt::ARG_REQUIRED);
  get_opt.long_option ("register-with-iortable", ACE_Get_Opt::ARG_REQUIRED);

  get_opt.long_option ("debug", ACE_Get_Opt::NO_ARG);
  get_opt.long_option ("verbose", 'v', ACE_Get_Opt::NO_ARG);
  get_opt.long_option ("help", 'h', ACE_Get_Opt::NO_ARG);

  char ch;

  while ((ch = get_opt ()) != EOF)
  {
    ACE_DEBUG ((LM_DEBUG,
                "%c\n",
                ch));

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
      else if (ACE_OS::strcmp ("iorfile", get_opt.long_option ()) == 0)
      {
        this->servant_mgr_.set_trait_value (CUTS_IOR_File_Trait (), get_opt.opt_arg ());
      }
      else if (0 == ACE_OS::strcmp ("register-with-iortable", get_opt.long_option ()))
      {
        this->servant_mgr_.set_trait_value (CUTS_IOR_Table_Trait (), get_opt.opt_arg ());
      }

      break;

    case 'o':
      this->servant_mgr_.set_trait_value (CUTS_IOR_File_Trait (), get_opt.opt_arg ());
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
void CUTS_Logging_Server::shutdown (void)
{
  try
  {
    this->servant_mgr_.deactivate ();

    if (!::CORBA::is_nil (this->orb_.in ()))
      this->orb_->shutdown ();
  }
  catch (const ::CORBA::Exception & ex)
  {
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - %s\n"),
                ex._info ().c_str ()));
  }
  catch (...)
  {
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - caught unknown exception in shutdown ()\n")));
  }
}

//
// destroy
//
void CUTS_Logging_Server::destroy (void)
{
  try
  {
    // Destroy the RootPOA.
    ACE_DEBUG ((LM_DEBUG,
                ACE_TEXT ("%T (%t) - %M - destorying the RootPOA\n")));

    if (!::CORBA::is_nil (this->root_poa_.in ()))
      this->root_poa_->destroy (1, 1);

    // Destroy the ORB.
    ACE_DEBUG ((LM_DEBUG,
                ACE_TEXT ("%T (%t) - %M - destorying the ORB\n")));

    if (!::CORBA::is_nil (this->orb_.in ()))
      this->orb_->destroy ();
  }
  catch (...)
  {
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - caught unknown exception in destroy ()\n")));
  }
}

//
// print_help
//
void CUTS_Logging_Server::print_help (void)
{
  std::cout << __HELP__ << std::endl;
  ACE_OS::exit (1);
}