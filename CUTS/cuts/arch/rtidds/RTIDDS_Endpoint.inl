// -*- C++ -*-
// $Id$

//
// CUTS_RTIDDS_Endpoint
//
CUTS_INLINE
CUTS_RTIDDS_Endpoint::CUTS_RTIDDS_Endpoint (void)
: participant_ (0),
  dds_topic_ (0)
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

//
// is_open
//
CUTS_INLINE
bool CUTS_RTIDDS_Endpoint::is_open (void) const
{
  return 0 != this->dds_topic_;
}
