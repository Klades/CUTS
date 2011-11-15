// -*- C++ -*-

//=============================================================================
/**
 * @file        Boost_JUnit_Formatter.h
 *
 * Boost formatter for generating JUnit compatible log files
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _CUTS_BOOST_JUNIT_FORMATTER_H_
#define _CUTS_BOOST_JUNIT_FORMATTER_H_

#include "Test_Log_Formats_export.h"
#include "boost/test/unit_test_log_formatter.hpp"
#include "boost/test/unit_test.hpp"

//=============================================================================
/**
 * @class CUTS_Boost_JUnit_Formatter
 *
 * JUnit log formatter for the Boost unit test framework. This is an
 * custom implementation of the boost::unit_test::unit_test_log_formatter.
 */
//=============================================================================

class TEST_LOG_FORMATS_Export CUTS_Boost_JUnit_Formatter :
  public boost::unit_test::unit_test_log_formatter
{
public:
  /// Default constructor.
  CUTS_Boost_JUnit_Formatter (void);

  /**
   * Initializing constructor.
   *
   * @param[in]       package       Package name of the test.
   */
  CUTS_Boost_JUnit_Formatter (const std::string & package);

  /// Destructor.
  virtual ~CUTS_Boost_JUnit_Formatter (void);

  // Start the custom log.
  void log_start (std::ostream & output,
                  boost::unit_test::counter_t test_cases_amount);

  // Log the build info for the unit test.
  void log_build_info (std::ostream & output);

  // End the custom log.
  void log_finish (std::ostream & output);

  // Log the start of a test unit.
  void test_unit_start (std::ostream & output,
                        const boost::unit_test::test_unit & tu );

  // Log the skipping of a test unit.
  void test_unit_skipped (std::ostream & output,
                          const::boost::unit_test::test_unit & tu);

  // Log the completion of a test unit.
  void test_unit_finish (std::ostream & output,
                         const boost::unit_test::test_unit & tu,
                         unsigned long elapsed);

  // Log an exception from the unit test.
  void log_exception (std::ostream & output,
                      const boost::unit_test::log_checkpoint_data & lcd,
                      boost::unit_test::const_string explanation);

  // Begin a log entry.
  void log_entry_start (std::ostream & output,
                        const boost::unit_test::log_entry_data & led,
                        boost::unit_test::unit_test_log_formatter::log_entry_types let);

  // Log the entry's value.
  void log_entry_value (std::ostream & output,
                        boost::unit_test::const_string value);

  // End a log entry.
  void log_entry_finish (std::ostream & output);

private:
  /// The package of the test suite.
  std::string package_;

  /// Flag that determines of the log entry is a valid type.
  std::string closing_tag_;
};

#endif  // !defined _CUTS_BOOST_JUNIT_FORMATTER_H_
