// $Id$

#include "Threadpool_Server_Strategy.h"

#if !defined (__CUTS_INLINE__)
#include "Threadpool_Server_Strategy.inl"
#endif

//
// run
//
int CUTS_Threadpool_Server_Strategy::run (void)
{
  // Spawn the child threads to help with the processing. We need to get
  // the their group id.
  this->grp_id_ =
    this->thr_manager_.spawn_n (this->thr_count_,
                                &CUTS_Threadpool_Server_Strategy::svc_run,
                                this);

  int retval = 0;

  if (this->grp_id_ != -1)
  {
    // Run the ORB's main event loop.
    retval = this->run_orb ();

    // Wait for all the child threads to finish processing.
    if (retval == 0)
    {
      ACE_DEBUG ((LM_DEBUG, 
                  "%T - %M - waiting for %d child thread(s) to exit\n",
                  this->thr_count_));

      this->thr_manager_.wait_grp (this->grp_id_);
    }
  }
  else
  {
    ACE_ERROR ((LM_ERROR,
                "%T - %M - failed to initialize thread pool [%m]\n"));
    retval = -1;
  }

  return retval;
}

//
// svc_run
//
ACE_THR_FUNC_RETURN CUTS_Threadpool_Server_Strategy::svc_run (void * param)
{
  // Extract the object from the parameter.
  CUTS_Threadpool_Server_Strategy * strategy =
    reinterpret_cast <CUTS_Threadpool_Server_Strategy *> (param);

  ACE_DEBUG ((LM_DEBUG,
              "%T - %M - running the child server thread (%t)\n"));

  // Run the ORB's main event loop.
  int const svc_status = strategy->run_orb ();

  ACE_THR_FUNC_RETURN status;
#if defined (ACE_HAS_INTEGRAL_TYPE_THR_FUNC_RETURN)
  status = static_cast <ACE_THR_FUNC_RETURN> (svc_status);
#else
  status = reinterpret_cast <ACE_THR_FUNC_RETURN> (svc_status);
#endif /* ACE_HAS_INTEGRAL_TYPE_THR_FUNC_RETURN */

  return status;
}

//
// run_orb
//
int CUTS_Threadpool_Server_Strategy::run_orb (void)
{
  try
  {
    // Run the ORB's main event loop.
    this->orb_->run ();
    return 0;
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
                "%T - %M - caught unknown error\n"));
  }

  return -1;
}

