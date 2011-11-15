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

#ifndef _CUTS_TESTING_LOG_MESSAGE_SERVICE_H_
#define _CUTS_TESTING_LOG_MESSAGE_SERVICE_H_

#include "Testing_LoggingServerListener_i.h"
#include "cuts/utils/testing/TAO_Testing_Service.h"
#include "cuts/utils/logging/server/LoggingServerS.h"
#include "cuts/ORB_Server_Task.h"
#include "cuts/Servant_Manager_T.h"
#include "Testing_Log_Message_Listener_export.h"

/**
 * @class CUTS_Testing_Log_Message_Listener
 *
 * Implementation of the logging service for the test manager.
 */
class CUTS_Testing_Log_Message_Listener :
  public CUTS_TAO_Testing_Service
{
public:
  /// Default constructor
  CUTS_Testing_Log_Message_Listener (void);

  /// Destructor.
  virtual ~CUTS_Testing_Log_Message_Listener (void);

  /**
   * Initialize the service.
   *
   * @param[in]       argc          Number of command-ling arguments
   * @param[in]       argv          Command-line arguments
   */
  virtual int init (int argc, char * argv []);

  /// Finalize the service.
  virtual int fini (void);

private:
  ::CUTS::LoggingServer_var logging_server_;

  CUTS_ORB_Server_Task orb_task_;

  CUTS_Testing_LoggingServerListener_i listener_;

  CUTS_Servant_Manager_T <CUTS_Testing_LoggingServerListener_i> servant_;

  ::CUTS::UUID_var cookie_;
};

CUTS_TESTING_SERVICE_DECL (CUTS_TESTING_LOG_MESSAGE_LISTENER_Export,
                           _make_CUTS_Testing_Log_Message_Listener);

#if defined (__CUTS_INLINE__)
#include "Testing_Log_Message_Listener.inl"
#endif

#endif  // !defined _CUTS_TEST_LOGGING_SERVICE_H_
