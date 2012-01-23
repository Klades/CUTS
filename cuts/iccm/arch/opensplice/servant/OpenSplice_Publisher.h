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

#ifndef _CUTS_ICCM_OPENSPLICE_PUBLISHER_H_
#define _CUTS_ICCM_OPENSPLICE_PUBLISHER_H_

#include "cuts/iccm/servant/Publisher.h"

#include "OpenSplice_EventsC.h"
#include "OpenSplice_svnt_export.h"

#include "ccpp_dds_dcps.h"

namespace iCCM
{

/**
 * @class OpenSplice_Publisher
 *
 * The base class for all OpenSplice publishers that are integrated into
 * the CCM architecture. In essence, this class is an adapter class that
 * allows a DDS publisher to integrate with the CCM architecture.
 */
class ICCM_OPENSPLICE_SVNT_Export OpenSplice_Publisher :
  public Publisher
{
public:
  /// Default constructor.
  OpenSplice_Publisher (void);

  /// Destructor.
  virtual ~OpenSplice_Publisher (void);

  /**
   * Configure the publish with the DDS publisher object. This object
   * will be used to send events to readers.
   *
   * @param[in]         publisher         Target DDS publisher
   * @param[in]         topic             Topic for writer
   */
  virtual void configure (::DDS::Publisher_ptr, const ACE_CString &) = 0;

  // Connect a consumer.
  virtual void connect (::Components::EventConsumerBase_ptr consumer);

  // Disconnect the consumer.
  virtual ::Components::EventConsumerBase_ptr disconnect (void);

protected:
  /**
   * Configure the publish with the DDS publisher object. This object
   * will be used to send events to readers.
   *
   * @param[in]         publisher         Target DDS publisher
   * @param[in]         topic             Topic for writer
   */
  void configure (::DDS::Publisher_ptr publisher, ::DDS::Topic_ptr topic);

  /// The consumer connected to this publisher.
  ::Components::OpenSplice::EventConsumer_var consumer_;

  /// The writer assigned to this publisher.
  ::DDS::DataWriter_var abstract_writer_;
};

}

#if defined (__CUTS_INLINE__)
#include "OpenSplice_Publisher.inl"
#endif

#endif  // !defined _CUTS_OPENSPLICE_CCM_PUBLISHER_H_
