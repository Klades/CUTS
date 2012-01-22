#include "Dmac_Log_Database_Miner.h"
#include "cuts/Auto_Functor_T.h"

//
// CUTS_Dmac_Log_Database_Miner
//
CUTS_Dmac_Log_Database_Miner::CUTS_Dmac_Log_Database_Miner (
    ACE_CString & pattern_file,
    ACE_CString & data_file,
    std::vector <CUTS_Dmac_Log_Format *> & found_items,
    CUTS_Test_Database & testdata)
: CUTS_Dmac_Log_Miner (pattern_file, data_file, found_items),
  testdata_ (testdata)
{

}

//
// ~CUTS_Dmac_Log_Database_Miner
//
CUTS_Dmac_Log_Database_Miner::~CUTS_Dmac_Log_Database_Miner (void)
{

}


//
// populate_candidates
//
void CUTS_Dmac_Log_Database_Miner::populate_candidates (void)
{
  // Find the positions of the static parts of the log formats
  // by comparing them with the log messages

  ADBC::SQLite::Query * query = this->testdata_.create_query ();

  CUTS_Auto_Functor_T <ADBC::SQLite::Query> auto_clean (
    query, &ADBC::SQLite::Query::destroy);

  ADBC::SQLite::Record * record = &query->execute (
    "SELECT * FROM cuts_logging ORDER BY lid");

  int j = 0;
  std::vector <CUTS_Dmac_Static_Part *>::iterator it;

  for (it = this->static_parts_.begin ();
       it != this->static_parts_.end (); it++)
  {
    char message[10000];
    for ( ; !record->done (); record->advance ())
    {
      // Get the message from the row.
      CUTS_DMAC_UTILS::string_vector word_list;
      record->get_data (5, message, sizeof (message));
      std::string row (message);

      CUTS_DMAC_UTILS::tokenize (row, word_list, this->delims_);
      (*it)->find_positions (word_list);

    }
    record->reset ();
  }
}


//
// create_next_dataset
//
void CUTS_Dmac_Log_Database_Miner::create_next_dataset (int round)
{

  // Create the dataset for the next iteration.

  ADBC::SQLite::Query * query = this->testdata_.create_query ();

  CUTS_Auto_Functor_T <ADBC::SQLite::Query> auto_clean (
    query, &ADBC::SQLite::Query::destroy);

  ADBC::SQLite::Record * record =
    &query->execute ("SELECT * FROM cuts_logging ORDER BY lid");

  char message [10000];

  std::stringstream output_file;
  std::ofstream output;
  output_file << (round + 1) << "-dataset";
  output.open (output_file.str ().c_str ());

  while(!record->done ())
  {
    // Get the message

    CUTS_DMAC_UTILS::string_vector trace_items;

    record->get_data (5, message, sizeof (message));

    std::string message_str (message);

    // Tokenize
    CUTS_DMAC_UTILS::tokenize (message_str, trace_items, this->delims_);

    // Compare it with the log formats
    record->advance ();
    if ((CUTS_DMAC_UTILS::match_log_format (trace_items, this->current_items_, false)) < 0 )
    {
      // Save the non-matching messages for the next iteration
      CUTS_DMAC_UTILS::remove_new_lines (message_str);

      output << message_str;
      if (!record->done ())
        output << std::endl;
    }
  }

  record->reset ();
  output.close ();

}