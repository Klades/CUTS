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

#ifndef _CUTS_LOGGER_H_
#define _CUTS_LOGGER_H_

#include "../LoggingClientC.h"
#include "ace/UUID.h"
#include "Client_Logger_export.h"
#include "Format_Parser.h"

/**
 * @class CUTS_Client_Logger
 */
class CUTS_CLIENT_LOGGER_Export CUTS_Client_Logger
{
public:
  /// Default constructor.
  CUTS_Client_Logger (void);

  /// Destructor.
  ~CUTS_Client_Logger (void);

  int log (int severity, const char * format, ...);

  int connect (const char * client);

  int disconnect (void);

  int set_uuid (const ACE_Utils::UUID & uuid);

private:
  int set_uuid_i (const ACE_Utils::UUID & uuid);

  ::CORBA::ORB_var orb_;

  ::CUTS::LoggingClient_var client_;

  ::CUTS::Logger_var logger_;

  ACE_Utils::UUID uuid_;

  CUTS_Format_Parser parser_;
};

#endif  // !defined _CUTS_LOGGER_H_
