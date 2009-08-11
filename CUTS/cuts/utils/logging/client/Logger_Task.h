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

  int handle_log_message (const ACE_Utils::UUID & uuid, const ::CUTS::LogMessage & msg);

  int handle_input (ACE_HANDLE);

private:
  virtual int svc (void);

  void insert_message (::CUTS::TestLogMessage & test_logmsg,
                       const ACE_Utils::UUID & uuid,
                       const ::CUTS::LogMessage & msg);

  void copy_message (::CUTS::LogMessage & dst, const ::CUTS::LogMessage & src);

  void send_message_packet (const ::CUTS::LogMessagePacket & packet);

  ::CORBA::ORB_var orb_;

  ::CUTS::LoggingServer_var server_;

  ::CUTS::LogMessagePacket packets_[2];

  ACE_Pair <::CUTS::LogMessagePacket *,
            ::CUTS::LogMessagePacket *> buffers_;

  size_t index_;

  ACE_Thread_Mutex swap_mutex_;
};

#if defined (__CUTS_INLINE__)
#include "Logger_Task.inl"
#endif

#endif  // !defined _CUTS_LOGGER_TASK_H_
