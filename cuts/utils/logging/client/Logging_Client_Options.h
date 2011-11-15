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
#include "ace/Time_Value.h"

/**
 * @class CUTS_Logging_Client_Options
 *
 * Options for the loggin client application.
 */
class CUTS_Logging_Client_Options
{
public:
  CUTS_Logging_Client_Options (void)
    : thr_count_ (1)
  {

  }

  /// The size of the threadpool.
  size_t thr_count_;
};

#endif // !defined _CUTS_LOGGING_CLIENT_OPTIONS_H_
