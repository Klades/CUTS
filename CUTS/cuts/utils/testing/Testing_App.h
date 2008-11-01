// -*- C++ -*-

//=============================================================================
/**
 * @file          CUTS_Testing_App.h
 *
 * $Id$
 *
 * @author        James H. Hill
 */
//=============================================================================

#ifndef _CUTS_TESTING_APP_H_
#define _CUTS_TESTING_APP_H_

#include "Testing_App_Task.h"
#include "Testing_Options.h"
#include "ace/Condition_T.h"
#include "ace/Service_Gestalt.h"
#include "ace/SString.h"
#include "ace/Thread_Mutex.h"

namespace CUTS
{
  // Forward decl.
  class serviceDescription;
}

/**
 * @class CUTS_Testing_App
 *
 * The main entry point class for the application.
 */
class CUTS_Testing_App
{
public:
  /// Default constructor.
  CUTS_Testing_App (void);

  /// Destructor.
  ~CUTS_Testing_App (void);

  /**
   * Run the main part of the application. This method does not return
   * until the shutdown () method is invoked.
   *
   * @param[in]       argc        Number of command-line arguments
   * @param[in]       argv        The command-line arguments
   */
  int run_main (int argc, char * argv []);

  /// Shutdown the testing application. This will stop the ORBs main
  /// event loop and allow the run_main () method to return.
  int shutdown (void);

  /**
   * Get the options for the testing application.
   *
   * @return        Options for the testing application.
   */
  const CUTS_Testing_Options & options (void) const;

protected:
  /**
   * Parse the command-line arguments.
   *
   * @param[in]       argc        Number of command-line arguments
   * @param[in]       argv        The command-line arguments
   * @retval          0           Successfully parsed arguments
   * @retval          -1          Failed to parse arguments
   */
  virtual int parse_args (int argc, char * argv []);

private:
  /// Print the help for this application.
  void print_help (void);

  /// Deploy the current test.
  int deploy_test (void);

  /// Teardown the current test.
  int teardown_test (void);

  /// Load the configuration for the test.
  int load_configuration (void);

  int load_service (const CUTS::serviceDescription &);

  /// Timer id for the test.
  long test_timer_id_;

  /// Task for the testing application.
  CUTS_Testing_App_Task task_;

  /// Options for the testing application.
  CUTS_Testing_Options opts_;

  /// Lock for the condition variable.
  ACE_Thread_Mutex lock_;

  /// Condition variable to wait for shutdown.
  ACE_Condition <ACE_Thread_Mutex> shutdown_;

  /// Service configurator for this test.
  ACE_Service_Gestalt svc_config_;
};

#if defined (__CUTS_INLINE__)
#include "Testing_App.inl"
#endif

#endif  // !defined _CUTS_TESTING_APP_H_
