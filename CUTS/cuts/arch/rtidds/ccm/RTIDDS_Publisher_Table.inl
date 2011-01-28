// -*- C++ -*-
// $Id$

//
// CUTS_RTIDDS_CCM_Publisher_Table
//
CUTS_INLINE
CUTS_RTIDDS_CCM_Publisher_Table::CUTS_RTIDDS_CCM_Publisher_Table (void)
{

}

//
// ~CUTS_RTIDDS_CCM_Publisher_Table
//
CUTS_INLINE
CUTS_RTIDDS_CCM_Publisher_Table::~CUTS_RTIDDS_CCM_Publisher_Table (void)
{

}

//
// configure
//
CUTS_INLINE
void CUTS_RTIDDS_CCM_Publisher_Table::configure (::DDSPublisher * publisher)
{
  this->publisher_ = publisher;
}
