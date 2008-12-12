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

    for (int i = 0; i < 30; ++ i)
    {
      BOOST_CHECK (logger.log (LM_DEBUG,
                              "This is a simple message with an integer %d",
                              2345));
    }
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
boost::unit_test::test_suite *
init_unit_test_suite (int argc, char * argv[])
{
  using namespace ::boost::unit_test;

  test_suite * test = BOOST_TEST_SUITE ("CUTS_Test_Logger");

  // Add the unit test to the master suite.
  test->p_name.value = "CUTS_Test_Logger";
  test->add (make_test_case (&test::constructor, "CUTS_Test_Logger (void)"));
  test->add (make_test_case (&test::configure, "configure (short)"));
  test->add (make_test_case (&test::connect_noname, "connect (void)"));
  test->add (make_test_case (&test::log, "log (long, const char *, ...)"));

  INSTALL_BOOST_LOG_FORMATTER (CUTS_Boost_JUnit_Formatter ("CUTS"), false);

  return test;
}
