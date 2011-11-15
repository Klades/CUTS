// -*- C++ -*-

//=============================================================================
/**
 *  @file         TCPIP_ComponentServer.h
 *
 *  $Id$
 *
 *  @author       James H. Hill
 */
//=============================================================================

#ifndef _CUTS_TCPIP_COMPONENT_SERVER_H_
#define _CUTS_TCPIP_COMPONENT_SERVER_H_

#include "TCPIP_ORB.h"

/**
 * @class CUTS_TCPIP_ComponentServer
 */
class CUTS_TCPIP_Export CUTS_TCPIP_ComponentServer
{
public:
  CUTS_TCPIP_ComponentServer (void);

  virtual ~CUTS_TCPIP_ComponentServer (void);

  virtual int init (int argc, char * argv []);

  virtual int activate (void);

  virtual void shutdown (void);

  CUTS_TCPIP_ORB & the_ORB (void);

private:
  /// The ORB for the component server.
  CUTS_TCPIP_ORB orb_;
};

#if defined (__CUTS_INLINE__)
#include "TCPIP_ComponentServer.inl"
#endif

#endif  // !defined _CUTS_TCPIP_COMPONENT_SERVER_H_
