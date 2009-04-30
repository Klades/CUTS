// -*- C++ -*-

//=============================================================================
/**
 *  @file         TCPIP_CCM_EventConsumer.h
 *
 *  $Id$
 *
 *  @author       James H. Hill
 */
//=============================================================================

#ifndef _CUTS_TCPIP_CCM_COMPONENTSERVER_H_
#define _CUTS_TCPIP_CCM_COMPONENTSERVER_H_

#include "TCPIP_CCM_export.h"
#include "tao/PortableServer/PortableServer.h"
#include "ace/Task.h"

/**
 * @class CUTS_TCPIP_CCM_ComponentServer
 */
class CUTS_TCPIP_CCM_Export CUTS_TCPIP_CCM_ComponentServer :
  public ACE_Task_Base
{
public:
  /// Default constructor.
  CUTS_TCPIP_CCM_ComponentServer (void);

  /// Destructor.
  virtual ~CUTS_TCPIP_CCM_ComponentServer (void);

  int init (int & argc, char * argv[]);

  int svc (void);

  int shutdown (void);

private:
  /// The ORB for the server.
  CORBA::ORB_var orb_;

  /// The root POA for the server.
  PortableServer::POA_var root_;
};

#if defined (__CUTS_INLINE__)
#include "TCPIP_CCM_ComponentServer.inl"
#endif

#endif  // !defined _CUTS_TCPIP_CCM_COMPONENTSERVER_H_
