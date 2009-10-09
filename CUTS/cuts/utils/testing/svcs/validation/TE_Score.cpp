// $Id$

#include "ace/Singleton.h"
#include "ace/Null_Mutex.h"
#include "TE_Score_App.h"

#define CUTS_TE_SCORE_APP \
  ACE_Singleton < CUTS_TE_Score_App, ACE_Null_Mutex>::instance ()

//
// ACE_TMAIN
//
int ACE_TMAIN (int argc, char * argv [])
{
  try
  {
    int retval = CUTS_TE_SCORE_APP->run_main (argc, argv);
    return retval == 0 ? 0 : 1;
  }
  catch (...)
  {
    return 1;
  }
}
