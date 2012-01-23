// $Id$

#include "OpenSplice_Servant.h"

#if !defined (__CUTS_INLINE__)
#include "OpenSplice_Servant.inl"
#endif

namespace iCCM
{

//
// OpenSplice_Servant
//
OpenSplice_Servant::
OpenSplice_Servant (const char * name)
: Servant (name)
{
  // Create the participant for this servant.
  ::DDS::DomainParticipantFactory_var factory =
    ::DDS::DomainParticipantFactory::get_instance ();

  this->participant_ =
    factory->create_participant (0,
                                 PARTICIPANT_QOS_DEFAULT,
                                 0,
                                 ::DDS::ANY_STATUS);
}

}
