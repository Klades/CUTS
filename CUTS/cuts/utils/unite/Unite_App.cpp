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
"  --datagraph=FILE          override existing datagraph in configuration\n"
"  --sandbox=PATH            location for storing scratchpad data\n"
"\n"
"  --show-trend              show the data trend for the test\n"
"\n"
"Service options:\n"
"  --disable=NAME            disable service with id NAME\n"
"\n"
"Output options:\n"
"  -h, --help                print this help message\n";

class load_service
{
public:
  typedef ::CUTS::XML::serviceList::service_iterator::value_type value_type;

  load_service (CUTS_Unite_Presentation_Service_Manager & mgr)
    : mgr_ (mgr)
  {

  }

  void operator () (const value_type & value) const
  {
    this->mgr_.load_service (value->id ().c_str (),
                             value->location ().c_str (),
                             value->classname ().c_str (),
                             value->params_p () ? value->params ().c_str () : 0);
  }

private:
  mutable CUTS_Unite_Presentation_Service_Manager & mgr_;
};


//
// CUTS_Unite_App
//
CUTS_Unite_App::CUTS_Unite_App (void)
: sandbox_ ("."),
  show_trend_ (false)
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
  ::CUTS::XML::testConfig config ("", "", "", ::CUTS::XML::datagraphLink (""));

  XSC::XML::XML_Error_Handler error_handler;
  config_file->setErrorHandler (&error_handler);

  if (config_file.read (this->config_.c_str ()))
    config_file >>= config;

  // Load the services.
  if (config.services_p ())
    this->load_services (config.services ());

  // Construct the binary version of the unit test.
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

  ::CUTS::XML::datagraphType datagraph ("");

  if (this->datagraph_.empty ())
  {
    if (datagraph_file.read (config.datagraph ().location ().c_str ()))
      datagraph_file >>= datagraph;
  }
  else
  {
    if (datagraph_file.read (this->datagraph_.c_str ()))
      datagraph_file >>= datagraph;
  }

  // Build the graph for this unit test.
  CUTS_Unit_Test_Graph graph;
  CUTS_Unit_Test_Graph_Builder graph_builder;

  ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("%T (%t) - %M - building datagraph; please wait...\n")));

  if (!graph_builder.build (datagraph, graph))
    ACE_ERROR_RETURN ((LM_ERROR,
                       "%T (%t) - %M - failed to build unit test graph %s\n",
                       datagraph.name ().c_str ()),
                       -1);

  // Open the database that contains the test data.
  CUTS_Test_Database testdata;

  if (!testdata.open (this->datafile_))
    ACE_ERROR_RETURN ((LM_ERROR,
                       "%T (%t) - %M - failed to open %s\n",
                       this->datafile_.c_str ()),
                       -1);

  // Open the repository for the test data.
  CUTS_Variable_Table_Repo repo;
  if (!repo.open (this->sandbox_, testdata))
    ACE_ERROR_RETURN ((LM_ERROR,
                       "%T (%t) - %M - failed to open variable table repo\n"),
                       -1);

  ACE_High_Res_Timer timer;
  timer.start ();

  // Time the evaluation operation.
  ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("%T (%t) - %M - constructing variable table; please wait...\n")));

  // Construct the variable table for the log format graph.
  if (!repo.insert (graph))
    ACE_ERROR_RETURN ((LM_ERROR,
                       "%T (%t) - %M - failed to construct variable table\n"),
                       -1);

  // Evaluate the unit test.
  CUTS_Unit_Test_Result result (repo);

  // Time the evaluation operation.
  ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("%T (%t) - %M - evaluating datagraph; please wait...\n")));

  if (result.evaluate (unit_test, graph.name (), !this->show_trend_) != 0)
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

  std::cout << "Evaluation time: "
            << elapsed.sec () << "." << elapsed.usec () << std::endl;

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
  get_opt.long_option ("datagraph", ACE_Get_Opt::ARG_REQUIRED);
  get_opt.long_option ("sandbox", ACE_Get_Opt::ARG_REQUIRED);
  get_opt.long_option ("show-trend");
  get_opt.long_option ("disable", ACE_Get_Opt::ARG_REQUIRED);
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
      else if (ACE_OS::strcmp (get_opt.long_option (), "datagraph") == 0)
      {
        this->datagraph_ = get_opt.opt_arg ();
      }
      else if (ACE_OS::strcmp (get_opt.long_option (), "sandbox") == 0)
      {
        this->sandbox_ = get_opt.opt_arg ();
      }
      else if (ACE_OS::strcmp (get_opt.long_option (), "help") == 0)
      {
        this->print_help ();
      }
      else if (ACE_OS::strcmp (get_opt.long_option (), "show-trend") == 0)
      {
        this->show_trend_ = true;
      }
      else if (ACE_OS::strcmp (get_opt.long_option (), "disable") == 0)
      {
        this->disables_.insert (get_opt.opt_arg ());
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

//
// load_services
//
void CUTS_Unite_App::
load_services (const ::CUTS::XML::serviceList & list)
{
  std::for_each (list.begin_service (),
                 list.end_service (),
                 load_service (this->svc_mgr_));

  // Disable the service listed on the command-line.
  string_set::CONST_ITERATOR iter (this->disables_);

  for (; !iter.done (); ++ iter)
    this->svc_mgr_.suspend ((*iter).c_str ());
}
