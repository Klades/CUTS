// -*- C++ -*-

//=============================================================================
/**
 * @file        Server_Thread_Strategy.h
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _CUTS_LOGGING_SERVER_THREAD_STRATEGY_H_
#define _CUTS_LOGGING_SERVER_THREAD_STRATEGY_H_

#include "cuts/config.h"
#include "tao/corba.h"

/**
 * @class CUTS_Logging_Server_Thread_Strategy
 *
 * Abstract base class for implementing threading strategies for the 
 * logging server. The strategy is responsible for running the ORB's
 * main event loop.
 */
class CUTS_Logging_Server_Thread_Strategy
{
public:
  /**
   * Default constructor.
   *
   * @param[in]         orb           Target ORB to manage.
   */
  CUTS_Logging_Server_Thread_Strategy (CORBA::ORB_ptr orb);

  /// Destructor.
  virtual ~CUTS_Logging_Server_Thread_Strategy (void);

  /**
   * Run the thread strategy. This needs to run the ORB's main event
   * loop.
   */
  virtual int run (void) = 0;

protected:
  /// ORB associated with the server strategy.
  CORBA::ORB_ptr orb_;
};

#if defined (__CUTS_INLINE__)
#include "Server_Thread_Strategy.inl"
#endif

#endif  // !defined _CUTS_LOGGING_SERVER_THREAD_STRATEGY_H_
