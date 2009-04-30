// -*- C++ -*-

//=============================================================================
/**
 *  @file         TCPIP_CCM_Events_Impl.h
 *
 *  $Id$
 *
 *  @author       James H. Hill
 */
//=============================================================================

#ifndef _CUTS_TCPIP_CCM_EVENTS_IMPL_H_
#define _CUTS_TCPIP_CCM_EVENTS_IMPL_H_

#include "ccm/CCM_EventsS.h"
#include "TCPIP_CCM_export.h"

/**
 * @class CUTS_TCPIP_CCM_Events_Impl
 */
class CUTS_TCPIP_CCM_Export CUTS_TCPIP_CCM_Events_Impl :
  public POA_Components::Events
{
protected:
  CUTS_TCPIP_CCM_Events_Impl (void);

public:
  virtual ~CUTS_TCPIP_CCM_Events_Impl (void);

  virtual ::Components::Cookie *
    subscribe (const char * publisher_name,
                ::Components::EventConsumerBase_ptr subscriber);

  virtual ::Components::EventConsumerBase_ptr
    unsubscribe (const char * publisher_name, ::Components::Cookie * ck);

  virtual Components::EventConsumerBase_ptr
    get_consumer (const char *);

  virtual void
    connect_consumer (const char *, Components::EventConsumerBase_ptr);

  virtual Components::EventConsumerBase_ptr
    disconnect_consumer (const char *);

  virtual Components::ConsumerDescriptions *
    get_all_consumers (void);

  virtual Components::ConsumerDescriptions *
    get_named_consumers (const Components::NameList &);

  virtual Components::EmitterDescriptions *
    get_all_emitters (void);

  virtual Components::EmitterDescriptions *
    get_named_emitters (const Components::NameList &);

  virtual Components::PublisherDescriptions *
    get_all_publishers (void);

  virtual Components::PublisherDescriptions *
    get_named_publishers (const Components::NameList &);
};

#if defined (__CUTS_INLINE__)
#include "TCPIP_CCM_Events_Impl.inl"
#endif

#endif  // !defined _CUTS_TCPIP_CCM_EVENTS_IMPL_H_
