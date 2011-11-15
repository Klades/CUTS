// -*- C++ -*-
// $Id$

//
// CUTS_TCPIP_ComponentServer
//
CUTS_INLINE
CUTS_TCPIP_ComponentServer::CUTS_TCPIP_ComponentServer (void)
{

}

//
// ~CUTS_TCPIP_ComponentServer
//
CUTS_INLINE
CUTS_TCPIP_ComponentServer::~CUTS_TCPIP_ComponentServer (void)
{

}

//
// init
//
CUTS_INLINE
int CUTS_TCPIP_ComponentServer::init (int argc, char * argv [])
{
  return this->orb_.init (argc, argv);
}

//
// activate
//
CUTS_INLINE
int CUTS_TCPIP_ComponentServer::activate (void)
{
  return this->orb_.run ();
}


//
// shutdown
//
CUTS_INLINE
void CUTS_TCPIP_ComponentServer::shutdown (void)
{
  this->orb_.shutdown ();
}

CUTS_INLINE
CUTS_TCPIP_ORB & CUTS_TCPIP_ComponentServer::the_ORB (void)
{
  return this->orb_;
}
