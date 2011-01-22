// -*- C++ -*-

//=============================================================================
/**
 *  @file         CCM_Publisher_T.h
 *
 *  $Id$
 *
 *  @author       James H. Hill
 */
//=============================================================================

#ifndef _CUTS_CCM_PUBLISHER_T_H_
#define _CUTS_CCM_PUBLISHER_T_H_

#include "tao/Valuetype/ValueFactory.h"
#include "tao/ORB_Core.h"

#include "CCM_Publisher.h"
#include "CCM_Traits_T.h"

/**
 * @class CUTS_CCM_Publisher_T
 *
 * Template for implementing a single subscriber. This will provide
 * the default implemenation, which is to send the event using CORBA.
 */
template <typename T>
class CUTS_CCM_Publisher_T :
  public CUTS_CCM_Single_Subscriber
{
public:
  /// Type definition of the traits type.
  typedef CUTS_CCM_Traits_T <T> traits_type;

  /// Type definition of the event type.
  typedef T event_type;

  /// Default constructor.
  CUTS_CCM_Publisher_T (void);

  /// Destructor.
  virtual ~CUTS_CCM_Publisher_T (void);

  /// Connect a consumer.
  virtual void connect (::Components::EventConsumerBase_ptr consumer);

  /// Disconnect the consumer.
  virtual ::Components::EventConsumerBase_ptr disconnect (void);

  /// Send an event via the consumer.
  void send_event (T * ev);

private:
  /// The consumer for the connection.
  typename traits_type::consumer_var_type consumer_;
};

#if defined (__CUTS_INLINE__)
#include "CCM_Publisher_T.inl"
#endif

#include "CCM_Publisher_T.cpp"

#endif  // !defined _CUTS_CCM_SINGLE_SUBSCRIBER_T_H_
