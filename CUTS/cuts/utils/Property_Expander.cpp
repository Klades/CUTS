// $Id$

#include "Property_Expander.h"

//
// CUTS_Property_Expander
//
CUTS_Property_Expander::
CUTS_Property_Expander (const CUTS_Property_Map & map)
: prop_map_ (map)
{

}

//
// ~CUTS_Property_Expander
//
CUTS_Property_Expander::~CUTS_Property_Expander (void)
{

}

//
// expand
//
int CUTS_Property_Expander::
expand (const char * str, bool use_env, std::ostream & out)
{
  CUTS_Property_Expander_Grammar grammar (this->prop_map_, use_env, out);

  boost::spirit::parse_info < > info =
    boost::spirit::parse (str, grammar);

  return info.full ? 0 : -1;
}
