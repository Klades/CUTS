// $Id$

#include "boost/test/unit_test.hpp"
#include "Boost_JUnit_Formatter.h"
#include "Test_Log.h"

#include "cuts/Log_T.h"
#include "ace/Null_Mutex.h"

template <typename T>
struct log_no_autogrow
{
public:
  log_no_autogrow (void)
  {

  }

  CUTS_Log_T <T, ACE_Null_Mutex> log_;
};

template <typename T>
struct log_autogrow
{
public:
  log_autogrow (void)
  {

  }

  CUTS_Log_T <T, ACE_Null_Mutex> log_;
};

//=============================================================================
/*
 * Unit_Test: constructor_size
 */
//=============================================================================

void constructor_size (void)
{
  int size = ACE_OS::rand () % 71;
  CUTS_Log_T <long, ACE_Null_Mutex> log (size);

  BOOST_CHECK (log.size () == size);
  BOOST_CHECK (log.used_size () == 0);
  BOOST_CHECK (log.free_size () == size);
}

//=============================================================================
/*
 * Unit_Test: next_free_record
 */
//=============================================================================

void next_free_record (void)
{
  int size = ACE_OS::rand () % 71;
  CUTS_Log_T <long, ACE_Null_Mutex> log (size);
  long * val;

  for (int i = 1; i <= size; i ++)
  {
    // Get the next free record.
    val = log.next_free_record ();

    // Validate the record.
    BOOST_CHECK (val != 0);
    BOOST_CHECK (log.used_size () == i);
    BOOST_CHECK (log.free_size () == size - i);

    if (val != 0)
      *val = i;
  }

  // The next record should be NIL.
  val = log.next_free_record ();
  BOOST_CHECK (val == 0);
}

//=============================================================================
/*
 * Unit_Test: reset
 */
//=============================================================================

void reset (void)
{
  int size = ACE_OS::rand () % 71;
  int stop = ACE_OS::rand () % size;

  CUTS_Log_T <long, ACE_Null_Mutex> log (size);
  long * val;

  for (int i = 1; i <= stop; i ++)
  {
    // Get the next free record.
    val = log.next_free_record ();

    if (val != 0)
      *val = i;
  }

  log.reset ();
  BOOST_CHECK (log.free_size () == size);
  BOOST_CHECK (log.used_size () == 0);
}

//
// init_unit_test_suite
//
boost::unit_test::test_suite *
init_unit_test_suite (int argc, char * argv[])
{
  using namespace ::boost::unit_test;

  test_suite * test = BOOST_TEST_SUITE ("CUTS_Log_T &lt;T&gt;");

  // Add the unit test to the master suite.
  test->p_name.value = "CUTS_Log_T &lt;T&gt;";

  test->add (make_test_case (&constructor_size, "CUTS_Log_T (size_t n)"));
  test->add (make_test_case (&next_free_record, "next_free_record (void)"));
  test->add (make_test_case (&reset, "reset (void)"));

  INSTALL_BOOST_LOG_FORMATTER (CUTS_Boost_JUnit_Formatter ("CUTS"), false);
  return test;
}
