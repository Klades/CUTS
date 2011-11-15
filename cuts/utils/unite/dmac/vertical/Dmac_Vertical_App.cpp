#include "ace/Get_Opt.h"
#include <iostream>
#include "cuts/utils/testing/Test_Database.h"
#include "ace/Log_Msg.h"
#include "adbc/SQLite/Connection.h"
#include "cuts/Auto_Functor_T.h"
#include "Dmac_Vertical_App.h"



static const char * __HELP__ =
"cuts-dmac-vertical - Convert the database to veetical-format\n"
"\n"
"USAGE: cuts-dmac-vertical [OPTIONS]\n"
"\n"
"General options:\n"
"  -f, --file=FILE           Data file containing the traces\n"
"  -h, --help                print this help message\n";


//
// CUTS_Dmac_Vertical_App
//
CUTS_Dmac_Vertical_App::CUTS_Dmac_Vertical_App (void)
{

}

//
// ~CUTS_Dmac_Vertical_App
//
CUTS_Dmac_Vertical_App::~CUTS_Dmac_Vertical_App (void)
{

}

//
// run_main
//
int CUTS_Dmac_Vertical_App::run_main (int argc, char * argv [])
{

  if (this->parse_args (argc, argv) == -1)
      return -1;

  // open the database

  CUTS_Test_Database testdata;

  if (!testdata.open (this->input_file_))
    ACE_ERROR_RETURN ((LM_ERROR,
                    ACE_TEXT ("%T (%t) - %M - failed to open %s\n"),
                    input_file_.c_str()),
                    -1);

  // Create the query
  ADBC::SQLite::Query * query = testdata.create_query ();

  CUTS_Auto_Functor_T <ADBC::SQLite::Query> auto_clean (
    query, &ADBC::SQLite::Query::destroy);

  ADBC::SQLite::Record * record = &query->execute (
    "SELECT * FROM cuts_logging ORDER BY lid");

  char message[1024];
  int count = 1;

  // Tokenize thr trace and convert to vertical data format

  CUTS_DMAC_UTILS::sequence_details word_index;
  vertical_list_t vertical_list;
  std::set <std::string> word_list;
  std::set <std::string>::iterator it1;

  const std::string delim = " \n-<>";

  for ( ; !record->done (); record->advance ())
  {
      // Get the message from the row.
    record->get_data (5, message, sizeof (message));
    std::string row (message);

    CUTS_Dmac_Vertical_Format * format =
        new CUTS_Dmac_Vertical_Format ();

    this->tokenize (row, word_list, delim, format);

    format->tid (count);
    vertical_list.push_back (format);
    count++;
  }

  record->reset ();

  int number = 1;

  // print the vertical list

  for (it1 = word_list.begin (); it1 != word_list.end (); it1++)
  {
    word_index.insert (std::pair <std::string, int> (*it1, number));
    number++;
  }

  v_iter it2;
  for (it2 = vertical_list.begin (); it2 != vertical_list.end (); it2++)
  {
    ((CUTS_Dmac_Vertical_Format *)(*it2))->populate (word_index);
    ((CUTS_Dmac_Vertical_Format *)(*it2))->print_row_words ();
  }

  return 1;

}

//
// print_help
//
void CUTS_Dmac_Vertical_App::print_help (void)
{
  std::cerr << __HELP__ << std::endl;
  ACE_OS::exit (0);
}


//
// parse arguments
//
int CUTS_Dmac_Vertical_App::parse_args (int argc, char * argv [])
{
  const char * optstr = "hf:";

  ACE_Get_Opt get_opt (argc, argv, optstr);

  get_opt.long_option ("file", 'f', ACE_Get_Opt::ARG_REQUIRED);
  get_opt.long_option ("help", 'h');

  char ch;

  while ((ch = get_opt ()) != EOF)
  {
    switch (ch)
    {
    case 0:
      if (ACE_OS::strcmp (get_opt.long_option (), "file") == 0)
      {
        this->input_file_ = get_opt.opt_arg ();
      }
      else if (ACE_OS::strcmp (get_opt.long_option (), "help") == 0)
      {
        this->print_help ();
      }
      break;

    case 'f':
      this->input_file_ = get_opt.opt_arg ();
      break;

    case 'h':
      this->print_help ();
      break;

    }
  }
  return 0;
}

//
// tokenize
//
void CUTS_Dmac_Vertical_App::tokenize (
                 const std::string & str,
                 std::set<std::string> & tokens,
                 const std::string & delimiters,
                 CUTS_Dmac_Vertical_Format * format)
{
    // Skip delimiters at beginning.
    std::string::size_type lastPos = str.find_first_not_of (delimiters, 0);
    // Find first "non-delimiter".
    std::string::size_type pos = str.find_first_of (delimiters, lastPos);

    while (std::string::npos != pos || std::string::npos != lastPos)
    {
      tokens.insert (str.substr (lastPos, pos - lastPos));
      format->insert_word (str.substr (lastPos, pos - lastPos));

      // Skip delimiters.  Note the "not_of"
      lastPos = str.find_first_not_of (delimiters, pos);
      // Find next "non-delimiter"
      pos = str.find_first_of (delimiters, lastPos);
    }
}