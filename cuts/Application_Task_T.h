// -*- C++ -*-

//=============================================================================
/**
 * @file    Application_Task_T.h
 *
 * $Id$
 *
 * @author James H. Hill <hillj@isis.vanderbilt.edu>
 */
//=============================================================================

#ifndef _CUTS_APPLICATION_TASK_T_H_
#define _CUTS_APPLICATION_TASK_T_H_

#if !defined (ACE_LACKS_PRAGMA_ONCE)
# pragma once
#endif  // ACE_LACKS_PRAGMA_ONCE

#include "Application_Task.h"

/**
 * @class CUTS_Application_Task_T
 *
 * This class defines an application task. An application task is one
 * that processes a workload when a component is activated.
 */
template <typename COMPONENT>
class CUTS_Application_Task_T : public CUTS_Application_Task
{
public:
  /// Type definition for the hosting component type.
  typedef COMPONENT Component_Type;

  /// Type definition for pointer to member funcntion.
  typedef void (COMPONENT::* Method_Pointer) (void);

  /// Default constructor
  CUTS_Application_Task_T (void);

  /// Destructor.
  virtual ~CUTS_Application_Task_T (void);

  /**
   * Initalize the application task. This method must be called before
   * the task can be activated. This method will set the target
   * component and the member function that is to be called when the
   * task is activated.
   *
   * @param[in]     component         Pointer to the target component.
   * @param[in]     method            Target method to invoke on component.
   */
  void init (Component_Type * component, Method_Pointer method);

  int svc (void);

private:
  /// Pointer the parent component of the stored method.
  Component_Type * component_;

  /// Pointer to the <COMPONENT> member function assigned
  /// to this trigger event.
  Method_Pointer method_;
};

#if defined (__CUTS_INLINE__)
# include "Application_Task_T.inl"
#endif

#include "Application_Task_T.cpp"

#endif  // !defined _CUTS_APPLICATION_TASK_T_H_
