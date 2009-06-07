// -*- C++ -*-
// $Id$

//
// ~CUTS_CHAOS_CCM_EventConsumer
//
CUTS_INLINE
CUTS_CHAOS_CCM_ComponentServer::~CUTS_CHAOS_CCM_ComponentServer (void)
{

}

//
// init
//
CUTS_INLINE
int CUTS_CHAOS_CCM_ComponentServer::init (int argc, char * argv [])
{
  return CUTS_TCPIP_ComponentServer::init (argc, argv);
}
