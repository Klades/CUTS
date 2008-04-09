// $Id$

#include "Node_Daemon_i.h"

#if !defined (__CUTS_INLINE__)
#include "Node_Daemon_i.inl"
#endif

#include "Active_Process.h"
#include "Process_Info.h"
//#include "Process_Log.h"
#include "Server_Options.h"
#include "ace/INET_Addr.h"
#include "ace/Null_Mutex.h"
#include "ace/OS_NS_unistd.h"
#include "ace/OS_NS_stdio.h"
#include "ace/OS_NS_string.h"
#include "ace/Process.h"
#include "ace/Process_Manager.h"
#include "ace/Singleton.h"

#define PROCESS_LOG() \
  ACE_Singleton <Process_Log, ACE_Null_Mutex>::instance ()

//
// CUTS_Node_Daemon_i
//
CUTS_Node_Daemon_i::CUTS_Node_Daemon_i (CORBA::ORB_ptr orb)
  : event_handler_ (*this),
    timer_ (-1),
    orb_ (orb)
{
  this->init ();
  this->recover ();
}

//
// ~CUTS_Node_Daemon_i
//
CUTS_Node_Daemon_i::~CUTS_Node_Daemon_i (void)
{
  // Wait for the process manager thread to return and it's
  // event handler. This means waiting for all processes
  // created by this process manager to exit.
  VERBOSE_MESSAGE ((LM_DEBUG,
                    "*** info (node daemon): waiting for %u tasks(s) to exit\n",
                    this->pm_.managed ()));
  this->pm_.wait ();

  VERBOSE_MESSAGE ((LM_DEBUG,
                    "*** info (node daemon): deactivating the process listener\n"));
  this->event_handler_.deactivate ();

  VERBOSE_MESSAGE ((LM_DEBUG,
                    "*** info (node daemon) : deactivating the timer queue\n"));
  this->timer_queue_.deactivate ();
  this->timer_queue_.cancel (this->timer_);
}

//
// spawn_task
//
CORBA::ULong CUTS_Node_Daemon_i::task_spawn (const CUTS::Node_Task & task)
{
  if (this->process_map_.find (task.name.in ()) == 0)
  {
    ACE_ERROR_RETURN ((LM_ERROR,
                       "*** error (node daemon): '%s' task already exists\n",
                       task.name.in ()),
                       1);
  }

  // Prepare the command line for the task.
  this->p_options_.command_line ("%s %s",
                                 task.execname.in (),
                                 task.arguments.in ());

  // Spawn the new task and register the <event_handler_> as the
  // notifier for process termination.
  VERBOSE_MESSAGE ((LM_DEBUG,
                    "*** info (node daemon): spawning new process ['%s']\n",
                    this->p_options_.command_line_buf ()));

  // Spawn the new process.
  pid_t pid = this->pm_.spawn (this->p_options_, &this->event_handler_);

  if (pid != ACE_INVALID_PID && pid != 0)
  {
    // All a new information block about the task.
    CUTS_Process_Info * info = 0;
    ACE_NEW_THROW_EX (info, CUTS_Process_Info (), CORBA::NO_MEMORY ());
    ACE_Auto_Ptr <CUTS_Process_Info> auto_clean (info);

    // Initialize the task information block.
    info->pid_ = pid;
    info->state_ = 1;
    info->name_ = task.name.in ();
    info->exec_ = task.execname.in ();
    info->args_ = task.arguments.in ();

    // Save the information block to a mapping.
    int retval = this->process_map_.bind (task.name.in (), info);

    if (retval == 0)
    {
      auto_clean.release ();
    }
    else if (retval == -1)
    {
      ACE_ERROR ((LM_ERROR,
                  "*** error (node daemon): failed to save spawned task\n"));
    }
  }
  else
  {
    ACE_ERROR ((LM_ERROR,
                "*** error (node daemon): failed to spawn task [%m]\n"));
  }

  return 0;
}

//
// task_terminate
//
CORBA::ULong CUTS_Node_Daemon_i::
task_terminate (const char * name, CORBA::Boolean wait)
{
  // Locate the pid for the task.
  CUTS_Process_Info * info = 0;
  int retval = this->process_map_.find (name, info);

  if (retval == 0)
  {
    // Terminate the located task.
    if (this->task_terminate_i (*info, wait) == 0)
    {
      // Remove the process from the mapping.
      if (this->process_map_.unbind (name) == 0)
        delete info;
    }
  }
  else
  {
    ACE_ERROR ((LM_WARNING,
                "*** warning (node daemon): %s was not found\n",
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
                "*** error (node daemon): failed to terminate <%s>\n",
                info.name_.c_str ()));
  }

  return retval;
}

//
// task_restart
//
CORBA::ULong CUTS_Node_Daemon_i::task_restart (const char * name)
{
  CUTS::Node_Task_var task_info;

  // Get information about the task.
  if (this->task_info (name, task_info) != 0)
    return -1;

  // Terminate the task.
  if (this->task_terminate (name, true) != 0)
    return -1;

  // Spawn the task again.
  return this->task_spawn (task_info);
}

//
// task_info
//
CORBA::ULong CUTS_Node_Daemon_i::
task_info (const char * name, CUTS::Node_Task_out info)
{
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
  //PROCESS_LOG ()->log_file ("cutsnode_d.dat");

  // Initialize the default <p_options_>.
  this->p_options_.avoid_zombies (0);
  this->p_options_.setgroup (0);

#if defined (ACE_WIN32)
  this->p_options_.creation_flags (CREATE_NEW_PROCESS_GROUP |
                                   CREATE_DEFAULT_ERROR_MODE);
#endif

  // We need to set the working directory for the process
  // if it was specified as a command-line option.
  if (!SERVER_OPTIONS ()->init_dir_.empty ())
  {
    VERBOSE_MESSAGE ((LM_DEBUG,
                      "*** info: setting working directory to %s\n",
                      SERVER_OPTIONS ()->init_dir_.c_str ()));

    this->p_options_.
      working_directory (SERVER_OPTIONS ()->init_dir_.c_str ());
  }

  // We need to activate the event handler. It is responsible for
  // receiving notifications about processes terminating.
  if (!this->event_handler_.activate ())
  {
    ACE_ERROR ((LM_WARNING,
                "*** warning (node daemon): failed to active event "
                "handler; cannot manager spawned processes\n"));
  }

  // Activate the cleaning thread. It is responsible for scrubbing
  // the process log and removing all invalid entries. Right now,
  // it is set for 300 seconds (i.e., 5 minutes).
  VERBOSE_MESSAGE ((LM_DEBUG,
                    "*** info (node daemon): activating cleaning thread\n"));

  ACE_Time_Value interval (300);
  ACE_Time_Value abstime =
    this->timer_queue_.timer_queue ()->gettimeofday () + interval;

  this->timer_ =
    this->timer_queue_.schedule (&this->event_handler_, 0, abstime, interval);

  if (this->timer_ != -1)
  {
    this->timer_queue_.activate ();
  }
  else
  {
    ACE_ERROR ((LM_ERROR,
                "*** error (node daemon): failed to activate "
                "cleaning thread\n"));
  }
}

//
// recover
//
size_t CUTS_Node_Daemon_i::recover (void)
{
  //size_t count = 0;
  //CUTS_Process_Info_Set active_list;

  //// Get all the active process in the process log.
  //PROCESS_LOG ()->get_active_processes (active_list);
  //CUTS_Process_Info_Set::ITERATOR iter (active_list);

  //while (iter.done () == 0)
  //{
  //  // Get the next process for the <active_list>. We only need
  //  // to continue if we successfully have gotten an entry.
  //  CUTS_Process_Info * info = 0;
  //  iter.next (info);

  //  if (info == 0)
  //    continue;

  //  // Create an <Active_Process> entry so we can actually
  //  // manage this process using our <Process_Manager>.
  //  CUTS_Active_Process * a_process = 0;
  //  ACE_NEW_THROW_EX (a_process,
  //                    CUTS_Active_Process (info->pid_),
  //                    CORBA::NO_MEMORY ());

  //  ACE_Auto_Ptr <CUTS_Active_Process> auto_clean (a_process);

  //  if (a_process->running ())
  //  {
  //    pid_t pid = this->pm_.spawn (a_process,
  //                                 this->p_options_,
  //                                 &this->event_handler_);

  //    if (pid != ACE_INVALID_PID && pid != 0)
  //    {
  //      // Increment the recovery counter.
  //      ++ count;

  //      // Release the object since the manager now owns it.
  //      auto_clean.release ();
  //    }
  //    else
  //    {
  //      ACE_ERROR ((LM_ERROR,
  //                  "*** error (node daemon): failed to recover pid %d\n",
  //                  info->pid_));
  //    }
  //  }
  //  else
  //  {
  //    VERBOSE_MESSAGE ((LM_DEBUG,
  //                      "*** info (node daemon): pid %u is not active\n",
  //                      info->pid_));

  //    // Remove the entry from the log and delete its resources.
  //    if (PROCESS_LOG ()->process_exit (info->pid_))
  //    {
  //      VERBOSE_MESSAGE ((LM_DEBUG,
  //                        "*** info (node daemon): removed pid %u "
  //                        "from log\n",
  //                        info->pid_));
  //    }
  //    else
  //    {
  //      ACE_ERROR ((LM_ERROR,
  //                  "*** error (node daemon): failed to remove pid %u "
  //                  "from log\n",
  //                  info->pid_));
  //    }
  //  }

  //  // Advance to the next element in the collection.
  //  iter.advance ();
  //}

  return 0;
}

//
// clean
//
void CUTS_Node_Daemon_i::clean (void)
{
  //size_t active_count = 0;
  //bool retval = PROCESS_LOG ()->clean (&active_count);

  //VERBOSE_MESSAGE ((LM_DEBUG,
  //                  "*** info (node daemon): %s the log file [active=%u]\n",
  //                  retval ? "successfully cleaned" : "failed to clean",
  //                  active_count));
}

//
// shutdown
//
void CUTS_Node_Daemon_i::shutdown (CORBA::Boolean kill_task)
{
  // @@ We should have a flag specifying how to shutdown,
  // e.g., force|nowait|wait

  VERBOSE_MESSAGE ((LM_DEBUG,
                    "*** info: (node daemon): shutting down...\n"));

  if (kill_task)
  {
    ACE_READ_GUARD (ACE_RW_Thread_Mutex, guard, this->process_map_.mutex ());

    CUTS_Process_Info * info = 0;
    Process_Map::ITERATOR iter (this->process_map_);

    for ( ; !iter.done (); iter.advance ())
    {
      // Kill this task and wait for it to terminate.
      info = iter->item ();      
      this->task_terminate_i (*info, true);

      // Delete the information about the process.
      delete info;
    }
  }

  // Remove all the task from the listing.
  this->process_map_.unbind_all ();

  // Shutdown the ORB.
  this->orb_->shutdown ();
}
