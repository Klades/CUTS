// $Id$

#include "ace/Null_Mutex.h"
#include "ace/Singleton.h"
#include "Executor_App.h"

#define CUTS_T2M_EXECUTOR_APP \
  ACE_Singleton <CUTS_T2M_Executor_App, ACE_Null_Mutex>::instance ()

//
// main
//
int main (int argc, char * argv [])
{
  int retval;

  try
  {
    retval = CUTS_T2M_EXECUTOR_APP->run_main (argc, argv);
  }
  catch (...)
  {
    ACE_ERROR ((LM_ERROR,
                "%T (%t) - %M - caught unknown exception (%n:%l)\n"));

    retval = -1;
  }

  return retval == 0 ? 0 : 1;
}
