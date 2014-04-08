// -*- C++ -*-
// $Id$

namespace iCCM
{

//
// CoreDX_Servant
//
CUTS_INLINE
CoreDX_Servant::CoreDX_Servant (const char * name)
: DDS_Servant <CoreDX> (name)
{

}

//
// ~CoreDX_Servant
//
CUTS_INLINE
CoreDX_Servant::~CoreDX_Servant (void)
{

}

//
// configure
//
CUTS_INLINE
void CoreDX_Servant::configure (void)
{
  DDS_Servant <CoreDX>::configure ();
}


}
