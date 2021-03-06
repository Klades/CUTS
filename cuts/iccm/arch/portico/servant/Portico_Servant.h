// -*- C++ -*-

//==============================================================================
/**
 *  @file       Portico_Servant.h
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
//==============================================================================

#ifndef _ICCM_PORTICO_SERVANT_H_
#define _ICCM_PORTICO_SERVANT_H_

#include "cuts/iccm/servant/Servant.h"

#include "Portico_EventConsumer.h"
#include "Portico_Publisher.h"
#include "Portico_Publisher_Table.h"

#include "ace/Thread_Mutex.h"
#include "ace/Condition_T.h"
#include "NullFederateAmbassador.hh"
#include "fedtime.hh"


namespace iCCM
{

/**
 * @class Portico_Servant
 *
 * Base class for all Portico servant objects. This class enables
 * the container to send commands to the servant, such as
 * domain-specific configuration information.
 */
class ICCM_PORTICO_SVNT_Export Portico_Servant :
  public Servant
{
public:
  /// Trait definitions for iCCM::Servant_T object.
  typedef Portico_EventConsumer eventconsumer_type;
  typedef Portico_Publisher publisher_type;
  typedef Portico_Publisher_Table publisher_table_type;

  /// Default constructor.
  Portico_Servant (const char * name);

  /// Destructor.
  virtual ~Portico_Servant (void);

  /**
   * Configure the servant/federate. This is when the servant notifies
   * the execution of what objects/interactions it will publish and
   * subsribe to.
   */
  virtual int install (const std::string & fed, const std::string & exec) = 0;

  /// Remove the servant.
  virtual void remove (void);


  /**
   * The federate ambassador has discovered a new object in
   * the simulation.
   *
   * @param[in]         obj               New object instance
   * @param[in]         obj_class         Object class type
   * @param[in]         obj_name          Name of the object instance
   */
  virtual void discoverObjectInstance (RTI::ObjectHandle obj,
                                       RTI::ObjectClassHandle obj_class,
                                       const char * obj_name)
                                       throw (RTI::CouldNotDiscover,
                                              RTI::ObjectClassNotKnown,
                                              RTI::FederateInternalError);

  virtual void announceSynchronizationPoint (const char *label,
                                             const char *tag) throw (RTI::FederateInternalError);

  virtual void timeAdvanceGrant (const RTI::FedTime & theTime)
                                throw (RTI::InvalidFederationTime,
                                       RTI::TimeAdvanceWasNotInProgress,
                                       RTI::FederateInternalError);

  /// Get a reference to the RTI ambassador
  RTI::RTIambassador & rti_ambassador (void);

  /// Get a reference to the RTI ambassador
  const RTI::RTIambassador & rti_ambassador (void) const;

  // Get a reference to the null federate ambassador
  NullFederateAmbassador & null_ambassador (void);

  /**
   * Advance the simulation by the specified amount of time. Control
   * does not return from this method until the request time amount is
   * granted.
   *
   * @param[in]         amt           Amount to advance time
   */
  void advance_time (const RTIfedTime & amt);

  /// Get current time of the federate. Unfortunately, this cannot
  /// be changed externally. This time changes whenever the federate
  /// ambassador receives a callback from the RTI.
  const RTIfedTime & federate_time (void) const;

  /// Wait for a new object to be discovered. The current thread will
  /// sleep until a new object has been discovered.
  void wait_for_object_discovery (const ACE_Time_Value * tv = 0);

protected:
  /// The NullFederate ambassador
  NullFederateAmbassador nfamb_;

  /// RTI ambassador for the servant.
  RTI::RTIambassador rtiamb_;

  /// The target execution name.
  std::string execname_;

  /// The federate's current time.
  RTIfedTime federate_time_;

  /// The federate's lookahead time.
  RTIfedTime federate_lookahead_;

  /// The federate's time is advancing.
  bool is_advancing_;

  /// Mutex for the discovery condition object.
  ACE_Thread_Mutex obj_discovery_mutex_;

  /// Condition for discoverying an object.
  ACE_Condition <ACE_Thread_Mutex> obj_discovery_;
};

}

#if defined (__CUTS_INLINE__)
#include "Portico_Servant.inl"
#endif

#endif  // !defined _ICCM_Portico_SERVANT_H_
