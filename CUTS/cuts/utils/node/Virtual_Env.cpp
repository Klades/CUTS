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
#include "ace/OS_NS_fcntl.h"
#include "ace/FILE_Connector.h"

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

  // Process the executable's text.
  ACE_CString executable;

  if (0 != this->expand_tag_string ("executable", opts.exec_, executable))
    return -1;

  // Process the command-line argument's text.
  ACE_CString arguments;

  if (0 != this->expand_tag_string ("arguments", opts.args_, arguments))
    return -1;

  // Set the command-line for the new process.
  options.command_line (ACE_TEXT ("%s %s"),
                        executable.c_str (),
                        arguments.c_str ());

  // Determine if we need to redirect output. Make sure to expand
  // the strings before trying to open the file for writing.

  /// @todo Need to re-add support for piping output to a HANDLE. The
  ///       plan is to support multiple protocols (e.g., file and socket)

  ACE_FILE_Connector file_conn;
  ACE_FILE_IO stdout_file, stderr_file;
  ACE_CString stdout_filename, stderr_filename;

  if (!opts.stdout_.empty () &&
      0 == this->expand_tag_string ("output", opts.stdout_, stdout_filename))
  {
    ACE_FILE_Addr filename (stdout_filename.c_str ());

    if (0 != file_conn.connect (stdout_file, filename))
      ACE_ERROR ((LM_ERROR,
                  ACE_TEXT ("%T (%t) - %M - failed to redirect ")
                  ACE_TEXT ("standard output\n")));
  }

  if (!opts.stderr_.empty () &&
      0 == this->expand_tag_string ("error", opts.stderr_, stderr_filename))
  {
    ACE_FILE_Addr filename (stderr_filename.c_str ());

    if (0 != file_conn.connect (stderr_file, filename))
      ACE_ERROR ((LM_ERROR,
                  ACE_TEXT ("%T (%t) - %M - failed to redirect ")
                  ACE_TEXT ("standard error\n")));
  }

  // Set the handles for redirecting the output.
  options.set_handles (ACE_INVALID_HANDLE,
                       stdout_file.get_handle (),
                       stderr_file.get_handle ());

  // Set the working directory for the new process.
  ACE_CString working_dir;
  if (0 == this->expand_tag_string ("workingdirectory", opts.cwd_, working_dir))
    options.working_directory (working_dir.c_str ());

  // Set the environment variables for the process.
  for (CUTS_Property_Map::const_iterator iter (this->env_.map ()); !iter.done (); ++ iter)
    options.setenv (iter->key ().c_str (), iter->item ().c_str ());

  // Determine if we must delay the startup of this process. If
  // so, then let's hold off on spawning the new process based on
  // the "delay" specification.
  this->simulate_delay (opts.delay_);

  // Spawn the new process.
  ACE_DEBUG ((LM_INFO,
              ACE_TEXT ("%T (%t) - %M - spawning process with id %s\n"),
              opts.name_.c_str ()));

  ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("%T (%t) - %M - command-line is %s\n"),
              options.command_line_buf ()));

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
// simulate_delay
//
int CUTS_Virtual_Env::simulate_delay (const ACE_Time_Value & tv)
{
  // There is no need to continue if the delay is 0.
  if (tv == ACE_Time_Value::zero)
    return 0;

  if (0 == this->delay_.schedule (tv))
  {
    // Wait for the scheduled delay to complete.
    if (0 == this->delay_.wait_for_delay_completion ())
      return 0;

    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - failed to wait %d.%d second ")
                ACE_TEXT ("delay to complete\n"),
                tv.sec (),
                tv.usec ()));
  }
  else
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - failed to schedule %d.%d second delay\n"),
                tv.sec (),
                tv.usec ()));

  return -1;
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
// expand_tag_string
//
int CUTS_Virtual_Env::
expand_tag_string (const char * tag,
                   const ACE_CString & str,
                   ACE_CString & target)
{
  // Execute the text processor.
  CUTS_Text_Processor processor (this->env_);
  if (processor.evaluate (str.c_str (), target, true))
    return 0;

  ACE_ERROR ((LM_ERROR,
              ACE_TEXT ("%T (%t) - %M - failed to process <%s>\n"),
              tag));

  return -1;
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
