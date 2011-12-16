// -*- C++ -*-

//=============================================================================
/**
 *  @file         Portico_CCM_Publisher.h
 *
 *  Id: CCM_Publisher.h.tmpl 3238 2011-12-07 04:12:45Z hillj Portico_Publisher.h 3086 2011-01-22 05:53:51Z hillj
 *
 *  @author       James H. Hill
 */
//=============================================================================

#ifndef _PORTICO_PUBLISHER_H_
#define _PORTICO_PUBLISHER_H_

#include "ace/UUID.h"
#include "cuts/arch/ccm/CCM_Publisher.h"

#include "Portico_EventsC.h"
#include "Portico_ObjectClass_Factory.h"

#include "Portico_CCM_export.h"

/**
 * @class Portico_CCM_Publisher
 *
 * The base class for all Portico publishers that are integrated into
 * the CCM architecture. In essence, this class is an adapter class that
 * allows a Portico publisher to integrate with the CCM architecture.
 */
class PORTICO_CCM_Export Portico_CCM_Publisher :
  public CUTS_CCM_Publisher
{
public:
  /// Default constructor.
  Portico_CCM_Publisher (void);

  /// Destructor.
  virtual ~Portico_CCM_Publisher (void);

  /**
   * Connect an event consumer to this publisher. This reference should
   * be narrowed to a ::Components::Portico::EventConsumer object.
   *
   * @param[in]           consumer          Referene to event consumer.
   */
  virtual void connect (::Components::EventConsumerBase_ptr consumer);

  /// Helper method for storing a connection.
  void connect (::Components::Portico::EventConsumer_ptr p);

  /// Disconnect the consumer.
  virtual ::Components::EventConsumerBase_ptr disconnect (void);

  /**
   * Initialize this publisher's handle.
   *
   * @param[in]           rtiamb            Pointer to the ambassador
   */
  virtual void init (RTI::RTIambassador * rtiamb) = 0;

  /**
   * Send an event.
   *
   * @param[in]           attrs             Event attributes
   */
  void send_event (const RTI::AttributeHandleValuePairSet & attrs);

protected:
  /// The consumer connected to this publisher.
  ::Components::Portico::EventConsumer_var consumer_;

  /// Pointer to the ambassador.
  RTI::RTIambassador * rtiamb_;

  /// Object instance this publisher is managing.
  RTI::ObjectHandle obj_handle_;

  /// Tag for the object instance.
  ACE_Utils::UUID tag_;
};

#if defined (__CUTS_INLINE__)
#include "Portico_CCM_Publisher.inl"
#endif

#endif
