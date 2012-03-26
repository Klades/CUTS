#include "ace/Get_Opt.h"
#include <iostream>
#include "cuts/utils/testing/Test_Database.h"
#include "ace/Log_Msg.h"
#include "adbc/SQLite/Connection.h"
#include "cuts/Auto_Functor_T.h"
#include "Dmac_Vertical_Generator.h"


//
// CUTS_Dmac_Vertical_Generator
//
CUTS_Dmac_Vertical_Generator::CUTS_Dmac_Vertical_Generator (
    std::string & delims)
: delims_ (delims)
{

}

//
// ~CUTS_Dmac_Vertical_Generator
//
CUTS_Dmac_Vertical_Generator::~CUTS_Dmac_Vertical_Generator (void)
{

}

//
// tokenize
//
void CUTS_Dmac_Vertical_Generator::tokenize (
                  const std::string & str,
                  std::set<std::string> & tokens,
                  std::string & delimiters,
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

//
// CUTS_Dmac_DB_Vertical_Generator
//
CUTS_Dmac_DB_Vertical_Generator::
CUTS_Dmac_DB_Vertical_Generator (std::string & delims)
: CUTS_Dmac_Vertical_Generator (delims)
{

}

//
// ~CUTS_Dmac_DB_Vertical_Generator
//
CUTS_Dmac_DB_Vertical_Generator::
~CUTS_Dmac_DB_Vertical_Generator ()
{

}

//
// generate
//
int CUTS_Dmac_DB_Vertical_Generator::
generate (ACE_CString & db_file, int round)
{
  CUTS_Test_Database testdata;

  if (!testdata.open (db_file))
    ACE_ERROR_RETURN ((LM_ERROR,
                    ACE_TEXT ("%T (%t) - %M - failed to open %s\n"),
                    db_file.c_str()),
                    -1);

  // Create the query
  ADBC::SQLite::Query * query = testdata.create_query ();

  CUTS_Auto_Functor_T <ADBC::SQLite::Query> auto_clean (
    query, &ADBC::SQLite::Query::destroy);

  ADBC::SQLite::Record * record = &query->execute (
    "SELECT * FROM cuts_logging ORDER BY lid");

  char message [10000];
  int count = 1;

  // Tokenize thr trace and convert to vertical data format

  CUTS_DMAC_UTILS::sequence_details word_index;
  CUTS_Dmac_Vertical_Generator::vertical_list_t vertical_list;
  std::set <std::string> word_list;
  std::set <std::string>::iterator it1;


  std::string delim (this->delims_.c_str ());

  for ( ; !record->done (); record->advance ())
  {
      // Get the message from the row.
    record->get_data (5, message, sizeof (message));
    std::string row (message);

    CUTS_Dmac_Vertical_Format * format =
        new CUTS_Dmac_Vertical_Format ();

    //CUTS_Dmac_Vertical_Generator::
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

  std::stringstream output_file;
  std::ofstream output;

  // The vvertical format needs to be stored in a file called with .data
  // extension.
  output_file << round << ".data";
  output.open (output_file.str ().c_str ());

  v_iter it2;
  for (it2 = vertical_list.begin (); it2 != vertical_list.end (); it2++)
  {
    ((CUTS_Dmac_Vertical_Format *)(*it2))->populate (word_index);
    ((CUTS_Dmac_Vertical_Format *)(*it2))->print_row_words (output);
  }

  output.close ();
  return 1;

}

//
// CUTS_Dmac_File_Vertical_Generator
//
CUTS_Dmac_File_Vertical_Generator::
CUTS_Dmac_File_Vertical_Generator (std::string & delims)
: CUTS_Dmac_Vertical_Generator (delims)
{

}

//
// ~CUTS_Dmac_File_Vertical_Generator
//
CUTS_Dmac_File_Vertical_Generator::
~CUTS_Dmac_File_Vertical_Generator ()
{

}

//
// generate
//
int CUTS_Dmac_File_Vertical_Generator::
generate (ACE_CString & db_file, int round)
{
  ifstream data_file (db_file.c_str ());
  this->row_count_ = 0;

  if (data_file.is_open())
  {
    CUTS_DMAC_UTILS::sequence_details word_index;
    vertical_list_t vertical_list;
    std::set <std::string> word_list;
    std::set <std::string>::iterator it1;


    std::string delim (this->delims_.c_str ());
    int count = 1;

    // Read line by line and tokenize
    while (data_file.good ())
    {
      std::string row;
      getline (data_file, row);

      CUTS_Dmac_Vertical_Format * format =
        new CUTS_Dmac_Vertical_Format ();

      this->tokenize (row, word_list, delim, format);
      format->tid (count);
      vertical_list.push_back (format);
      count++;
    }
    this->row_count_ = count - 1;

    int number = 1;

    // print the vertical list to the file
    for (it1 = word_list.begin (); it1 != word_list.end (); it1++)
    {
      word_index.insert (std::pair <std::string, int> (*it1, number));
      number++;
    }

    std::stringstream output_file;
    std::ofstream output;

    output_file << round << ".data";
    output.open (output_file.str ().c_str ());

    v_iter it2;
    for (it2 = vertical_list.begin (); it2 != vertical_list.end (); it2++)
    {
      ((CUTS_Dmac_Vertical_Format *)(*it2))->populate (word_index);
      ((CUTS_Dmac_Vertical_Format *)(*it2))->print_row_words (output);
    }
    output.close ();
    data_file.close ();

    return 1;
  }
  else
  {
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - failed to open %s\n"),
                       db_file.c_str ()),
                       -1);
  }
}