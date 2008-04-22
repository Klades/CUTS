// -*- C++ -*-

//=============================================================================
/**
 * @file        Node_Daemon_Server.cpp
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

#include "Node_Daemon_i.h"
#include "Server_Options.h"
#include "cutsnode.h"

#include "tao/IORTable/IORTable.h"

#include "ace/Get_Opt.h"
#include "ace/OS_NS_unistd.h"
#include "ace/Process_Mutex.h"
#include "ace/streams.h"
#include "ace/Env_Value_T.h"

#include "XSCRT/utils/File_T.h"
#include "XSCRT/utils/XML_Schema_Resolver_T.h"

//
// parse_args
//
int parse_args (int argc, char * argv [])
{
  // Setup the <ACE_Get_Opt> variable.
  const char * opts = "c:vo:d:";
  ACE_Get_Opt get_opt (argc, argv, opts);

  // Setup the long options for the command-line
  get_opt.long_option ("working-directory", 'd', ACE_Get_Opt::ARG_REQUIRED);
  get_opt.long_option ("ior-file", 'o', ACE_Get_Opt::ARG_REQUIRED);
  get_opt.long_option ("verbose", 'v', ACE_Get_Opt::NO_ARG);
  get_opt.long_option ("config", 'c', ACE_Get_Opt::NO_ARG);

  int option;
  while ((option = get_opt ()) != EOF)
  {
    switch (option)
    {
    case 0:
      if (ACE_OS::strcmp (get_opt.long_option (), "working-directory") == 0)
        SERVER_OPTIONS ()->init_dir_ = get_opt.opt_arg ();

      else if (ACE_OS::strcmp (get_opt.long_option (), "ior-file") == 0)
        SERVER_OPTIONS ()->ior_file_ = get_opt.opt_arg ();
      
      else if (ACE_OS::strcmp (get_opt.long_option (), "verbose") == 0)
        SERVER_OPTIONS ()->verbose_ = true;
      
      else if (ACE_OS::strcmp (get_opt.long_option (), "config") == 0)
        SERVER_OPTIONS ()->config_ = get_opt.opt_arg ();
      
      break;

    case 'c':
      SERVER_OPTIONS ()->config_ = get_opt.opt_arg ();
      break;

    case 'd':
      SERVER_OPTIONS ()->init_dir_ = get_opt.opt_arg ();
      break;

    case 'o':
      SERVER_OPTIONS ()->ior_file_ = get_opt.opt_arg ();
      break;

    case 'v':
      SERVER_OPTIONS ()->verbose_ = true ;
      break;

    case '?':
      /* unknown option; do nothing */
      break;

    case ':':
      ACE_ERROR ((LM_ERROR,
                  "%c is missing an argument\n",
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
// load_initial_config
//
int load_initial_config (const char * config, CUTS_Node_Daemon_i * daemon)
{
  // Get the CUTS_ROOT environment variable value.
  ACE_Env_Value <const char *> CUTS_ROOT ("CUTS_ROOT", "");

  std::ostringstream cuts_schema;
  cuts_schema << CUTS_ROOT << "/etc/schemas/";

  // Create the file reader for the configuration file.
  XSCRT::utils::File_Reader_T <
    CUTS::nodeConfig> reader (&CUTS::node);

  try
  {
    // Configure the entity resolver.
    reader.parser ()->setEntityResolver (
      XSCRT::utils::xml_schema_resolver (
        XSCRT::utils::Basic_Resolver_T <char> (cuts_schema.str ().c_str ())));

    // Discard comment nodes in the document.
    if (reader.parser ()->canSetFeature (xercesc::XMLUni::fgDOMComments, false))
      reader.parser ()->setFeature (xercesc::XMLUni::fgDOMComments, false);

    // Disable datatype normalization. The XML 1.0 attribute value
    // normalization always occurs though.
    if (reader.parser ()->canSetFeature (xercesc::XMLUni::fgDOMDatatypeNormalization, true))
      reader.parser ()->setFeature (xercesc::XMLUni::fgDOMDatatypeNormalization, true);

    // Do not create EntityReference nodes in the DOM tree. No
    // EntityReference nodes will be created, only the nodes
    // corresponding to their fully expanded substitution text will be
    // created.
    if (reader.parser ()->canSetFeature (xercesc::XMLUni::fgDOMEntities, false))
      reader.parser ()->setFeature (xercesc::XMLUni::fgDOMEntities, false);

    // Perform Namespace processing.
    if (reader.parser ()->canSetFeature (xercesc::XMLUni::fgDOMNamespaces, true))
      reader.parser ()->setFeature (xercesc::XMLUni::fgDOMNamespaces, true);

    // Do not include ignorable whitespace in the DOM tree.
    if (reader.parser ()->canSetFeature (xercesc::XMLUni::fgDOMWhitespaceInElementContent, false))
      reader.parser ()->setFeature (xercesc::XMLUni::fgDOMWhitespaceInElementContent, false);

    // Perform Validation
    if (reader.parser ()->canSetFeature (xercesc::XMLUni::fgDOMValidation, true))
      reader.parser ()->setFeature (xercesc::XMLUni::fgDOMValidation, true);

    // Enable the GetParser()'s schema support.
    if (reader.parser ()->canSetFeature (xercesc::XMLUni::fgXercesSchema, true))
      reader.parser ()->setFeature (xercesc::XMLUni::fgXercesSchema, true);

    // Enable full schema constraint checking, including checking which
    // may be time-consuming or memory intensive. Currently, particle
    // unique attribution constraint checking and particle derivation
    // restriction checking are controlled by this option.
    if (reader.parser ()->canSetFeature (xercesc::XMLUni::fgXercesSchemaFullChecking, true))
      reader.parser ()->setFeature (xercesc::XMLUni::fgXercesSchemaFullChecking, true);

    // The GetParser() will treat validation error as fatal and will exit.
    if (reader.parser ()->canSetFeature (xercesc::XMLUni::fgXercesValidationErrorAsFatal, false))
      reader.parser ()->setFeature (xercesc::XMLUni::fgXercesValidationErrorAsFatal, false);

    CUTS::nodeConfig node_config;

    // Open the default configuration.
    if (reader.open (config) == -1)
    {
      ACE_ERROR_RETURN ((LM_ERROR,
                         "failed to open configuration file [%s]\n",
                         config),
                         -1);
    }

    // Read the default node configuration.
    reader >> node_config;

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
        daemon->task_spawn (task);
      }
    }

    return 0;
  }
  catch (const xercesc::DOMException & ex)
  {
    ACE_ERROR ((LM_ERROR,  
                "%s\n",
                ex.getMessage ()));
  }
  catch (const xercesc::XMLException & )
  {
    ACE_ERROR ((LM_ERROR,
                "caught XML exception\n"));
  }
  catch (...)
  {
    ACE_ERROR ((LM_ERROR,
                "caught unknown exception\n"));
  }

  return -1;
}

//
// write_ior_to_file
//
void write_ior_to_file (const char * ior, const char * filename)
{
  try
  {
    // Open the IOR file for writing.
    std::ofstream iorfile;
    iorfile.open (filename);

    if (iorfile.is_open ())
    {
      if (SERVER_OPTIONS ()->verbose_)
      {
        ACE_DEBUG ((LM_DEBUG,
                    "writing node daemon IOR to file %s\n",
                    SERVER_OPTIONS ()->ior_file_.c_str ()));
      }

      // Write the IOR to the file.
      iorfile << ior << std::endl;
      iorfile.close ();
    }
    else
    {
      ACE_DEBUG ((LM_ERROR,
                  "*** error: failed to open %s for writing\n",
                  SERVER_OPTIONS ()->ior_file_.c_str ()));
    }
  }
  catch (CORBA::Exception & ex)
  {
    ACE_ERROR ((LM_ERROR,
                "*** %s\n",
                ex._info ().c_str ()));
  }
  catch (...)
  {
    ACE_ERROR ((LM_ERROR,
                "*** error: caught unknown exception\n"));
  }
}

//
// main
//
int main (int argc, char * argv [])
{
  // We only allow one instance of the daemon to run at a
  // time. This way we don't have any confusion as to which
  // one we are talking to.
  ACE_Process_Mutex process_lock ("cutsnode_d");
  ACE_Guard <ACE_Process_Mutex> guard (process_lock, 0);

  if (guard.locked () == 0)
  {
    ACE_ERROR_RETURN ((LM_ERROR,
                       "*** error: cutsnode_d is already active\n"),
                       1);
  }

  try
  {
    // Initalize the ORB
    ::CORBA::ORB_var orb = ::CORBA::ORB_init (argc, argv);

    if (parse_args (argc, argv) == -1)
      return 1;

    // Get a reference to the <IORTable>.
    VERBOSE_MESSAGE ((LM_DEBUG,
                      "resolving initial reference to IOR table\n"));

    ::CORBA::Object_var obj = orb->resolve_initial_references ("IORTable");
    ::IORTable::Table_var ior_table = ::IORTable::Table::_narrow (obj.in ());

    if (::CORBA::is_nil (ior_table.in ()))
    {
      ACE_ERROR_RETURN ((LM_ERROR,
                         "(%N:%l) failed to resolve IOR table\n"),
                         1);
    }

    // Get a reference to the <RootPOA>
    VERBOSE_MESSAGE ((LM_DEBUG,
                      "resolving initial reference to RootPOA\n"));
    obj = orb->resolve_initial_references ("RootPOA");
    PortableServer::POA_var poa = PortableServer::POA::_narrow (obj.in ());

    // Activate the POAManager
    VERBOSE_MESSAGE ((LM_DEBUG,
                      "getting reference to POAManager\n"));
    PortableServer::POAManager_var mgr = poa->the_POAManager ();
    mgr->activate ();

    // Create a <CUTS::Node_Daemon>
    VERBOSE_MESSAGE ((LM_DEBUG,
                      "creating the node daemon server\n"));

    CUTS_Node_Daemon_i * daemon_i = 0;

    ACE_NEW_RETURN (
      daemon_i, 
      CUTS_Node_Daemon_i (::CORBA::ORB::_duplicate (orb.in ())), 1);

    // Attempt the recover any lost processes.
    size_t count = daemon_i->recover ();

    VERBOSE_MESSAGE ((LM_DEBUG,
                      "recovered %u processes\n",
                      count));

    // Activate the <CUTS::Node_Daemon> and write it's IOR to file.
    CUTS::Task_Manager_var daemon = daemon_i->_this ();
    ::PortableServer::ServantBase_var servant = daemon_i;

      // Convert the object to its string format and write the
      // IOR to file and to the IOR table.
    ::CORBA::String_var objstr = orb->object_to_string (daemon);
    ior_table->bind ("CUTS/NodeDaemon", objstr.in ());

    if (!SERVER_OPTIONS ()->ior_file_.empty ())
    {
      write_ior_to_file (objstr.in (), 
                         SERVER_OPTIONS ()->ior_file_.c_str ());
    }

    // Load the initial configuration.
    if (!SERVER_OPTIONS ()->config_.empty ())
      load_initial_config (SERVER_OPTIONS ()->config_.c_str (), daemon_i);
      
    // Run the ORB...
    VERBOSE_MESSAGE ((LM_DEBUG, "activating node daemon ORB\n"));
    orb->run ();

    // Destroy the RootPOA.
    VERBOSE_MESSAGE ((LM_DEBUG, "destroying the RootPOA\n"));
    poa->destroy (1, 1);

    // Destroy the ORB.
    VERBOSE_MESSAGE ((LM_DEBUG, "destroying the ORB\n"))
    orb->destroy ();

    return 0;
  }
  catch (::CORBA::Exception & ex)
  {
    ACE_ERROR ((LM_ERROR,
                "%s\n",
                ex._info ().c_str ()));
  }
  catch (...)
  {
    ACE_ERROR ((LM_ERROR,
                "*** error: caught unknown exception\n"));
  }

  return 1;
}
