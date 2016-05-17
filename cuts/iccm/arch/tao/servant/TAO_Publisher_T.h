// -*- C++ -*-

//=============================================================================
/**
 *  @file         TAO_Publisher_T.h
 *
 *  $Id$
 *
 *  @author       James H. Hill
 */
//=============================================================================

#ifndef _ICCM_TAO_PUBLISHER_T_H_
#define _ICCM_TAO_PUBLISHER_T_H_

#include "TAO_EventsC.h"
#include "TAO_Publisher.h"

namespace iCCM
{

/**
 * @class TAO_Publisher_T
 *
 * Template version of the TAO publisher object that is bound to
 * an specific event type.
 */
template <typename EVENT>
class TAO_Publisher_T :
  public TAO_Publisher
{
public:
  /// Typedef for event type
  typedef EVENT event_type;

  /// Default constructor.
  TAO_Publisher_T (void);

  /// Destructor.
  virtual ~TAO_Publisher_T (void);

  /// Connect the consumer.
  virtual void connect (::Components::EventConsumerBase_ptr consumer);

  /// Allocate a new event.
  EVENT * allocate_event (void);

  /// Send an event via the consumer.
  void send_event (EVENT * ev);
  void send_event (::Components::EventBase * ev);
};

}

#if defined (__CUTS_INLINE__)
#include "TAO_Publisher_T.inl"
#endif

#include "TAO_Publisher_T.cpp"

#endif  // !defined _ICCM_TAO_PUBLISHER_T_H_
