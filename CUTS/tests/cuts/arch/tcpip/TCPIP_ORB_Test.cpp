// $Id$

#include "Boost_JUnit_Formatter.h"
#include "Test_Log.h"
#include "cuts/arch/tcpip/TCPIP_ORB.h"
#include "boost/test/unit_test.hpp"

namespace test
{

static char ** __argv__;
static int __argc__;

//
// constuctor
//
void constructor (void)
{
  CUTS_TCPIP_ORB tcpip_orb;
}

void init (void)
{
  CUTS_TCPIP_ORB tcpip_orb;
  int retval = tcpip_orb.init (__argc__, __argv__);

  BOOST_CHECK (-1 != retval);
}

}

//
// init_unit_test_suite
//
boost::unit_test::test_suite *
init_unit_test_suite (int argc, char * argv[])
{
  using namespace ::boost::unit_test;

  // Initialize ACE.
  ACE::init ();

  test::__argc__ = argc;
  test::__argv__ = argv;

  test_suite * test = BOOST_TEST_SUITE ("CUTS_TCPIP_ORB");

  // Add the unit test to the master suite.
  test->p_name.value = "CUTS_TCPIP_ORB";
  test->add (make_test_case (&test::constructor, "CUTS_TCPIP_ORB (void)"));
  test->add (make_test_case (&test::init, "CUTS_TCPIP_ORB (void)"));

  INSTALL_BOOST_LOG_FORMATTER (CUTS_Boost_JUnit_Formatter ("CUTS"), false);

  return test;
}
