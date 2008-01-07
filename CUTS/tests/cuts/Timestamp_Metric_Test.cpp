// $Id$

#include "boost/test/unit_test.hpp"
#include "cuts/Timestamp_Metric.h"
#include "ace/OS_NS_sys_time.h"
#include "Boost_JUnit_Formatter.h"
#include "Test_Log.h"

//=============================================================================
/*
 * Unit_Test: CUTS_Timestamp_Metric_contructor
 */
//=============================================================================

void CUTS_Timestamp_Metric_contructor (void)
{
  // Test the default constructor.
  CUTS_Timestamp_Metric tma;
  BOOST_CHECK (tma.timestamp () == ACE_Time_Value::zero);

  // Test the initializing constructor.
  ACE_Time_Value current_time = ACE_OS::gettimeofday ();
  CUTS_Timestamp_Metric tmb (current_time);

  BOOST_CHECK (tmb.timestamp () == current_time);
}

//=============================================================================
/*
 * Unit_Test: CUTS_Timestamp_Metric_setter
 */
//=============================================================================

void CUTS_Timestamp_Metric_setter (void)
{
  CUTS_Timestamp_Metric metric;
  ACE_Time_Value current_time = ACE_OS::gettimeofday ();

  metric.timestamp (current_time);
  BOOST_CHECK (metric.timestamp () == current_time);
}

//=============================================================================
/*
 * Unit_Test: CUTS_Timestamp_Metric_reset
 */
//=============================================================================

void CUTS_Timestamp_Metric_reset (void)
{
  CUTS_Timestamp_Metric metric (ACE_OS::gettimeofday ());
  metric.reset ();

  BOOST_CHECK (metric.timestamp () == ACE_Time_Value::zero);
}

//=============================================================================
/*
 * Unit_Test: CUTS_Timestamp_Metric_is_valid
 */
//=============================================================================

void CUTS_Timestamp_Metric_is_valid (void)
{
  CUTS_Timestamp_Metric metric;
  BOOST_CHECK (!metric.is_valid ());

  metric.timestamp (ACE_OS::gettimeofday ());
  BOOST_CHECK (metric.is_valid ());
}

//
// init_unit_test_suite
//
bool init_unit_test_suite (void)
{
  using namespace ::boost::unit_test;

  // Add the unit test to the test suite.
  framework::master_test_suite ().p_name.value = "CUTS_Timestamp_Metric";
  framework::master_test_suite ().add (BOOST_TEST_CASE (&CUTS_Timestamp_Metric_contructor));
  framework::master_test_suite ().add (BOOST_TEST_CASE (&CUTS_Timestamp_Metric_setter));
  framework::master_test_suite ().add (BOOST_TEST_CASE (&CUTS_Timestamp_Metric_reset));
  framework::master_test_suite ().add (BOOST_TEST_CASE (&CUTS_Timestamp_Metric_is_valid));

  INSTALL_BOOST_LOG_FORMATTER (CUTS_Boost_JUnit_Formatter ("CUTS"), false);
  return true;
}
