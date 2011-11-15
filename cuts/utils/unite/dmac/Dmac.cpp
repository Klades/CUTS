#include "Dmac_App.h"
#include "ace/Singleton.h"
#include "ace/Null_Mutex.h"

#define CUTS_DMAC_APP \
  ACE_Singleton <CUTS_Dmac_App, ACE_Null_Mutex>::instance ()

//
// main
//
int main (int argc, char * argv [])
{
  try
  {
    return CUTS_DMAC_APP->run_main (argc, argv);
  }
  catch (...)
  {
    ACE_ERROR ((LM_ERROR,
                "%T (%t) - %M - caught unknown exception\n"));
  }

  return 1;
}
