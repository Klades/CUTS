// -*- C++ -*-

//=============================================================================
/**
 * @file        Test_Logger.h
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _CUTS_TEST_LOGGER_H_
#define _CUTS_TEST_LOGGER_H_

#include "ace/Auto_Ptr.h"
#include "ace/Log_Priority.h"
#include "ace/SStringfwd.h"
#include "Test_Logger_export.h"
#include "Format_Parser.h"

// Forward decl.
class CUTS_Test_Logger_i;

/**
 * @class CUTS_Test_Logger
 *
 * Workload generator for generating text log messages for a test and
 * storing them in a database.
 */
class CUTS_TEST_LOGGER_Export CUTS_Test_Logger
{
public:
  /// Default constructor
  CUTS_Test_Logger (void);

  /// Destructor
  ~CUTS_Test_Logger (void);

  /**
   * Configure the test logger. This sets the port for connecting to the
   * logging client.
   *
   * @param[in]             port          Port number of logging client
   */
  bool configure (short port);

  /**
   * Connect to the test manager identified by \a test.
   *
   * @param[in]             test          Name of the test.
   */
  bool connect_using_location (const ACE_CString & location);

  bool connect_using_name (const ACE_CString & name);

  /// Connect to the existing test manager.
  bool connect (void);

  /**
   *
   */
  bool log (long severity, const char * format, ...);

private:
  /// Parser for format messages.
  CUTS_Format_Parser parser_;

  /// The implementation for the test logger.
  ACE_Auto_Ptr <CUTS_Test_Logger_i> impl_;
};

#endif  // !defined _CUTS_TEST_LOGGER_H_
