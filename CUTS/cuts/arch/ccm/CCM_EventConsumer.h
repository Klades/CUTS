// -*- C++ -*-

//=============================================================================
/**
 *  @file         CCM_EventConsumer.h
 *
 *  $Id$
 *
 *  @author       James H. Hill
 */
//=============================================================================

#ifndef _CUTS_CCM_EVENTCONSUMER_H_
#define _CUTS_CCM_EVENTCONSUMER_H_

#include "ccm/CCM_EventConsumerBaseS.h"
#include "CCM_export.h"

/**
 * @class CUTS_CCM_EventConsumer
 *
 * Base class for all event consumer's that will be interfacing
 * with the CUTS_CCM_Servant_T object.
 */
class CUTS_CCM_Export CUTS_CCM_EventConsumer :
  public virtual POA_Components::EventConsumerBase
{
protected:
  /// Default constructor.
  CUTS_CCM_EventConsumer (void);

public:
  /// Destructor.
  virtual ~CUTS_CCM_EventConsumer (void);

  virtual void push_event (::Components::EventBase *);

  virtual void ciao_push_event (::Components::EventBase *,
                                const char *,
                                ::CORBA::TypeCode_ptr);
};

#if defined (__CUTS_INLINE__)
#include "CCM_EventConsumer.inl"
#endif

#endif  // !defined _CUTS_TCPIP_CCM_EVENTCONSUMER_H_
