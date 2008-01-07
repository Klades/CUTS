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
#include "boost/test/unit_test_log.hpp"

#define INSTALL_BOOST_LOG_FORMATTER(format_type, retval) \
  do \
  { \
    boost::unit_test::unit_test_log_formatter * formatter = 0; \
    ACE_NEW_RETURN (formatter, format_type, retval); \
    boost::unit_test::unit_test_log.set_formatter (formatter); \
  } while (0);

#endif  // !defined _CUTS_TEST_LOG_H_
