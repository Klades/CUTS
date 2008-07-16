// -*- C++ -*-

//=============================================================================
/**
 * @file        Single_Thread_Server_Strategy.h
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _CUTS_LOGGING_SINLGE_THREAD_SERVER_STRATEGY_H_
#define _CUTS_LOGGING_SINLGE_THREAD_SERVER_STRATEGY_H_

#include "Server_Thread_Strategy.h"

/**
 * @class CUTS_Single_Thread_Server_Strategy
 */
class CUTS_Single_Thread_Server_Strategy :
  public CUTS_Logging_Server_Thread_Strategy
{
public:
  CUTS_Single_Thread_Server_Strategy (CORBA::ORB_ptr orb);

  virtual ~CUTS_Single_Thread_Server_Strategy (void);

  virtual int run (void);
};

#endif  // !defined _CUTS_LOGGING_SINLGE_THREAD_SERVER_STRATEGY_H_
