// -*- C++ -*-

//=============================================================================
/**
 * @file          Logging_Server_Task.h
 *
 * $Id$
 *
 * @author        James H. Hill
 */
//=============================================================================

#ifndef _CUTS_TEST_LOGGING_SERVER_TASK_H_
#define _CUTS_TEST_LOGGING_SERVER_TASK_H_

#include "cuts/config.h"
#include "ace/Task.h"

// Forward decl.
class CUTS_Test_Logging_Server;

/**
 * @class CUTS_Test_Logging_Server_Task
 */
class CUTS_Test_Logging_Server_Task : public ACE_Task_Base
{
public:
  /**
   * Initializing constructor
   *
   * @param[in]       server      Reference to the server
   */
  CUTS_Test_Logging_Server_Task (CUTS_Test_Logging_Server & server);

  /// Destructor
  virtual ~CUTS_Test_Logging_Server_Task (void);

  /// Service method for the task.
  virtual int svc (void);

private:
  /// Reference to the logging server.
  CUTS_Test_Logging_Server & server_;
};

#if defined (__CUTS_INLINE__)
#include "Logging_Server_Task.inl"
#endif

#endif  // !defined _CUTS_TEST_LOGGING_SERVER_TASK_H_
