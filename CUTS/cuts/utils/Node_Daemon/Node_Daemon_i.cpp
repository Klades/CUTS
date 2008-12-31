// $Id$

#include "Node_Daemon_i.h"

#if !defined (__CUTS_INLINE__)
#include "Node_Daemon_i.inl"
#endif

#include "Active_Process.h"
#include "Process_Info.h"
#include "Process_Log.h"
#include "cuts/utils/Text_Processor.h"
#include "cuts/utils/Property_Parser.h"
#include "ace/INET_Addr.h"
#include "ace/Null_Mutex.h"
#include "ace/OS_NS_unistd.h"
#include "ace/OS_NS_stdio.h"
#include "ace/OS_NS_string.h"
#include "ace/Env_Value_T.h"
#include "ace/Process.h"
#include "ace/Process_Manager.h"
#include "ace/Singleton.h"
#include "ace/FILE_Connector.h"
#include <sstream>

#define PROCESS_LOG() \
  ACE_Singleton <Process_Log, ACE_Null_Mutex>::instance ()

//
// CUTS_Node_Daemon_i
//
CUTS_Node_Daemon_i::CUTS_Node_Daemon_i (CORBA::ORB_ptr orb)
  : event_handler_ (*this),
    timer_ (-1),
    orb_ (CORBA::ORB::_duplicate (orb)),
    active_ (true)
{
  this->init ();
  this->recover ();
}

//
// ~CUTS_Node_Daemon_i
//
CUTS_Node_Daemon_i::~CUTS_Node_Daemon_i (void)
{
  // Deactivate the event handler.
  this->event_handler_.deactivate ();

  // Deactivate the timer queue for the daemon.
  this->timer_queue_.deactivate ();
  this->timer_queue_.cancel (this->timer_);
}

//
// spawn_task
//
CORBA::ULong CUTS_Node_Daemon_i::
task_spawn (const CUTS::taskDescriptor & task)
{
  if (!this->active_)
    return -1;

  if (this->process_map_.find (task.id.in ()) == 0)
  {
    ACE_ERROR_RETURN ((LM_ERROR,
                       "%T (%t) - %M - '%s' task already exists\n",
                       task.id.in ()),
                       1);
  }

  CUTS_Process_Info * info = 0;
  ACE_NEW_THROW_EX (info, CUTS_Process_Info (), CORBA::NO_MEMORY ());
  ACE_Auto_Ptr <CUTS_Process_Info> auto_clean (info);

  // Duplicate the default process options.
  this->duplicate_defualt_process_options (info->options_);

  // Decode the environment variable in the executable and arguments
  // member of the task descriptor.
  CUTS_Text_Processor preprocessor (this->prop_map_);
  ACE_CString exec_value, args_value, result;

  if (preprocessor.evaluate (task.executable.in (), exec_value) != 0)
  {
    ACE_ERROR ((LM_WARNING,
                "%T (%t) - %M - failed to preproess <executable> value\n",
                task.executable.in ()));
  }

  if (preprocessor.evaluate (task.arguments.in (), args_value) != 0)
  {
    ACE_ERROR ((LM_WARNING,
                "%T (%t) - %M - failed to preproess <arguments> value\n",
                task.arguments.in ()));
  }

  // Prepare the command line for the task.
  info->id_ = task.id.in ();
  info->options_.command_line ("%s %s",
                               exec_value.c_str (),
                               args_value.c_str ());

  // Set the working directory for the process if there is one
  // specified in the data structure.
  if (ACE_OS::strlen (task.workingdirectory.in ()) != 0)
  {
    ACE_CString cwd;

    if (preprocessor.evaluate (task.workingdirectory.in (), cwd) != 0)
    {
      ACE_DEBUG ((LM_WARNING,
                  "%T (%t) - %M - failed to preprocess <workingdirectory> "
                  "value [%s]\n",
                  task.workingdirectory.in ()));
    }

    ACE_DEBUG ((LM_INFO,
                "%T (%t) - %M - setting working directory to %s\n",
                cwd.c_str ()));

    info->options_.working_directory (cwd.c_str ());
  }
  else
  {
    // We need to set the working directory for the process
    // if it was specified as a command-line option.
    if (!this->init_dir_.empty ())
    {
      ACE_DEBUG ((LM_INFO,
                  "%T (%t) - %M - setting working directory to %s\n",
                  this->init_dir_.c_str ()));

      info->options_.working_directory (this->init_dir_.c_str ());
    }
  }

  // Next, redirect the output/error streams.
  ACE_FILE_IO stderr_handle;
  ACE_FILE_IO stdout_handle;

  ACE_FILE_Connector disk;
  ACE_FILE_Addr file_addr;

  if (ACE_OS::strlen (task.output.in ()) != 0)
  {
    // Preprocess the output filename.
    if (preprocessor.evaluate (task.output.in (), result) == -1)
    {
      ACE_ERROR_RETURN ((LM_ERROR,
                         "%T (%t) - %M - failed to evaluate output filename\n"),
                         -1);
    }

    ACE_DEBUG ((LM_DEBUG,
                "%T (%t) - %M - setting output filename to: %s\n",
                result.c_str ()));

    // Open the file for the process.
    file_addr.set (result.c_str ());

    if (disk.connect (stdout_handle, file_addr) == -1)
    {
      ACE_ERROR ((LM_ERROR,
                  "%T (%t) - %M - failed to open file %s\n",
                  file_addr.get_path_name ()));
    }
  }

  if (ACE_OS::strlen (task.error.in ()) != 0)
  {
    // Preprocess the error filename.
    if (preprocessor.evaluate (task.error.in (), result) == -1)
    {
      ACE_ERROR_RETURN ((LM_ERROR,
                         "%T (%t) - %M - failed to evaluate error filename\n"),
                         -1);
    }

    ACE_DEBUG ((LM_DEBUG,
                "%T (%t) - %M - setting error filename to: %s\n",
                result.c_str ()));

    // Open the file for the process.
    file_addr.set (result.c_str ());

    if (disk.connect (stderr_handle, file_addr) == -1)
    {
      ACE_ERROR ((LM_ERROR,
                  "%T - %M - failed to open file %s\n",
                  file_addr.get_path_name ()));
    }
  }

  // Set the handles for the process.
  info->options_.set_handles (ACE_INVALID_HANDLE,
                              stdout_handle.get_handle (),
                              stderr_handle.get_handle ());

  // Spawn the new task and register the <event_handler_> as the
  // notifier for process termination.
  int retval = this->task_spawn_i (*info);

  if (retval == 0)
    auto_clean.release ();

  return retval;
}

//
// task_terminate
//
CORBA::ULong CUTS_Node_Daemon_i::
task_terminate (const char * name, CORBA::Boolean wait)
{
  if (!this->active_)
    return -1;

  // Locate the pid for the task.
  CUTS_Process_Info * info = 0;

  int retval = this->process_map_.find (name, info);

  if (retval == 0)
  {
    // Terminate the located task.
    if (this->task_terminate_i (*info, wait) == 0)
    {
      ACE_ERROR ((LM_ERROR,
                  "%T (%t) - %M - successfully termintaed task <%s>\n",
                  name));
    }
    else
    {
      ACE_ERROR ((LM_ERROR,
                  "%T (%t) - %M - failed to terminate task <%s>\n",
                  name));
    }
  }
  else
  {
    ACE_ERROR ((LM_WARNING,
                "%T (%t) - %M - %s was not found\n",
                name));
  }

  return retval;
}

//
// task_terminate_i
//
int CUTS_Node_Daemon_i::
task_terminate_i (CUTS_Process_Info & info, bool wait)
{
  // Terminate the process and wait for it to d
  ACE_DEBUG ((LM_DEBUG,
              "%T (%t) - %M - terminating task <%s>\n",
              info.id_.c_str ()));

  int retval = this->pm_.terminate (info.pid_);

  if (retval == 0)
  {
    // We may have to wait for the process to terminate.
    if (wait)
      this->pm_.wait (info.pid_);
  }
  else
  {
    ACE_ERROR ((LM_ERROR,
                "%T (%t) - %M - failed to terminate <%s>\n",
                info.id_.c_str ()));
  }

  return retval;
}

//
// task_restart
//
CORBA::ULong CUTS_Node_Daemon_i::task_restart (const char * name)
{
  if (!this->active_)
    return -1;

  ACE_DEBUG ((LM_INFO,
              "%T (%t) - %M - restarting task <%s>\n", name));

  // Locate the task. There is not need to restart the task
  // if we can't find it.
  CUTS_Process_Info * info = 0;

  if (this->process_map_.find (name, info) != 0)
    return -1;

  // Terminate the task. This also means removing the task from
  // the process map.
  this->pm_.register_handler (0, info->pid_);

  if (this->task_terminate_i (*info, true) != 0)
    return -1;

  // Remove the process from the map and the log.
  this->process_map_.unbind (name);
  //PROCESS_LOG ()->process_remove (info->pid_);

  // Spawn the task again.
  ACE_Auto_Ptr <CUTS_Process_Info> auto_clean (info);

  int retval = this->task_spawn_i (*info);

  if (retval == 0)
    auto_clean.release ();

  return retval;
}

//
// task_info
//
CORBA::ULong CUTS_Node_Daemon_i::
task_info (const char * name, CUTS::taskDescriptor_out info)
{
  if (!this->active_)
    return -1;

  return 0;
}

//
// unmanage
//
void CUTS_Node_Daemon_i::unmanage (pid_t pid)
{
  // Lock down the process map and get an iterator.
  Process_Map::ITERATOR iter (this->process_map_);

  do
  {
    // Prevent the process map from being modified.
    ACE_READ_GUARD (ACE_RW_Thread_Mutex,
                    guard,
                    this->process_map_.mutex ());

    for (; !iter.done (); iter ++)
    {
      if (iter->item ()->pid_ == pid)
        break;
    }
  } while (0);

  if (!iter.done ())
  {
    // Delete the allocated element.
    CUTS_Process_Info * info = iter->item ();

    // Remove the information from the listing.
    if (this->process_map_.unbind (iter) == 0)
      delete info;
  }

  // Remove the process from the log.
  //PROCESS_LOG ()->process_remove (pid);
}

//
// init
//
void CUTS_Node_Daemon_i::init (void)
{
  // Initialize the contained process manager.
  this->pm_.open (ACE_Process_Manager::DEFAULT_SIZE,
                  this->event_handler_.reactor ());

  // Set the process log for the node daemon.
  ACE_Env_Value <const char *> CUTS_ROOT ("CUTS_ROOT", "");

  std::ostringstream ostr;
  ostr << CUTS_ROOT << "/etc/cutsnode_d.dat";

  //PROCESS_LOG ()->log_file (ostr.str ().c_str ());

  // Initialize the default <p_options_>.
  this->p_options_.avoid_zombies (0);
  this->p_options_.setgroup (0);

#if defined (ACE_WIN32)
  this->p_options_.creation_flags (CREATE_NEW_PROCESS_GROUP |
                                   CREATE_DEFAULT_ERROR_MODE);
#endif

  // We need to activate the event handler. It is responsible for
  // receiving notifications about processes terminating.
  if (!this->event_handler_.activate ())
  {
    ACE_ERROR ((LM_WARNING,
                "%T (%t) - %M - failed to active event "
                "handler; cannot manager spawned processes\n"));
  }

  // Activate the cleaning thread. It is responsible for scrubbing
  // the process log and removing all invalid entries. Right now,
  // it is set for 300 seconds (i.e., 5 minutes).
  //VERBOSE_MESSAGE ((LM_DEBUG,
  //                  "*** info (node daemon): activating cleaning thread\n"));

  //ACE_Time_Value interval (300);
  //ACE_Time_Value abstime =
  //  this->timer_queue_.timer_queue ()->gettimeofday () + interval;

  //this->timer_ =
  //  this->timer_queue_.schedule (&this->event_handler_, 0, abstime, interval);

  //if (this->timer_ != -1)
  //{
  //  this->timer_queue_.activate ();
  //}
  //else
  //{
  //  ACE_ERROR ((LM_ERROR,
  //              "*** error (node daemon): failed to activate "
  //              "cleaning thread\n"));
  //}
}

//
// recover
//
size_t CUTS_Node_Daemon_i::recover (void)
{
  size_t count = 0;
  CUTS_Process_Info_Set active_list;

  // Get all the active process in the process log.
  //PROCESS_LOG ()->get_active_processes (active_list);

  CUTS_Process_Info_Set::iterator iter (active_list);
  ACE_Auto_Ptr <CUTS_Process_Info> info;

  for (; !iter.done (); ++ iter)
  {
    // Create an <Active_Process> entry so we can actually
    // manage this process using our <Process_Manager>.
    info.reset (*iter);
    CUTS_Active_Process * a_process = 0;

    ACE_NEW_THROW_EX (a_process,
                      CUTS_Active_Process (info->pid_),
                      CORBA::NO_MEMORY ());

    ACE_Auto_Ptr <CUTS_Active_Process> auto_clean (a_process);

    if (a_process->running ())
    {
      // Duplicate the default process options.
      this->duplicate_defualt_process_options (info->options_);

      pid_t pid = this->pm_.spawn (a_process,
                                   info->options_,
                                   &this->event_handler_);

      if (pid == info->pid_)
      {
        // Release the process since the manager owns it.
        auto_clean.release ();

        // Save the information block to a mapping.
        int retval = this->process_map_.bind (info->id_, info.get ());

        switch (retval)
        {
        case 0:
          info.release ();
          break;

        case 1:
          ACE_ERROR ((LM_ERROR,
                      "%T (%t) - %M - process with pid = %d already in map\n",
                      info->pid_));
          break;

        case -1:
          ACE_ERROR ((LM_ERROR,
                      "%T (%t) - %M - failed to save process with pid = %d in map\n",
                      info->pid_));
          break;
        }

        // Increment the recovery counter.
        ++ count;
      }
      else
      {
        ACE_ERROR ((LM_CRITICAL,
                    "%T (%t) - %M - fatal error: recovered pid's do not match [%d != %d]",
                    pid,
                    info->pid_));
      }
    }
    else
    {
      ACE_DEBUG ((LM_DEBUG,
                  "%T (%t) - %M - info (node daemon): pid %u is not active\n",
                  info->pid_));

      // Remove the entry from the log and delete its resources.
      //if (PROCESS_LOG ()->process_remove (info->pid_))
      //{
      //  VERBOSE_MESSAGE ((LM_DEBUG,
      //                    "*** info (node daemon): removed pid %u "
      //                    "from log\n",
      //                    info->pid_));
      //}
      //else
      //{
      //  ACE_ERROR ((LM_ERROR,
      //              "*** error (node daemon): failed to remove pid %u "
      //              "from log\n",
      //              info->pid_));
      //}
    }
  }

  return 0;
}

//
// clean
//
void CUTS_Node_Daemon_i::clean (void)
{
  size_t active_count = 0;
  //bool retval = PROCESS_LOG ()->clean (&active_count);

  //VERBOSE_MESSAGE ((LM_DEBUG,
  //                  "*** info (node daemon): %s the log file [active=%u]\n",
  //                  retval ? "successfully cleaned" : "failed to clean",
  //                  active_count));
}

//
// duplicate_defualt_process_options
//
void CUTS_Node_Daemon_i::
duplicate_defualt_process_options (ACE_Process_Options & opts)
{
  opts.avoid_zombies (this->p_options_.avoid_zombies ());
  opts.setgroup (this->p_options_.getgroup ());
  opts.creation_flags (this->p_options_.creation_flags ());
}

//
// task_spawn_i
//
int CUTS_Node_Daemon_i::
task_spawn_i (CUTS_Process_Info & info)
{
  // Spawn the new task and register the <event_handler_> as the
  // notifier for process termination.
  ACE_DEBUG ((LM_DEBUG,
              "%T (%t) - %M - spawning new process ['%s']\n",
              info.options_.command_line_buf ()));

  // Spawn the new process.
  pid_t pid = this->pm_.spawn (info.options_, &this->event_handler_);

  if (pid != ACE_INVALID_PID && pid != 0)
  {
    // Save the information about the process.
    info.pid_ = pid;
    info.state_ = 1;

    // Save the information block to a mapping.
    int retval = this->process_map_.bind (info.id_, &info);

    if (retval == -1)
    {
      ACE_ERROR_RETURN ((LM_ERROR,
                         "%T (%t) - %M - failed to save spawned task\n"),
                         -1);
    }

    // Write the process to the log.
    //PROCESS_LOG ()->process_insert (info);
  }
  else
  {
    ACE_ERROR_RETURN ((LM_ERROR,
                       "%T (%t) - %M - failed to spawn task [%m]\n"),
                       -1);
  }

  return 0;
}

//
// insert_properties
//
void CUTS_Node_Daemon_i::
insert_properties (const ACE_Array <ACE_CString> & props)
{
  ACE_Array <ACE_CString>::
    const_iterator iter = props.begin (), iter_end = props.end ();

  CUTS_Property_Parser parser (this->prop_map_);

  for (; iter != iter_end; ++ iter)
  {
    if (!parser.parse (iter->c_str ()))
    {
      ACE_ERROR ((LM_ERROR,
                  "%T (%t) - %M - failed to parse property '%s'\n",
                  iter->c_str ()));
    }
  }
}

//
// terminate_tasks
//
void CUTS_Node_Daemon_i::terminate_tasks (void)
{
  // First, gather the process ids of all the active processes.
  ACE_Unbounded_Set <pid_t> pids;
  Process_Map::ITERATOR iter (this->process_map_);

  for ( ; !iter.done (); ++ iter)
    pids.insert (iter->item ()->pid_);

  ACE_DEBUG ((LM_INFO,
              "%T (%t) - %M - terminating %d process(es)\n",
              pids.size ()));

  // Now, iterate over all the gathered pid's, whilet terminating
  // each process. The default implemenation will handle the
  // unregistration of the process with the daemon.

  ACE_Unbounded_Set <pid_t>::ITERATOR pid_iter (pids);

  for ( ; !pid_iter.done (); ++ pid_iter)
  {
    pid_t pid = *pid_iter;

    // Terminate the process. First, we try to terminate the process
    // using a singal. This will give the process a chance to do any
    // cleanup operations.
    ACE_DEBUG ((LM_DEBUG,
                "%T (%t) - %M - signalling process %d to terminate\n",
                pid));

    int retval = this->pm_.terminate (pid, SIGTERM);

    if (retval == -1)
    {
      // Force termination of the process. This is used as a last
      // resort just in case we are not able to gracefully terminate
      // the process via a signal.
      ACE_DEBUG ((LM_DEBUG,
                  "%T (%t) - %M - forcing process %d to terminate\n",
                  pid));

      retval = this->pm_.terminate (pid);

      if (retval == -1)
      {
        ACE_ERROR ((LM_WARNING,
                    "%T (%t) - %M - failed to terminate process %d\n",
                    pid));
      }
    }

    // Release the resources of this process.
    if (retval == 0)
      this->unmanage (pid);
  }
}
