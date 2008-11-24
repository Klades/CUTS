// -*- C++ -*-

//=============================================================================
/**
 * @file        Logging_Client_Task.h
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _CUTS_LOGGING_SERVER_TASK_H_
#define _CUTS_LOGGING_SERVER_TASK_H_

#include "Logging_Client_export.h"
#include "tao/corba.h"
#include "ace/Task.h"

/**
 * @class CUTS_Logging_Client_Task
 *
 * Active object for the logging server. This allows the server to
 * give the ORB a threadpool for handling client requests.
 */
class CUTS_Logging_Client_Task : public ACE_Task_Base
{
public:
  /**
   * Initializing constructor.
   */
  CUTS_Logging_Client_Task (CORBA::ORB_ptr orb);

  /// Destructor.
  virtual ~CUTS_Logging_Client_Task (void);

private:
  /// Service handler routine for the task.
  int svc (void);

  /// The CORBA orb to run.
  CORBA::ORB_var orb_;
};

#if defined (__CUTS_INLINE__)
#include "Logging_Client_Task.inl"
#endif

#endif  // !defined _CUTS_LOGGING_SERVER_TASK_H_
