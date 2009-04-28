// $Id$

#if !defined (__CUTS_INLINE__)
#include "Config_List_Parser_T.inl"
#endif

#include "boost/spirit/core.hpp"
#include "boost/spirit/utility/lists.hpp"
#include "boost/spirit/iterator/file_iterator.hpp"
#include "ace/Log_Msg.h"

//
// parse
//
template <typename ACTOR>
bool CUTS_Config_List_Parser_T <ACTOR>::parse (const char * filename)
{
  // Find the start of the file.
  typedef boost::spirit::file_iterator <char> iterator_t;
  iterator_t begin (filename);

  if (!begin)
    return false;

  // Find the end of the file.
  iterator_t end = begin.make_end ();

  // Parse the configuration file.
  boost::spirit::parse_info <iterator_t> info =
    boost::spirit::parse (begin, end, this->grammar_, boost::spirit::space_p);

  return info.full;
}
