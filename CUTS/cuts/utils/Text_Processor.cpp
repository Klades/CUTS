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
bool CUTS_Text_Processor::evaluate (const char * str,
                                    ACE_CString & output,
                                    bool use_env,
                                    bool ignore_variables,
                                    bool ignore_commands)
{
  // First, expand the properties in the string.
  this->property_eval_.config ().use_env_ = true;

  if (!this->property_eval_.evaluate (str))
    return false;

  // The second pass will substitute all the commands in the string. We
  // can just store the result in the <output>
  return this->command_sub_.evaluate (this->buffer_.str ().c_str (), output);
}
