// -*- C++ -*-

//=============================================================================
/**
 *  @file         TCPIP_Publisher_T.h
 *
 *  $Id$
 *
 *  @author       James H. Hill
 */
//=============================================================================

#ifndef _ICCM_TCPIP_PUBLISHER_T_H_
#define _ICCM_TCPIP_PUBLISHER_T_H_

#include "TCPIP_EventsC.h"
#include "TCPIP_Publisher.h"
#include "../stub/TCPIP_Remote_Endpoint_T.h"

namespace iCCM
{

/**
 * @class TCPIP_Publisher_T
 *
 * Template version of the TCPIP publisher object that is bound to
 * an specific event type.
 */
template <typename EVENT>
class TCPIP_Publisher_T :
  public TCPIP_Publisher
{
public:
  /// Typedef for event type
  typedef EVENT event_type;

  /// Default constructor.
  TCPIP_Publisher_T (void);

  /// Destructor.
  virtual ~TCPIP_Publisher_T (void);

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
  void send_event (EVENT * ev);

  /// Disconnect the consumer.
  virtual ::Components::EventConsumerBase_ptr disconnect (void);

protected:
  /// The endpoint for the subscriber.
  CUTS_TCPIP_Remote_Endpoint_T <EVENT> endpoint_;
};

}

#if defined (__CUTS_INLINE__)
#include "TCPIP_Publisher_T.inl"
#endif

#include "TCPIP_Publisher_T.cpp"

#endif  // !defined _ICCM_TCPIP_PUBLISHER_T_H_
