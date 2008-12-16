// $Id$

#include "Property_Parser.h"

///////////////////////////////////////////////////////////////////////////////
// class CUTS_Property_Parser_i

//
// CUTS_Property_Parser_i
//
CUTS_Property_Parser::
CUTS_Property_Parser_i::CUTS_Property_Parser_i (CUTS_Property_Map & map)
: prop_map_ (map)
{

}

///////////////////////////////////////////////////////////////////////////////
// class CUTS_Property_Parser

//
// CUTS_Property_Parser
//
CUTS_Property_Parser::
CUTS_Property_Parser (CUTS_Property_Map & map)
: prop_map_ (map)
{

}

//
// ~CUTS_Property_Parser
//
CUTS_Property_Parser::~CUTS_Property_Parser (void)
{

}

//
// parse
//
bool CUTS_Property_Parser::parse (const char * str)
{
  CUTS_Property_Parser_i parser (this->prop_map_);

  boost::spirit::parse_info < > info =
    boost::spirit::parse (str, parser, boost::spirit::space_p);

  return info.full;
}
