// -*- C++ -*-

//=============================================================================
/**
 *  @file         Tron_EventConsumer.h
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

#ifndef _ICCM_TRON_EVENTCONSUMER_H_
#define _ICCM_TRON_EVENTCONSUMER_H_

#include "cuts/iccm/servant/EventConsumer.h"

#include "Tron_EventsS.h"
#include "Tron_svnt_export.h"

namespace iCCM
{

// Forward decl.
class Tron_Servant;

/**
 * @class Tron_EventConsumer
 *
 * Servant implmentation of the ::Components::Tron::EventConsumer
 * object that is defined in Tron_Events.idl. This class also
 * inherits from iCCM::EventConsumer so that it can be used in the Servant_T
 * class, which implements common behavior for all CCM servant objects.
 */
class ICCM_TRON_SVNT_Export Tron_EventConsumer :
  public virtual EventConsumer,
  public virtual ::POA_Components::Tron::EventConsumer
{
public:
  /// Default constructor.
  Tron_EventConsumer (void);

  /// Destructor.
  virtual ~Tron_EventConsumer (void);

  /// INSERT CODE HERE

private:
  /// INSERT CODE HERE
};

}

#if defined (__CUTS_INLINE__)
#include "Tron_EventConsumer.inl"
#endif

#endif  // !defined _ICCM_Tron_EVENTCONSUMER_H_
