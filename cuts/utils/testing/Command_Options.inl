// $Id: Command_Options.inl

//
// CUTS_Command_Options
//
CUTS_INLINE
CUTS_Command_Options::CUTS_Command_Options (void)
: wait_for_completion_ (false)
{

}

//
// CUTS_Command_Options
//
CUTS_INLINE
CUTS_Command_Options::
CUTS_Command_Options (const CUTS_Command_Options & copy)
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
// ~CUTS_Command_Options
//
CUTS_INLINE
CUTS_Command_Options::~CUTS_Command_Options (void)
{

}
