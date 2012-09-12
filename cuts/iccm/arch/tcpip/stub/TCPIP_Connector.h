// -*- C++ -*-

//=============================================================================
/**
 *  @file         TCPIP_Connector.h
 *
 *  $Id$
 *
 *  @author       James H. Hill
 */
//=============================================================================

#ifndef _CUTS_TCPIP_CONNECTOR_H_
#define _CUTS_TCPIP_CONNECTOR_H_

#include "ace/Connector.h"
#include "ace/SOCK_Connector.h"
#include "ace/Singleton.h"
#include "ace/RW_Thread_Mutex.h"
#include "TCPIP_Connector_Svc_Handler.h"

/**
 * @class CUTS_TCPIP_Connector
 */
class CUTS_TCPIP_Export CUTS_TCPIP_Connector :
  public ACE_Connector <CUTS_TCPIP_Connector_Svc_Handler, ACE_SOCK_Connector>
{
public:
  typedef ACE_Connector <CUTS_TCPIP_Connector_Svc_Handler,
                         ACE_SOCK_Connector>
                         connector_type;

  typedef connector_type::peer_addr_type peer_addr_type;

  typedef connector_type::stream_type stream_type;

  /// Default constructor.
  CUTS_TCPIP_Connector (void);

  /// Destructor.
  virtual ~CUTS_TCPIP_Connector (void);

  int get_peer (const char * addr,
                CUTS_TCPIP_Connector_Svc_Handler * & handler);

  int get_peer (const peer_addr_type & addr,
                CUTS_TCPIP_Connector_Svc_Handler * & handler);

private:
  typedef ACE_Hash_Map_Manager <peer_addr_type,
                                CUTS_TCPIP_Connector_Svc_Handler *,
                                ACE_RW_Thread_Mutex>
                                peer_table_type;

  /// The peer table for the services.
  peer_table_type peer_table_;

  ACE_RW_Thread_Mutex connect_lock_;
};

#define CUTS_TCPIP_CONNECTOR \
  ACE_Singleton <CUTS_TCPIP_Connector, ACE_RW_Thread_Mutex>

#if defined (__CUTS_INLINE__)
#include "TCPIP_Connector.inl"
#endif

#endif  // !defined _CUTS_TCPIP_CONNECTOR_H_
