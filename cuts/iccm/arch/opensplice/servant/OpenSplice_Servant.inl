// -*- C++ -*-
// $Id$

namespace iCCM
{

//
// OpenSplice_Servant
//
CUTS_INLINE
OpenSplice_Servant::OpenSplice_Servant (const char * name)
: DDS_Servant <OpenSplice> (name)
{

}

//
// ~OpenSplice_Servant
//
CUTS_INLINE
OpenSplice_Servant::~OpenSplice_Servant (void)
{

}

//
// configure
//
CUTS_INLINE
void OpenSplice_Servant::configure (void)
{
  DDS_Servant <OpenSplice>::configure ();
}

}
