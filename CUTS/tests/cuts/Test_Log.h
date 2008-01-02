// -*- C++ -*-

//=============================================================================
/**
 * @file        Test_Log.h
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _CUTS_TEST_LOG_H_
#define _CUTS_TEST_LOG_H_

#include "ace/OS_Memory.h"

#define INSTALL_BOOST_LOG_FORMATTER(format_type, test_suite) \
  do \
  { \
    boost::unit_test::unit_test_log_formatter * formatter = 0; \
    ACE_NEW_RETURN (formatter, \
                    format_type (boost::unit_test::unit_test_log::instance ()), \
                    test_suite); \
    boost::unit_test::unit_test_log::instance ().set_log_formatter (formatter); \
  } while (0);

#endif  // !defined _CUTS_TEST_LOG_H_
