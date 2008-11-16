// $Id$

#include "Logging_Server_Task.h"

#if !defined (__CUTS_INLINE__)
#include "Logging_Server_Task.inl"
#endif

#include "Logging_Server.h"

//
// svc
//
int CUTS_Test_Logging_Server_Task::svc (void)
{
  try
  {
    if (!CORBA::is_nil (this->server_.orb_.in ()))
    {
      ACE_DEBUG ((LM_DEBUG,
                  "%T (%t) - %M - running the ORB's event loop\n"));
      this->server_.orb_->run ();
    }
    else
    {
      ACE_ERROR ((LM_ERROR,
                  "%T (%t) - %M - server's ORB is NIL\n"));
    }

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
