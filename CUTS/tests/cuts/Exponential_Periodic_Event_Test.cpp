// $Id$

#include "boost/test/unit_test.hpp"
#include "cuts/Periodic_Event_T.h"
#include "ace/Condition_T.h"
#include "ace/Recursive_Thread_Mutex.h"
#include "ace/Guard_T.h"
#include "ace/streams.h"
#include "Boost_JUnit_Formatter.h"
#include "Test_Log.h"

class Simple_Test_Event_Port
{
public:
  Simple_Test_Event_Port (size_t max_count)
    : count_ (0),
      max_count_ (max_count),
      is_done_ (mutex_)
  {

  }

  void handle_timeout (void)
  {
    ACE_GUARD (ACE_Thread_Mutex, guard, this->mutex_);

    // Increment the counter.
    ++ this->count_;

    // Signal all the waiting threads.
    if (this->count_ == this->max_count_)
      this->is_done_.broadcast ();
  }

  size_t count (void) const
  {
    return this->count_;
  }

  int run (void)
  {
    this->start_time_ = ACE_OS::gettimeofday ();

    ACE_GUARD_RETURN (ACE_Thread_Mutex, guard, this->mutex_, -1);
    this->is_done_.wait ();

    this->stop_time_ = ACE_OS::gettimeofday ();
    return 0;
  }

  size_t events_per_second () const
  {
    ACE_Time_Value duration = this->stop_time_ - this->start_time_;
    return this->count_ / duration.sec ();
  }


private:
  size_t count_;

  size_t max_count_;

  ACE_Thread_Mutex mutex_;

  ACE_Condition <ACE_Thread_Mutex> is_done_;

  ACE_Time_Value start_time_;

  ACE_Time_Value stop_time_;
};

void run (void)
{
  Simple_Test_Event_Port test (2000);

  CUTS_Periodic_Event_T <Simple_Test_Event_Port> generator;
  generator.init (&test, &Simple_Test_Event_Port::handle_timeout);
  generator.configure (CUTS_Periodic_Event::PE_EXPONENTIAL, 20);

  // Activate the test and wait for it to complete.
  if (generator.activate () == 0)
  {
    test.run ();
  }
  else
    ACE_ERROR ((LM_ERROR,
                "%T (%t) - %M - failed to activate the generator\n"));

  std::cout << "results: " << test.events_per_second ()
            << " events/sec" << std::endl;

  generator.deactivate ();
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
