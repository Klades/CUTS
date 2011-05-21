#include <iostream>
#include "Dmac_Sequence.h"

#if !defined (__CUTS_INLINE__)
#include "Dmac_Sequence.inl"
#endif


//
// populate_items
//
void CUTS_Dmac_Sequence::populate_items (CUTS_DMAC_UTILS::string_vector & raw_sequence)
{
  // Add position details for each sequence items/

  CUTS_DMAC_UTILS::s_iter it;

  for (it = raw_sequence.begin (); it != raw_sequence.end (); it++)
    this->key_position_table_.insert (std::pair <std::string, int>(*it, -1));
}

//
// add_row_id
//
void CUTS_Dmac_Sequence::add_row_id (int id)
{
  this->row_ids_.push_back (id);
}

//
// valid_pattern
//
bool CUTS_Dmac_Sequence::valid_pattern (CUTS_DMAC_UTILS::string_vector & trace,
                                        int row_id)
{
  // check whether the sequence is contained in the same
  // positions of each log message they contain

  if (this->check_positions (trace))
  {
    if(this->add_row_)
    {
      this->add_row_id (row_id);
      this->row_count_ = this->row_count_ + 1;

      if (trace.size () > this->max_row_words_)
        this->max_row_words_ = trace.size ();
    }
  }
  else
  {
    return false;
    trace.clear ();
  }

  trace.clear ();
  return true;
}


//
// position_already_updated
//
bool CUTS_Dmac_Sequence::position_already_updated ()
{
  // Check whether the position information is already
  // found for this sequence

  CUTS_DMAC_UTILS::sequence_details_iter it;

  for (it = this->key_position_table_.begin ();
        it != this->key_position_table_.end (); it++)
  {
    if ((*it).second == -1)
      return false;
  }
  return true;
}

//
// check_subset
//
bool CUTS_Dmac_Sequence::check_subset (CUTS_DMAC_UTILS::string_vector & trace)
{
  CUTS_DMAC_UTILS::sequence_details_iter it1;
  CUTS_DMAC_UTILS::s_iter it2;

  // The sequence should be a subset in the log message
  // inorder for it to be qualified.

  bool match = false;

  for (it1 = this->key_position_table_.begin ();
        it1 != this->key_position_table_.end (); it1++)
  {
    for (it2 = trace.begin (); it2 != trace.end (); it2++)
    {
      match = false;
      if ((*it1).first.compare (*it2) == 0)
      {
        match = true;
        break;
      }
    }
    if (!match)
      return match;
  }
  return true;
}

//
// check_positions
//
bool CUTS_Dmac_Sequence::check_positions (CUTS_DMAC_UTILS::string_vector & trace)
{
  bool move_further = true;

  // We move forward only if the sequence is a subset and
  // it is not already added.

  if (this->check_subset (trace))
  {
    if (!position_already_updated ())
    {
      CUTS_DMAC_UTILS::sequence_details_iter it1;
      CUTS_DMAC_UTILS::s_iter it2;

      // Compare the positions of the items in the sequences
      // with the posiitons of the items in the trace.
      for (it1 = this->key_position_table_.begin ();
           it1 != this->key_position_table_.end (); it1++)
      {
        int i = 0;
        for (it2 = trace.begin (); it2 != trace.end (); it2++)
        {
          if ((*it1).first.compare (*it2) == 0)
          {
            (*it1).second = i;
            break;
          }
          i++;
        }
      }
      this->add_row_ = true;
      return true;
    }
    else
    {
      CUTS_DMAC_UTILS::sequence_details_iter it1;
      CUTS_DMAC_UTILS::s_iter it2;

      // If the posiiton of the sequence is already added then
      // newly found sequence should match with the
      // already added one. If any mismacth found then
      // discard this sequence

      for (it1 = this->key_position_table_.begin ();
        it1 != this->key_position_table_.end (); it1++)
      {
        if (!move_further)
          return false;

        int i = 0;
        for (it2 = trace.begin (); it2 != trace.end (); it2++)
        {
          move_further = false;
          if ((*it1).first.compare (*it2) == 0)
          {
            if (i == ((*it1).second))
              move_further = true;

            else
              move_further = false;

            break;
          }
          i++;
        }
      }
    }
    this->add_row_ = true;
    return move_further;
  }
  else
  {
    this->add_row_ = false;
    return true;
  }
}

//
// match_row_set
//
bool CUTS_Dmac_Sequence::match_row_set (CUTS_Dmac_Sequence & sequence)
{
  // Check whether the two sequences are contained in the same
  // set of messages.

  unsigned int i;
  CUTS_DMAC_UTILS::int_vector::size_type size1 = this->row_ids_.size ();
  CUTS_DMAC_UTILS::int_vector::size_type size2 = sequence.row_ids_.size ();

  // They should be equal in size, inorder them to be qualified.
  if (size1 != size2)
    return false;

  // If the sizes are same the message ids should be the same.
  for (i=0; i < size1; i++)
  {
    if (this->row_ids_[i] != sequence.row_ids_[i])
      return false;
  }
  return true;

}

//
// print_pattern
//
void CUTS_Dmac_Sequence::print_pattern ()
{
  CUTS_DMAC_UTILS::sequence_details_iter it1;
  CUTS_DMAC_UTILS::i_iter it2;

  for (it1 = this->key_position_table_.begin ();
       it1 != this->key_position_table_.end (); it1++)
    std::cout <<(*it1).first << " "<<(*it1).second << std::endl;

  std::cout << std::endl;
  std::cout << "Rows: ";

  for (it2 = this->row_ids_.begin ();
       it2 != this->row_ids_.end ();
       it2++)
    std::cout << (*it2) << " ";

  std::cout << std::endl;
  std::cout << "Num rows: " << this->row_count_ << std::endl;
}