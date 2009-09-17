// $Id$

//
// CUTS_Process_Options
//
CUTS_INLINE
CUTS_Process_Options::CUTS_Process_Options (void)
: wait_for_completion_ (false)
{

}

//
// CUTS_Process_Options
//
CUTS_INLINE
CUTS_Process_Options::
CUTS_Process_Options (const CUTS_Process_Options & copy)
: name_ (copy.name_),
  exec_ (copy.exec_),
  args_ (copy.args_),
  cwd_ (copy.cwd_),
  delay_ (copy.delay_),
  stderr_ (copy.stderr_),
  stdout_ (copy.stdout_),
  wait_for_completion_ (copy.wait_for_completion_)
{

}

//
// ~CUTS_Process_Options
//
CUTS_INLINE
CUTS_Process_Options::~CUTS_Process_Options (void)
{

}
