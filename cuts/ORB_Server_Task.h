// -*- C++ -*-

//=============================================================================
/**
 * @file        ORB_Server_Task.h
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _CUTS_ORB_SERVER_TASK_H_
#define _CUTS_ORB_SERVER_TASK_H_

#include "cuts/CUTS_export.h"
#include "tao/ORB.h"
#include "ace/Task.h"

/**
 * @class CUTS_ORB_Server_Task
 *
 * Helper object for running multiple ORB threads in a server.
 */
class CUTS_Export CUTS_ORB_Server_Task : public ACE_Task_Base
{
public:
  /**
   * Initializing constructor.
   */
  CUTS_ORB_Server_Task (CORBA::ORB_ptr orb = CORBA::ORB::_nil ());

  /// Destructor.
  virtual ~CUTS_ORB_Server_Task (void);

  /**
   * Initialize the ORB for the task.
   */
  int reset (CORBA::ORB_ptr orb = CORBA::ORB::_nil ());

  /**
   * Service routine for the task. If you do not want to spawn mutiple
   * ORB threads, then you can invoke this method directly. If will run
   * the ORB's main event loop using the current thread.
   */
  virtual int svc (void);

private:
  /// Target ORB controlled by this task.
  CORBA::ORB_var orb_;
};

#if defined (__CUTS_INLINE__)
#include "ORB_Server_Task.inl"
#endif

#endif  // !defined _CUTS_ORB_SERVER_TASK_H_
