// $Id$

#include "Text_Variable_Importer.h"

#if !defined (__CUTS_INLINE__)
#include "Text_Variable_Importer.inl"
#endif

#include "cuts/utils/Property_Map.h"
#include "cuts/utils/Property_Parser.h"
#include "boost/spirit/iterator/file_iterator.hpp"

//
// handle_import
//
int CUTS_Text_Variable_Importer::
handle_import (const ACE_CString & location, CUTS_Property_Map & vars)
{
  // Open the file for parsing.
  boost::spirit::file_iterator <char> begin_iter (location.c_str ());

  if (begin_iter)
  {
    boost::spirit::file_iterator <char> end_iter = begin_iter.make_end ();

    CUTS_Property_Parser parser (vars);
    if (parser.parse (begin_iter, end_iter))
      return 0;

    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - failed to parse %s\n"),
                location.c_str ()));
  }
  else
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - failed to open %s\n"),
                location.c_str ()));


  return -1;
}
