#include "Dmac_Log_Miner.h"

//
// CUTS_Dmac_Log_Miner
//
CUTS_Dmac_Log_Miner::CUTS_Dmac_Log_Miner (
    ACE_CString & pattern_file,
    ACE_CString & data_file,
    std::vector <CUTS_Dmac_Log_Format *> & found_items)
: pattern_file_ (pattern_file),
  data_file_ (data_file),
  found_items_ (found_items)
{

}

//
// ~CUTS_Dmac_Log_Miner
//
CUTS_Dmac_Log_Miner::~CUTS_Dmac_Log_Miner ()
{

}

//
// delim
//
void CUTS_Dmac_Log_Miner::delim (std::string delims)
{
  this->delims_ = delims;
}



//
// refine
//
void CUTS_Dmac_Log_Miner::refine ()
{
  // Extract maximal-sequences from the already found
  // frequent-sequences

  ifstream pattern_file (this->pattern_file_.c_str ());
  std::vector <CUTS_DMAC_UTILS::string_vector> temp;

  // Read the sequence file and tokenize the sequences
  if (pattern_file.is_open())
  {
    while (pattern_file.good ())
    {
      std::vector <std::string> pattern_items;
      std::string pattern_str;
      getline (pattern_file, pattern_str);
      CUTS_DMAC_UTILS::tokenize (pattern_str,
                                 pattern_items,
                                 this->delims_);
      temp.push_back (pattern_items);
    }
    pattern_file.close ();
  }

  int remove_count = 0;

  do
  {
    if (temp.size () == 0)
      break;

    // Find the largest item
    std::vector <CUTS_DMAC_UTILS::string_vector>::iterator it;

    size_t max_size = 0;
    size_t max_index = 0;
    size_t index = 0;
    for (it = temp.begin (); it != temp.end (); it++)
    {
      if ((*it).size () > max_size)
      {
        max_size = (*it).size ();
        max_index = index;
      }
      index++;
    }

    // Create a new static part and populate it
    CUTS_DMAC_UTILS::string_vector current = temp.at (max_index);

    CUTS_Dmac_Static_Part * static_part = new CUTS_Dmac_Static_Part ();

    static_part->populate_items (current);

    this->static_parts_.push_back (static_part);
    this->refined_sequences_.push_back (current);

    // Keep on removing all the subsequences of the maximal
    // sequences

    temp.erase (temp.begin () + max_index);

    if (temp.size () > 0)
      remove_count = this->remove_redundant (temp, current);

  }while (remove_count != 0);

}


//
// mine
//
void CUTS_Dmac_Log_Miner::mine (void)
{
  // Populate the candidates first
  this->populate_candidates ();

  // We have the candidates, so create the log formats
  this->create_log_format_list ();
}

//
// create_log_format_list
//
void CUTS_Dmac_Log_Miner::create_log_format_list ()
{

  // For each static part, create a log format

  std::vector <CUTS_Dmac_Static_Part *>::iterator it;
  int current_size = this->found_items_.size ();

  for (it = this->static_parts_.begin ();
       it != this->static_parts_.end (); it++)
  {
    (*it)->insert_log_format (this->current_items_, current_size);
  }
}

//
// print_refined_sequences
//
void CUTS_Dmac_Log_Miner::print_refined_sequences ()
{
  std::vector <CUTS_DMAC_UTILS::string_vector>::iterator it;

  std::cout << "Refined sequences:" << std::endl;
  std::cout << "=================" << std::endl;

  for (it = this->refined_sequences_.begin ();
       it != this->refined_sequences_.end (); it++)
  {
    CUTS_DMAC_UTILS::s_iter it1;
    for (it1 = (*it).begin (); it1 != (*it).end (); it1++)
    {
      std::cout << (*it1) << " ";
    }
    std::cout << std::endl;
  }
}

//
// remove_redundant
//
int CUTS_Dmac_Log_Miner::remove_redundant (
    std::vector <CUTS_DMAC_UTILS::string_vector> & seq_list,
    CUTS_DMAC_UTILS::string_vector & selected_seq)
{

  // This implements the algorithm for removing the sub-sequences
  // of maximal sequences and pruning the dataset.

  CUTS_DMAC_UTILS::int_vector itemes_to_remove;

  std::vector <CUTS_DMAC_UTILS::string_vector>::iterator it;

  int i = 0;

  for (it = seq_list.begin (); it != seq_list.end (); it++)
  {
    if (CUTS_DMAC_UTILS::is_sub_sequence (selected_seq, (*it)))
    {
      itemes_to_remove.push_back (i);
    }
    i++;
  }

  // Keep on removing till there are items

  if (itemes_to_remove.size () > 0)
  {
    int count = 0;
    CUTS_DMAC_UTILS::i_iter it1;
    for (it1 = itemes_to_remove.begin ();
         it1 != itemes_to_remove.end (); it1++)
    {
      int x = (*it1) - count;
      seq_list.erase (seq_list.begin ()+ x);
      count++;
    }
  }

  return selected_seq.size ();
}

//
// current_items
//
std::vector <CUTS_Dmac_Log_Format *> & CUTS_Dmac_Log_Miner::current_items ()
{
  return this->current_items_;
}

//
// total_records
//
long CUTS_Dmac_Log_Miner::total_records ()
{
  return this->total_records_;
}

//
// total_records
//
void CUTS_Dmac_Log_Miner::total_records (long total)
{
  this->total_records_ = total;
}