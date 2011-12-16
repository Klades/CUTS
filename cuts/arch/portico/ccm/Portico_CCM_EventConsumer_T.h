// -*- C++ -*-

//=============================================================================
/**
 *  @file         Portico_CCM_EventConsumer_T.h
 *
 *  $Id$
 *
 *  @author       James H. Hill
 */
//=============================================================================

#ifndef _PORTICO_CCM_EVENTCONSUMER_T_H_
#define _PORTICO_CCM_EVENTCONSUMER_T_H_

#include "Portico_CCM_EventConsumer.h"

/**
 * @class Portico_CCM_EventConsumer_T
 *
 * Servant implmentation of the ::Components::Portico::EventConsumer
 * object that is defined in Portico_Events.idl. This class also
 * inherits from CUTS_CCM_EventConsumer so that it can be used in the
 * CUTS_CCM_Servant_T class, which implements common behavior for all CCM
 * servant objects.
 */
template <typename SERVANT, typename EVENT>
class Portico_CCM_EventConsumer_T : public Portico_CCM_EventConsumer
{
public:
  /// Type definition of the servant upcall method.
  typedef void (SERVANT::*SERVANT_UPCALL) (EVENT * ev);

  /// Default constructor.
  Portico_CCM_EventConsumer_T (SERVANT * servant, SERVANT_UPCALL upcall);

  /// Destructor.
  virtual ~Portico_CCM_EventConsumer_T (void);

  /**
   * Initialize the event consumer. This will configure the
   * consumer's ObjectClass information.
   */
  void init (RTI::RTIambassador * rtiamb);

  /**
   * Observe the specified object.
   *
   * @param[in]           oid               Object instance handle
   */
  virtual void observe_object (const char * tag);

  /**
   * Dispatch an event. This will convert RTI event to a CORBA
   * event and then forward it to the servant.
   */
  void dispatch_event (const RTI::AttributeHandleValuePairSet & attrs);

private:
  /// Type definition of the object class factory.
  typedef typename
    Portico_ObjectClass_Trait_T <EVENT>::objectclass_factory_type
    objectclass_factory_type;

  /// Pointer to the constructed object class.
  std::auto_ptr <objectclass_factory_type> factory_;

  /// Parent servant for the event consumer.
  SERVANT * servant_;

  /// Upcall method for the servant.
  SERVANT_UPCALL upcall_;
};

#if defined (__CUTS_INLINE__)
#include "Portico_CCM_EventConsumer_T.inl"
#endif

#include "Portico_CCM_EventConsumer_T.cpp"

#endif  // !defined _PORTICO_CCM_EVENTCONSUMER_T_H_
