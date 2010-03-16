#include "cuts/Time_Value_History.h"
#include "boost/test/unit_test.hpp"
#include "Boost_JUnit_Formatter.h"
#include "Test_Log.h"

struct fixture
{
  fixture (void)
	  : tvx()
  {
  }

  CUTS_Time_Value_Ex tvx;
};

//=============================================================================
/*
 * Unit_Test: constructor
 */
//=============================================================================

void constructor (void)
{
  CUTS_Time_Value_Ex time_value_ex;

  BOOST_CHECK (time_value_ex.start_ == ACE_Time_Value::zero);
  BOOST_CHECK (time_value_ex.stop_ == ACE_Time_Value::zero);
}


//=============================================================================
/*
 * Unit_Test: copy_constructor
 */
//=============================================================================

void copy_constructor (void)
{
  fixture f;
  CUTS_Time_Value_Ex time_value_ex(f.tvx);

  BOOST_CHECK (time_value_ex.start_ == f.tvx.start_);
  BOOST_CHECK (time_value_ex.stop_ == f.tvx.start_);
}

//=============================================================================
/*
 * Unit_Test: operator_equal
 */
//=============================================================================

void operator_equal (void)
{
  fixture f;
  CUTS_Time_Value_Ex time_value_ex;

  time_value_ex = f.tvx;

  BOOST_CHECK (time_value_ex.start_ == f.tvx.start_);
  BOOST_CHECK (time_value_ex.stop_ == f.tvx.stop_);
}

//
// init_unit_test_suite
//
boost::unit_test::test_suite *
init_unit_test_suite (int argc, char * argv[])
{
  using namespace ::boost::unit_test;

  test_suite * test = BOOST_TEST_SUITE ("CUTS_Time_Value_History");

  // Add the unit test to the master suite.
  test->p_name.value = "CUTS_Time_Value_History";
  test->add (make_test_case (&constructor, "CUTS_Time_Value_Ex (void)"));
  test->add (make_test_case (&copy_constructor, "CUTS_Time_Value_Ex (const CUTS_Time_Value_Ex &amp;)"));
  test->add (make_test_case (&operator_equal, "operator = (const CUTS_Time_Value_Ex &amp;)"));

  INSTALL_BOOST_LOG_FORMATTER (CUTS_Boost_JUnit_Formatter ("CUTS"), false);

  return test;
}