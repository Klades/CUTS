// -*- C++ -*-

//=============================================================================
/**
 *  @file         TCPIP_Svc_Handler.h
 *
 *  $Id$
 *
 *  @author       James H. Hill
 */
//=============================================================================

#ifndef _CUTS_TCPIP_EVENT_HANDLER_H_
#define _CUTS_TCPIP_EVENT_HANDLER_H_

#include "ace/Acceptor.h"
#include "ace/Svc_Handler.h"
#include "ace/SOCK_Stream.h"
#include "config.h"

// Forward decl.
class CUTS_TCPIP_Servant_Manager;

/**
 * @class CUTS_TCPIP_Event_Handler
 */
class CUTS_TCPIP_Event_Handler :
  public ACE_Svc_Handler <ACE_SOCK_Stream, ACE_MT_SYNCH>
{
public:
  /// Type definition of the base class.
  typedef ACE_Svc_Handler <ACE_SOCK_Stream, ACE_MT_SYNCH> parent_type;

  /// Default constructor.
  CUTS_TCPIP_Event_Handler (const CUTS_TCPIP_Servant_Manager * om = 0);

  /// Destructor.
  virtual ~CUTS_TCPIP_Event_Handler (void);

  ///// Open the service handler.
  //int open (void * args);

  virtual int handle_input (ACE_HANDLE fd);

private:
  /// The active state of the handler.
  bool is_active_;

  /// The object manager for the ORB.
  const CUTS_TCPIP_Servant_Manager * obj_mgr_;
};

#if defined (__CUTS_INLINE__)
#include "TCPIP_Event_Handler.inl"
#endif

#endif  // !defined _CUTS_TCPIP_EVENT_HANDLER_H_
