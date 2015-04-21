// $Id$

#if !defined (__CUTS_INLINE__)
#include "Config_List_Parser_T.inl"
#endif

#include "boost/spirit/include/classic_core.hpp"
#include "boost/spirit/include/classic_lists.hpp"
#include "boost/spirit/include/classic_file_iterator.hpp"

//
// parse
//
template <typename ACTOR>
bool CUTS_Config_List_Parser_T <ACTOR>::parse (const char * filename)
{
  // Find the start of the file.
  typedef boost::spirit::classic::file_iterator <char> iterator_t;
  iterator_t begin (filename);

  if (!begin)
    return false;

  // Find the end of the file.
  iterator_t end = begin.make_end ();

  // Parse the configuration file.
  boost::spirit::classic::parse_info <iterator_t> info =
    boost::spirit::classic::parse (begin, end, this->grammar_, boost::spirit::classic::space_p);

  return info.full;
}
