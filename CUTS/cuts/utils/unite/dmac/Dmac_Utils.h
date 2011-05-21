#ifndef _CUTS_DMAC_UTILS_H_
#define _CUTS_DMAC_UTILS_H_

#include <vector>
#include <string>
#include <map>
#include <set>

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
                 CUTS_DMAC_UTILS::string_vector & tokens);



}

#endif  // !defined _CUTS_DMAC_UTILS_H_