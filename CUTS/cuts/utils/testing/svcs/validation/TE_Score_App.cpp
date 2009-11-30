// $Id$

#include "TE_Score_App.h"

#if !defined (__CUTS_INLINE__)
#include "TE_Score_App.inl"
#endif

#include "TE_Score_Evaluator.h"
#include "cuts/utils/unite/cuts-unite.h"
#include "cuts/utils/unite/Dataflow_Graph.h"
#include "cuts/utils/unite/Dataflow_Graph_Builder.h"
#include "cuts/utils/unite/Dataset_Repo.h"
#include "cuts/utils/unite/Dataset_Result.h"
#include "cuts/utils/unite/Unite_Datagraph_File.h"
#include "cuts/utils/unite/Validation_Test_File.h"
#include "cuts/utils/testing/Test_Database.h"

#include "XSC/utils/XML_Error_Handler.h"

#include "ace/Get_Opt.h"
#include "ace/streams.h"

const char * __HELP__ =
"CUTS test execution (TE) score utility\n"
"\n"
"USAGE: cuts-tescore [OPTIONS]\n"
"\n"
"General options:\n"
"  -c, --config=FILE        config file with validation information\n"
"  --test=FILE              test database file\n"
"\n"
"  --sandbox=DIR            location to store temporary files\n"
"\n"
"Output options:\n"
"  -h, --help               print this help message\n";

/**
 * @struct state_copy_t
 */
struct state_copy_t
{
  /// Type definition of the value type.
  typedef CUTS::XML::validationType::state_const_iterator::value_type const_value_type;

  state_copy_t (CUTS_TE_Score_State_List & list)
    : list_ (list),
      index_ (0)
  {

  }

  void operator () (const_value_type state)
  {
    CUTS_TE_Score_State & curr_state = this->list_[this->index_ ++];

    curr_state.name_ = state->name ().c_str ();
    curr_state.condition_ = state->condition ().c_str ();
    curr_state.priority_ = state->priority ();

    if (state->minoccurs_p ())
      curr_state.min_occurs_ = state->minoccurs ();

    if (state->maxoccurs_p ())
    {
      if (state->maxoccurs () == "unbounded")
      {
        curr_state.max_occurs_ = -1;
      }
      else
      {
        std::istringstream istr (state->maxoccurs ());
        istr >> curr_state.max_occurs_;
      }
    }

    if (state->isvalid_p ())
      curr_state.is_valid_ = state->isvalid ();
  };

private:
  /// Target list of states.
  CUTS_TE_Score_State_List & list_;

  /// Current index value.
  size_t index_;
};

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
    CUTS_Validation_Test_File validation_file;

    XSC::XML::XML_Error_Handler error_handler;
    validation_file->setErrorHandler (&error_handler);

    if (!validation_file.read (this->opts_.config_file_.c_str ()))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to read %s\n"),
                         this->opts_.config_file_.c_str ()),
                         -1);

    ::CUTS::XML::validationType validation_test ("");
    validation_file >>= validation_test;

    // Copy the states to the prefered format.
    CUTS_TE_Score_State_List states (validation_test.count_state ());

    std::for_each (validation_test.begin_state (),
                   validation_test.end_state (),
                   state_copy_t (states));

    // Load the datagraph from the test.
    CUTS_Unite_Datagraph_File datagraph_file;
    datagraph_file->setErrorHandler (&error_handler);

    if (!datagraph_file.read (validation_test.datagraph ().c_str ()))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to read %s\n"),
                         validation_test.datagraph ().c_str ()),
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
    if (!test_db.open (this->opts_.test_db_file_))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to test database %s\n"),
                         this->opts_.test_db_file_.c_str ()),
                         -1);

    // Open the dataset repository for writing.
    ACE_DEBUG ((LM_DEBUG,
                ACE_TEXT ("%T (%t) - %M - opening dataset repository\n")));

    CUTS_Dataset_Repo repo;

    if (!repo.open (this->opts_.sandbox_, test_db))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to open dataset repository\n"),
                         this->opts_.test_db_file_.c_str ()),
                         -1);

    // Create a new dataset in the repository.
    ACE_DEBUG ((LM_DEBUG,
                ACE_TEXT ("%T (%t) - %M - inserting new dataset into repository\n")));

    if (!repo.insert (graph))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to construct variable table\n")),
                         -1);

    ACE_DEBUG ((LM_INFO,
                ACE_TEXT ("%T (%t) - %M - evaluating correctness; please wait...\n")));

    // Evaluate the states for the current test.
    CUTS_TE_Score_Evaluator evaluator (repo);
    evaluator.evaluate (graph.name (), states);

    std::cout
      << std::endl
      << "CUTS TE Score Results" << std::endl
      << "=================================================" << std::endl
      << ". Points awarded : " << evaluator.points () << std::endl
      << ". Max points     : " << evaluator.max_points () << std::endl
      << ". Final grade    : " << std::fixed << std::setprecision (this->opts_.precision_)
      << (evaluator.final_grade () * 100.0) << "%" << std::endl
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
  get_opt.long_option ("sandbox", ACE_Get_Opt::ARG_REQUIRED);
  get_opt.long_option ("help", 'h', ACE_Get_Opt::NO_ARG);

  char opt;

  while ((opt = get_opt ()) != EOF)
  {
    switch (opt)
    {
    case 0:
      if (0 == ACE_OS::strcmp ("test", get_opt.long_option ()))
      {
        this->opts_.test_db_file_ = get_opt.opt_arg ();
      }
      else if (0 == ACE_OS::strcmp ("config", get_opt.long_option ()))
      {
        this->opts_.config_file_ = get_opt.opt_arg ();
      }
      else if (0 == ACE_OS::strcmp ("sandbox", get_opt.long_option ()))
      {
        this->opts_.sandbox_ = get_opt.opt_arg ();
      }
      else if (0 == ACE_OS::strcmp ("help", get_opt.long_option ()))
      {
        this->print_help ();
      }

      break;

    case 't':
      this->opts_.test_db_file_ = get_opt.opt_arg ();
      break;

    case 'c':
      this->opts_.config_file_ = get_opt.opt_arg ();
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
  std::cerr << ::__HELP__ << std::endl;
  ACE_OS::exit (1);
}
