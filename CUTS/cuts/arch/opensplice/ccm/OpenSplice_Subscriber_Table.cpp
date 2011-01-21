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
configure (::DDS::Publisher_ptr publisher)
{
  this->publisher_ = ::DDS::Publisher::_duplicate (publisher);
}
