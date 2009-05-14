// -*- C++ -*-

//=============================================================================
/**
 * @file        CCM_Event_Handler_T.h
 *
 * $Id$
 *
 * @author      James H. Hill <j dot hill at vanderbilt dot edu>
 */
//=============================================================================

#ifndef _CUTS_CCM_EVENT_HANDLER_T_H_
#define _CUTS_CCM_EVENT_HANDLER_T_H_

#include "ace/Task_Ex_T.h"
#include "cuts/Active_Object.h"

/**
 * @class CUTS_CCM_Event_Handler_T
 */
template <typename T, typename EVENT>
class CUTS_CCM_Event_Handler_T :
  protected ACE_Task_Ex <ACE_MT_SYNCH, EVENT>,
  public CUTS_Active_Object
{
public:
  /// Type definition of the component type.
  typedef T component_type;

  /// Type definition of the event type.
  typedef EVENT event_type;

  /// Type definition of the callback for the event handler.
  typedef void (T::*callback_type) (EVENT *);

  /// Default constructor.
  CUTS_CCM_Event_Handler_T (void);

  /**
   * Initializing constructor
   *
   * @param[in]       component       Target component for callback
   * @param[in]       method          Method to invoke on \a component
   */
  CUTS_CCM_Event_Handler_T (T * component, callback_type method);

  /// Destructor
  virtual ~CUTS_CCM_Event_Handler_T (void);

  /**
   * Initialize the event handler.
   *
   * @param[in]       component       Target component for callback
   * @param[in]       method          Method to invoke on \a component
   */
  int init (T * component, callback_type method);

  int activate (void);

  int deactivate (void);

  /**
   * Handle an event. This will enqueue the event.
   */
  virtual int handle_event (EVENT * ev);

  virtual int svc (void);

  void thread_count (size_t count);

  void affinity_mask (ACE_UINT32 mask);

private:
  /// Type definition of the task type.
  typedef ACE_Task_Ex <ACE_MT_SYNCH, EVENT> task_type;

  /// Target component to invoke.
  T * component_;

  /// Method to invoke on component.
  callback_type method_;

  /// Number of threads to spawn.
  size_t thr_count_;

  ACE_UINT32 affinity_mask_;
};

#if defined (__CUTS_INLINE__)
#include "CCM_Event_Handler_T.inl"
#endif

#include "CCM_Event_Handler_T.cpp"

#endif  // !defined _CUTS_CCM_EVENT_HANDLER_T_H_
