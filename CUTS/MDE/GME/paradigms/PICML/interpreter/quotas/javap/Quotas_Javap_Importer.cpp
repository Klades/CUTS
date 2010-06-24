// $Id$

#include "Quotas_Javap_Importer_App.h"
#include "ace/Singleton.h"
#include "ace/Null_Mutex.h"

#define QUOTAS_JAVAP_IMPORTER_APP \
  ACE_Singleton < Quotas_Javap_Importer_App, ACE_Null_Mutex >::instance ()

//
// ACE_TMAIN
//
int ACE_TMAIN (int argc, char * argv [])
{
  try
  {
    return QUOTAS_JAVAP_IMPORTER_APP->run_main (argc, argv);
  }
  catch (...)
  {
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - caught unknown exception\n")));
  }
}
