// -*- C++ -*-

//=============================================================================
/**
 *  @file         TCPIP_CCM_Remote_Endpoint_T.h
 *
 *  $Id$
 *
 *  @author       James H. Hill
 */
//=============================================================================

#ifndef _CUTS_TCPIP_CCM_REMOTE_ENDPOINT_T_H_
#define _CUTS_TCPIP_CCM_REMOTE_ENDPOINT_T_H_

#include "cuts/arch/tcpip/TCPIP_Remote_Endpoint_T.h"
#include "TCPIP_CCM_Remote_Endpoint.h"
#include "TCPIP_CCM_EventConsumer.h"

/**
 * @class CUTS_TCPIP_CCM_Subscriber_T
 */
template <typename T>
class CUTS_TCPIP_CCM_Subscriber_T :
  public CUTS_TCPIP_CCM_Subscriber
{
public:
  /// Default constructor.
  CUTS_TCPIP_CCM_Subscriber_T (void);

  /// Destructor.
  virtual ~CUTS_TCPIP_CCM_Subscriber_T (void);

  /// Connect the specified consumer.
  virtual void connect (::Components::EventConsumerBase_ptr ptr);

  /// Disconnect the current consumer.
  virtual ::Components::EventConsumerBase_ptr disconnect (void);

  /// Send an event to the connected consumer.
  void send_event (T * ev);

private:
  /// The consumer for the endpoint.
  ::Components::TCPIP::EventConsumerBase_var consumer_;

  /// The endpoint for the subscriber.
  CUTS_TCPIP_Remote_Endpoint_T <T> endpoint_;
};

#if defined (__CUTS_INLINE__)
#include "TCPIP_CCM_Remote_Endpoint_T.inl"
#endif

#include "TCPIP_CCM_Remote_Endpoint_T.cpp"

#endif  // !defined _CUTS_TCPIP_CCM_REMOTE_ENDPOINT_T_H_
