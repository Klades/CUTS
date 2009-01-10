// $Id$

#include "Template_Config_List_Parser.h"

#if !defined (__CUTS_INLINE__)
#include "Template_Config_List_Parser.inl"
#endif

#include "boost/spirit/core.hpp"
#include "boost/spirit/utility/lists.hpp"
#include "boost/spirit/iterator/file_iterator.hpp"
#include "ace/Log_Msg.h"

///////////////////////////////////////////////////////////////////////////////
// class CUTS_Template_Config_List_Parser_Grammar

//
// CUTS_Template_Config_List_Parser_Grammar
//
CUTS_Template_Config_List_Parser_Grammar::
CUTS_Template_Config_List_Parser_Grammar (const ACE_CString & template_file,
                                          const ACE_CString & output_dir,
                                          const CUTS_Property_Map & overrides)
: template_file_ (template_file),
  output_dir_ (output_dir),
  overrides_ (overrides)
{

}

//
// ~CUTS_Template_Config_List_Parser_Grammar
//
CUTS_Template_Config_List_Parser_Grammar::
~CUTS_Template_Config_List_Parser_Grammar (void)
{

}

///////////////////////////////////////////////////////////////////////////////
// class CUTS_Template_Config_List_Parser

//
// CUTS_Template_Config_List_Parser
//
CUTS_Template_Config_List_Parser::
CUTS_Template_Config_List_Parser (const ACE_CString & template_file,
                                  const ACE_CString & output_dir,
                                  const CUTS_Property_Map & overrides)
: grammar_ (template_file, output_dir, overrides)
{

}

//
// parse
//
bool CUTS_Template_Config_List_Parser::parse (const char * filename)
{
  // Find the start of the file.
  typedef boost::spirit::file_iterator <char> iterator_t;
  iterator_t begin (filename);

  if (begin)
  {
    // Find the end of the file.
    iterator_t end = begin.make_end ();

    // Parse the configuration file.
    boost::spirit::parse_info <iterator_t> info =
      boost::spirit::parse (begin, end, this->grammar_, boost::spirit::space_p);

    return info.full;
  }
  else
  {
    ACE_ERROR ((LM_ERROR,
                "%T (%t) - %M - failed to open file %s for reading\n",
                filename));
  }

  return false;
}
