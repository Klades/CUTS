// -*- C++ -*-

//=============================================================================
/**
 *  @file         Tron_Publisher.h
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

#ifndef _ICCM_TRON_PUBLISHER_H_
#define _ICCM_TRON_PUBLISHER_H_

#include "cuts/iccm/servant/Publisher.h"

#include "Tron_EventsC.h"
#include "Tron_svnt_export.h"

namespace iCCM
{

/**
 * @class Tron_Publisher
 *
 * The base class for all Tron publishers that are integrated into
 * the iCCM architecture. In essence, this class is an adapter class that
 * allows a Tron publisher to integrate with the iCCM architecture.
 */
class ICCM_TRON_SVNT_Export Tron_Publisher :
  public Publisher
{
public:
  /// Default constructor.
  Tron_Publisher (void);

  /// Destructor.
  virtual ~Tron_Publisher (void);

  /**
   * Connect an event consumer to this publisher. This reference should
   * be narrowed to a ::Components::Tron::EventConsumer object.
   *
   * @param[in]           consumer          Referene to event consumer.
   */
  virtual void connect (::Components::EventConsumerBase_ptr consumer);

  /// Disconnect the consumer.
  virtual ::Components::EventConsumerBase_ptr disconnect (void);

  /// INSERT CODE HERE

protected:
  /// The consumer connected to this publisher.
  ::Components::Tron::EventConsumer_var consumer_;

  /// INSERT CODE HERE
};

}

#if defined (__CUTS_INLINE__)
#include "Tron_Publisher.inl"
#endif

#endif  // !defined _ICCM_TRON_PUBLISHER_H_
