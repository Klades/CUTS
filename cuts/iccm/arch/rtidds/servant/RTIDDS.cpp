// $Id$

#include "RTIDDS.h"

#if !defined (__CUTS_INLINE__)
#include "RTIDDS.inl"
#endif

namespace iCCM
{
  const unsigned long RTIDDS::ANY_SAMPLE_STATE = ::DDS_ANY_SAMPLE_STATE;
  const unsigned long RTIDDS::ANY_VIEW_STATE = ::DDS_ANY_VIEW_STATE;
  const unsigned long RTIDDS::ANY_INSTANCE_STATE = ::DDS_ANY_INSTANCE_STATE;

  const RTIDDS::instancehandle_type RTIDDS::HANDLE_NIL = ::DDS_HANDLE_NIL;

  const long RTIDDS::LENGTH_UNLIMITED = ::DDS_LENGTH_UNLIMITED;
}

/**
 * QoS operators
 */
void operator <<= (::iCCM::RTIDDS::datareaderqos_type & out, const ::iCCM::RTIDDS::datareaderqos_type & in)
{
  out = in;
}

void operator <<= (::iCCM::RTIDDS::topicqos_type & out, const ::iCCM::RTIDDS::topicqos_type & in)
{
  out = in;
}

