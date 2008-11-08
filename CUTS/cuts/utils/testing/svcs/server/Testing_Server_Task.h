// -*- C++ -*-

//=============================================================================
/**
 * @file          Testing_Server_Task.h
 *
 * $Id$
 *
 * @author        James H. Hill
 */
//=============================================================================

#ifndef _CUTS_TESTING_SERVER_TASK_H_
#define _CUTS_TESTING_SERVER_TASK_H_

#include "ace/Task.h"
#include "tao/corba.h"

// Forward decl.
class CUTS_Testing_Server;

/**
 * @class CUTS_Testing_Server_Task
 */
class CUTS_Testing_Server_Task : public ACE_Task_Base
{
public:
  /**
   * Initailizing constructor.
   */
  CUTS_Testing_Server_Task (CUTS_Testing_Server & server);

  /// Destructor
  virtual ~CUTS_Testing_Server_Task (void);

protected:
  /// Main entry point for the task.
  virtual int svc (void);

private:
  /// Reference to the testing server.
  CUTS_Testing_Server & server_;
};

#endif  // !defined _CUTS_TESTING_SERVER_TASK_H_
