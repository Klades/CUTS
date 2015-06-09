// -*- C++ -*-

//=============================================================================
/**
 *  @file         CHAOS_EventConsumer.h
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

#ifndef _ICCM_CHAOS_EVENTCONSUMER_H_
#define _ICCM_CHAOS_EVENTCONSUMER_H_

#include "cuts/iccm/servant/EventConsumer.h"

#include "CHAOS_EventsS.h"
#include "CHAOS_svnt_export.h"

namespace iCCM
{

// Forward decl.
class CHAOS_Servant;

/**
 * @class CHAOS_EventConsumer
 *
 * Servant implmentation of the ::Components::CHAOS::EventConsumer
 * object that is defined in CHAOS_Events.idl. This class also
 * inherits from iCCM::EventConsumer so that it can be used in the Servant_T
 * class, which implements common behavior for all CCM servant objects.
 *
 * CHAOS does not have its own EventConsumers.  Instead, it is a proxy
 * to architecture-specific EventConsumers.
 */
class ICCM_CHAOS_SVNT_Export CHAOS_EventConsumer :
  public virtual EventConsumer,
  public virtual ::POA_Components::CHAOS::EventConsumer
{
public:
  /// Default constructor.
  CHAOS_EventConsumer (void);

  /// Destructor.
  virtual ~CHAOS_EventConsumer (void);

  /// CCM Lifecycle event calls
  virtual void activate (void);
  virtual void passivate (void);

  virtual void push_event (::Components::EventBase *);
  virtual void allocate (ptrdiff_t & symbol);

  virtual void impl (iCCM::EventConsumer * impl);
  virtual iCCM::EventConsumer * impl (void);

protected:
  ::iCCM::EventConsumer * impl_;
};

}

#if defined (__CUTS_INLINE__)
#include "CHAOS_EventConsumer.inl"
#endif

#endif  // !defined _ICCM_CHAOS_EVENTCONSUMER_H_
