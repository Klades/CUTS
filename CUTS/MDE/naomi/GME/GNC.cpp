// $Id$

#include "GNC_App.h"
#include "ace/Log_Msg.h"

//
// main
//
int ACE_TMAIN (int argc, char * argv [])
{
  CUTS_GNC_App app;

  u_long default_mask =
    LM_EMERGENCY | LM_ALERT | LM_CRITICAL | LM_ERROR | LM_WARNING | LM_NOTICE;

  ACE_Log_Msg::instance ()->priority_mask (default_mask, ACE_Log_Msg::PROCESS);

  if (app.parse_args (argc, argv) == -1)
  {
    ACE_ERROR_RETURN ((LM_ERROR,
                       "*** error: failed to parse command-line arguments\n"),
                       1);
  }

  return app.run_main ();
}
