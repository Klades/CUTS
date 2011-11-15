// -*- C++ -*-

//=============================================================================
/**
 *  @file         TCPIP_Acceptor.h
 *
 *  $Id$
 *
 *  @author       James H. Hill
 */
//=============================================================================

#ifndef _CUTS_TCPIP_ACCEPTOR_H_
#define _CUTS_TCPIP_ACCEPTOR_H_

#include "ace/SOCK_Acceptor.h"
#include "TCPIP_Event_Handler.h"
#include "TCPIP_export.h"

// Forward decl.
class CUTS_TCPIP_Servant_Manager;

/**
 * @class CUTS_TCPIP_Acceptor
 */
class CUTS_TCPIP_Acceptor :
  public ACE_Acceptor <CUTS_TCPIP_Event_Handler, ACE_SOCK_Acceptor>
{
public:
  /// Type defintion of the acceptor type.
  typedef ACE_Acceptor <CUTS_TCPIP_Event_Handler,
                        ACE_SOCK_Acceptor> acceptor_type;

  /// Type definition of the PEER_ADDR.
  typedef ACE_SOCK_Acceptor::PEER_ADDR PEER_ADDR;

  /// Type definition of the PEER_STREAM.
  typedef ACE_SOCK_Acceptor::PEER_STREAM PEER_STREAM;

  /// Default constructor.
  CUTS_TCPIP_Acceptor (const CUTS_TCPIP_Servant_Manager & obj_mgr);

  /// Destructor.
  virtual ~CUTS_TCPIP_Acceptor (void);

  virtual int make_svc_handler (CUTS_TCPIP_Event_Handler *& sh);

private:
  /// Object manager for this connection.
  const CUTS_TCPIP_Servant_Manager & obj_mgr_;
};

#if defined (__CUTS_INLINE__)
#include "TCPIP_Acceptor.inl"
#endif

#endif  // !defined _CUTS_TCPIP_ACCEPTOR_H_
