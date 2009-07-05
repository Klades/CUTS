// $Id$

#include "Virtual_Env.h"

#if !defined (__CUTS_INLINE__)
#include "Virtual_Env.inl"
#endif

#include "Process_Dependency_Graph.h"
#include "Process_Options.h"
#include "cuts/utils/Text_Processor.h"
#include "boost/graph/topological_sort.hpp"

/**
 * @struct spawn_process
 */
struct spawn_process
{
  spawn_process (CUTS_Virtual_Env & env, CUTS_Process_Dependency_Graph & graph)
    : env_ (env),
      graph_ (graph),
      retval_ (0)
  {

  }

  void operator () (CUTS_Process_Dependency_Graph::vertex_descriptor vertex)
  {
    // Get the vertex's properties to spawn the new process.
    ACE_CString name =
      boost::get (boost::vertex_name_t (), this->graph_, vertex);

    CUTS_Process_Options * opts =
      boost::get (CUTS_Process_Dependency_Graph_Traits::process_opts_t (),
                  this->graph_,
                  vertex);

    // Spawn the new process.
    int retval =  this->env_.spawn (name, *opts);

    if (0 != retval)
      ++ this->retval_;
  }

  int retval (void) const
  {
    return this->retval_;
  }

private:
  CUTS_Virtual_Env & env_;

  CUTS_Process_Dependency_Graph & graph_;

  int retval_;
};

//
// open
//
int CUTS_Virtual_Env::open (void)
{
  return this->delay_.activate ();
}

//
// close
//
int CUTS_Virtual_Env::close (void)
{
  // First, delete all the process options.
  for (PROCESS_OPTIONS_MAP::ITERATOR iter (this->startup_);
       !iter.done (); ++ iter)
  {
    delete iter->item ();
  }

  // Remove all the process for the map.
  this->startup_.unbind_all ();

  for (PROCESS_OPTIONS_MAP::ITERATOR iter (this->shutdown_);
       !iter.done (); ++ iter)
  {
    delete iter->item ();
  }

  // Remove all the process for the map.
  this->shutdown_.unbind_all ();

  // Finally, close the delay handler.
  this->delay_.close ();
  return 0;
}

//
// spawn
//
int CUTS_Virtual_Env::
spawn (const ACE_CString & name, const CUTS_Process_Options & opts)
{
  ACE_DEBUG ((LM_INFO,
              ACE_TEXT ("%T (%t) - %M - spawning process with id %s\n"),
              name.c_str ()));

  // Initialize the ACE process options structure.
  ACE_Process_Options options (this->inherit_);
  CUTS_Text_Processor processor (this->env_);

  // Process the executable's text.
  ACE_CString executable;
  if (!processor.evaluate (opts.executable_.c_str (), executable, true))
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - failed to process executable text\n")));

  // Process the command-line argument's text.
  ACE_CString arguments;
  if (!processor.evaluate (opts.arguments_.c_str (), arguments, true))
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - failed to process executable text\n")));

  options.command_line (ACE_TEXT ("%s %s"),
                        executable.c_str (),
                        arguments.c_str ());

  if (!opts.working_directory_.empty ())
    options.working_directory (opts.working_directory_.c_str ());

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
                    name.c_str ()));
    }
    else
      ACE_ERROR ((LM_ERROR,
                  ACE_TEXT ("%T (%t) - %M - failed to schedule delay for %s\n"),
                  name.c_str ()));
  }

  // Spawn the new process.
  ACE_Event_Handler * handler = opts.wait_for_completion_ ? 0 : this;
  pid_t pid = this->proc_man_.spawn (options, handler);

  if (ACE_INVALID_PID == pid)
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %T - failed to spawn process %s; %m\n"),
                       name.c_str ()),
                       -1);

  if (opts.wait_for_completion_)
  {
    // We should use a *condition* variable here and let the
    // handle_exit () method notify us when the process has exited.
    this->proc_man_.wait (pid);
  }
  else
  {
    if (-1 == this->managed_.bind (name, pid))
      ACE_ERROR ((LM_WARNING,
                  ACE_TEXT ("%T (%t) - %M - process %s will not be ")
                  ACE_TEXT ("managed by environment\n"),
                  name.c_str ()));
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
spawn (const PROCESS_OPTIONS_MAP & proc_list)
{
  int retval = 0;

  // First, create a dependency graph of the prodess. This will
  // ensure we start the process in the correct order.
  CUTS_Process_Dependency_Graph graph;

  // First, insert all the processes into the map
  for (PROCESS_OPTIONS_MAP::CONST_ITERATOR iter (proc_list);
       !iter.done (); ++ iter)
  {
    switch (graph.insert (iter->key (), iter->item ()))
    {
    case 1:
      ACE_ERROR ((LM_ERROR,
                  ACE_TEXT ("%T (%t) - %M - %s already in graph\n"),
                  iter->key ().c_str ()));
      break;

    case -1:
      ACE_ERROR ((LM_ERROR,
                  ACE_TEXT ("%T (%t) - %M - failed to add %s to graph\n"),
                  iter->key ().c_str ()));
      break;
    }
  }

  // Next, link the processes based on their dependencies
  for (PROCESS_OPTIONS_MAP::CONST_ITERATOR iter (proc_list);
       !iter.done (); ++ iter)
  {
    CUTS_Process_Options * opts = iter->item ();

    for (ACE_Unbounded_Set <ACE_CString>::CONST_ITERATOR after_iter (opts->after_);
         !after_iter.done ();
         ++ after_iter)
    {
      if (0 != graph.connect (iter->key (), *after_iter))
        ACE_ERROR ((LM_ERROR,
                    ACE_TEXT ("%T (%t) - %M - failed to create link between %s and %s\n"),
                    iter->key ().c_str (),
                    (*after_iter).c_str ()));
    }
  }

  // Get the execution order for the processes.
  typedef std::vector <CUTS_Process_Dependency_Graph::vertex_descriptor> vertex_list;
  vertex_list sorted_list;

  try
  {
    graph.get_execution_order (sorted_list);

    // Finally, spawn each of the processes.
    spawn_process result =
      std::for_each (sorted_list.begin (),
                     sorted_list.end (),
                     spawn_process (*this, graph));

    return result.retval ();
  }
  catch (const boost::not_a_dag & ex)
  {
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - %s\n"),
                ex.what ()));
  }

  return -1;
}

//
// shutdown
//
int CUTS_Virtual_Env::shutdown (void)
{
  // First, terminate all the executing task.

  // Finally, execute all the shutdown processes.
  return this->spawn (this->shutdown_);
}

//
// install
//
int CUTS_Virtual_Env::
install (const ACE_CString & name, CUTS_Process_Options * opts, bool startup)
{
  if (startup)
    return this->startup_.bind (name, opts);
  else
    return this->shutdown_.bind (name, opts);
}
