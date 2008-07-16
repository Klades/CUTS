// -*- C++ -*-

//=============================================================================
/**
 * @file        Threadpool_Server_Strategy.h
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _CUTS_LOGGING_THREADPOOL_SERVER_STRATEGY_H_
#define _CUTS_LOGGING_THREADPOOL_SERVER_STRATEGY_H_

#include "Server_Thread_Strategy.h"
#include "ace/Thread_Manager.h"

/**
 * @class CUTS_Threadpool_Server_Strategy
 *
 * Configures the server to use a threadpool for running the ORB's main
 * event loop.
 */ 
class CUTS_Threadpool_Server_Strategy :
  public CUTS_Logging_Server_Thread_Strategy
{
public:
  /**
   * Initializing constructor.
   *
   * @param[in]       orb       Target ORB to handle.
   */ 
  CUTS_Threadpool_Server_Strategy (CORBA::ORB_ptr orb);

  /// Destructor.
  virtual ~CUTS_Threadpool_Server_Strategy (void);

  /// Run the thread strategy on the ORB.
  virtual int run (void);

  /**
   * Get the size of the threadpool.
   *
   * @return          Size of the threadpool.
   */
  size_t thr_count (void) const;

  /**
   * Set the threadpool size.
   *
   * @param[in]       count       Size of the threadpool.
   */
  void thr_count (size_t count);

private:
  /// Service routine for the thread pool.
  static ACE_THR_FUNC_RETURN svc_run (void * param);

  /// Run the ORB's main event loop.
  int run_orb (void);

  /// The thread pool's personal thread manager.
  ACE_Thread_Manager thr_manager_;

  /// Group id of the spawned threads.
  int grp_id_;

  /// Set the number of threads.
  size_t thr_count_;
};

#if defined (__CUTS_INLINE__)
#include "Threadpool_Server_Strategy.inl"
#endif

#endif  // !defined _CUTS_LOGGING_THREADPOOL_SERVER_STRATEGY_H_
