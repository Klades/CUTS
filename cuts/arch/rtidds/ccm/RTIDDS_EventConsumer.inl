// -*- C++ -*-
// $Id$

//
// CUTS_RTIDDS_CCM_EventConsumer
//
CUTS_INLINE
CUTS_RTIDDS_CCM_EventConsumer::CUTS_RTIDDS_CCM_EventConsumer (void)
: subscriber_ (0),
  abstract_reader_ (0)
{

}

//
// ~CUTS_RTIDDS_CCM_EventConsumer
//
CUTS_INLINE
CUTS_RTIDDS_CCM_EventConsumer::~CUTS_RTIDDS_CCM_EventConsumer (void)
{
  this->close ();
}
