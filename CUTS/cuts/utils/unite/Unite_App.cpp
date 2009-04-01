// $Id$

#include "Unite_App.h"
#include "Unite_Config_File.h"
#include "Unite_Datagraph_File.h"
#include "Unit_Test.h"
#include "Unit_Test_Builder.h"
#include "Unit_Test_Result.h"
#include "Unit_Test_Graph.h"
#include "Unit_Test_Graph_Builder.h"
#include "Variable_Table_Repo.h"
#include "presentation/console/Console_Presentation_Service.h"
#include "cuts/utils/testing/Test_Database.h"
#include "ace/Get_Opt.h"
#include "ace/Env_Value_T.h"
#include "ace/High_Res_Timer.h"
#include "XSC/utils/XML_Error_Handler.h"

static const char * __HELP__ =
"UNITE - a QoS unit test evaluation engine\n"
"\n"
"USAGE: cuts-unite [OPTIONS]\n"
"\n"
"General options:\n"
"  -f, --datafile=FILE       CUTS database that contains the syestem traces\n"
"  -c, --config=FILE         configuration file for evaluation\n"
"  --sandbox=PATH            location for storing scratchpad data\n"
"\n"
"Output options:\n"
"  -h, --help                print this help message\n";

//
// CUTS_Unite_App
//
CUTS_Unite_App::CUTS_Unite_App (void)
: sandbox_ (".")
{
  this->svc_mgr_.open ("cuts-unite",
                       ACE_DEFAULT_LOGGER_KEY,
                       false,
                       true,
                       true);

  this->svc_mgr_.process_directive (ace_svc_desc_CUTS_Console_Presentation_Service);
}

//
// CUTS_Unite_App
//
CUTS_Unite_App::~CUTS_Unite_App (void)
{

}

//
// run_main
//
int CUTS_Unite_App::run_main (int argc, char * argv [])
{
  if (this->parse_args (argc, argv) == -1)
    return -1;

  // Load the configuration file.
  CUTS_Unite_Config_File config_file;
  CUTS::uniteConfig config ("", "", "", CUTS::datagraphLink (""));

  XSC::XML::XML_Error_Handler error_handler;
  config_file->setErrorHandler (&error_handler);

  if (config_file.read (this->config_.c_str ()))
    config_file >>= config;

  CUTS_Unit_Test unit_test;
  CUTS_Unit_Test_Builder builder;

  if (!builder.build (config, unit_test))
    ACE_ERROR_RETURN ((LM_ERROR,
                       "%T (%t) - %M - failed to build unit test in %s\n",
                       this->config_.c_str ()),
                       -1);

  // Load the XML document that contains the log formats.
  // Process the log formats.
  CUTS_Unite_Datagraph_File datagraph_file;
  datagraph_file->setErrorHandler (&error_handler);

  CUTS::datagraphType dgraph ("", CUTS::logformatList (std::list< ::CUTS::logformatType > ()));

  if (datagraph_file.read (config.datagraph ().location ().c_str ()))
    datagraph_file >>= dgraph;

  // Build the graph for this unit test.
  CUTS_Unit_Test_Graph graph;
  CUTS_Unit_Test_Graph_Builder graph_builder;

  if (!graph_builder.build (dgraph, graph))
    ACE_ERROR_RETURN ((LM_ERROR,
                       "%T (%t) - %M - failed to build unit test graph %s\n",
                       dgraph.name ().c_str ()),
                       -1);

  // Open the database that contains the test data.
  CUTS_Test_Database testdata;

  if (!testdata.open (this->datafile_))
    ACE_ERROR_RETURN ((LM_ERROR,
                       "%T (%t) - %M - failed to open %s\n",
                       this->datafile_.c_str ()),
                       -1);

  // Open the repository for the test data.
  CUTS_Variable_Table_Repo repo (this->sandbox_);

  if (!repo.open (testdata))
    ACE_ERROR_RETURN ((LM_ERROR,
                       "%T (%t) - %M - failed to open variable table repo\n"),
                       -1);

  // Construct the variable table for the log format graph.
  if (!repo.insert (graph))
    ACE_ERROR_RETURN ((LM_ERROR,
                       "%T (%t) - %M - failed to construct variable table\n"),
                       -1);

  // Evaluate the unit test.
  CUTS_Unit_Test_Result result (repo);

  // Time the evaluation operation.
  ACE_High_Res_Timer timer;
  timer.start ();

  if (result.evaluate (unit_test, graph.name ()) != 0)
    ACE_ERROR_RETURN ((LM_ERROR,
                       "%T (%t) - %M - failed to evaluate test %s [vtable=%s]\n",
                       unit_test.name ().c_str (),
                       graph.name ().c_str ()),
                       -1);

  // Stop the timer for the evaluation.
  timer.stop ();

  // Determine the elapsed time of the evaluation.
  ACE_Time_Value elapsed;
  timer.elapsed_time (elapsed);

  // Present the results to the end-user.
  this->svc_mgr_.handle_result (result);

  return 0;
}

//
// parse_args
//
int CUTS_Unite_App::parse_args (int argc, char * argv [])
{
  const char * optstr = "hc:f:";

  ACE_Get_Opt get_opt (argc, argv, optstr);

  get_opt.long_option ("config", 'c', ACE_Get_Opt::ARG_REQUIRED);
  get_opt.long_option ("datafile", 'f', ACE_Get_Opt::ARG_REQUIRED);
  get_opt.long_option ("sandbox", ACE_Get_Opt::ARG_REQUIRED);
  get_opt.long_option ("help", 'h');

  char ch;

  while ((ch = get_opt ()) != EOF)
  {
    switch (ch)
    {
    case 0:
      if (ACE_OS::strcmp (get_opt.long_option (), "config") == 0)
      {
        this->config_ = get_opt.opt_arg ();
      }
      else if (ACE_OS::strcmp (get_opt.long_option (), "datafile") == 0)
      {
        this->datafile_ = get_opt.opt_arg ();
      }
      else if (ACE_OS::strcmp (get_opt.long_option (), "sandbox") == 0)
      {
        this->sandbox_ = get_opt.opt_arg ();
      }
      else if (ACE_OS::strcmp (get_opt.long_option (), "help") == 0)
      {
        this->print_help ();
      }
      break;

    case 'c':
      this->config_ = get_opt.opt_arg ();
      break;

    case 'f':
      this->datafile_ = get_opt.opt_arg ();
      break;

    case 'h':
      this->print_help ();
    }
  }

  return 0;
}

//
// print_help
//
void CUTS_Unite_App::print_help (void)
{
  std::cerr << __HELP__ << std::endl;
  ACE_OS::exit (0);
}
