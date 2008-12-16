// $Id$

#include "Property_Expander.h"

///////////////////////////////////////////////////////////////////////////////
// class CUTS_Property_Expander

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
bool CUTS_Property_Expander::
expand (const char * str, bool use_env, std::ostream & out)
{
  CUTS_Property_Expander_i parser (this->prop_map_, use_env, out);

  boost::spirit::parse_info < > info =
    boost::spirit::parse (str, parser);

  return info.full;
}

///////////////////////////////////////////////////////////////////////////////
// class CUTS_Property_Expander_i

//
// CUTS_Property_Expander_i
//
CUTS_Property_Expander::CUTS_Property_Expander_i::
CUTS_Property_Expander_i (const CUTS_Property_Map & map,
                          bool use_env,
                          std::ostream & ostr)
  : ostr_ (ostr),
    use_env_ (use_env),
    prop_map_ (map)
{

}
