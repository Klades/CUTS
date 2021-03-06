// -*- C++ -*-

//=============================================================================
/**
 *  @file         CCM_EventConsumer_T.h
 *
 *  $Id$
 *
 *  @author       James H. Hill
 */
//=============================================================================

#ifndef _CUTS_CCM_EVENTCONSUMER_T_H_
#define _CUTS_CCM_EVENTCONSUMER_T_H_

#include "tao/Valuetype/ValueFactory.h"
#include "tao/ORB_Core.h"
#include "CCM_EventConsumer.h"
#include "Consumer_Task.h"

/**
 * @class CUTS_CCM_EventConsumer_T
 */
template <typename T, typename SERVANT>
class CUTS_CCM_EventConsumer_T :
  public CUTS_CCM_EventConsumer
{
public:
  /// Type definition of the event type.
  typedef T event_type;

  /// Type definition of the servant type.
  typedef SERVANT servant_type;

  /// Type definition of the task type.
  typedef Consumer_Task<SERVANT, T> task_type;

  /// Type definition of the upcall method into servant.
  typedef int (*upcall_method_type) (SERVANT *, T *);

  /**
   * Initializing constructor.
   *
   * @param[in]       servant       Servant to callback
   * @param[in]       upcall        Method for upcall
   */
  CUTS_CCM_EventConsumer_T (SERVANT * servant, upcall_method_type upcall);

  /// Destructor.
  virtual ~CUTS_CCM_EventConsumer_T (void);

  virtual void push_event (T * ev);

  virtual void push_event (::Components::EventBase *ev);

private:
  /// Servant that own the event consumer.
  SERVANT * servant_;

  /// Callback function back into the servant.
  upcall_method_type upcall_;

  /// Task to send events to
  task_type * task_;
};

#if defined (__CUTS_INLINE__)
#include "CCM_EventConsumer_T.inl"
#endif

#include "CCM_EventConsumer_T.cpp"

#endif  // !defined _CUTS_TCPIP_CCM_EVENTCONSUMER_H_
