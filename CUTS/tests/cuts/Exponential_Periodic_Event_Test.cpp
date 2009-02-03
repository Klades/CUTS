// $Id$

#include "boost/test/unit_test.hpp"
#include "cuts/Periodic_Event_T.h"
#include "ace/Condition_T.h"
#include "ace/RW_Thread_Mutex.h"
#include "ace/Guard_T.h"
#include "ace/streams.h"
#include "Boost_JUnit_Formatter.h"
#include "Test_Log.h"

class Simple_Component
{
public:
  Simple_Component (size_t max_count)
    : count_ (0),
      max_count_ (max_count),
      done_ (mutex_)
  {

  }

  void handle_timeout (void)
  {
    ACE_GUARD (ACE_Thread_Mutex, guard, this->mutex_);

    // Increment the counter.
    ++ this->count_;

    // Signal all the waiting threads.
    if (this->count_ == this->max_count_)
      this->done_.broadcast ();
  }

  size_t count (void) const
  {
    return this->count_;
  }

  void wait (void)
  {
    ACE_GUARD (ACE_Thread_Mutex, guard, this->mutex_);
    this->done_.wait ();
  }

private:
  size_t count_;

  size_t max_count_;

  ACE_Thread_Mutex mutex_;

  ACE_Condition <ACE_Thread_Mutex> done_;
};

void run (void)
{
  Simple_Component component (2000);

  CUTS_Periodic_Event_T <Simple_Component> generator;
  generator.init (&component, &Simple_Component::handle_timeout);
  generator.configure (CUTS_Periodic_Event::PE_EXPONENTIAL, 20);

  // Get the start time of the test.
  ACE_Time_Value start_time = ACE_OS::gettimeofday ();

  // Activate the test and wait for it to complete.
  generator.activate ();
  component.wait ();

  // Get the stop time of the test.
  ACE_Time_Value stop_time = ACE_OS::gettimeofday ();

  // Calculate the duration, and the arrival rate.
  ACE_Time_Value duration = stop_time - start_time;

  std::cout << "results: " << component.count () / duration.sec ()
            << " events/sec" << std::endl;
}

//
// init_unit_test_suite
//
boost::unit_test::test_suite *
init_unit_test_suite (int argc, char * argv[])
{
  using namespace ::boost::unit_test;

  test_suite * test = BOOST_TEST_SUITE ("CUTS_Exponential_Periodic_Event");

  // Add the unit test to the master suite.
  test->p_name.value = "CUTS_Exponential_Periodic_Event";

  test->add (make_test_case (&run, "run"));

  INSTALL_BOOST_LOG_FORMATTER (CUTS_Boost_JUnit_Formatter ("CUTS"), false);
  return test;
}
