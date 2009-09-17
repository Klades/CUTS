// $Id$

#include "Virtual_Env.h"

#if !defined (__CUTS_INLINE__)
#include "Virtual_Env.inl"
#endif

#include "Process_Dependency_Graph.h"
#include "Process_Options.h"
#include "cuts/utils/Text_Processor.h"
#include "boost/graph/topological_sort.hpp"
#include "ace/Reactor.h"

//
// close
//
int CUTS_Virtual_Env::close (void)
{
  this->delay_.close ();
  return 0;
}

//
// start
//
int CUTS_Virtual_Env::start (void)
{
  if (this->delay_.reactor ()->reactor_event_loop_done ())
    this->delay_.reactor ()->reset_reactor_event_loop ();

  // Activate the delay handler for the process.
  if (0 != this->delay_.activate ())
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - failed to activate delay handler\n")),
                       -1);

  // Spawn the startup processes.
  return this->spawn (this->startup_);
}

//
// spawn
//
int CUTS_Virtual_Env::
spawn (const CUTS_Process_Options & opts)
{
  // Initialize the ACE process options structure.
  ACE_Process_Options options (this->inherit_);
  CUTS_Text_Processor processor (this->env_);

  // Process the executable's text.
  ACE_CString executable;
  if (!processor.evaluate (opts.exec_.c_str (), executable, true))
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - failed to process executable text\n")));

  // Process the command-line argument's text.
  ACE_CString arguments;
  if (!processor.evaluate (opts.args_.c_str (), arguments, true))
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - failed to process executable text\n")));

  options.command_line (ACE_TEXT ("%s %s"),
                        executable.c_str (),
                        arguments.c_str ());

  if (!opts.cwd_.empty ())
    options.working_directory (opts.cwd_.c_str ());

  for (CUTS_Property_Map::const_iterator iter (this->env_.map ()); !iter.done (); ++ iter)
    options.setenv (iter->key ().c_str (), iter->item ().c_str ());

  /// @todo Need to re-add support for piping output to a HANDLE. The
  ///       plan is to support multiple protocols (e.g., file and socket)

  // Determine if we must delay the startup of this process. If
  // so, then let's hold off on spawning the new process based on
  // the "delay" specification.
  if (opts.delay_ != ACE_Time_Value::zero)
  {
    if (0 == this->delay_.schedule (opts.delay_))
    {
      if (0 != this->delay_.wait_for_delay_completion ())
        ACE_ERROR ((LM_ERROR,
                    ACE_TEXT ("%T (%t) - %M - failed to wait for %s delay\n"),
                    opts.name_.c_str ()));
    }
    else
      ACE_ERROR ((LM_ERROR,
                  ACE_TEXT ("%T (%t) - %M - failed to schedule delay for %s\n"),
                  opts.name_.c_str ()));
  }

  // Spawn the new process.
  ACE_DEBUG ((LM_INFO,
              ACE_TEXT ("%T (%t) - %M - spawning process with id %s\n"),
              opts.name_.c_str ()));

  ACE_Event_Handler * handler = opts.wait_for_completion_ ? 0 : this;
  pid_t pid = this->proc_man_.spawn (options, handler);

  if (ACE_INVALID_PID == pid)
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %T - failed to spawn process %s; %m\n"),
                       opts.name_.c_str ()),
                       -1);

  if (opts.wait_for_completion_)
  {
    // We should use a *condition* variable here and let the
    // handle_exit () method notify us when the process has exited.
    ACE_DEBUG ((LM_INFO,
                ACE_TEXT ("%T (%t) - %M - waiting for process to complete\n")));

    this->proc_man_.wait (pid);
  }
  else
  {
    if (-1 == this->managed_.bind (opts.name_, pid))
      ACE_ERROR ((LM_WARNING,
                  ACE_TEXT ("%T (%t) - %M - process %s will not be ")
                  ACE_TEXT ("managed by environment\n"),
                  opts.name_.c_str ()));
  }

  return 0;
}

//
// terminate
//
int CUTS_Virtual_Env::terminate (const ACE_CString & name)
{
  pid_t pid = ACE_INVALID_PID;

  if (-1 == this->managed_.find (name, pid))
    ACE_ERROR_RETURN ((LM_ERROR,
                      ACE_TEXT ("%T (%t) - %M - failed to locate process ")
                      ACE_TEXT ("with name %s\n"),
                      name.c_str ()),
                      -1);

  // First, try to signal the process to terminate. Otherwise, we need
  // to force it to terminate.
  int retval = this->proc_man_.terminate (pid, SIGTERM);

  if (-1 == retval)
    retval = this->proc_man_.terminate (pid);

  if (-1 == retval)
    ACE_ERROR_RETURN ((LM_ERROR,
                      ACE_TEXT ("%T (%t) - %M - failed to terminate process ")
                      ACE_TEXT ("with name %s\n"),
                      name.c_str ()),
                      -1);

  // Should we *wait* for the process to terminate just to sure that
  // it did terminate??

  // Remove the process from the listing.
  if (-1 == this->managed_.unbind (name))
    ACE_ERROR ((LM_WARNING,
                ACE_TEXT ("%T (%t) - %M - reference to process %s still remains\n")));

  return 0;
}

//
// spawn
//
int CUTS_Virtual_Env::
spawn (const CUTS_Process_Options_List & proc_list)
{
  CUTS_Process_Options_List::ITERATOR iter (proc_list);

  int retval = 0;

  for (; !iter.done (); ++ iter)
  {
    if (0 != this->spawn ((*iter).item_))
    {
      ACE_ERROR ((LM_ERROR,
                  ACE_TEXT ("%T (%t) - %M - failed to spawn %s\n"),
                  (*iter).item_.name_.c_str ()));

      ++ retval;
    }
  }

  return retval;
}

//
// shutdown
//
int CUTS_Virtual_Env::shutdown (void)
{
  // Terminate each of the active processes.
  pid_t pid;

  for (PROCESS_MANAGER::ITERATOR iter (this->managed_); !iter.done (); ++ iter)
  {
    // First, try to signal the process to terminate. Otherwise, we need
    // to force it to terminate.
    ACE_DEBUG ((LM_INFO,
                ACE_TEXT ("%T (%t) - %M - terminating process %s\n"),
                iter->key ().c_str ()));

    pid = iter->item ();
    int retval = this->proc_man_.terminate (pid, SIGTERM);

    if (-1 == retval)
      retval = this->proc_man_.terminate (pid);

    if (-1 == retval)
      ACE_ERROR_RETURN ((LM_ERROR,
                        ACE_TEXT ("%T (%t) - %M - failed to terminate process ")
                        ACE_TEXT ("with name %s\n"),
                        iter->key ().c_str ()),
                        -1);
  }

  // Remove all the process.
  this->managed_.unbind_all ();

  // Finally, execute all the shutdown processes.
  if (0 != this->spawn (this->shutdown_))
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - failed to execute shutdown processes\n")),
                       -1);

  // Shutdown the delay handler.
  this->delay_.close ();
  return 0;
}

//
// restart
//
int CUTS_Virtual_Env::restart (void)
{
  if (0 == this->shutdown ())
  {
    if (0 != this->start ())
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to start environment\n")),
                         -1);

    return 0;
  }
  else
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - failed to shutdown environment\n")));

  return -1;
}
