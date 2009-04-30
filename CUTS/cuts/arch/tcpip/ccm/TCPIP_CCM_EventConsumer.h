// -*- C++ -*-

//=============================================================================
/**
 *  @file         TCPIP_CCM_EventConsumer.h
 *
 *  $Id$
 *
 *  @author       James H. Hill
 */
//=============================================================================

#ifndef _CUTS_TCPIP_CCM_EVENTCONSUMER_H_
#define _CUTS_TCPIP_CCM_EVENTCONSUMER_H_

#include "EventsS.h"
#include "TCPIP_CCM_export.h"

// Forward decl.
class CUTS_TCPIP_Servant;

/**
 * @class CUTS_TCPIP_CCM_EventConsumer
 */
class CUTS_TCPIP_CCM_Export CUTS_TCPIP_CCM_EventConsumer :
  public ::POA_Components::TCPIP::EventConsumerBase
{
public:
  CUTS_TCPIP_CCM_EventConsumer (CUTS_TCPIP_Servant * parent, long event);

  virtual ~CUTS_TCPIP_CCM_EventConsumer (void);

  virtual ::Components::TCPIP::Endpoint * remote_endpoint (void);

  virtual void push_event (Components::EventBase *);

  virtual void ciao_push_event (Components::EventBase *,
                                const char *,
                                CORBA::TypeCode_ptr);
private:
  CUTS_TCPIP_Servant * parent_;

  long event_;
};

#if defined (__CUTS_INLINE__)
#include "TCPIP_CCM_EventConsumer.inl"
#endif

#endif  // !defined _CUTS_TCPIP_CCM_EVENTCONSUMER_H_
