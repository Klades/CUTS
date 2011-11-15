// $Id$

#include "cuts/Time_Measurement.h"

#if !defined (__CUTS_INLINE__)
#include "cuts/Time_Measurement.inl"
#endif

#include "cuts/Metrics_Visitor.h"
#include "ace/Numeric_Limits.h"

//
// accept
//
void CUTS_Time_Measurement::
accept (CUTS_Metrics_Visitor & visitor) const
{
  visitor.visit_time_measurement (*this);
}

//
// operator /
//
ACE_Time_Value
operator / (const ACE_Time_Value & tv, double d)
{
  // The floating type to be used in the computations.  It should be
  // large enough to hold a time_t.  We actually want a floating type
  // with enough digits in its mantissa to hold a time_t without
  // losing precision.  For example, if FLT_RADIX is 2 and
  // LDBL_MANT_DIG is 64, a long double has a 64 bit wide mantissa,
  // which would be sufficient to hold a 64 bit time_t value without
  // losing precision.
  //
  // For now we'll simply go with long double if it is larger than
  // time_t.  We're hosed if long double isn't large enough.
  typedef ACE::If_Then_Else<(sizeof (double) > sizeof (time_t)),
                            double,
                            long double>::result_type float_type;

  float_type time_total =
    (tv.sec ()
     + static_cast <float_type> (tv.usec ()) / ACE_ONE_SECOND_IN_USECS) / d;

  // shall we saturate the result?
  static const float_type max_int =
    ACE_Numeric_Limits<time_t>::max () + 0.999999;
  static const float_type min_int =
    ACE_Numeric_Limits<time_t>::min () - 0.999999;

  if (time_total > max_int)
    time_total = max_int;
  if (time_total < min_int)
    time_total = min_int;

  const time_t time_sec = static_cast<time_t> (time_total);

  time_total -= time_sec;
  time_total *= ACE_ONE_SECOND_IN_USECS;

  suseconds_t time_usec = static_cast<suseconds_t> (time_total);

  // round up the result to save the last usec
  if (time_usec > 0 && (time_total - time_usec) >= 0.5)
    ++time_usec;
  else if (time_usec < 0 && (time_total - time_usec) <= -0.5)
    --time_usec;

  ACE_Time_Value tv_result (time_sec, time_usec);
  return tv_result;
}
