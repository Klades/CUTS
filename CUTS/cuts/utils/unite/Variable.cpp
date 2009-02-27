// $Id$

#include "Variable.h"

#if !defined (__CUTS_INLINE__)
#include "Variable.inl"
#endif

#include <sstream>

///////////////////////////////////////////////////////////////////////////////
// class CUTS_Integer_Log_Format_Variable

//
// CUTS_Integer_Log_Format_Variable
//
void CUTS_Integer_Log_Format_Variable::
value (const char * begin, const char * end)
{
  std::string temp (begin, end);
  std::istringstream istr (temp);

  istr >> this->value_;
}
