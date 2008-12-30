// -*- C++ -*-

//=============================================================================
/**
 * @file        BarrierCallback_i.h
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _CUTS_BARRIER_CALLBACK_I_H_
#define _CUTS_BARRIER_CALLBACK_I_H_

#include "../barrierS.h"
#include "ace/Condition_T.h"
#include "ace/Thread_Mutex.h"

/**
 * @class CUTS_Barrier_Callback_i
 */
class CUTS_Barrier_Callback_i : public POA_CUTS::BarrierCallback
{
public:
  /// Default constructor.
  CUTS_Barrier_Callback_i (void);

  /// Destructor.
  virtual ~CUTS_Barrier_Callback_i (void);

  void signal (void);

  void abort (void);

  int wait (void);

private:
  ACE_Thread_Mutex mutex_;

  ACE_Condition <ACE_Thread_Mutex> is_ready_;

  int retval_;
};

#if defined (__CUTS_INLINE__)
#include "BarrierCallback_i.inl"
#endif

#endif  // !defined _CUTS_BARRIER_CALLBACK_I_H_
