// $Id$

#include "Command_Substitution.h"

#if !defined (__CUTS_INLINE__)
#include "Command_Substitution.inl"
#endif

#include <sstream>

//
// evaluate
//
int CUTS_Command_Substitution::
evaluate (const char * str, ACE_CString & result)
{
  std::ostringstream ostr;
  CUTS_Command_Substitution_Grammar grammar (ostr);

  boost::spirit::parse_info < > info =
    boost::spirit::parse (str, grammar >> !boost::spirit::end_p);

  if (info.full)
    result = ostr.str ().c_str ();

  return info.full ? 0 : -1;
}
