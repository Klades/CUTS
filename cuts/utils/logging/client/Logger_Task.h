// -*- C++ -*-

//=============================================================================
/**
 * @file      Logger_Task.h
 *
 * $Id$
 *
 * @author    James H. Hill
 */
//=============================================================================

#ifndef _CUTS_LOGGER_TASK_H_
#define _CUTS_LOGGER_TASK_H_

#include "Log_Message_Handler.h"
#include "../server/LoggingServerC.h"
#include "ace/Task.h"
#include "ace/Pair_T.h"
#include "ace/Thread_Mutex.h"
#include "ace/Condition_T.h"

// Forward decl.
class CUTS_LoggingClient_i;

/**
 * @class CUTS_Logger_Task
 */
class CUTS_Logger_Task :
  public ACE_Task_Base,
  public CUTS_Log_Message_Handler
{
public:
  CUTS_Logger_Task (void);

  virtual ~CUTS_Logger_Task (void);

  int init (::CORBA::ORB_ptr orb);

  int handle_log_messages (const ACE_Utils::UUID & uuid,
                           const ::CUTS::LogMessages & msgs);

private:
  virtual int svc (void);

  ::CORBA::ORB_var orb_;

  ::CUTS::LoggingServer_var server_;

  ACE_CString hostname_;
};

#if defined (__CUTS_INLINE__)
#include "Logger_Task.inl"
#endif

#endif  // !defined _CUTS_LOGGER_TASK_H_
