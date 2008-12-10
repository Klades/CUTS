// -*- C++ -*-

//=============================================================================
/**
 * @file        Logging_Server_Options.h
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _CUTS_LOGGING_SERVER_OPTIONS_H_
#define _CUTS_LOGGING_SERVER_OPTIONS_H_

#include "ace/SString.h"

class CUTS_Logging_Server_Options
{
public:
  CUTS_Logging_Server_Options (void)
    : thread_count_ (1)
  {

  }

  /// Number of threads to run in the server.
  size_t thread_count_;

  /// Location of the client file
  ACE_CString clients_file_;
};

#endif  // !defined _CUTS_LOGGING_SERVER_OPTIONS_H_