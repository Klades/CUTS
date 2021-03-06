// -*- C++ -*-

//=============================================================================
/**
 *  @file         TCPIP_EventConsumer.h
 *
 *  $Id$
 *
 *  Code generated by iCCM skeleton project generator that is include
 *  in the CUTS (http://cuts.cs.iupui.edu) and developed by:
 *
 *      Software Engineering & Distributed System (SEDS) Group
 *      Indiana Univesity-Purdue University Indianapolis
 *      Indianapolis, IN 46202
 */
//=============================================================================

#ifndef _ICCM_TCPIP_EVENTCONSUMER_H_
#define _ICCM_TCPIP_EVENTCONSUMER_H_

#include "cuts/iccm/servant/EventConsumer.h"

#include "TCPIP_EventsS.h"
#include "TCPIP_svnt_export.h"

namespace iCCM
{

// Forward decl.
class TCPIP_Servant;

/**
 * @class TCPIP_EventConsumer
 *
 * Servant implmentation of the ::Components::TCPIP::EventConsumer
 * object that is defined in TCPIP_Events.idl. This class also
 * inherits from iCCM::EventConsumer so that it can be used in the Servant_T
 * class, which implements common behavior for all CCM servant objects.
 */
class ICCM_TCPIP_SVNT_Export TCPIP_EventConsumer :
  public virtual EventConsumer,
  public virtual ::POA_Components::TCPIP::EventConsumer
{
public:
  /// Default constructor.
  TCPIP_EventConsumer (void);

  /// Destructor.
  virtual ~TCPIP_EventConsumer (void);

  /// Method for sending a CORBA event.
  virtual void push_event (::Components::EventBase *);
};

}

#if defined (__CUTS_INLINE__)
#include "TCPIP_EventConsumer.inl"
#endif

#endif  // !defined _ICCM_TCPIP_EVENTCONSUMER_H_
