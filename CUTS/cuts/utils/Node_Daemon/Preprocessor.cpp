// $Id$

#include "Preprocessor.h"
#include "ace/Log_Msg.h"
#include "ace/SString.h"

//
// CUTS_Text_Preprocessor
//
CUTS_Text_Preprocessor::
CUTS_Text_Preprocessor (const CUTS_Property_Map & map)
: variable_sub_ (map)
{

}

//
// ~CUTS_Text_Preprocessor
//
CUTS_Text_Preprocessor::~CUTS_Text_Preprocessor (void)
{

}

//
// evaluate
//
int CUTS_Text_Preprocessor::
evaluate (const char * str, ACE_CString & output)
{
  int retval = 0;

  // The first pass of the preprocessor will expand all variables
  // in the string.
  ACE_CString pass1;

  if (!this->variable_sub_.expand (str, pass1))
  {
    ACE_ERROR ((LM_WARNING,
                "%T - %M - failed to expand environment variables\n"));

    ++ retval;
  }

  // The second pass will substitute all the commands in the string. We
  // can just store the result in the <output>
  if (!this->command_sub_.evaluate (pass1.c_str (), output))
  {
    ACE_ERROR ((LM_WARNING,
                "%T - %M - failed to substitute some of the commands\n"));

    ++ retval;
  }

  // Return the number of errors.
  return retval;
}
