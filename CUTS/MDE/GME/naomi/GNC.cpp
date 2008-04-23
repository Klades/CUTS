// $Id$

#include "GNC_App.h"
#include "ace/Log_Msg.h"

//
// main
//
int main (int argc, char * argv [])
{
  CUTS_GNC_App app;

  if (app.parse_args (argc, argv) == -1)
  {
    ACE_ERROR_RETURN ((LM_ERROR,
                       "*** error: failed to parse command-line arguments\n"),
                       1);
  }

  return app.run_main ();
}
