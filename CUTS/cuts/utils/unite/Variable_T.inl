// -*- C++ -*-
// $Id$

//
// CUTS_Basic_Log_Format_Variable_T
//
template <typename T>
CUTS_INLINE
CUTS_Basic_Log_Format_Variable_T <T>::
CUTS_Basic_Log_Format_Variable_T (size_t index)
: CUTS_Log_Format_Variable (CUTS_Log_Format_Variable_Type_T <T>::result_type, index)
{

}

//
// CUTS_Basic_Log_Format_Variable_T
//
template <typename T>
CUTS_INLINE
CUTS_Basic_Log_Format_Variable_T <T>::~CUTS_Basic_Log_Format_Variable_T (void)
{

}

//
// bind
//
template <typename T>
CUTS_INLINE
void CUTS_Basic_Log_Format_Variable_T <T>::bind (ADBC::SQLite::Parameter & param)
{
  param.bind (&this->value_);
}