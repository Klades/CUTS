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
#include "ace/SString.h"
#include "ace/Thread_Mutex.h"
#include "ace/Condition_T.h"

// Forward decl.
class CUTS_DB_Connection;

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
  virtual ~CUTS_Testing_App (void);

  /**
   * Run the main part of the application. This method does not return 
   * until the shutdown () method is invoked.
   *
   * @param[in]       argc        Number of command-line arguments
   * @param[in]       argv        The command-line arguments
   */
  virtual int run_main (int argc, char * argv []);

  /// Shutdown the testing application. This will stop the ORBs main 
  /// event loop and allow the run_main () method to return.
  virtual int shutdown (void);

  /// Start a new test in the database (if applicable).
  int start_new_test (void);

  /// Stop the current test.
  int stop_current_test (void);

  long current_test_number (void) const;

  /**
   * Get the name of the testing application. This is determined by the
   * --name=NAME command-line option.
   *
   * @return        Name of the testing application.
   */
  const ACE_CString & name (void) const;

protected:
  /// Implementation of the run_main () function.
  int run_main_i (void);

  /**
   * Parse the command-line arguments.
   *
   * @param[in]       argc        Number of command-line arguments
   * @param[in]       argv        The command-line arguments
   * @retval          0           Successfully parsed arguments
   * @retval          -1          Failed to parse arguments
   */
  virtual int parse_args (int argc, char * argv []);

  /// Print the help for this application.
  void print_help (void);

  /// Connect to the specified database.
  void connect_to_database (void);

  /// Verbosity of the application.
  bool verbose_;

  /// Server address of the test database.
  ACE_CString server_addr_;

  /// The connection for the database service.
  ACE_Auto_Ptr <CUTS_DB_Connection> conn_;

private:
  /// Name of the testing application. The default name of the 
  /// application is '(default)'.
  ACE_CString name_;

  /// The test number associated with the experiment.
  long test_number_;

  /// The desired test duration.
  long test_duration_;

  /// Timer id for the test.
  long test_timer_id_;

  /// Task for the testing application.
  ACE_Auto_Ptr <CUTS_Testing_App_Task> task_;

  ACE_Thread_Mutex lock_;

  ACE_Condition <ACE_Thread_Mutex> shutdown_; 
};

#endif  // !defined _CUTS_TESTING_APP_H_
