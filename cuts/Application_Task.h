// -*- C++ -*-

//=============================================================================
/**
 * @file        Application_Task.h
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _CUTS_APPLICATION_TASK_H_
#define _CUTS_APPLICATION_TASK_H_

#include "Active_Object.h"
#include "ace/Task.h"

/**
 * @class CUTS_Application_Task
 *
 * Base class for periodic event generators.
 */
class CUTS_Export CUTS_Application_Task :
  public ACE_Task_Base,
  public CUTS_Active_Object
{
public:
  /// Default constructor.
  CUTS_Application_Task (void);

  /// Destructor.
  ~CUTS_Application_Task (void);

  /// Activate the periodic event.
  virtual int activate (void);

  /// Deactivate the periodic event.
  virtual int deactivate (void);

  /// Activation state getter
  bool is_active (void) const;

  /// Set the number of threads used with the task is activated.
  void nthreads (int n);

  /// Get number of threads for activation.
  int nthreads (void) const;

private:
  int nthreads_;

  /// Activation flag
  bool active_;
};

#if defined (__CUTS_INLINE__)
#include "Application_Task.inl"
#endif

#endif  // !defined _CUTS_APPLICATION_TASK_H_
