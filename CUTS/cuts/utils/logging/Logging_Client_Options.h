// -*- C++ -*-

//=============================================================================
/**
 * @file      Logging_Client_Options.h
 *
 * $Id$
 *
 * @author    James H. Hill
 */
//=============================================================================

#ifndef _CUTS_LOGGING_CLIENT_OPTIONS_H_
#define _CUTS_LOGGING_CLIENT_OPTIONS_H_

#include "ace/Singleton.h"
#include "ace/Null_Mutex.h"
#include "ace/SString.h"

/**
 * @class CUTS_Logging_Client_Options
 *
 * Options for the loggin client application.
 */
class CUTS_Logging_Client_Options
{
public:
  CUTS_Logging_Client_Options (void)
    : database_ ("localhost"),
      thr_count_ (1),
      timeout_ (30)
  {

  }

  /// Address of the logging database.
  ACE_CString database_;  

  /// The size of the threadpool.
  size_t thr_count_;
  
  /// Timeout to flush the server in seconds.
  size_t timeout_;
};

#define CUTS_LOGGING_OPTIONS \
  ACE_Singleton <CUTS_Logging_Client_Options, ACE_Null_Mutex>::instance ()

#endif // !defined _CUTS_LOGGING_CLIENT_OPTIONS_H_
