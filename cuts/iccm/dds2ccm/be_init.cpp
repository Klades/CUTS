// $Id$

#include <iostream>

#include "global_extern.h"
#include "be_extern.h"

#include "tao/Version.h"

//
// BE_version
//
void BE_version (void)
{
  ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("%s %s\n"),
              ACE_TEXT ("TAO_IDL, version"),
              ACE_TEXT (TAO_VERSION)));
}

//
// BE_init
//
int BE_init (int &, char *[])
{
  u_long default_mask =
    LM_EMERGENCY | LM_ALERT | LM_CRITICAL | LM_ERROR |
    LM_WARNING | LM_NOTICE | LM_DEBUG;

  ACE_Log_Msg::instance ()->priority_mask (default_mask, ACE_Log_Msg::PROCESS);

  // Initialize BE global data object.
  ACE_NEW_RETURN (be_global, BE_GlobalData (), -1);

  return 0;
}

//
// BE_post_init
//
void BE_post_init (char * files [], long nfiles)
{
  idl_global->multi_file_input (false);
  be_global->source_file_ = files[0];
}

