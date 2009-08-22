// -*- C++ -*-

//=============================================================================
/**
 * @file        Testing_Log_Message_Listener.h
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _CUTS_TESTING_LOGGINGSERVERLISTENER_I_H_
#define _CUTS_TESTING_LOGGINGSERVERLISTENER_I_H_

#include "cuts/utils/logging/server/LoggingServerS.h"
#include "ace/RW_Thread_Mutex.h"

// Forward decl.
class CUTS_Test_Database;

class CUTS_DB_Query;

/**
 * @class CUTS_Testing_LoggingServerListener_i
 */
class CUTS_Testing_LoggingServerListener_i :
  public POA_CUTS::LoggingServerListener
{
public:
  CUTS_Testing_LoggingServerListener_i (void);

  virtual ~CUTS_Testing_LoggingServerListener_i (void);

  int init (CUTS_Test_Database * database);

  virtual void handle_messages (const char * hostname,
                                const ::CUTS::UUID & test,
                                const ::CUTS::LogMessages & msgs);

private:
  CUTS_Test_Database * database_;

  ACE_RW_Thread_Mutex mutex_;
};

#endif  // !defined _CUTS_TESTING_LOGGINGSERVERLISTENER_I_H_
