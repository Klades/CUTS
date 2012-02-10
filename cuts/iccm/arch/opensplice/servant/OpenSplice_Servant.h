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

#ifndef _CUTS_OPENSPLICE_CCM_SERVANT_H_
#define _CUTS_OPENSPLICE_CCM_SERVANT_H_

#include "cuts/iccm/servant/Servant.h"

#include "OpenSplice_EventConsumer.h"
#include "OpenSplice_Publisher.h"
#include "OpenSplice_Publisher_Table.h"

namespace iccm
{
  // Forward decl.
  class DomainParticipantQos;

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
 *
 * Base class for all OpenSplice servant objects. This class enables
 * the container to send commands to the servant, such as configuration
 * information for each of its topics.
 */
class ICCM_OPENSPLICE_SVNT_Export OpenSplice_Servant :
  public Servant
{
public:
  typedef OpenSplice_EventConsumer eventconsumer_type;
  typedef OpenSplice_Publisher publisher_type;
  typedef OpenSplice_Publisher_Table publisher_table_type;

  /// Destructor.
  virtual ~OpenSplice_Servant (void);

  /// Configure the underlying servant.
  virtual void configure (void);

  virtual void configure (const ::iccm::DomainParticipantQos & qos);

  /**
   * Get the domain participant for the servant.
   *
   * @return     The current domain participant
   */
  virtual ::DDS::DomainParticipant_ptr participant (void);

  /// Test if the servant is a publisher.
  bool is_publisher (void) const;

  /**
   * Get the publisher assigned to this partcipant.
   *
   * @return        A :DDS::Publisher_ptr element.
   */
  ::DDS::Publisher_ptr get_publisher (void);

  /// Test is the servant is a subscriber.
  bool is_subscriber (void) const;

  /**
   * Get the subscriber assigned to this partcipant.
   *
   * @return        A :DDS::Subscriber_ptr element.
   */
  ::DDS::Subscriber_ptr get_subscriber (void);

protected:
  /// Default constructor.
  OpenSplice_Servant (const char * name);

  /// Create a data writer object.
  virtual ::DDS::DataWriter_ptr
    create_datawriter (const char * name,
                       const ::DDS::TopicQos & topic_qos,
                       ::DDS::Publisher_ptr publisher) = 0;

  /// Configure the event consumer for future data readers.
  virtual void
    configure_eventconsumer (const char * name,
                             const ::DDS::DataReaderQos & qos,
                             const ::DDS::TopicQos * topic_qos,
                             ::DDS::Subscriber_ptr publisher) = 0;

  /// The domain participant for the servant.
  ::DDS::DomainParticipant_var participant_;

  /// The publisher for the servant.
  ::DDS::Publisher_var publisher_;

  /// Collection of non-default publishers for this servant.
  ACE_Hash_Map_Manager <ACE_CString,
                        ::DDS::Publisher_var,
                        ACE_Null_Mutex> publishers_;

  /// The subscriber for the servant.
  ::DDS::Subscriber_var subscriber_;

  /// Collection of non-default subscribers.
  ACE_Hash_Map_Manager <ACE_CString,
                        ::DDS::Subscriber_var,
                        ACE_Null_Mutex> subscribers_;

  /// Collection to topic QoS entities.
  ACE_Hash_Map_Manager <ACE_CString,
                        ::DDS::TopicQos *,
                        ACE_Null_Mutex> topic_qos_;

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
