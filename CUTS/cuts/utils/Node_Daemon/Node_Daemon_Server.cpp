// $Id$

#include "Node_Daemon_Server.h"
#include "cutsnode.h"

#include "tao/IORTable/IORTable.h"

#include "ace/Get_Opt.h"
#include "ace/OS_NS_unistd.h"
#include "ace/streams.h"
#include "ace/Env_Value_T.h"

#include "XSC/utils/XML_Schema_Resolver.h"
#include "XSC/utils/XML_Error_Handler.h"
#include "XSCRT/utils/File_Reader_T.h"

static const char * __HELP__ =
"CUTS node manager for remotely invoking task on target \n"
"\n"
"USAGE: cutsnode_d [OPTIONS]\n"
"\n"
"Options:\n"
"  -d, --working-directory=DIR        working directory for the daemon\n"
"  -c, --config=FILE                  initial configuration file\n"
"  -o, --ior-file=NAME                output file for IOR\n"
"\n"
"  -DNAME=VALUE                      define property NAME=VALUE\n"
"\n"
"  -v, --verbose                      print verbose infomration\n"
"  --debug                            print debugging information\n"
"  -h, --help                         print this help message\n";

//
// CUTS_Node_Daemon_Server
//
CUTS_Node_Daemon_Server::CUTS_Node_Daemon_Server (void)
: daemon_ (0)
{

}

//
// ~CUTS_Node_Daemon_Server
//
CUTS_Node_Daemon_Server::~CUTS_Node_Daemon_Server (void)
{

}

//
// run
//
int CUTS_Node_Daemon_Server::run_main (int argc, char * argv [])
{
  try
  {
    // Initialize the ORB
    this->orb_ = ::CORBA::ORB_init (argc, argv);

    // Parse the remaining arguments.
    if (this->parse_args (argc, argv) == -1)
      return 1;

    // Get a reference to the RootPOA.
    ACE_DEBUG ((LM_DEBUG,
                "%T - %M - resolving initial reference to RootPOA\n"));

    CORBA::Object_var obj = this->orb_->resolve_initial_references ("RootPOA");
    PortableServer::POA_var poa = PortableServer::POA::_narrow (obj.in ());

    // Activate the POAManager
    ACE_DEBUG ((LM_DEBUG,
                "%T - %M - getting reference to POAManager\n"));

    PortableServer::POAManager_var mgr = poa->the_POAManager ();
    mgr->activate ();

    // Create the servant for the node daemon.
    ACE_DEBUG ((LM_DEBUG, "%T - %M - creating the node daemon server\n"));
    ACE_NEW_RETURN (this->daemon_, CUTS_Node_Daemon_i (this->orb_), 1);

    // Setup the servant before activate it.
    this->daemon_->initial_directory (this->opts_.init_dir_);

    if (this->opts_.defines_.size () > 0)
      this->daemon_->insert_properties (this->opts_.defines_);

    this->load_initial_config ();

    // Activate the <CUTS::Node_Daemon> and write it's IOR to file.
    CUTS::Task_Manager_var daemon = this->daemon_->_this ();
    this->servant_ = this->daemon_;

    // Export the reference to the servant's IOR
    this->write_ior_to_file ();
    this->write_ior_to_table ();

    // Run the ORB's main event loop.
    ACE_DEBUG ((LM_DEBUG, "%T - %M - running ORB's main event loop\n"));
    this->orb_->run ();

    // Terminate all the task in the task manager.
    this->daemon_->terminate_tasks ();

    // Destroy the RootPOA.
    ACE_DEBUG ((LM_DEBUG, "%T - %M - destroying the RootPOA\n"));
    poa->destroy (1, 1);

    // Destroy the ORB.
    ACE_DEBUG ((LM_DEBUG, "%T - %M - destroying the ORB\n"));
    this->orb_->destroy ();
    return 0;
  }
  catch (const ::CORBA::Exception & ex)
  {
    ACE_ERROR ((LM_ERROR,
                "%T - %M - %s\n",
                ex._info ().c_str ()));
  }
  catch (...)
  {
    ACE_ERROR ((LM_ERROR,
                "%T - %M - caught unknown exception\n"));
  }
}

//
// parse_args
//
int CUTS_Node_Daemon_Server::parse_args (int argc, char * argv [])
{
  // Setup the <ACE_Get_Opt> variable.
  const char * opts = "c:vo:d:D:";
  ACE_Get_Opt get_opt (argc, argv, opts);

  // Setup the long options for the command-line
  get_opt.long_option ("working-directory", 'd', ACE_Get_Opt::ARG_REQUIRED);
  get_opt.long_option ("config", 'c', ACE_Get_Opt::ARG_REQUIRED);
  get_opt.long_option ("ior-file", 'o', ACE_Get_Opt::ARG_REQUIRED);

  get_opt.long_option ("verbose", 'v', ACE_Get_Opt::NO_ARG);
  get_opt.long_option ("debug", ACE_Get_Opt::NO_ARG);
  get_opt.long_option ("help", 'h', ACE_Get_Opt::NO_ARG);

  int option;
  while ((option = get_opt ()) != EOF)
  {
    switch (option)
    {
    case 0:
      if (ACE_OS::strcmp (get_opt.long_option (), "working-directory") == 0)
      {
        this->opts_.init_dir_ = get_opt.opt_arg ();
      }
      else if (ACE_OS::strcmp (get_opt.long_option (), "ior-file") == 0)
      {
        this->opts_.ior_file_ = get_opt.opt_arg ();
      }
      else if (ACE_OS::strcmp (get_opt.long_option (), "verbose") == 0)
      {
        u_long mask =
          ACE_Log_Msg::instance ()->priority_mask (ACE_Log_Msg::PROCESS);

        mask |= LM_INFO;

        ACE_Log_Msg::instance ()->priority_mask (mask, ACE_Log_Msg::PROCESS);
      }
      else if (ACE_OS::strcmp (get_opt.long_option (), "debug") == 0)
      {
        u_long mask =
          ACE_Log_Msg::instance ()->priority_mask (ACE_Log_Msg::PROCESS);

        mask |= LM_DEBUG;

        ACE_Log_Msg::instance ()->priority_mask (mask, ACE_Log_Msg::PROCESS);
      }
      else if (ACE_OS::strcmp (get_opt.long_option (), "config") == 0)
      {
        this->opts_.config_ = get_opt.opt_arg ();
      }
      else if (ACE_OS::strcmp (get_opt.long_option (), "help") == 0)
      {
        std::cout << __HELP__ << std::endl;
        ACE_OS::exit (0);
      }
      break;

    case 'c':
      this->opts_.config_ = get_opt.opt_arg ();
      break;

    case 'd':
      this->opts_.init_dir_ = get_opt.opt_arg ();
      break;

    case 'o':
      this->opts_.ior_file_ = get_opt.opt_arg ();
      break;

    case 'h':
      std::cout << __HELP__ << std::endl;
      ACE_OS::exit (0);
      break;

    case 'D':
      this->opts_.defines_.push_back (get_opt.opt_arg ());
      break;

    case 'v':
      {
        u_long mask =
          ACE_Log_Msg::instance ()->priority_mask (ACE_Log_Msg::PROCESS);

        mask |= LM_INFO;

        ACE_Log_Msg::instance ()->priority_mask (mask, ACE_Log_Msg::PROCESS);
      }
      break;

    case '?':
      /* unknown option; do nothing */
      break;

    case ':':
      ACE_ERROR ((LM_ERROR,
                  "%T - %M - %c is missing an argument\n",
                  get_opt.opt_opt ()));
      return -1;
      break;

    default:
      /* do nothing */;
    }
  }

  return 0;
}

//
// shutdown
//
void CUTS_Node_Daemon_Server::shutdown (void)
{
  try
  {
    this->orb_->shutdown ();
  }
  catch (const CORBA::Exception & ex)
  {
    ACE_ERROR ((LM_ERROR,
                "%T (%t) - %M - %s\n",
                ex._info ().c_str ()));
  }
}

//
// load_initial_config
//
int CUTS_Node_Daemon_Server::load_initial_config (void)
{
  if (this->opts_.config_.empty ())
    return 0;

  ACE_DEBUG ((LM_INFO,
              "%T - %M - loading initial configuration [file=%s]\n",
              this->opts_.config_.c_str ()));

  // Get the CUTS_ROOT environment variable value.
  ACE_Env_Value <const char *> CUTS_ROOT ("CUTS_ROOT", "");

  std::ostringstream cuts_schema;
  cuts_schema << CUTS_ROOT << "/etc/schemas/";

  // Create the file reader for the configuration file.
  XSCRT::utils::File_Reader_T <CUTS::nodeConfig> reader (&CUTS::reader::node);

  try
  {
    // Configure the entity resolver.
    XSC::XML::Basic_Resolver br (cuts_schema.str ().c_str ());
    XSC::XML::XML_Schema_Resolver <XSC::XML::Basic_Resolver> resolver (br);
    reader->setEntityResolver (&resolver);

    // Configure the error handler.
    XSC::XML::XML_Error_Handler error_handler;
    reader->setErrorHandler (&error_handler);

    // Set the features for the parser.
    reader->setCreateCommentNodes (false);
    reader->setCreateEntityReferenceNodes (false);
    reader->setDoNamespaces (true);
    reader->setIncludeIgnorableWhitespace (false);
    reader->setValidationScheme (AbstractDOMParser::ValSchemes::Val_Auto);
    reader->setDoSchema (true);
    reader->setValidationSchemaFullChecking (true);
    reader->setValidationConstraintFatal (true);

    CUTS::nodeConfig node_config;

    // Open the default configuration.
    if (!reader.read (this->opts_.config_.c_str ()))
    {
      ACE_ERROR_RETURN ((LM_ERROR,
                         "%T - %M - failed to open configuration file [%s]\n",
                         this->opts_.config_.c_str ()),
                         -1);
    }

    // Read the default node configuration.
    reader >>= node_config;

    if (node_config.tasklist_p ())
    {
      // Get the task list for the node.
      CUTS::taskList const & tasks = node_config.tasklist ();

      CUTS::taskList::task_const_iterator
        iter = tasks.begin_task (), iter_end = tasks.end_task ();

      // Begin each of the task on the node daemon.
      CUTS::taskDescriptor task;

      for ( ; iter != iter_end; iter ++)
      {
        // Initialize the task descriptor.
        task.id = ::CORBA::string_dup (iter->id ().c_str ());
        task.executable = ::CORBA::string_dup (iter->executable ().c_str ());

        task.arguments =
          ::CORBA::string_dup (iter->arguments_p () ?
                               iter->arguments ().c_str () : "");

        task.workingdirectory =
          ::CORBA::string_dup (iter->workingdirectory_p () ?
                               iter->workingdirectory ().c_str () : "");

        // Spawn the new task.
        this->daemon_->task_spawn (task);
      }
    }

    return 0;
  }
  catch (const xercesc::DOMException & ex)
  {
    ACE_ERROR ((LM_ERROR,
                "%T - %M - %s\n",
                ex.getMessage ()));
  }
  catch (const xercesc::XMLException & )
  {
    ACE_ERROR ((LM_ERROR,
                "%T - %M - caught XML exception\n"));
  }
  catch (...)
  {
    ACE_ERROR ((LM_ERROR,
                "%T - %M - caught unknown exception\n"));
  }

  return -1;
}

//
// write_ior_to_file
//
int CUTS_Node_Daemon_Server::write_ior_to_file (void)
{
  if (this->opts_.ior_file_.empty ())
    return 0;

  try
  {
    // Open the IOR file for writing.
    std::ofstream iorfile;
    iorfile.open (this->opts_.ior_file_.c_str ());

    if (iorfile.is_open ())
    {
      // Convert the servant to a string, or IOR.
      CORBA::String_var ior = this->orb_->object_to_string (this->daemon_->_this ());

      ACE_DEBUG ((LM_DEBUG,
                  "%T - %M - writing node daemon IOR to file %s\n",
                  this->opts_.ior_file_.c_str ()));

      // Write the IOR to the file.
      iorfile << ior.in () << std::endl;
      iorfile.close ();

      return 0;
    }
    else
    {
      ACE_DEBUG ((LM_ERROR,
                  "%T - %M - failed to open %s for writing\n",
                  this->opts_.ior_file_.c_str ()));
    }
  }
  catch (const CORBA::Exception & ex)
  {
    ACE_ERROR ((LM_ERROR,
                "%T - %M - %s\n",
                ex._info ().c_str ()));
  }
  catch (...)
  {
    ACE_ERROR ((LM_ERROR,
                "%T - %M - caught unknown exception\n"));
  }

  return -1;
}

//
// write_ior_to_file
//
int CUTS_Node_Daemon_Server::write_ior_to_table (void)
{
  try
  {
    // Locate the IORTable for the ORB.
    CORBA::Object_var obj = this->orb_->resolve_initial_references ("IORTable");
    IORTable::Table_var ior_table = IORTable::Table::_narrow (obj.in ());

    // Convert the servant to a string, or IOR.
    CORBA::String_var ior = this->orb_->object_to_string (this->daemon_->_this ());

    ACE_DEBUG ((LM_DEBUG,
                "%T - %M - writing node daemon IOR to IORTable\n"));

    ior_table->bind ("CUTS/NodeDaemon", ior.in ());
    return 0;
  }
  catch (const CORBA::Exception & ex)
  {
    ACE_ERROR ((LM_ERROR,
                "%T - %M - %s\n",
                ex._info ().c_str ()));
  }
  catch (...)
  {
    ACE_ERROR ((LM_ERROR,
                "%T - %M - caught unknown exception\n"));
  }

  return -1;
}

