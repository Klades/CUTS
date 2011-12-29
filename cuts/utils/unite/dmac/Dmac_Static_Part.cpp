#include "Dmac_Static_Part.h"

//
// CUTS_Dmac_Static_Part
//
CUTS_Dmac_Static_Part::CUTS_Dmac_Static_Part (void)
{

}

//
// ~CUTS_Dmac_Static_Part
//
CUTS_Dmac_Static_Part::~CUTS_Dmac_Static_Part (void)
{

}

//
// find_positions
//
void CUTS_Dmac_Static_Part::find_positions (
    CUTS_DMAC_UTILS::string_vector & message)
{
  // Assign the position values for the words of the static parts, based
  // on the log message data

  // First check whether the log format is a subsequence of a log message
  if (CUTS_DMAC_UTILS::is_sub_sequence (message, this->items_))
  {
    CUTS_DMAC_UTILS::int_vector positions;
    size_t j = 0;
    for (size_t i = 0; i < this->items_.size (); i++)
    {
      while (j < message.size ())
      {
        if (this->items_ [i] == message [j])
        {
          positions.push_back (j);
          j++;
          break;
        }
        else
          j++;
      }
    }

    bool add = true;

    for (size_t k = 0; k < this->position_lists_.size (); k++)
    {
      // Checks for duplicate positions vectors
      if (CUTS_DMAC_UTILS::is_similar (positions, this->position_lists_ [k]))
      {
        add = false;
        break;
      }
    }
    if (add)
    {
      // A new position vector so add it.

      this->position_lists_.push_back (positions);
      this->message_sizes_.push_back (message.size ());
    }
  }
}

//
// populate_items
//
void CUTS_Dmac_Static_Part::populate_items (
    CUTS_DMAC_UTILS::string_vector & items)
{
  CUTS_DMAC_UTILS::s_iter it;

  for (it = items.begin (); it != items.end (); it++)
    this->items_.push_back (*it);
}

//
// insert_log_format
//
void CUTS_Dmac_Static_Part::insert_log_format (
    std::vector <CUTS_Dmac_Log_Format *> & lf_list,
    int current_size)
{
  // Create a new log format using the static parts and
  // stores in the list

  size_t size = lf_list.size ();
  for (size_t i = 0; i < this->position_lists_.size (); i++)
  {
    std::string place_holder("{}");
    CUTS_DMAC_UTILS::string_vector final (this->message_sizes_ [i],
                                          place_holder);

    for (size_t j = 0; j < this->position_lists_ [i].size (); j++)
    {
      final.at (this->position_lists_ [i].at (j)) = this->items_.at (j);
    }
    // Id for the log format is created based on the current size of the
    // entire log format list and the current list

    size = size + 1;
    CUTS_Dmac_Log_Format * lf = new CUTS_Dmac_Log_Format (size + current_size, final);
    lf_list.push_back (lf);
  }
}