// $Id$

#include "RTIDDS_Subscriber_Table.h"

//
// CUTS_RTIDDS_CCM_Subscriber_Table
//
CUTS_RTIDDS_CCM_Subscriber_Table::
CUTS_RTIDDS_CCM_Subscriber_Table (void)
{

}

//
// ~CUTS_RTIDDS_CCM_Subscriber_Table
//
CUTS_RTIDDS_CCM_Subscriber_Table::
~CUTS_RTIDDS_CCM_Subscriber_Table (void)
{

}

//
// configure
//
void CUTS_RTIDDS_CCM_Subscriber_Table::
configure (::DDSDomainParticipant * participant)
{
  this->participant_ = participant;
}
