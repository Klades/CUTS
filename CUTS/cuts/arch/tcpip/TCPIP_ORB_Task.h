// -*- C++ -*-

//=============================================================================
/**
 *  @file         TCPIP_ORB_Task.h
 *
 *  $Id$
 *
 *  @author       James H. Hill
 */
//=============================================================================

#ifndef _CUTS_TCPIP_ORB_TASK_H_
#define _CUTS_TCPIP_ORB_TASK_H_

#include "ace/Task.h"
#include "TCPIP_export.h"

// Forward decl.
class CUTS_TCPIP_ORB;

/**
 * @class CUTS_TCPIP_ORB_Task
 *
 * Active object for running the TCP/IP ORB event loop.
 */
class CUTS_TCPIP_Export CUTS_TCPIP_ORB_Task :
  public ACE_Task_Base
{
public:
  /**
   * Initializing constructor.
   */
  CUTS_TCPIP_ORB_Task (CUTS_TCPIP_ORB & orb);

  /// Destructor.
  ~CUTS_TCPIP_ORB_Task (void);

  /// Service handler method.
  int svc (void);

private:
  /// Reference to the contained ORB.
  CUTS_TCPIP_ORB & orb_;
};

#if defined (__CUTS_INLINE__)
#include "TCPIP_ORB_Task.inl"
#endif

#endif  // !defined _CUTS_TCPIP_ORB_TASK_H_
