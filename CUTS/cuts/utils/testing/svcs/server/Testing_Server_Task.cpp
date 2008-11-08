// $Id$

#include "Testing_Server_Task.h"
#include "Testing_Server_export.h"
#include "Testing_Server.h"
#include "ace/Reactor.h"

//
// CUTS_Testing_Server_Task
//
CUTS_Testing_Server_Task::
CUTS_Testing_Server_Task (CUTS_Testing_Server & server)
: server_ (server)
{
  CUTS_TESTING_SERVER_TRACE ("CUTS_Testing_Server_Task::CUTS_Testing_Server_Task (CORBA::ORB_ptr)");
}

//
// ~CUTS_Testing_Server_Task
//
CUTS_Testing_Server_Task::~CUTS_Testing_Server_Task (void)
{
  CUTS_TESTING_SERVER_TRACE ("CUTS_Testing_Server_Task::~CUTS_Testing_Server_Task (void)");
}

//
// svc
//
int CUTS_Testing_Server_Task::svc (void)
{
  CUTS_TESTING_SERVER_TRACE ("CUTS_Testing_Server_Task::svc (void)");

  try
  {
    // Get a hold of the ORB for the server.
    CORBA::ORB_var orb = this->server_.the_ORB ();

    if (::CORBA::is_nil (orb.in ()))
    {
      ACE_ERROR_RETURN ((LM_ERROR,
                         "%T (%t) - %M - ORB is a NIL reference\n"),
                         -1);
    }

    ACE_DEBUG ((LM_INFO,
                "%T (%t) - %M - running the ORB's main event loop\n"));

    // Run the ORB's main event loop.
    orb->run ();
    return 0;
  }
  catch (const CORBA::Exception & ex)
  {
    ACE_ERROR ((LM_ERROR,
                "%T (%t) - %M - %s\n",
                ex._info ().c_str ()));
  }

  return -1;
}
