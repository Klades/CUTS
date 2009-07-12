// -*- C++ -*-
// $Id$

//
// CUTS_RTIDDS_Endpoint
//
CUTS_INLINE
CUTS_RTIDDS_Endpoint::CUTS_RTIDDS_Endpoint (void)
{

}

//
// ~CUTS_RTIDDS_Endpoint
//
CUTS_INLINE
CUTS_RTIDDS_Endpoint::~CUTS_RTIDDS_Endpoint (void)
{
  this->close ();
}

//
// topic
//
CUTS_INLINE
::DDSTopic * CUTS_RTIDDS_Endpoint::topic (void)
{
  return this->dds_topic_;
}

