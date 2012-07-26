// -*- C++ -*-

//=============================================================================
/**
 * @file       Client_Logger.h
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _CUTS_CLIENT_LOGGER_H_
#define _CUTS_CLIENT_LOGGER_H_

#include "ace/UUID.h"

#include "Client_Logger_export.h"

// Forward decl.
class CUTS_Client_Logger_Impl;

/**
 * @class CUTS_Client_Logger
 */
class CUTS_CLIENT_LOGGER_Export CUTS_Client_Logger
{
public:
  /// Default constructor.
  CUTS_Client_Logger (const char * name = "");

  /// Destructor.
  ~CUTS_Client_Logger (void);

  int log (int severity, const char * format, ...);

  int connect (const char * client);

  int disconnect (void);

  int set_uuid (const ACE_Utils::UUID & uuid);

  int get_uuid (ACE_Utils::UUID & uuid);

private:
  CUTS_Client_Logger_Impl * impl_;
};

#endif  // !defined _CUTS_LOGGER_H_
