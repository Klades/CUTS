// -*- C++ -*-

//=============================================================================
/**
 * @file        Node_Daemon_Client.cpp
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

#include "Node_DaemonC.h"
#include "Client_Options.h"
#include "ace/Get_Opt.h"
#include "ace/Log_Msg.h"
#include "ace/OS_NS_unistd.h"

//
// parse_args
//
int parse_args (int argc, char * argv[])
{
  // Setup the <ACE_Get_Opt> variable.
  const char * opts = "hv";
  ACE_Get_Opt get_opt (argc, argv, opts);

  // Setup the long options for the command-line
  get_opt.long_option ("help", 'h', ACE_Get_Opt::NO_ARG);
  get_opt.long_option ("verbose", 'v', ACE_Get_Opt::NO_ARG);

  get_opt.long_option ("task-terminate", ACE_Get_Opt::ARG_REQUIRED);
  get_opt.long_option ("task-restart", ACE_Get_Opt::ARG_REQUIRED);
  get_opt.long_option ("shutdown", ACE_Get_Opt::NO_ARG);

  int option;
  while ((option = get_opt ()) != EOF)
  {
    switch (option)
    {
    case 0:
      if (ACE_OS::strcmp (get_opt.long_option (), "shutdown") == 0)
        CLIENT_OPTIONS ()->shutdown_ = true;

      else if (ACE_OS::strcmp (get_opt.long_option (), "task-terminate") == 0)
        CLIENT_OPTIONS ()->terminate_list_.insert (get_opt.opt_arg ());

      else if (ACE_OS::strcmp (get_opt.long_option (), "task-restart") == 0)
        CLIENT_OPTIONS ()->restart_list_.insert (get_opt.opt_arg ());

      break;

    case 'h':
      // we need to display the help then exit
      ACE_OS::exit (0);
      break;

    case 'v':
      CLIENT_OPTIONS ()->verbose_ = true;
      break;

    case '?':
      // unknown option; do nothing
      break;

    case ':':
      ACE_ERROR_RETURN ((LM_ERROR,
                         "%c is missing an argument\n",
                         get_opt.opt_opt ()),
                         1);
      break;

    default:
      /* do nothing */;
    }
  }

  return 0;
}

//
// terminate_tasks
//
void terminate_tasks (CUTS::Task_Manager_ptr daemon)
{
  VERBOSE_MESSAGE ((LM_INFO,
                    "terminating %d tasks\n",
                    CLIENT_OPTIONS ()->terminate_list_.size ()));

  ACE_Unbounded_Set <ACE_CString>::
    const_iterator iter (CLIENT_OPTIONS ()->terminate_list_);

  CORBA::String_var taskname;

  for ( ; !iter.done (); iter ++)
  {
    VERBOSE_MESSAGE ((LM_INFO,
                      "terminating task <%s>\n",
                      (*iter).c_str ()));

    taskname = CORBA::string_dup ((*iter).c_str ());

    if (daemon->task_terminate (taskname.in (), true) == 0)
    {
      VERBOSE_MESSAGE ((LM_INFO,
                        "successfully terminated task <%s>\n",
                        (*iter).c_str ()));
    }                  
    else
    {
      ACE_ERROR ((LM_ERROR,
                  "failed to terminate task <%s>\n",
                  (*iter).c_str ()));
    }
  }
}

//
// restart_tasks
//
void restart_tasks (CUTS::Task_Manager_ptr daemon)
{
  VERBOSE_MESSAGE ((LM_INFO,
                    "restarting %d tasks\n",
                    CLIENT_OPTIONS ()->restart_list_.size ()));

  ACE_Unbounded_Set <ACE_CString>::
    const_iterator iter (CLIENT_OPTIONS ()->restart_list_);

  CORBA::String_var taskname;

  for ( ; !iter.done (); iter ++)
  {
    VERBOSE_MESSAGE ((LM_INFO,
                      "terminating task <%s>\n",
                      (*iter).c_str ()));

    taskname = CORBA::string_dup ((*iter).c_str ());
   
    if (daemon->task_restart (taskname.in ()) == 0)
    {
      VERBOSE_MESSAGE ((LM_INFO,     
                        "successfully restarted task <%s>\n",
                        (*iter).c_str ()));
    }
    else
    {
      ACE_ERROR ((LM_ERROR,
                  "failed to restart task <%s>\n",
                  (*iter).c_str ()));
    }
  }
}

//
// main
//
int main (int argc, char * argv [])
{
  try
  {
    // initalize the ORB
    CORBA::ORB_var orb = CORBA::ORB_init (argc, argv);

    if (parse_args (argc, argv) != 0)
      return 1;

    // Resolve the initiale reference to the Node_Daemon
    VERBOSE_MESSAGE ((LM_DEBUG,
                      "resolving initial reference to NodeDaemon\n"));
    ::CORBA::Object_var obj = orb->resolve_initial_references ("NodeDaemon");
    ::CORBA::String_var strobj = orb->object_to_string (obj.in ());

    if (::CORBA::is_nil (obj.in ()))
    {
      ACE_ERROR_RETURN ((
        LM_ERROR,
        "failed to resolved initial reference to NodeDaemon\n"),
        1);
    }

    // Narrow the generic object to a CUTS/Node_Daemon object.
    VERBOSE_MESSAGE ((LM_DEBUG,
                      "extracting node daemon from object reference\n"));

    CUTS::Task_Manager_var daemon =
      CUTS::Task_Manager::_narrow (obj.in ());

    if (::CORBA::is_nil (daemon.in ()))
    {
      ACE_ERROR_RETURN ((LM_ERROR,
                         "object was not a %s\n",
                         daemon->_interface_repository_id ()),
                         1);
    }

    // Shutdown the target node daemon, if necessary.
    if (CLIENT_OPTIONS ()->shutdown_)
    {
      VERBOSE_MESSAGE ((LM_DEBUG,
                        "shutting down target node daemon\n"));

      daemon->shutdown (true);
    }
    else
    {
      // Terminate all the specified tasks.
      terminate_tasks (daemon.in ());

      // Restart all the specified tasks.
      restart_tasks (daemon.in ());
    }

    // Destroy the ORB.
    VERBOSE_MESSAGE ((LM_DEBUG, "destroying the ORB\n"));
    orb->destroy ();
    return 0;
  }
  catch (::CORBA::Exception & ex)
  {
    ACE_ERROR ((LM_ERROR,
                "%s\n",
                ex._info ().c_str ()));
  }
  catch (...)
  {
    ACE_ERROR ((LM_ERROR,
                "*** error: caught unknown exception\n"));
  }

  return 1;
}
