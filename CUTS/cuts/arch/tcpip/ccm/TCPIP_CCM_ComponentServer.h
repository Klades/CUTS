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

#include "cuts/arch/tcpip/TCPIP_ComponentServer.h"
#include "tao/PortableServer/PortableServer.h"
#include "ace/Task.h"
#include "TCPIP_CCM_export.h"

/**
 * @class CUTS_TCPIP_CCM_ComponentServer
 */
class CUTS_TCPIP_CCM_Export CUTS_TCPIP_CCM_ComponentServer :
  public CUTS_TCPIP_ComponentServer,
  public ACE_Task_Base
{
public:
  /// Default constructor.
  CUTS_TCPIP_CCM_ComponentServer (void);

  /// Destructor.
  virtual ~CUTS_TCPIP_CCM_ComponentServer (void);

  virtual int init (int & argc, char * argv[]);

  virtual int shutdown (void);

  virtual int activate (void);

  virtual int destroy (void);

  /// Service routine for the task/server.
  virtual int svc (void);

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
