// $Id$

#include "RTIDDS_Servant.h"

#if !defined (__CUTS_INLINE__)
#include "RTIDDS_Servant.inl"
#endif

namespace iCCM
{

//
// configure
//
void RTIDDS_Servant::configure (const ::iccm::DomainParticipantQos & value)
{
  // Perform the default configuration.
  this->do_default_configure ();

  // Finally, configure all the remaining ports/entities.
  this->configure ();
}


}
