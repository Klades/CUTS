// $Id$

#include "OpenSplice.h"

#if !defined (__CUTS_INLINE__)
#include "OpenSplice.inl"
#endif

namespace iCCM
{

}

/**
 * QoS operators
 */
void operator <<= (::iCCM::OpenSplice::datareaderqos_type & out, const ::iCCM::OpenSplice::datareaderqos_type & in)
{
  out = in;
}

void operator <<= (::iCCM::OpenSplice::topicqos_type & out, const ::iCCM::OpenSplice::topicqos_type & in)
{
  out = in;
}
