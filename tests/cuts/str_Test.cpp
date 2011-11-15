// $Id$

#include "boost/test/unit_test.hpp"
#include "Boost_JUnit_Formatter.h"
#include "Test_Log.h"

#include "cuts/str.h"
#include "ace/OS_NS_string.h"

struct fixture
{
  fixture (void)
    : str_ ("This is a simple string")
  {
  }

  CUTS_str str_;
};

//=============================================================================
/*
 * Unit_Test: constructor
 */
//=============================================================================

void constructor (void)
{
  CUTS_str str;

  BOOST_CHECK (ACE_OS::strcmp (str, "") == 0);
  BOOST_CHECK (ACE_OS::strlen (str) == 0);
}

//=============================================================================
/*
 * Unit_Test: init_constructor
 */
//=============================================================================

void init_constructor (void)
{
  const char * str = "This is a simple string";
  CUTS_str s1 (str);

  BOOST_CHECK (ACE_OS::strcmp (s1, str) == 0);
}

//=============================================================================
/*
 * Unit_Test: copy_constructor
 */
//=============================================================================

void copy_constructor (void)
{
  fixture f;
  CUTS_str str (f.str_);

  BOOST_CHECK (ACE_OS::strcmp (str, f.str_) == 0);
}

//=============================================================================
/*
 * Unit_Test: operator_equal
 */
//=============================================================================

void operator_equal (void)
{
  fixture f;
  CUTS_str str;

  str = f.str_;

  BOOST_CHECK (ACE_OS::strcmp (str, f.str_) == 0);
}


//
// init_unit_test_suite
//
boost::unit_test::test_suite *
init_unit_test_suite (int argc, char * argv[])
{
  using namespace ::boost::unit_test;

  test_suite * test = BOOST_TEST_SUITE ("CUTS_str");

  // Add the unit test to the master suite.
  test->p_name.value = "CUTS_str";
  test->add (make_test_case (&constructor, "CUTS_str (void)"));
  test->add (make_test_case (&init_constructor, "CUTS_str (const char *)"));
  test->add (make_test_case (&copy_constructor, "CUTS_str (const CUTS_str &amp;)"));
  test->add (make_test_case (&operator_equal, "operator = (const CUTS_str &amp;)"));

  INSTALL_BOOST_LOG_FORMATTER (CUTS_Boost_JUnit_Formatter ("CUTS"), false);

  return test;
}
