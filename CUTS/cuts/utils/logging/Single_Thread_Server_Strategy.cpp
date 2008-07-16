// $Id$

#include "Single_Thread_Server_Strategy.h"
#include "TestLoggerClient_i.h"

//
// CUTS_Single_Thread_Server_Strategy
//
CUTS_Single_Thread_Server_Strategy::
CUTS_Single_Thread_Server_Strategy (CORBA::ORB_ptr orb)
: CUTS_Logging_Server_Thread_Strategy (orb)
{

}

//
// ~CUTS_Single_Thread_Server_Strategy
//
CUTS_Single_Thread_Server_Strategy::~CUTS_Single_Thread_Server_Strategy (void)
{

}

//
// run
//
int CUTS_Single_Thread_Server_Strategy::run (void)
{
  try
  {
    // Run the ORB's main event loop.
    this->orb_->run ();
  }
  catch (const CORBA::Exception & ex)
  {
    ACE_ERROR ((LM_ERROR,
                "%T - %M - %s\n",
                ex._info ().c_str ()));
  }
  catch (...)
  {
    ACE_ERROR ((LM_ERROR,
                "%T - %M - caught unknown exception\n"));
  }

  return -1;
}
