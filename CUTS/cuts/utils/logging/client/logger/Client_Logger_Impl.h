// -*- C++ -*-

//=============================================================================
/**
 * @file       Logger.h
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _CUTS_LOGGER_IMPL_H_
#define _CUTS_LOGGER_IMPL_H_

#include "../LoggingClientC.h"
#include "ace/UUID.h"
#include "Client_Logger_export.h"
#include "Format_Parser.h"

/**
 * @class CUTS_Client_Logger
 */
class CUTS_Client_Logger_Impl
{
public:
  /// Default constructor.
  CUTS_Client_Logger_Impl (const char * name = "");

  /// Destructor.
  ~CUTS_Client_Logger_Impl (void);

  /**
   * Connect to the logging client.
   *
   * @param[in]       client        Location of the logging client.
   */
  int connect (const char * client);

  /// Disconnect from the logging client.
  int disconnect (void);

  /**
   * Log a new message.
   *
   * @param[in]     severity        Severity level of the message
   * @param[in]     message         Message to log
   * @param[in]     msglen          Length of the \a message
   */
  int log (int severity, const char * message, size_t msglen);

  /**
   * Set the UUID for the logger.
   *
   * @param[in]       uuid          New UUID for the logger.
   */
  int set_uuid (const ACE_Utils::UUID & uuid);

  /**
   * Get the UUID for the logger.
   *
   * @param[out]      uuid          UUID of the logger.
   */
  int get_uuid (ACE_Utils::UUID & uuid);

private:
  /// Helper method to set the UUID of the logger.
  int set_uuid_i (const ACE_Utils::UUID & uuid);

  ::CORBA::ORB_var orb_;

  ::CUTS::LoggingClient_var client_;

  ::CUTS::Logger_var logger_;

  ACE_Utils::UUID uuid_;
};

#endif  // !defined _CUTS_LOGGER_IMPL_H_
