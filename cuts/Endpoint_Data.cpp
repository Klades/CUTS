// $Id$

#include "cuts/Endpoint_Data.h"

#if !defined (__CUTS_INLINE__)
#include "cuts/Endpoint_Data.inl"
#endif

//
// zero
//
const CUTS_Endpoint_Data CUTS_Endpoint_Data::zero;

//
// operator =
//
const CUTS_Endpoint_Data & CUTS_Endpoint_Data::
operator = (const CUTS_Endpoint_Data & rhs)
{
  this->set (rhs.toc_, rhs.data_size_);
  return *this;
}

//
// operator +=
//
const CUTS_Endpoint_Data &
CUTS_Endpoint_Data::operator += (const CUTS_Endpoint_Data & rhs)
{
  this->data_size_ += rhs.data_size_;
  this->toc_ += rhs.toc_;
  return *this;
}

//
// operator /
//
CUTS_Endpoint_Data operator / (const CUTS_Endpoint_Data & data, double d)
{
  ACE_Time_Value tmp_tv (data.time_of_completion ());
  tmp_tv *= (1.0 / d);

  size_t tmp_size =
    static_cast <size_t> (static_cast <double> (data.data_size ()) / d);

  return CUTS_Endpoint_Data (tmp_tv, tmp_size);
}
