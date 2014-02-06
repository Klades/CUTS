// -*- C++ -*-

//=============================================================================
/**
 * @file    LOCKWorker.h
 *
 * $Id$
 *
 * This file contains the default Lock worker in CUTS.
 *
 * @author James H. Hill <hillj@isis.vanderbilt.edu>
 */
//=============================================================================

#ifndef _CUTS_LOCK_WORKER_H_
#define _CUTS_LOCK_WORKER_H_

#include "ace/Thread_Mutex.h"
#include "ace/Condition_T.h"

#include "cuts/Worker.h"

#include "Lock_Worker_export.h"

/**
 * @class CUTS_Lock_Worker
 *
 * Basic worker that acquires and releases locks.
 * Simply uses a ACE_Thread_Mutex for now, but could support different
 * types and potientally guards.
 */
class CUTS_LOCK_WORKER_Export CUTS_Lock_Worker :
  public CUTS_Worker
{
public:
  /// Constructor.
  CUTS_Lock_Worker (void);

  /// Destructor.
  virtual ~CUTS_Lock_Worker (void);

  /// wait, automatically acquires and releases lock
  void wait (void);

  /// signal, automatically acquires and releases lock
  void signal (void);

  /// acquire the lock
  void acquire (void);

  /// release the lock
  void release (void);

  /// noop, hack for modeling purposes
  void noop (void);

protected:
  ACE_Thread_Mutex mutex_;
  ACE_Condition <ACE_Thread_Mutex> cond_;
};

CUTS_WORKER_FACTORY_EXPORT_DECL (CUTS_LOCK_WORKER_Export);

#if defined (__CUTS_INLINE__)
#include "Lock_Worker.inl"
#endif

#endif  // !defined _CUTS_LOCK_WORKER_H_