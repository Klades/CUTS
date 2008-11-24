// -*- C++ -*-

#ifndef _CUTS_LOCAL_LOGGING_CLIENT_APP_H_
#define _CUTS_LOCAL_LOGGING_CLIENT_APP_H_

#include "LocalTestLoggerClient_i.h"
#include "Logging_Client_Task.h"
#include "tao/PortableServer/PortableServer.h"
#include "Test_Logger_Map.h"

/**
 * @class CUTS_Local_Logging_Client_App
 */
class CUTS_Local_Logging_Client_App
{
public:
  /// Default constructor.
  CUTS_Local_Logging_Client_App (const CUTS_TestLoggerClient_i & client);

  /// Destructor.
  ~CUTS_Local_Logging_Client_App (void);

  /**
   * Run the local logging client on the specified port.
   *
   * @param[in]       port          Target local port
   * @param[in]       threads       Number of threads
   */
  int run_main (u_short port, size_t threads = 1);

  /// Shutdown the application.
  void shutdown (void);

  int destroy (void);

private:
  int register_with_iortable (void);

  /// ORB for the application.
  CORBA::ORB_var orb_;

  /// The root POA for the application.
  PortableServer::POA_var root_poa_;

  /// Task for the application.
  ACE_Auto_Ptr <CUTS_Logging_Client_Task> task_;

  const CUTS_TestLoggerClient_i & client_;

  /// Pointer to the local test logger client implementation.
  ACE_Auto_Ptr <CUTS_LocalTestLoggerClient_i> servant_;
};

#endif  // !defined _CUTS_LOCAL_LOGGING_CLIENT_APP_H_
