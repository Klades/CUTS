// $Id$

#include <algorithm>
#include <vector>
#include <numeric>
#include "boost/test/unit_test.hpp"
#include "ace/OS_NS_unistd.h"
#include "ace/OS_NS_stdlib.h"
#include "cuts/Time_Measurement.h"
#include "Boost_JUnit_Formatter.h"
#include "Test_Log.h"

static CUTS_Time_Measurement tm_;

//=============================================================================
/*
 * Time_Measurement_Constructor
 */
//=============================================================================

void Time_Measurement_Constructor (void)
{
  BOOST_CHECK (tm_.max_value () == ACE_Time_Value::zero);
  BOOST_CHECK (tm_.min_value () == ACE_Time_Value::zero);
  BOOST_CHECK (tm_.summation () == ACE_Time_Value::zero);
  BOOST_CHECK (tm_.count () == 0);
}

//=============================================================================
/*
 * Time_Measurement_Add_Time
 */
//=============================================================================

void Time_Measurement_Add_Time (void)
{
  ACE_Time_Value tv;

  long msec = ACE_OS::rand () % 1000;
  tv.msec (msec);

  do
  {
    CUTS_Time_Measurement tm;
    tm += tv;

    BOOST_CHECK (tm.count () == 1);
    BOOST_CHECK (tm.summation () == tv);
    BOOST_CHECK (tm.max_value () == tv);
    BOOST_CHECK (tm.min_value () == tv);
  } while (0);

  // randomly generate 50-100 numbers and verify the time measurement
  // object handles them correctly.

  size_t length = 50 + (ACE_OS::rand () % 50);

  typedef std::vector <long> Long_Vector;
  Long_Vector values (length);

  for (size_t i = 0; i < length; i ++)
  {
    msec = ACE_OS::rand () % 1000;
    tv.msec (msec);

    values[i] = msec;

    tm_ += tv;
  }

  Long_Vector::iterator min_iter =
    std::min_element (values.begin (), values.end ());
  Long_Vector::iterator max_iter =
    std::max_element (values.begin (), values.end ());
  long sum = std::accumulate (values.begin (), values.end (), 0);

  BOOST_CHECK (tm_.count () == length);
  BOOST_CHECK (tm_.min_value ().msec () == *min_iter);
  BOOST_CHECK (tm_.max_value ().msec () == *max_iter);
  BOOST_CHECK (tm_.summation ().msec () == sum);
}

//=============================================================================
/*
 * Time_Measurement_Reset
 */
//=============================================================================

void Time_Measurement_Reset (void)
{
  tm_.reset ();

  BOOST_CHECK (tm_.max_value () == ACE_Time_Value::zero);
  BOOST_CHECK (tm_.min_value () == ACE_Time_Value::zero);
  BOOST_CHECK (tm_.summation () == ACE_Time_Value::zero);
  BOOST_CHECK (tm_.count () == 0);
}

//
// init_unit_test_suite
//
boost::unit_test::test_suite *
init_unit_test_suite (int argc, char * argv[])
{
  using namespace ::boost::unit_test;

  test_suite * test = BOOST_TEST_SUITE ("CUTS_Time_Measurement");

  // Add the unit test to the test suite.
  test->p_name.value = "CUTS_Time_Measurement";
  test->add (BOOST_TEST_CASE (&Time_Measurement_Constructor));
  test->add (BOOST_TEST_CASE (&Time_Measurement_Add_Time));
  test->add (BOOST_TEST_CASE (&Time_Measurement_Reset));

  INSTALL_BOOST_LOG_FORMATTER (CUTS_Boost_JUnit_Formatter ("CUTS"), false);

  return test;
}
