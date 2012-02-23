// -*- C++ -*-

//=============================================================================
/**
 *  @file         OpenSplice_Servant.h
 *
 *  $Id$
 *
 *  @author       James H. Hill
 */
//=============================================================================

#ifndef _ICCM_OPENSPLICE_SERVANT_H_
#define _ICCM_OPENSPLICE_SERVANT_H_

#include "cuts/iccm/arch/dds/servant/DDS_Servant.h"
#include "OpenSplice.h"

namespace iccm
{
  // Forward decl.
  class TopicQos;

  // Forward decl.
  class PublisherQos;

  // Forward decl.
  class SubscriberQos;

  // Forward decl.
  class DataReaderQos;

  // Forward decl.
  class DataWriterQos;
}

namespace iCCM
{

/**
 * @class OpenSplice_Servant
 */
class ICCM_OPENSPLICE_SVNT_Export OpenSplice_Servant :
  public DDS_Servant <OpenSplice>
{
public:
  /**
   * Initializing constructor.
   *
   * @param[in]       name        Name of the servant
   */
  OpenSplice_Servant (const char * name);

  /// Destructor.
  virtual ~OpenSplice_Servant (void);

  /// Default configuration.
  virtual void configure (void);

  /// Initialize Qos configuration.
  virtual void configure (const ::iccm::DomainParticipantQos & qos);

private:
  void configure_topic (const ::iccm::TopicQos & value);
  void configure_publisher (const ::iccm::PublisherQos & value);
  void configure_subscriber (const ::iccm::SubscriberQos & value);
  void configure_datareader (const ::iccm::DataReaderQos & value);
  void configure_datawriter (const ::iccm::DataWriterQos & value);
};

}

#if defined (__CUTS_INLINE__)
#include "OpenSplice_Servant.inl"
#endif

#endif  // !defined _CUTS_OPENSPLICE_CCM_SERVANT_H_
