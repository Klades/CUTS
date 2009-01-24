// $Id$

#include "Text_Processor.h"

#if !defined (__CUTS_INLINE__)
#include "Text_Processor.inl"
#endif

#include "ace/SString.h"
#include <sstream>

//
// evaluate
//
int CUTS_Text_Processor::evaluate (const char * str,
                                   ACE_CString & output,
                                   bool use_env,
                                   bool ignore_variables,
                                   bool ignore_commands)
{
  int retval = 0;

  // The first pass of the preprocessor will expand all variables
  // in the string.
  std::ostringstream ostr;

  if (this->prop_expander_.expand (str, true, ostr) != 0)
  {
    ACE_ERROR ((LM_WARNING,
                "%T - %M - failed to expand environment variables\n"));

    ++ retval;
  }

  // The second pass will substitute all the commands in the string. We
  // can just store the result in the <output>
  if (this->command_sub_.evaluate (ostr.str ().c_str (), output) != 0)
  {
    ACE_ERROR ((LM_WARNING,
                "%T - %M - failed to substitute some of the commands\n"));

    ++ retval;
  }

  // Return the number of errors.
  return retval;
}
