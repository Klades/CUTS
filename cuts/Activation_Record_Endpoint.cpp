// $Id$

#include "cuts/Activation_Record_Endpoint.h"

#if !defined (__CUTS_INLINE__)
#include "cuts/Activation_Record_Endpoint.inl"
#endif

//
// operator =
//
const CUTS_Activation_Record_Endpoint &
CUTS_Activation_Record_Endpoint::
operator = (const CUTS_Activation_Record_Endpoint & rhs)
{
  this->set (rhs.id_, rhs.toc_, rhs.data_size_);
  return *this;
}

//
// set
//
void CUTS_Activation_Record_Endpoint::
set (int id, const ACE_Time_Value & toc, size_t data_size)
{
  this->id_ = id;
  this->CUTS_Endpoint_Data::set (toc, data_size);
}
