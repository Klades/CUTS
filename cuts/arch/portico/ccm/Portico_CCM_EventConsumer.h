// -*- C++ -*-

//=============================================================================
/**
 *  @file         Portico_CCM_EventConsumer.h
 *
 *  $Id$
 *
 *  @author       James H. Hill
 */
//=============================================================================

#ifndef _PORTICO_CCM_EVENTCONSUMER_H_
#define _PORTICO_CCM_EVENTCONSUMER_H_

#include "ace/Unbounded_Set.h"
#include "cuts/arch/ccm/CCM_EventConsumer.h"

#include "Portico_ObjectClass_Factory.h"
#include "Portico_EventsS.h"

#include "Portico_CCM_export.h"

// Forward decl.
class Portico_Servant;

/**
 * @class Portico_CCM_EventConsumer
 *
 * Servant implmentation of the ::Components::Portico::EventConsumer
 * object that is defined in Portico_Events.idl. This class also
 * inherits from CUTS_CCM_EventConsumer so that it can be used in the
 * CUTS_CCM_Servant_T class, which implements common behavior for all CCM
 * servant objects.
 */
class PORTICO_CCM_Export Portico_CCM_EventConsumer :
  public virtual CUTS_CCM_EventConsumer,
  public virtual ::POA_Components::Portico::EventConsumer
{
public:
  /// Default constructor.
  Portico_CCM_EventConsumer (void);

  /// Destructor.
  virtual ~Portico_CCM_EventConsumer (void);

  /**
   * Initialize this publisher's handle.
   *
   * @param[in]           rtiamb            Pointer to the ambassador
   */
  virtual void init (RTI::RTIambassador * rtiamb) = 0;

  /// Finalize the event consumer.
  virtual void fini (void);

  /**
   * Dispatch an event. This will make an upcall to the
   * contained servant via the contained upcall method.
   *
   * @param[in]           attr              Event attributes
   */
  virtual void dispatch_event (const RTI::AttributeHandleValuePairSet &) = 0;

  /**
   * Observe the specified object.
   *
   * @param[in]           oid               Object instance handle
   */
  virtual void observe_object (const char * tag);

  /**
   * Stop observing the specified object.
   *
   * @param[in]           oid               Object instance handle
   */
  virtual void unobserve_object (const char * tag);

  /// Test of the object handle is observed.
  bool is_observed (RTI::ObjectHandle handle) const;

protected:
  /// Pointer to the ambassador.
  RTI::RTIambassador * rtiamb_;

  /// The publisher's target object handle.
  RTI::ObjectHandle obj_handle_;

  /// Set of object instances this consumer handles.
  ACE_Unbounded_Set < RTI::ObjectHandle > handles_;
};

#if defined (__CUTS_INLINE__)
#include "Portico_CCM_EventConsumer.inl"
#endif

#endif  // !defined _Portico_CCM_EVENTCONSUMER_H_
