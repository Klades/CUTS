// -*- C++ -*-
// $Id$

//
// CUTS_Timestamp_Metric
//
CUTS_INLINE
CUTS_Timestamp_Metric::CUTS_Timestamp_Metric (void)
: timestamp_ (ACE_Time_Value::zero)
{

}

//
// CUTS_Timestamp_Metric
//
CUTS_INLINE
CUTS_Timestamp_Metric::CUTS_Timestamp_Metric (const CUTS_Timestamp_Metric & tm)
  : timestamp_ (tm.timestamp_)
{

}

//
// CUTS_Timestamp_Metric
//
CUTS_INLINE
CUTS_Timestamp_Metric::CUTS_Timestamp_Metric (const ACE_Time_Value & tv)
: timestamp_ (tv)
{

}

//
// ~CUTS_Timestamp_Metric
//
CUTS_INLINE
CUTS_Timestamp_Metric::~CUTS_Timestamp_Metric (void)
{

}

//
// timestamp
//
CUTS_INLINE
const ACE_Time_Value & CUTS_Timestamp_Metric::timestamp (void) const
{
  return this->timestamp_;
}

//
// timestamp
//
CUTS_INLINE
void CUTS_Timestamp_Metric::timestamp (const ACE_Time_Value & tv)
{
  this->timestamp_ = tv;
}

//
// is_valid
//
CUTS_INLINE
bool CUTS_Timestamp_Metric::is_valid (void) const
{
  return this->timestamp_ != ACE_Time_Value::zero;
}

//
// operator =
//
CUTS_INLINE
const CUTS_Timestamp_Metric & CUTS_Timestamp_Metric::
operator = (const CUTS_Timestamp_Metric & rhs)
{
  this->timestamp_ = rhs.timestamp_;
  return *this;
}
