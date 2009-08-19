// -*- C++ -*-

//=============================================================================
/**
 * @file        TestLogger_i.h
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _CUTS_TEST_LOGGER_I_H_
#define _CUTS_TEST_LOGGER_I_H_

#include "LoggingClientS.h"
#include "cuts/Log_T.h"
#include "ace/UUID.h"
#include "ace/Null_Mutex.h"
#include "ace/RW_Thread_Mutex.h"

// Forward decl.
class CUTS_Log_Message_Handler;

/**
 * @class CUTS_Logger_i
 *
 * Default implemenation of the CUTS::TestLogger interface.
 */
class CUTS_Logger_i :
  public virtual POA_CUTS::Logger
{
public:
  /**
   * Initializing constructor
   *
   * @param[in]         uuid              Unique id of the logger
   * @param[in]         msg_queue_size    Size of the message queue
   */
  CUTS_Logger_i (CUTS_Log_Message_Handler * handler, const ACE_Utils::UUID & uuid);

  /// Destructor.
  virtual ~CUTS_Logger_i (void);

  virtual void log (const ::CUTS::LogMessage & logmsg);

  /// Get the UUID assigned to the logger.
  ::CUTS::UUID * uuid (void);

private:
  void flush (void);

  /// Parent of the logger.
  CUTS_Log_Message_Handler * handler_;

  /// Id of the logger assigned by the parent.
  ACE_Utils::UUID uuid_;

  CUTS_Log_T <::CUTS::LogMessage, ACE_Null_Mutex> queue_;

  ACE_RW_Thread_Mutex flush_lock_;
};

#if defined (__CUTS_INLINE__)
#include "Logger_i.inl"
#endif

#endif  // !defined _CUTS_TEST_LOGGER_I_H_
