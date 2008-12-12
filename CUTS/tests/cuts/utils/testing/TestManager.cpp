// $Id$

#include "Boost_JUnit_Formatter.h"
#include "Test_Log.h"
#include "cuts/utils/testing/svcs/server/testingC.h"
#include "boost/test/unit_test.hpp"
#include "boost/test/unit_test_suite.hpp"
#include "tao/corba.h"
#include "cuts/UUID.h"
#include <sstream>

class fixture
{
public:
  static int init (int argc, char * argv [])
  {
    try
    {
      fixture::orb_ = ::CORBA::ORB_init (argc, argv, argv[0]);
    }
    catch (...)
    {
      BOOST_ERROR ("failed to initialize fixture");
    }

    return -1;
  }

  static ::CORBA::ORB_ptr the_ORB ()
  {
    return ::CORBA::ORB::_duplicate (fixture::orb_.in ());
  }

  fixture (const ACE_CString & strref)
  {
    // Get the test manager.
    ::CORBA::Object_var obj = fixture::orb_->string_to_object (strref.c_str ());

    // Narrow object to a test manager.
    this->tm_ = CUTS::TestManager::_narrow (obj.in ());
  }

  CUTS::TestManager_ptr the_Manager ()
  {
    return CUTS::TestManager::_duplicate (this->tm_.in ());
  }

private:
  static ::CORBA::ORB_var orb_;

  CUTS::TestManager_var tm_;
};

::CORBA::ORB_var fixture::orb_;

namespace test
{
//
// constuctor
//
static void constructor (void)
{
  try
  {
    ::CORBA::ORB_var orb = fixture::the_ORB ();

    // Resolve the TestManager
    const char * str = "corbaname:rir:#CUTS/TestManager/(default)";
    ::CORBA::Object_var obj = orb->string_to_object (str);
    BOOST_CHECK (!::CORBA::is_nil (obj.in ()));

    CUTS::TestManager_var tm = CUTS::TestManager::_narrow (obj.in ());
    BOOST_CHECK (!::CORBA::is_nil (tm.in ()));
  }
  catch (const CORBA::Exception & ex)
  {
    BOOST_ERROR (ex._info ().c_str ());
  }
  catch (...)
  {
    BOOST_ERROR ("caught unknown exception");
  }
}

//
// connect
//
static void details (void)
{
  try
  {
    fixture f ("corbaname:rir:#CUTS/TestManager/(default)");
    CUTS::TestManager_var tm = f.the_Manager ();

    // Get the test details.
    CUTS::TestDetails_var details = tm->details ();

    // Convert the UUID into an useable object.
    ACE_Utils::UUID uuid;
    details->uid >>= uuid;

    std::ostringstream ostr;
    ostr << "Test Name: " << details->name.in () << std::endl
         << "Test UUID: " << uuid.to_string ()->c_str ();

    ACE_DEBUG ((LM_DEBUG,
                "%s\n",
                ostr.str ().c_str ()));
  }
  catch (const CORBA::Exception & ex)
  {
    BOOST_ERROR (ex._info ().c_str ());
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

  // Initialize the fixture then the framework.
  fixture::init (argc, argv);

  test_suite * test = BOOST_TEST_SUITE ("CUTS_TestManager");

  // Add the unit test to the master suite.
  test->add (make_test_case (&test::constructor, "CUTS_TestManager (void)"));
  test->add (make_test_case (&test::details, "details ()"));

  INSTALL_BOOST_LOG_FORMATTER (CUTS_Boost_JUnit_Formatter ("CUTS"), false);

  return test;
}
