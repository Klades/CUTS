// -*- C++ -*-

//=============================================================================
/**
 *  @file       RTIDDS_Publisher.h
 *
 *  $Id$
 *
 *  @author     James H. Hill
 */
//=============================================================================

#ifndef _CUTS_RTIDDS_PUBLISHER_H_
#define _CUTS_RTIDDS_PUBLISHER_H_

#include "ndds/ndds_cpp.h"
#include "cuts/arch/ccm/CCM_Publisher.h"
#include "cuts/arch/rtidds/RTIDDS_Endpoint.h"
#include "RTIDDS_EventsC.h"
#include "RTIDDS_CCM_export.h"

/**
 * @class CUTS_RTIDDS_CCM_Publisher
 *
 * Base class for all CCM-enabled RTI-DDS publishers.
 */
class CUTS_RTIDDS_CCM_Export CUTS_RTIDDS_CCM_Publisher :
  public CUTS_CCM_Publisher
{
public:
  /// Default constructor.
  CUTS_RTIDDS_CCM_Publisher (void);

  /// Destructor.
  virtual ~CUTS_RTIDDS_CCM_Publisher (void);

  /**
   * Configure the DDS publisher for this wrapper object.
   *
   * @param[in]       publisher         The new publisher
   */
  virtual void configure (::DDSPublisher * publisher);

  // Connect a new event consumer.
  virtual void connect (::Components::EventConsumerBase_ptr consumer);

  // Disconnect the event consumer.
  virtual ::Components::EventConsumerBase_ptr disconnect (void);

protected:
  /// The connected event consumer.
  ::Components::RTIDDS::EventConsumer_var consumer_;

  /// The contained DDS publisher.
  ::DDSPublisher * publisher_;

  /// The writer assigned to this publisher.
  ::DDSDataWriter * abstract_writer_;

  /// The DDS endpoint.
  CUTS_RTIDDS_Endpoint endpoint_;
};

#if defined (__CUTS_INLINE__)
#include "RTIDDS_Publisher.inl"
#endif

#endif
