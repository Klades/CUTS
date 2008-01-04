// -*- C++ -*-
// $Id$

#include <math.h>
#include "boost/test/unit_test.hpp"
#include "cuts/workers/CPU/CPU_Worker.h"
#include "ace/OS_NS_sys_time.h"
#include "ace/Log_Msg.h"
#include "ace/Time_Value.h"
#include "ace/High_Res_Timer.h"
#include "ace/Thread.h"
#include "ace/Malloc_T.h"
#include "ace/Null_Mutex.h"
#include "Boost_JUnit_Formatter.h"
#include "Test_Log.h"

void Unit_Test_CPU_run (void)
{
  CUTS_CPU_Worker worker;
  ACE_High_Res_Timer timer;
  ACE_Time_Value elapsed;

  for (size_t i = 0; i < 100; i ++)
  {
    size_t msec = 500;

    timer.start ();
    worker.run (msec);
    timer.stop ();

    timer.elapsed_time (elapsed);
    ACE_DEBUG ((LM_DEBUG,
                "proposed time = %d; elapsed time = %d; diff = %d msec\n",
                msec,
                elapsed.msec (),
                msec - elapsed.msec ()));
  }
}

//
// init_unit_test_suite
//
bool init_unit_test_suite (void)
{
  using namespace ::boost::unit_test;

  // Add the unit test to the test suite.
  framework::master_test_suite ().p_name.value = "CUTS_CPU_Worker";
  framework::master_test_suite ().add (BOOST_TEST_CASE (&Unit_Test_CPU_run));

  INSTALL_BOOST_LOG_FORMATTER (CUTS_Boost_JUnit_Formatter, false);
  return true;
}
