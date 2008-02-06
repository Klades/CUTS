// $Id$

#include "boost/test/unit_test.hpp"
#include "Boost_JUnit_Formatter.h"
#include "Test_Log.h"

#include "cuts/Statistics_T.h"

struct fixture
{
public:
  fixture (void)
  {
    this->stats_ += 10;
    this->stats_ += 5;
    this->stats_ += 15;
  }

  CUTS_Statistics_T <long> stats_;
};

//=============================================================================
/*
 * Unit_Test: constructor
 */
//=============================================================================

void constructor (void)
{
  CUTS_Statistics_T <long> stats;
  BOOST_CHECK (stats.count () == 0);
  BOOST_CHECK (stats.min_value () == 0);
  BOOST_CHECK (stats.max_value () == 0);
  BOOST_CHECK (stats.summation () == 0);
}

//=============================================================================
/*
 * Unit_Test: copy_constructor
 */
//=============================================================================

void copy_constructor (void)
{
  fixture f;

  CUTS_Statistics_T <long> s2 (f.stats_);
  BOOST_CHECK (f.stats_.count () == 3);
  BOOST_CHECK (f.stats_.min_value () == 5);
  BOOST_CHECK (f.stats_.max_value () == 15);
  BOOST_CHECK (f.stats_.summation () == 30);
}

//=============================================================================
/*
 * Unit_Test: operator_plus_equal_value
 */
//=============================================================================

void operator_plus_equal_value (void)
{
  CUTS_Statistics_T <long> stats;

  stats += 10;
  BOOST_CHECK (stats.count () == 1);
  BOOST_CHECK (stats.min_value () == 10);
  BOOST_CHECK (stats.max_value () == 10);
  BOOST_CHECK (stats.summation () == 10);

  stats += 5;
  BOOST_CHECK (stats.count () == 2);
  BOOST_CHECK (stats.min_value () == 5);
  BOOST_CHECK (stats.max_value () == 10);
  BOOST_CHECK (stats.summation () == 15);

  stats += 15;
  BOOST_CHECK (stats.count () == 3);
  BOOST_CHECK (stats.min_value () == 5);
  BOOST_CHECK (stats.max_value () == 15);
  BOOST_CHECK (stats.summation () == 30);
}

//=============================================================================
/*
 * Unit_Test: operator_plus_equal_statistics
 */
//=============================================================================

void operator_plus_equal_statistics (void)
{
  fixture f;
  CUTS_Statistics_T <long> stats;

  stats += f.stats_;
  BOOST_CHECK (stats.count () == 3);
  BOOST_CHECK (stats.min_value () == 5);
  BOOST_CHECK (stats.max_value () == 15);
  BOOST_CHECK (stats.summation () == 30);
}

//=============================================================================
/*
 * Unit_Test: operator_equal_statistics
 */
//=============================================================================

void operator_equal_statistics (void)
{
  fixture f;
  CUTS_Statistics_T <long> stats;

  stats = f.stats_;
  BOOST_CHECK (stats.count () == 3);
  BOOST_CHECK (stats.min_value () == 5);
  BOOST_CHECK (stats.max_value () == 15);
  BOOST_CHECK (stats.summation () == 30);
}

//=============================================================================
/*
 * Unit_Test: reset
 */
//=============================================================================

void reset (void)
{
  fixture f;
  f.stats_.reset ();

  BOOST_CHECK (f.stats_.count () == 0);
  BOOST_CHECK (f.stats_.min_value () == 0);
  BOOST_CHECK (f.stats_.max_value () == 0);
  BOOST_CHECK (f.stats_.summation () == 0);
}

//=============================================================================
/*
 * Unit_Test: avg_value
 */
//=============================================================================

void avg_value (void)
{
  fixture f;

  long avg;
  f.stats_.avg_value (avg);

  BOOST_CHECK (avg == 10);
}

//
// init_unit_test_suite
//
bool init_unit_test_suite (void)
{
  using namespace ::boost::unit_test;

  // Add the unit test to the master suite.
  framework::master_test_suite ().p_name.value = "CUTS_Statistics_T";

  framework::master_test_suite ().add (
    make_test_case (&constructor,
    "Statistics_T (void)"));

  framework::master_test_suite ().add (
    make_test_case (&copy_constructor,
    "Statistics_T (const Statistics_T &)"));

  framework::master_test_suite ().add (
    make_test_case (&operator_plus_equal_value,
    "operator += (T &)"));

  framework::master_test_suite ().add (
    make_test_case (&operator_plus_equal_statistics,
    "operator += (const CUTS_Statistic_T &)"));

  framework::master_test_suite ().add (
    make_test_case (&operator_equal_statistics,
    "operator = (const CUTS_Statistic_T &)"));

  framework::master_test_suite ().add (
    make_test_case (&reset,
    "reset (void)"));

  framework::master_test_suite ().add (
    make_test_case (&avg_value,
    "avg_value (T &)"));

  INSTALL_BOOST_LOG_FORMATTER (CUTS_Boost_JUnit_Formatter ("CUTS"), false);

  return true;
}
