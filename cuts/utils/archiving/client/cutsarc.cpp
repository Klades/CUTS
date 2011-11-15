// $Id$

#include "Test_Archive_Client.h"
#include "ace/Null_Mutex.h"
#include "ace/Singleton.h"

#define CUTS_TEST_ARCHIVE_CLIENT \
  ACE_Singleton <CUTS_Test_Archive_Client, ACE_Null_Mutex>::instance ()

//
// main
//
int main (int argc, char * argv [])
{
  int retval;

  try
  {
    // Run the client.
    retval = CUTS_TEST_ARCHIVE_CLIENT->run_main (argc, argv);
  }
  catch (...)
  {
    ACE_ERROR ((LM_ERROR,
                "%T (%t) - %M - caught unknown exception\n"));

    retval = 1;
  }

  // Destroy the client.
  CUTS_TEST_ARCHIVE_CLIENT->destroy ();

  return retval;
}
