// -*- C++ -*-

//=============================================================================
/**
 * @file          TestLoggerClient_i.h
 *
 * $Id$
 *
 * @author        James H. Hill
 */
//=============================================================================

#ifndef _CUTS_TEST_LOGGER_CLIENT_I_H_
#define _CUTS_TEST_LOGGER_CLIENT_I_H_

#include "LoggingClientS.h"
#include "ace/Unbounded_Set.h"
#include "ace/UUID.h"
#include "cuts/config.h"

// Forward decl.
class CUTS_Log_Message_Handler;

/**
 * @class CUTS_LoggingClient_i
 *
 * Implementation of the ::CUTS::LoggingClient interface. This object
 * is not thread-safe and must be activated under the RootPOA, or a
 * single-threaded POA. Otherwise, unknown behavior many occur.
 */
class CUTS_LoggingClient_i :
  public virtual ::POA_CUTS::LoggingClient
{
public:
  /**
   * Initializing constructor.
   *
   * @param[in]       parent        Parent POA
   * @param[in]       handler       Target log message handler
   */
  CUTS_LoggingClient_i (::PortableServer::POA_ptr parent,
                        CUTS_Log_Message_Handler * handler);

  /// Destructor
  virtual ~CUTS_LoggingClient_i (void);

  /**
   * Get the logger for the specified test. If there is no logger for
   * the specified test, then a new one is created.
   *
   * @param[in]     test        Test for which logger to retrieve
   * @return        Reference to the logger.
   */
  virtual ::CUTS::Logger_ptr get_logger (const ::CUTS::UUID & test);

  /**
   * Release a logger's reference. Once all references to a logger have
   * been released, then the logger resources are freed, i.e., the logger
   * is destroyed.
   *
   * @param[in]     logger      Logger to release.
   */
  virtual void release (::CUTS::Logger_ptr logger);

private:
  /// POA for activating the CUTS::TestLogger servants
  ::PortableServer::POA_var logger_poa_;

  /// Target handler for the logging client.
  CUTS_Log_Message_Handler * handler_;
};

#if defined (__CUTS_INLINE__)
#include "LoggingClient_i.inl"
#endif

#endif  // !defined _CUTS_TEST_LOGGER_CLIENT_I_H_
