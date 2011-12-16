// -*- C++ -*-

//=============================================================================
/**
 *  @file         Portico_CCM_Publisher_Table_T.h
 *
 *  $Id$
 *
 *  @author       James H. Hill
 */
//=============================================================================

#ifndef _PORTICO_CCM_PUBLISHER_TABLE_T_H_
#define _PORTICO_CCM_PUBLISHER_TABLE_T_H_

#include "cuts/arch/ccm/CCM_Publisher_Table_T.h"

#include "Portico_CCM_Publisher_Table.h"
#include "Portico_CCM_Publisher_T.h"

/**
 * @class Portico_CCM_Publisher_Table_T
 *
 * Template version of the publisher table. It is bound to an event
 * type such that all its consumers publish the same event type, but
 * to different ObjectClass instances.
 */
template <typename EVENT>
class Portico_CCM_Publisher_Table_T :
  public CUTS_CCM_Publisher_Table_T <Portico_CCM_Publisher_Table, Portico_CCM_Publisher_T <EVENT> >
{
public:
  /// Type definition of the base type.
  typedef CUTS_CCM_Publisher_Table_T <Portico_CCM_Publisher_Table,
                                      Portico_CCM_Publisher_T <EVENT> >
                                      base_type;

  /// Default constructor.
  Portico_CCM_Publisher_Table_T (void);

  /// Destructor.
  virtual ~Portico_CCM_Publisher_Table_T (void);

  /**
   * Initialize this publisher's handle.
   *
   * @param[in]           rtiamb            Pointer to the ambassador
   */
  void init (RTI::RTIambassador * rtiamb);

  // Subscribe the consumer.
  virtual ::Components::Cookie * subscribe (::Components::EventConsumerBase_ptr);

  // Unsubscribe a consumer.
  virtual ::Components::EventConsumerBase_ptr unsubscribe (::Components::Cookie *);

  /// Allocate a new event of type EVENT.
  EVENT * allocate_event (void);

  /**
   * Send an event to connected event consumers.
   *
   * @param[in]       ev        Event to send
   */
  void send_event (EVENT * ev);

private:
  /// Type definition of the object class factory.
  typedef typename
    Portico_ObjectClass_Trait_T <EVENT>::objectclass_factory_type
    objectclass_factory_type;

  /// Pointer to the constructed object class.
  std::auto_ptr <objectclass_factory_type> factory_;
};

#if defined (__CUTS_INLINE__)
#include "Portico_CCM_Publisher_Table_T.inl"
#endif

#include "Portico_CCM_Publisher_Table_T.cpp"

#endif  // !defined _PORTICO_CCM_PUBLISHER_TABLE_T_H_
