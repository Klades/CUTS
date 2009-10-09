// $Id$

#include "TE_Score_App.h"

#if !defined (__CUTS_INLINE__)
#include "TE_Score_App.inl"
#endif

#include "TE_Score_Evaluator.h"
#include "cuts/utils/unite/Correctness_Test_File.h"
#include "cuts/utils/unite/Dataflow_Graph.h"
#include "cuts/utils/unite/Dataflow_Graph_Builder.h"
#include "cuts/utils/unite/Dataset_Repo.h"
#include "cuts/utils/unite/Dataset_Result.h"
#include "cuts/utils/unite/Unite_Datagraph_File.h"
#include "cuts/utils/testing/Test_Database.h"

#include "XSC/utils/XML_Error_Handler.h"

#include "ace/Get_Opt.h"
#include "ace/streams.h"

//
// run_main
//
int CUTS_TE_Score_App::run_main (int argc, char * argv [])
{
  try
  {
    if (0 != this->parse_args (argc, argv))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to parse command-line arguments\n")),
                         -1);

    // Load the configuration file.
    CUTS_Correctness_Test_File cfg_file;

    XSC::XML::XML_Error_Handler error_handler;
    cfg_file->setErrorHandler (&error_handler);

    if (!cfg_file.read (this->config_file_.c_str ()))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to read %s\n"),
                         this->config_file_.c_str ()),
                         -1);

    ::CUTS::XML::correctnessTestType correctness_test ("");
    cfg_file >>= correctness_test;

    // Load the datagraph from the test.
    CUTS_Unite_Datagraph_File datagraph_file;
    datagraph_file->setErrorHandler (&error_handler);

    if (!datagraph_file.read (correctness_test.datagraph ().c_str ()))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to read %s\n"),
                         correctness_test.datagraph ().c_str ()),
                         -1);

    ::CUTS::XML::datagraphType datagraph ("");
    datagraph_file >>= datagraph;

    // Build the datagraph for this test.
    CUTS_Dataflow_Graph graph;
    CUTS_Dataflow_Graph_Builder graph_builder;

    if (!graph_builder.build (datagraph, graph))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to build datagraph %s\n"),
                         datagraph.name ().c_str ()),
                         -1);

    // Open the test database for reading.
    ACE_DEBUG ((LM_DEBUG,
                ACE_TEXT ("%T (%t) - %M - opening test datafile\n")));

    CUTS_Test_Database test_db;
    if (!test_db.open (this->test_db_file_))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to test database %s\n"),
                         this->test_db_file_.c_str ()),
                         -1);

    // Open the dataset repository for writing.
    ACE_DEBUG ((LM_DEBUG,
                ACE_TEXT ("%T (%t) - %M - opening dataset repository\n")));

    CUTS_Dataset_Repo repo;
    if (!repo.open (":memory:", test_db))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to open dataset repository\n"),
                         this->test_db_file_.c_str ()),
                         -1);

    // Create a new dataset in the repository.
    ACE_DEBUG ((LM_DEBUG,
                ACE_TEXT ("%T (%t) - %M - inserting new dataset into repository\n")));

    if (!repo.insert (graph))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to construct variable table\n")),
                         -1);

    CUTS_Dataset_Result result (repo);
    CUTS_TE_Score_Evaluator evaluator (result);

    ACE_DEBUG ((LM_INFO,
                ACE_TEXT ("%T (%t) - %M - evaluating correctness; please wait...\n")));

    evaluator.evaluate (graph.name (),
                        correctness_test.begin_state (),
                        correctness_test.end_state ());

    std::cout
      << std::endl
      << "CUTS TE Score Results" << std::endl
      << "=================================================" << std::endl
      << ". Points awarded : " << evaluator.points () << std::endl
      << ". Max points     : " << evaluator.max_points () << std::endl
      << ". Final grade    : " << evaluator.final_grade () << "%" << std::endl
      << std::endl;

    // Close the test database.
    test_db.close ();

    return 0;
  }
  catch (const CUTS_DB_Exception & ex)
  {
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - %s\n"),
                ex.message ().c_str ()));
  }

  return -1;
}

//
// parse_args
//
int CUTS_TE_Score_App::parse_args (int argc, char * argv [])
{
  const char * optstr = "hc:t:";
  ACE_Get_Opt get_opt (argc, argv, optstr);

  get_opt.long_option ("config", 'c', ACE_Get_Opt::ARG_REQUIRED);
  get_opt.long_option ("test", 't', ACE_Get_Opt::ARG_REQUIRED);
  get_opt.long_option ("help", 'h', ACE_Get_Opt::NO_ARG);

  char opt;

  while ((opt = get_opt ()) != EOF)
  {
    switch (opt)
    {
    case 0:
      if (0 == ACE_OS::strcmp ("test", get_opt.long_option ()))
      {
        this->test_db_file_ = get_opt.opt_arg ();
      }
      else if (0 == ACE_OS::strcmp ("config", get_opt.long_option ()))
      {
        this->config_file_ = get_opt.opt_arg ();
      }
      else if (0 == ACE_OS::strcmp ("help", get_opt.long_option ()))
      {
        this->print_help ();
      }

      break;

    case 't':
      this->test_db_file_ = get_opt.opt_arg ();
      break;

    case 'c':
      this->config_file_ = get_opt.opt_arg ();
      break;

    case 'h':
      this->print_help ();
      break;
    }
  }

  return 0;
}

//
// print_help
//
void CUTS_TE_Score_App::print_help (void)
{

}
