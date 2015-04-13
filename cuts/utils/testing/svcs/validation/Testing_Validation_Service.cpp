// $Id$

#include "Testing_Validation_Service.h"
#include "TE_Score_Evaluator.h"
#include "cuts/unite/Unite_Datagraph_File.h"
#include "cuts/unite/Unite_Validation_File.h"
#include "cuts/unite/Dataflow_Graph.h"
#include "cuts/unite/Dataflow_Graph_Builder.h"
#include "cuts/unite/Dataset_Repo.h"
#include "cuts/unite/Dataset_Result.h"
#include "cuts/unite/cuts-unite.h"
#include "cuts/unite/Dataflow_Graph_Analyzer.h"
#include "cuts/utils/testing/Testing_App_Base.h"
#include "XSC/utils/XML_Error_Handler.h"
#include "ace/Get_Opt.h"

//
// __HELP__
//
static const char * __HELP__ =
"CUTS validation service responsible for validating a test\n"
"\n"
"USAGE: CUTS_Testing_Validation_Service [OPTIONS]\n"
"\n"
"  -c, --config FILE         file defining the validation condition\n"
"  -d, --datagraph FILE      datagraph file for this test \n"
"  -h, --help                print this help message\n";

CUTS_TESTING_SERVICE_IMPL (CUTS_Testing_Validation_Service,
                           _make_CUTS_Testing_Validation_Service);

//
// CUTS_Testing_Server
//
CUTS_Testing_Validation_Service::CUTS_Testing_Validation_Service (void)
{
}

//
// CUTS_Testing_Server
//
CUTS_Testing_Validation_Service::~CUTS_Testing_Validation_Service (void)
{
}

//
// run_main
//
int CUTS_Testing_Validation_Service::init (int argc, char * argv [])
{

  if (this->parse_args (argc, argv) == -1)
  {
    ACE_ERROR_RETURN  ((LM_ERROR,
                        "%T (%t) - %M - failed to parse command-line options\n"),
                        -1);
  }

  return 0;
}

//
// handle_shutdown
//
int CUTS_Testing_Validation_Service::handle_shutdown (const ACE_Time_Value & tv)
{
  return this->validate_test ();
}

//
// parse_args
//
int CUTS_Testing_Validation_Service::parse_args (int argc, char * argv [])
{
  const char * options = ACE_TEXT (":c:d:h:");

  ACE_Get_Opt get_opt (argc, argv, options);

  get_opt.long_option ("config", 'c', ACE_Get_Opt::ARG_REQUIRED);
  get_opt.long_option ("datagraph", 'd', ACE_Get_Opt::ARG_REQUIRED);
  get_opt.long_option ("help", 'h', ACE_Get_Opt::NO_ARG);

  int ch;

  while ((ch = get_opt ()) != EOF)
  {
    switch (ch)
    {
        case 0:
          if (ACE_OS::strcmp (get_opt.long_option (), "config") == 0)
          {
            this->validation_config_ = get_opt.opt_arg ();
          }
          else if (ACE_OS::strcmp (get_opt.long_option (), "datagraph") == 0)
          {
            this->datagraph_ = get_opt.opt_arg ();
          }
          else if (ACE_OS::strcmp (get_opt.long_option (), "help") == 0)
          {
            this->print_help ();
          }
          break;

        case 'c':
          this->validation_config_ = get_opt.opt_arg ();
          break;

        case 'd':
          this->datagraph_ = get_opt.opt_arg ();
          break;

        case 'h':
          this->print_help ();
          break;

    }
  }

  if (this->validation_config_.empty ())
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - missing validation configuration (--config)\n")),
                       -1);

  return 0;
}

//
// parse_config_file
//
int CUTS_Testing_Validation_Service::validate_test (void)
{
  XSC::XML::XML_Error_Handler error_handler;

  // Load the XML document that contains the datagraph.
  CUTS_Unite_Datagraph_File datagraph_file;
  datagraph_file->setErrorHandler (&error_handler);

  ::CUTS::XML::datagraphType datagraph ("");

  if (this->datagraph_.empty ())
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - datagraph file not found\n")),
                       -1);

  if (!datagraph_file.read (this->datagraph_.c_str ()))
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - failed to read datagraph file (%s)\n"),
                       this->datagraph_.c_str ()),
                       -1);

  datagraph_file >>= datagraph;

  // Build the datagraph for this test.
  CUTS_Dataflow_Graph graph;
  CUTS_Dataflow_Graph_Builder graph_builder;

  ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("%T (%t) - %M - building datagraph; please wait...\n")));

  if (!graph_builder.build (datagraph, graph))
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - failed to build datagraph %s\n"),
                       datagraph.name ().c_str ()),
                       -1);

  // Open the database that contains the test data.
  CUTS_Test_Database & test_db = this->test_app ()->test_db ();

  ACE_CString repo_location (":memory:");
  CUTS_Dataflow_Graph_Analyzer analyzer (&graph);
  analyzer.analyze (test_db, repo_location);

  CUTS_Dataset_Repo * repo = analyzer.join (test_db, repo_location);

  ACE_DEBUG ((LM_DEBUG,
             ACE_TEXT ("%T (%t) - %M - validating test; please wait...\n")));

  // Open the XML document for reading.
  CUTS_Unite_Validation_File validation_file;
  validation_file->setErrorHandler (&error_handler);

  if (!validation_file.read (this->validation_config_.c_str ()))
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - failed to load validation file %s\n"),
                       this->validation_config_.c_str ()),
                       -1);

  // Load the information from the file.
  ::CUTS::XML::validationType validation ("");
  validation_file >>= validation;

  // Validate the dataset.
  CUTS_TE_Score_Evaluator evaluator (*repo);
  //bool validation_result = evaluator.evaluate (datagraph.name ().c_str (),
  //                                          validation_state,
  //                                          0,
  //                                          -1);

  //std::cout << "Test validation "
  //          << (validation_result ? "succeeded" : "failed")
  //          << std::endl;

  return 0;
}

//
// print_help
//
void CUTS_Testing_Validation_Service::print_help (void)
{
  std::cout << ::__HELP__ << std::endl;
  ACE_OS::exit (1);
}


