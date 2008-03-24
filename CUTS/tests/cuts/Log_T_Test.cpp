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
 * Unit_Test: constructor
 */
//=============================================================================

void constructor (void)
{
  CUTS_Log_T <long, ACE_Null_Mutex> log;
  
  BOOST_CHECK (log.size () == 0);
  BOOST_CHECK (log.used_size () == 0);
  BOOST_CHECK (log.free_size () == 0);
  BOOST_CHECK (log.auto_grow ());
}


//=============================================================================
/*
 * Unit_Test: constructor_autogrow
 */
//=============================================================================

void constructor_autogrow (void)
{
  CUTS_Log_T <long, ACE_Null_Mutex> log (0, true);

  BOOST_CHECK (log.size () == 0);
  BOOST_CHECK (log.free_size () == 0);
  BOOST_CHECK (log.auto_grow () == true);
}

//=============================================================================
/*
 * Unit_Test: constructor_no_autogrow
 */
//=============================================================================

void constructor_no_autogrow (void)
{
  CUTS_Log_T <long, ACE_Null_Mutex> log (0, false);

  BOOST_CHECK (log.size () == 0);
  BOOST_CHECK (log.free_size () == 0);
  BOOST_CHECK (log.auto_grow () == false);
}

//=============================================================================
/*
 * Unit_Test: copy_constructor
 */
//=============================================================================

void copy_constructor (void)
{

}

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
 * Unit_Test: auto_grow
 */
//=============================================================================

void auto_grow (void)
{
  CUTS_Log_T <long, ACE_Null_Mutex> log (0, false);
  BOOST_CHECK (log.auto_grow () == false);

  log.auto_grow (true);
  BOOST_CHECK (log.auto_grow () == true);
}

//=============================================================================
/*
 * Unit_Test: next_free_record
 */
//=============================================================================

void next_free_record (void)
{
  int size = ACE_OS::rand () % 71;
  CUTS_Log_T <long, ACE_Null_Mutex> log (size, false);
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

  // Now, let's enable auto grow. This should allow use to add
  // N more records.
  int extra = ACE_OS::rand () % 23;
  log.auto_grow (true);

  for (int i = 1; i <= extra; i ++)
  {
    val = log.next_free_record ();

    BOOST_CHECK (val != 0);
    BOOST_CHECK (log.used_size () == size + i);
    BOOST_CHECK (log.free_size () == log.size () - log.used_size ());

    if (val != 0)
      *val = i;
  }
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

  CUTS_Log_T <long, ACE_Null_Mutex> log (size, false);
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
bool init_unit_test_suite (void)
{
  using namespace ::boost::unit_test;

  // Add the unit test to the master suite.
  framework::master_test_suite ().p_name.value =
    "CUTS_Log_T &lt;T&gt;";

  framework::master_test_suite ().add (
    make_test_case (&constructor,
    "CUTS_Log_T (void)"));

  framework::master_test_suite ().add (
    make_test_case (&constructor_no_autogrow,
    "CUTS_Log_T (size_t, bool auto_grow = false)"));

  framework::master_test_suite ().add (
    make_test_case (&constructor_autogrow,
    "CUTS_Log_T (size_t, bool auto_grow = true)"));

  framework::master_test_suite ().add (
    make_test_case (&constructor_size,
    "CUTS_Log_T (size_t n)"));

  //framework::master_test_suite ().add (
  //  make_test_case (&copy_constructor,
  //  "CUTS_Log_T (const CUTS_Log_T &amp;)"));

  framework::master_test_suite ().add (
    make_test_case (&auto_grow,
    "auto_grow ([bool flag])"));

  framework::master_test_suite ().add (
    make_test_case (&next_free_record,
    "next_free_record (void)"));

  framework::master_test_suite ().add (
    make_test_case (&reset,
    "reset (void)"));

  INSTALL_BOOST_LOG_FORMATTER (CUTS_Boost_JUnit_Formatter ("CUTS"), false);
  return true;
}
