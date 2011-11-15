// -*- C++ -*-

//=============================================================================
/**
 * @file    Periodic_Event_T.h
 *
 * $Id$
 *
 * @author James H. Hill <hillj@isis.vanderbilt.edu>
 */
//=============================================================================

#ifndef _CUTS_PERIODIC_EVENT_T_H_
#define _CUTS_PERIODIC_EVENT_T_H_

#if !defined (ACE_LACKS_PRAGMA_ONCE)
# pragma once
#endif  // ACE_LACKS_PRAGMA_ONCE

#include "Periodic_Event.h"

/**
 * @class CUTS_Periodic_Event_T
 *
 * This class defines a periodic trigger. A periodic trigger is one
 * that processes workload on a periodic basis. It also has an associated
 * probablity for performing the workload to create non-determinism.
 */
template <typename COMPONENT>
class CUTS_Periodic_Event_T : public CUTS_Periodic_Event
{
public:
  /// Type definition for the hosting component type.
  typedef COMPONENT Component_Type;

  /// Type definition for pointer to member funcntion.
  typedef void (COMPONENT::* Method_Pointer) (void);

  /**
   * Default constructor. The default settings for the trigger is
   * 1 Hz with a probability of 1.0 of firing.
   */
  CUTS_Periodic_Event_T (void);

  /// Destructor.
  virtual ~CUTS_Periodic_Event_T (void);

  /**
   * Initalize the periodic trigger. This method must be called before
   * the trigger can be activated. This method will set the target
   * component and the member function that is to be called when the
   * trigger fires.
   *
   * @param[in]     component         Pointer to the target component.
   * @param[in]     method            Target method to invoke on component.
   */
  void init (Component_Type * component, Method_Pointer method);

protected:
  /// Handler for the timeout event.
  virtual int handle_timeout_i (void);

private:
  /// Pointer the parent component of the stored method.
  Component_Type * component_;

  /// Pointer to the <COMPONENT> member function assigned
  /// to this trigger event.
  Method_Pointer method_;
};

#if defined (__CUTS_INLINE__)
# include "Periodic_Event_T.inl"
#endif

#include "Periodic_Event_T.cpp"

#endif  // !defined _CUTS_PERIODIC_EVENT_T_H_
