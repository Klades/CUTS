// $Id$

#include "OpenSplice_Subscriber_Table.h"

//
// CUTS_OpenSplice_CCM_Subscriber_Table
//
CUTS_OpenSplice_CCM_Subscriber_Table::
CUTS_OpenSplice_CCM_Subscriber_Table (void)
{
  
}

//
// ~CUTS_OpenSplice_CCM_Subscriber_Table
//
CUTS_OpenSplice_CCM_Subscriber_Table::
~CUTS_OpenSplice_CCM_Subscriber_Table (void)
{

}

//
// configure
//
void CUTS_OpenSplice_CCM_Subscriber_Table::
configure (::DDS::DomainParticipant_ptr participant)
{
  this->participant_ = ::DDS::DomainParticipant::_duplicate (participant);
}
