// $Id$

#include "ace/Singleton.h"
#include "ace/Null_Mutex.h"
#include "NodeDaemon_Client_App.h"

#define CUTS_NODEDAEMON_CLIENT \
  ACE_Singleton <CUTS_NodeDaemon_Client_App, ACE_Null_Mutex>::instance ()

//
// ACE_TMAIN
//
int ACE_TMAIN (int argc, char * argv [])
{
  try
  {
    int retval = CUTS_NODEDAEMON_CLIENT->run_main (argc, argv);
    return 0 == retval ? 0 : 1;
  }
  catch (...)
  {
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - caught unknown exception\n")));
  }

  return 1;
}
