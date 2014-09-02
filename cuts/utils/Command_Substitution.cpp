// $Id$

#include "Command_Substitution.h"

#if !defined (__CUTS_INLINE__)
#include "Command_Substitution.inl"
#endif

#include <sstream>

//
// evaluate
//
bool CUTS_Command_Substitution::
evaluate (const char * str, ACE_CString & result)
{
  std::string ostr;
  CUTS_Command_Substitution_Grammar <const char *> grammar;

  const char * begin (str);
  const char * end (begin + ACE_OS::strlen (begin));

  bool retval = boost::spirit::qi::phrase_parse (begin,
                                                 end,
                                                 grammar (&ostr),
                                                 boost::spirit::qi::space);

  if (retval)
    result = ostr.c_str ();

  return retval;
}
