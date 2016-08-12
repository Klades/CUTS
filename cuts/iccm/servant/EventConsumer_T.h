// -*- C++ -*-

//=============================================================================
/**
 *  @file         EventConsumer_T.h
 *
 *  $Id$
 *
 *  @author       James H. Hill
 */
//=============================================================================

#ifndef _EVENTCONSUMER_T_H_
#define _EVENTCONSUMER_T_H_

#include "tao/Valuetype/ValueFactory.h"
#include "tao/ORB_Core.h"

#include "EventConsumer.h"

namespace iCCM
{

/**
 * @class EventConsumer_T
 */
template <typename T, typename SERVANT>
class EventConsumer_T : public EventConsumer
{
public:
  /// Type definition of the event type.
  typedef T event_type;

  /// Type definition of the servant type.
  typedef SERVANT servant_type;

  /// Type definition of the upcall method into servant.
  typedef int (*callback_method) (SERVANT *, T *);

  /**
   * Initializing constructor.
   *
   * @param[in]       servant       Servant to callback
   * @param[in]       upcall        Method for upcall
   * @param[in]       task          Task to run method call through
   */
  EventConsumer_T (SERVANT * servant, callback_method upcall, task_type * task = 0);

  /// Destructor.
  virtual ~EventConsumer_T (void);

protected:
  /// Servant that own the event consumer.
  SERVANT * servant_;

  /// Callback function back into the servant.
  callback_method callback_;
};

}

#if defined (__CUTS_INLINE__)
#include "EventConsumer_T.inl"
#endif

#include "EventConsumer_T.cpp"

#endif  // !defined _CUTS_TCPIP_EVENTCONSUMER_H_
