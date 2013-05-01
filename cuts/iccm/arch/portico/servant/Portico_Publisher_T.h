// -*- C++ -*-

//=============================================================================
/**
 *  @file         Portico_Publisher_T.h
 *
 *  $Id$
 *
 *  @author       James H. Hill
 */
//=============================================================================

#ifndef _ICCM_PORTICO_PUBLISHER_T_H_
#define _ICCM_PORTICO_PUBLISHER_T_H_

#include "Portico_EventsC.h"
#include "Portico_Publisher.h"

namespace iCCM
{

/**
 * @class Portico_Publisher_T
 *
 * Template version of the Portico publisher object that is bound to
 * an specific event type.
 */
template <typename EVENT>
class Portico_Publisher_T :
  public Portico_Publisher
{
public:
  /// Typedef for event type
  typedef EVENT event_type;

  /// Default constructor.
  Portico_Publisher_T (void);

  /// Destructor.
  virtual ~Portico_Publisher_T (void);

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

  /**
   * Initialize this publisher's handle.
   *
   * @param[in]           rtiamb            Pointer to the ambassador
   */
  void init (RTI::RTIambassador * rtiamb);

  // Import base class send_event so it is no hidden by this
  // class's implementation of send_event.
  using Portico_Publisher::send_event;

  /// Disconnect the consumer.
  virtual ::Components::EventConsumerBase_ptr disconnect (void);

protected:
  /// Type definition of the object class factory.
  typedef typename
    Portico_ObjectClass_Trait_T <EVENT>::objectclass_factory_type
    objectclass_factory_type;

  /// Pointer to the constructed object class.
  std::auto_ptr <objectclass_factory_type> factory_;

};

}

#if defined (__CUTS_INLINE__)
#include "Portico_Publisher_T.inl"
#endif

#include "Portico_Publisher_T.cpp"

#endif  // !defined _ICCM_PORTICO_PUBLISHER_T_H_
