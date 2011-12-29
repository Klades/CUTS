#include "Dmac_Log_File_Miner.h"

//
// CUTS_Dmac_Log_File_Miner
//
CUTS_Dmac_Log_File_Miner::CUTS_Dmac_Log_File_Miner (
    ACE_CString & pattern_file,
    ACE_CString & data_file,
    std::vector <CUTS_Dmac_Log_Format *> & found_items)
: CUTS_Dmac_Log_Miner (pattern_file, data_file, found_items)
{

}

//
// ~CUTS_Dmac_Log_File_Miner
//
CUTS_Dmac_Log_File_Miner::~CUTS_Dmac_Log_File_Miner (void)
{

}

//
// populate_candidates
//
void CUTS_Dmac_Log_File_Miner::populate_candidates (void)
{
  // Read the datafile and compare it with
  // static parts found.
  ifstream data_file;

  std::vector <CUTS_Dmac_Static_Part *>::iterator it;

  for (it = this->static_parts_.begin ();
       it != this->static_parts_.end (); it++)
  {
    data_file.open (this->data_file_.c_str ());
    data_file.seekg (0, ios::beg);
    if (data_file.is_open ())
    {
      while (data_file.good ())
      {
        CUTS_DMAC_UTILS::string_vector word_list;
        std::string row;
        getline (data_file, row);

        CUTS_DMAC_UTILS::tokenize (row, word_list, this->delims_);
        (*it)->find_positions (word_list);
      }
      data_file.close ();
    }
  }
}

//
// create_next_dataset
//
void CUTS_Dmac_Log_File_Miner::create_next_dataset (int round)
{
  ifstream data_file (this->data_file_.c_str ());

  std::stringstream output_file;
  std::ofstream output;
  output_file << (round + 1) << "-dataset";
  output.open (output_file.str ().c_str ());

  // Generate the next dataset for the mining process.
  // This will match log formats with the traces and prune
  // those messages which are instances of the already
  // found log formats

  if (data_file.is_open())
  {
    while (data_file.good ())
    {
      CUTS_DMAC_UTILS::string_vector trace_items;
      std::string message_str;

      getline (data_file, message_str);

      CUTS_DMAC_UTILS::tokenize (message_str, trace_items, this->delims_);

      if ((CUTS_DMAC_UTILS::match_log_format (
          trace_items, this->current_items_, false)) < 0)
      {
        output << message_str;
        if (data_file.good ())
          output << std::endl;
      }
    }
    data_file.close ();
    output.close ();
  }
}