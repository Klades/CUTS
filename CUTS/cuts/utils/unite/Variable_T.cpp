// $Id$

#if !defined (__CUTS_INLINE__)
#include "Variable_T.inl"
#endif

#include "ace/Log_Msg.h"
#include "ace/streams.h"
#include <sstream>

//
// CUTS_Basic_Log_Format_Variable_T
//
template <typename T>
void CUTS_Basic_Log_Format_Variable_T <T>::
value (const char * begin, const char * end)
{
  std::string temp (begin, end);
  std::istringstream istr (temp);

  istr >> this->value_;
}

template <typename T>
void CUTS_Basic_Log_Format_Variable_T <T>::
set_value (char *val)
{
	std::string temp(val);
	std::istringstream istr(temp);
	istr >> this->value_;
}


template <typename T>
void CUTS_Basic_Log_Format_Variable_T <T>::
value(T val)
{
	this->value_ = val;
}	

