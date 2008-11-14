// $Id$

#include "Boost_JUnit_Formatter.h"
#include "Test_Log.h"
#include "cuts/workers/Test_Logger/Test_Logger.h"
#include "boost/test/unit_test.hpp"

namespace test
{
//
// constuctor
//
static void constructor (void)
{
  CUTS_Test_Logger logger;
}

//
// connect
//
static void configure (void)
{
  try
  {
    CUTS_Test_Logger logger;
    BOOST_CHECK (logger.configure (10000));
  }
  catch (...)
  {
    BOOST_ERROR ("caught unknown exception");
  }
}

//
// connect_noname
//
static void connect_noname (void)
{
  try
  {
    CUTS_Test_Logger logger;
    BOOST_CHECK (logger.configure (10000));
    BOOST_CHECK (logger.connect ());
  }
  catch (...)
  {
    BOOST_ERROR ("caught unknown exception");
  }
}

static void log (void)
{
  try
  {
    CUTS_Test_Logger logger;
    BOOST_CHECK (logger.configure (10000));
    BOOST_CHECK (logger.connect ());

    BOOST_CHECK (logger.log (LM_DEBUG, "This is a simple message"));

    BOOST_CHECK (logger.log (LM_DEBUG,
                             "This is a simple message with an integer %d",
                             2345));
  }
  catch (...)
  {
    BOOST_ERROR ("caught unknown exception");
  }
}

}

//
// init_unit_test_suite
//
bool init_unit_test_suite (void)
{
  using namespace ::boost::unit_test;

  // Add the unit test to the master suite.
  framework::master_test_suite ().p_name.value = "CUTS_Test_Logger";

  framework::master_test_suite ().add (
    make_test_case (&test::constructor, "CUTS_Test_Logger (void)"));

  framework::master_test_suite ().add (
    make_test_case (&test::configure, "configure (short)"));

  framework::master_test_suite ().add (
    make_test_case (&test::connect_noname, "connect (void)"));

  framework::master_test_suite ().add (
    make_test_case (&test::log, "log (long, const char *, ...)"));

  INSTALL_BOOST_LOG_FORMATTER (CUTS_Boost_JUnit_Formatter ("CUTS"),
                               false);

  return true;
}
