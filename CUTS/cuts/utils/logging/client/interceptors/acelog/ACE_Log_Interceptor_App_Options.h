// -*- C++ -*-

//=============================================================================
/**
 * @file          ACE_Log_Interceptor_App_Options.h
 *
 * $Id$
 *
 * @author        Pooja Varshneya
 */
//=============================================================================

#ifndef _CUTS_ACE_LOG_INTERCEPTOR_APP_OPTIONS_H_
#define _CUTS_ACE_LOG_INTERCEPTOR_APP_OPTIONS_H_

#include "ace/SString.h"

// Macro needs to be defined where: in cuts/config.h or here?
#if !defined (CUTS_LOCAL_LOGGING_CLIENT_DEFAULT_PORT)
#  define CUTS_LOCAL_LOGGING_CLIENT_DEFAULT_PORT  30002
#endif

/**
 * @class CUTS_Template_App_Options
 */
class  CUTS_ACE_Log_Interceptor_App_Options
{
public:
  /// Default constructor. Set the default values for the command-line
  /// options.
   CUTS_ACE_Log_Interceptor_App_Options (void)
    : connect_port_ (CUTS_LOCAL_LOGGING_CLIENT_DEFAULT_PORT),
      is_connect_name_ (false),
      is_connect_location_ (false)
  {
  }

  /// String used for connecting with the logger.
  ACE_CString connect_string;

  /// Port for connection
  short connect_port_;

  /// Use environment variables in the conversion.
	bool is_connect_name_;
	bool is_connect_location_;
};

#endif /* _CUTS_ACE_LOG_INTERCEPTOR_APP_OPTIONS_H_ */
