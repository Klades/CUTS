// $Id$

#include "Unite_App.h"
#include "ace/Singleton.h"
#include "ace/Null_Mutex.h"

#define CUTS_UNITE_APP \
  ACE_Singleton <CUTS_Unite_App, ACE_Null_Mutex>::instance ()

//
// main
//
int main (int argc, char * argv [])
{
  u_long default_mask =
    LM_EMERGENCY | LM_ALERT | LM_CRITICAL | LM_ERROR | LM_WARNING | LM_NOTICE;

  ACE_Log_Msg::instance ()->priority_mask (default_mask, ACE_Log_Msg::PROCESS);

  try
  {
    return CUTS_UNITE_APP->run_main (argc, argv);
  }
  catch (...)
  {
    ACE_ERROR ((LM_ERROR,
                "%T (%t) - %M - caught unknown exception\n"));
  }

  return 1;
}