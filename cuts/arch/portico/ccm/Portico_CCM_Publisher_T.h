// -*- C++ -*-

//=============================================================================
/**
 *  @file         Portico_Publisher_T.h
 *
 *  Id: Portico_CCM_Publisher_T.h 3086 2011-01-22 05:53:51Z hillj
 *
 *  @author       James H. Hill
 */
//=============================================================================

#ifndef _PORTICO_CCM_PUBLISHER_T_H_
#define _PORTICO_CCM_PUBLISHER_T_H_

#include "Portico_EventsC.h"
#include "Portico_CCM_Publisher.h"

/**
 * @class Portico_CCM_Publisher_T
 *
 * Template version of the Portico publisher object that is bound to
 * an specific event type. The template parameter if the CORBA event
 * type that is published by this object.
 */
template <typename EVENT>
class Portico_CCM_Publisher_T : public Portico_CCM_Publisher
{
public:
  /// Type definition of the event type.
  typedef EVENT event_type;

  /// Default constructor.
  Portico_CCM_Publisher_T (void);

  /// Destructor.
  virtual ~Portico_CCM_Publisher_T (void);

  /**
   * Connect an event consumer to this publisher. This reference should
   * be narrowed to a ::Components::Portico::EventConsumer object.
   *
   * @param[in]           consumer          Referene to event consumer.
   */
  virtual void connect (::Components::EventConsumerBase_ptr consumer);

  /// Disconnect the consumer.
  virtual ::Components::EventConsumerBase_ptr disconnect (void);

  /**
   * Initialize this publisher's handle.
   *
   * @param[in]           rtiamb            Pointer to the ambassador
   */
  void init (RTI::RTIambassador * rtiamb);

  /// Allocate a new event of type EVENT.
  EVENT * allocate_event (void);

  /**
   * Publish a CORBA event. This method will transform the CORBA event
   * to a DDS event before publishing it over the network.
   *
   * @param[in]         ev            The event to send
   */
  void send_event (EVENT * ev);

  // Import base class send_event so it is no hidden by this
  // class's implementation of send_event.
  using Portico_CCM_Publisher::send_event;

private:
  /// Type definition of the object class factory.
  typedef typename
    Portico_ObjectClass_Trait_T <EVENT>::objectclass_factory_type
    objectclass_factory_type;

  /// Pointer to the constructed object class.
  std::auto_ptr <objectclass_factory_type> factory_;
};

#if defined (__CUTS_INLINE__)
#include "Portico_CCM_Publisher_T.inl"
#endif

#include "Portico_CCM_Publisher_T.cpp"

#endif  // !defined _PORTICO_CCM_SUBSCRIBER_T_H_
