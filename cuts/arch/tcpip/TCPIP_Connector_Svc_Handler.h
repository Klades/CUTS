// -*- C++ -*-

//=============================================================================
/**
 *  @file         TCPIP_Connect_Svc_Handler.h
 *
 *  $Id$
 *
 *  @author       James H. Hill
 */
//=============================================================================

#ifndef _CUTS_TCPIP_CONNECT_SVC_HANDLER_H_
#define _CUTS_TCPIP_CONNECT_SVC_HANDLER_H_

#include "ace/SOCK_Stream.h"
#include "ace/Svc_Handler.h"
#include "TCPIP_export.h"
#include "config.h"

/**
 * @class CUTS_TCPIP_Connector_Svc_Handler
 */
class CUTS_TCPIP_Export CUTS_TCPIP_Connector_Svc_Handler :
  public ACE_Svc_Handler <ACE_SOCK_Stream, ACE_MT_SYNCH>
{
public:
  /// Type definition of the base class.
  typedef ACE_Svc_Handler <ACE_SOCK_Stream, ACE_MT_SYNCH> parent_type;

  /// Default constructor.
  CUTS_TCPIP_Connector_Svc_Handler (void);

  /// Destructor.
  virtual ~CUTS_TCPIP_Connector_Svc_Handler (void);

  virtual int handle_output (ACE_HANDLE fd);
};

#if defined (__CUTS_INLINE__)
#include "TCPIP_Connector_Svc_Handler.inl"
#endif

#endif
