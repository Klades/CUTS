// $Id: Dmac_Utils.h

#ifndef _CUTS_DMAC_UTILS_H_
#define _CUTS_DMAC_UTILS_H_

#include <vector>
#include <string>
#include <map>
#include <set>

class CUTS_Dmac_Log_Format;

namespace CUTS_DMAC_UTILS
{
  // Type definition for vector of strings
  typedef std::vector <std::string> string_vector;

  // Type definition for string vector iterator
  typedef string_vector::iterator s_iter;

  // Type definition for vector of integers
  typedef std::vector <int> int_vector;

  // Type definition for integer vector iterator
  typedef int_vector::iterator i_iter;

  // Type definition for a string-int map
  typedef std::map <std::string, int> sequence_details;

  // Type definition for a string-int map iterator
  typedef sequence_details::iterator sequence_details_iter;

  // Type definition for a vector of integer sets
  typedef std::vector <std::set <int> > intset_vector;

  // Type definiton for integer pair
  typedef std::pair <int, int> int_pair;

  // Given a string this will tokenize it and fill the vector
  void tokenize (const std::string & str,
                 CUTS_DMAC_UTILS::string_vector & tokens,
                 std::string & delimitters);

  // Check whether a log format matches a particular trace
  int match_log_format (CUTS_DMAC_UTILS::string_vector & trace_items,
                        std::vector <CUTS_Dmac_Log_Format *> & item_list,
                        bool is_rel_mine);

  // Check whether a given log format instance is belongs to a particular
  // log format.
  bool match_log_format (CUTS_DMAC_UTILS::string_vector & trace_items,
                         CUTS_DMAC_UTILS::string_vector & log_format);

  // Check whether small_set is a subsequence of large_set
  bool is_sub_sequence (CUTS_DMAC_UTILS::string_vector & large_set,
                        CUTS_DMAC_UTILS::string_vector & small_set);

  // check whether two integer vectors are similar
  bool is_similar (CUTS_DMAC_UTILS::int_vector & first,
                   CUTS_DMAC_UTILS::int_vector & second);

  // Remove new line characters from a string
  void remove_new_lines (std::string & str);

}

#endif  // !defined _CUTS_DMAC_UTILS_H_