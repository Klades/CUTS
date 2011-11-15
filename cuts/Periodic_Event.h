// -*- C++ -*-

//=============================================================================
/**
 * @file        Periodic_Event.h
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _CUTS_PERIODIC_EVENT_H_
#define _CUTS_PERIODIC_EVENT_H_

#include "Active_Object.h"
#include "Periodic_Event_Strategy.h"
#include "ace/Timer_Heap.h"
#include "ace/Timer_Queue_Adapters.h"

/**
 * @class CUTS_Periodic_Event
 *
 * Base class for periodic event generators.
 */
class CUTS_Export CUTS_Periodic_Event :
  public ACE_Event_Handler,
  public CUTS_Active_Object
{
public:
  /// Valid strategies for the event generator.
  enum Strategy_Type
  {
    PE_UNDEFINED,
    PE_CONSTANT,
    PE_EXPONENTIAL
  };

  /// Destructor.
  ~CUTS_Periodic_Event (void);

  /// Activate the periodic event.
  virtual int activate (void);

  /// Deactivate the periodic event.
  virtual int deactivate (void);

  int configure (Strategy_Type type, double hertz);

  int schedule_timeout (const ACE_Time_Value & curr_time);

  int handle_timeout (const ACE_Time_Value & timeout, const void *);

  double hertz (void) const;

protected:
  virtual int handle_timeout_i (void) = 0;

  void convert (double secs, ACE_Time_Value & tv);

  /// Default constructor.
  CUTS_Periodic_Event (void);

  /// The strategy type for the event generator.
  Strategy_Type type_;

  /// Strategy for the periodic event.
  ACE_Auto_Ptr <CUTS_Periodic_Event_Strategy> strategy_;

  /// Timer ID for the trigger.
  long timer_;

  /// Hold the timeout value.
  double hertz_;

private:

  void cancel_timeout (void);

  /// The timer queue for the periodic task.
  ACE_Thread_Timer_Queue_Adapter <ACE_Timer_Heap> timer_queue_;
};

#if defined (__CUTS_INLINE__)
#include "Periodic_Event.inl"
#endif

#endif  // !defined _CUTS_PERIODIC_EVENT_H_
