// -*- C++ -*-
// $Id$

namespace iCCM
{

//
// RTIDDS_Servant
//
CUTS_INLINE
RTIDDS_Servant::RTIDDS_Servant (const char * name)
: DDS_Servant (name)
{

}

//
// ~RTIDDS_Servant
//
CUTS_INLINE
RTIDDS_Servant::~RTIDDS_Servant (void)
{

}

//
// configure
//
CUTS_INLINE
void RTIDDS_Servant::configure (void)
{
  DDS_Servant::configure ();
}

}
