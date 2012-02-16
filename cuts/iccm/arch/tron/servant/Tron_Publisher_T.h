// -*- C++ -*-

//=============================================================================
/**
 *  @file         Tron_Publisher_T.h
 *
 *  $Id$
 *
 *  @author       James H. Hill
 */
//=============================================================================

#ifndef _ICCM_TRON_PUBLISHER_T_H_
#define _ICCM_TRON_PUBLISHER_T_H_

#include "Tron_EventsC.h"
#include "Tron_Publisher.h"

namespace iCCM
{

/**
 * @class Tron_Publisher_T
 *
 * Template version of the Tron publisher object that is bound to
 * an specific event type.
 */
template <typename EVENT>
class Tron_Publisher_T :
  public Tron_Publisher
{
public:
  /// Default constructor.
  Tron_Publisher_T (void);

  /// Destructor.
  virtual ~Tron_Publisher_T (void);

  /// Connect the consumer.
  virtual void connect (::Components::EventConsumerBase_ptr consumer);

  /// Allocate a new event.
  EVENT * allocate_event (void);

  /**
   * Publish a CORBA event. This method will transform the CORBA event
   * to a DDS event before publishing it over the network.
   *
   * @param[in]         ev            The event to send
   */
  void send_event (typename traits_type::corba_event_type * ev);

protected:
  /// INSERT CODE HERE
};

}

#if defined (__CUTS_INLINE__)
#include "Tron_Publisher_T.inl"
#endif

#include "Tron_Publisher_T.cpp"

#endif  // !defined _ICCM_TRON_PUBLISHER_T_H_
