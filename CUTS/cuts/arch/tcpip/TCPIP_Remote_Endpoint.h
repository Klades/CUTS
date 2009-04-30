// -*- C++ -*-

//=============================================================================
/**
 *  @file         TCPIP_Remote_Endpoint.h
 *
 *  $Id$
 *
 *  @author       James H. Hill
 */
//=============================================================================

#ifndef _CUTS_TCPIP_REMOTE_ENDPOINT_H_
#define _CUTS_TCPIP_REMOTE_ENDPOINT_H_

#include "TCPIP_SPEC.h"

// Forward decl.
class CUTS_TCPIP_Connector_Svc_Handler;

/**
 * @class CUTS_TCPIP_Remote_Endpoint
 *
 * Remote endpoint abstraction for TCPIP. The endpoint contains info
 * about the target peer, target component, and event port to publish
 * events.
 */
class CUTS_TCPIP_Export CUTS_TCPIP_Remote_Endpoint
{
public:
  /// Default constructor.
  CUTS_TCPIP_Remote_Endpoint (void);

  /// Destructor.
  ~CUTS_TCPIP_Remote_Endpoint (void);

  int connect (const char * addr, const char * uuid, long event);

  /// Disconnect the endpoint.
  void disconnect (void);

  /// Test the endpoint connection.
  bool is_connected (void) const;

protected:
  /// Handler for the remote endpoint.
  CUTS_TCPIP_Connector_Svc_Handler * handler_;

  /// Header for sending event data to peer.
  CUTS_TCPIP_SPEC header_;
};

#if defined (__CUTS_INLINE__)
#include "TCPIP_Remote_Endpoint.inl"
#endif

#endif  // !defined _CUTS_TCPIP_REMOTE_ENDPOINT_H_
