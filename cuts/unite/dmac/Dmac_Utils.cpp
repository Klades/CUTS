#include "Dmac_Utils.h"
#include "Dmac_Log_Format.h"

//
// tokenize
//
void CUTS_DMAC_UTILS::tokenize (const std::string & str,
                                CUTS_DMAC_UTILS::string_vector & tokens,
                                std::string & delimiters)
{
 // Skip delimiters at beginning.
  std::string::size_type lastPos = str.find_first_not_of (delimiters, 0);
  // Find first "non-delimiter".
  std::string::size_type pos = str.find_first_of (delimiters, lastPos);

  while (std::string::npos != pos || std::string::npos != lastPos)
  {
    std::string item = str.substr (lastPos, pos - lastPos);
    tokens.push_back (item);

    lastPos = str.find_first_not_of (delimiters, pos);
    // Find next "non-delimiter"
    pos = str.find_first_of (delimiters, lastPos);
  }
}

//
// match_log_format
//
int CUTS_DMAC_UTILS::match_log_format (CUTS_DMAC_UTILS::string_vector & trace_items,
                                       std::vector <CUTS_Dmac_Log_Format *> & item_list,
                                       bool is_rel_mine)
{
  std::string empty_str ("{}");
  int matching_format = -1;

  for (unsigned int i = 0; i < item_list.size (); i++)
  {
    // Staic parts should be matched and if it is a mismatch
    // the log format should have a {} in the corrsponding
    // item for continue the matching
    CUTS_DMAC_UTILS::string_vector & log_format =
        item_list [i]->log_format_items ();

    if (trace_items.size () == log_format.size ())
    {
      for (unsigned int j = 0; j < log_format.size (); j++)
      {
        if (log_format [j].compare (empty_str) != 0)
        {
          if (log_format [j].compare (trace_items [j]) != 0)
          {
            matching_format = -1;
            break;
          }
          else
            matching_format = item_list [i]->id ();
        }
      }

      // For each matching log message incrment the coverage
      // value for this log format.

      if (matching_format >= 0)
      {
        // During the relation mining we don't need to increment the
        // coverage because it was done in the iterative mining step
        if (!is_rel_mine)
        {
          item_list [i]->increment_coverage ();
          item_list [i]->add_varaible_values (trace_items);
        }
        break;
      }
    }
  }

  return matching_format;
}

bool CUTS_DMAC_UTILS::
match_log_format (CUTS_DMAC_UTILS::string_vector & trace_items,
                  CUTS_DMAC_UTILS::string_vector & log_format)
{
  std::string empty_str ("{}");

  // Staic parts should be matched and if it is a mismatch
  // the log format should have a {} in the corrsponding
  // item for continue the matching

  if (trace_items.size () == log_format.size ())
  {
    for (unsigned int j = 0; j < log_format.size (); j++)
    {
      if (log_format [j].compare (empty_str) != 0)
      {
        if (log_format [j].compare (trace_items [j]) != 0)
        {
          return false;
        }
      }
    }
    return true;
  }
  else
    return false;
}

//
// is_sub_sequence
//
bool CUTS_DMAC_UTILS::is_sub_sequence (CUTS_DMAC_UTILS::string_vector & large_seq,
                                       CUTS_DMAC_UTILS::string_vector & small_seq)
{
  size_t j = 0;
  size_t large_size = large_seq.size ();
  size_t small_size = small_seq.size ();
  bool found = true;

  // Checks whether the small sequence is a
  // subsequence of the larger sequence

  for (size_t i = 0; i < small_size; i++)
  {
    while (j < large_size)
    {
      if (small_seq [i] == large_seq [j])
      {
        j++;
        break;
      }
      j++;

      if (j == large_size)
        found = false;
    }
  }

  return found;
}

//
// is_similar
//
bool CUTS_DMAC_UTILS::is_similar (CUTS_DMAC_UTILS::int_vector & first,
                                  CUTS_DMAC_UTILS::int_vector & second)
{
  if (first.size () != second.size ())
    return false;

  for (size_t i = 0; i < first.size (); i++)
  {
    if (first [i] != second [i])
      return false;
  }
  return true;
}

//
// remove_new_lines
//
void CUTS_DMAC_UTILS::remove_new_lines (std::string & str)
{
  size_t found = str.find('\n');

  while (found != std::string::npos)
  {
    std::string::iterator it;
    it = str.begin () + found;
    str.replace (it, it+1, 1, ' ');
    found = str.find('\n');
  }
}

//
// compare_date_time
//
bool CUTS_DMAC_UTILS::
compare_date_time (ACE_Date_Time & date_time1,
                   ACE_Date_Time & date_time2)
{
  long year1 = date_time1.year ();
  long year2 = date_time2.year ();
  long month1 = date_time1.month ();
  long month2 = date_time2.month ();
  long day1 = date_time1.day ();
  long day2 = date_time2.day ();
  long hour1 = date_time1.hour ();
  long hour2 = date_time2.hour ();
  long min1 = date_time1.minute ();
  long min2 = date_time2.minute ();
  long sec1 = date_time1.second ();
  long sec2 = date_time2.second ();
  long msec1 = date_time1.microsec ();
  long msec2 = date_time2.microsec ();

  if (year1 == year2)
  {
    if (month1 == month2)
    {
      if (day1 == day2)
      {
        if (hour1 == hour2)
        {
          if (min1 == min2)
          {
            if (sec1 == sec2)
            {
              if ((msec1 == msec2) || (msec1 < msec2)) return false;
              else return true;
            }
            else if (sec1 > sec2) return true;
            else return false;
          }
          else if (min1 > min2) return true;
          else return false;
        }
        else if (hour1 > hour2) return true;
        else return false;
      }
      else if (day1 > day2) return true;
      else return false;
    }
    else if (month1 > month2) return true;
    else return false;
  }
  else if (year1 > year2) return true;
  else return false;
}

//
// get_seconds_since_1970
//
double CUTS_DMAC_UTILS::
get_seconds_since_1970 (ACE_Date_Time & date_time)
{
  long years = date_time.year () - 1970;
  long months = date_time.month () - 1;
  long days = date_time.day () - 1;
  long hours = date_time.hour () - 1;
  long mins = date_time.minute () - 1;
  long secs = date_time.second () -1;
  long msecs = date_time.microsec ();

  // Based on Unix epoch conversions

  long total = years * 31556926 +
               months * 2629743 +
               days * 86400 +
               hours * 3600 +
               mins * 60 +
               secs;

  double fraction = (double)msecs /(double) 1000000;

  return ((double)total + fraction);

}