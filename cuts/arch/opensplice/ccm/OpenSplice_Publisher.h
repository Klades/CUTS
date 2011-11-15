// -*- C++ -*-

//=============================================================================
/**
 *  @file         OpenSplice_Publisher.h
 *
 *  $Id$
 *
 *  @author       James H. Hill
 */
//=============================================================================

#ifndef _CUTS_OPENSPLICE_PUBLISHER_H_
#define _CUTS_OPENSPLICE_PUBLISHER_H_

#include "OpenSplice_EventsC.h"

#include "cuts/arch/ccm/CCM_Publisher.h"
#include "cuts/arch/opensplice/OpenSplice_Endpoint.h"

#include "OpenSplice_CCM_export.h"

/**
 * @class CUTS_OpenSplice_CCM_Publisher
 *
 * The base class for all OpenSplice publishers that are integrated into
 * the CCM architecture. In essence, this class is an adapter class that
 * allows a DDS publisher to integrate with the CCM architecture.
 */
class CUTS_OPENSPLICE_CCM_Export CUTS_OpenSplice_CCM_Publisher :
  public CUTS_CCM_Publisher
{
public:
  /// Default constructor.
  CUTS_OpenSplice_CCM_Publisher (void);

  /// Destructor.
  virtual ~CUTS_OpenSplice_CCM_Publisher (void);

  /**
   * Configure the publish with the DDS publisher object. This object
   * will be used to send events to readers.
   *
   * @param[in]         publisher         Target DDS publisher
   */
  virtual void configure (::DDS::Publisher_ptr publisher);

  // Connect a consumer.
  virtual void connect (::Components::EventConsumerBase_ptr consumer);

  // Disconnect the consumer.
  virtual ::Components::EventConsumerBase_ptr disconnect (void);

protected:
  /// The consumer connected to this publisher.
  ::Components::OpenSplice::EventConsumer_var consumer_;

  /// The publisher assigned to this object.
  ::DDS::Publisher_var publisher_;

  /// The writer assigned to this publisher.
  ::DDS::DataWriter_var abstract_writer_;

  /// The underlying endpoint for the publisher.
  CUTS_OpenSplice_Endpoint endpoint_;
};

#if defined (__CUTS_INLINE__)
#include "OpenSplice_Publisher.inl"
#endif

#endif
