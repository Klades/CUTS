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

//=============================================================================
/**
 * @class CUTS_Boost_JUnit_Formatter
 *
 * JUnit log formatter for the Boost unit test framework.
 */
//=============================================================================

class TEST_LOG_FORMATS_Export CUTS_Boost_JUnit_Formatter :
  public boost::unit_test::unit_test_log_formatter
{
public:
  /**
   * Initializing constructor.
   *
   * @param[in]       log         Target unit test log.
   */
  explicit CUTS_Boost_JUnit_Formatter (const boost::unit_test::unit_test_log & log);

  /// Destructor.
  virtual ~CUTS_Boost_JUnit_Formatter (void);

  void start_log (std::ostream & output, bool log_build_info);

  void finish_log (std::ostream & output);

  void log_header (std::ostream & output,
                   boost::unit_test::unit_test_counter counter);

  void track_test_case_scope (std::ostream & output,
                              const boost::unit_test::test_case & tc,
                              bool in_out);

  void log_exception (std::ostream & output,
                      boost::unit_test::const_string test_name,
                      boost::unit_test::const_string explanation);

  void begin_log_entry (std::ostream & output,
                        log_entry_types let);

  void log_entry_value (std::ostream & output,
                        boost::unit_test::const_string value);

  void end_log_entry (std::ostream & output);

private:
  /// Flag that determines of the log entry is a valid type.
  std::string closing_tag_;
};

#endif  // !defined _CUTS_BOOST_JUNIT_FORMATTER_H_
