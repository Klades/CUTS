// ReaderLifespanQosPolicy.cpp 3548 2014-04-08 15:20:43Z dfeiock $

#include "CoreDX_Servant.h"

#if !defined (__CUTS_INLINE__)
#include "CoreDX_Servant.inl"
#endif

#include "cuts/iccm/ddsxml/dds.h"

#include "boost/lambda/lambda.hpp"
#include "boost/lambda/bind.hpp"

#define ICCM_DDS_DEFAULT_TOPIC "@default"

namespace boost
{
namespace detail
{
  template < >
  struct smart_ptr_pointee < ACE_Refcounted_Auto_Ptr < ::iccm::TopicQos, ACE_Null_Mutex > >
  {
    typedef ::iccm::TopicQos type;
  };

  template < >
  struct smart_ptr_pointee < ACE_Refcounted_Auto_Ptr < ::iccm::PublisherQos, ACE_Null_Mutex > >
  {
    typedef ::iccm::PublisherQos type;
  };

  template < >
  struct smart_ptr_pointee < ACE_Refcounted_Auto_Ptr < ::iccm::SubscriberQos, ACE_Null_Mutex > >
  {
    typedef ::iccm::SubscriberQos type;
  };

  template < >
  struct smart_ptr_pointee < ACE_Refcounted_Auto_Ptr < ::iccm::DataReaderQos, ACE_Null_Mutex > >
  {
    typedef ::iccm::DataReaderQos type;
  };

  template < >
  struct smart_ptr_pointee < ACE_Refcounted_Auto_Ptr < ::iccm::DataWriterQos, ACE_Null_Mutex > >
  {
    typedef ::iccm::DataWriterQos type;
  };
}
}

namespace iCCM
{

//
// configure
//
void CoreDX_Servant::configure (const ::iccm::DomainParticipantQos & value)
{
  // The participant has already been created with the
  // default qos, but we need to apply our own.  Therefore,
  // we need to delete it and recreate it with the correct qos.
  CoreDX::domainparticipantfactory_var_type factory =
    CoreDX::get_domainparticipantfactory_instance ();
  factory->delete_participant (this->participant_);

  ::DDS::DomainParticipantQos qos;
  factory->get_default_participant_qos (&qos);

  if (value.entity_factory_p ())
    this->apply (qos.entity_factory, value.entity_factory ());

  this->participant_ =
    factory->create_participant (0,
                                 qos,
                                 0,
                                 CoreDX::STATUS_MASK_NONE);

  // Configure each of the entities in the using information found in
  // the configuration file.
  namespace lambda = boost::lambda;

  std::for_each (value.begin_topic (),
                 value.end_topic (),
                 lambda::bind (&CoreDX_Servant::configure_topic, this, *lambda::_1));

  std::for_each (value.begin_publisher (),
                 value.end_publisher (),
                 lambda::bind (&CoreDX_Servant::configure_publisher, this, *lambda::_1));

  std::for_each (value.begin_subscriber (),
                 value.end_subscriber (),
                 lambda::bind (&CoreDX_Servant::configure_subscriber, this, *lambda::_1));

  std::for_each (value.begin_datareader (),
                 value.end_datareader (),
                 lambda::bind (&CoreDX_Servant::configure_datareader, this, *lambda::_1));

  std::for_each (value.begin_datawriter (),
                 value.end_datawriter (),
                 lambda::bind (&CoreDX_Servant::configure_datawriter, this, *lambda::_1));

  // Finally, configure all the remaining ports/entities.
  this->configure ();
}

//
// configure_topic
//
void CoreDX_Servant::configure_topic (const ::iccm::TopicQos & value)
{
  ::DDS::TopicQos * qos = 0;

  if (0 == this->topic_qos_.find (value.name ().c_str (), qos))
    return;

  ACE_NEW_THROW_EX (qos,
                    ::DDS::TopicQos (),
                    ::CORBA::NO_MEMORY ());

  ACE_Auto_Ptr < ::DDS::TopicQos > auto_clean (qos);

  this->participant_->get_default_topic_qos (qos);
  this->apply (*qos, value);

  if (0 == this->topic_qos_.bind (value.name ().c_str (), qos))
    auto_clean.release ();
}

//
// configure_publisher
//
void CoreDX_Servant::
configure_publisher (const ::iccm::PublisherQos & value)
{
  ::DDS::Publisher * publisher = 0;

  if (0 == this->publishers_.find (value.name ().c_str (), publisher))
    return;

  // Build the qos, starting with the default from the participant
  DDS::PublisherQos qos;
  this->participant_->get_default_publisher_qos (&qos);
  this->apply (qos, value);

  ACE_ERROR ((LM_DEBUG,
              ACE_TEXT ("%T (%t) - %M - configuring publisher <%s>\n"),
              value.name ().c_str ()));

  // Create a new publisher, and save it for later usage.
  publisher =
    this->participant_->create_publisher (qos,
                                          0,
                                          0);

  this->publishers_.bind (value.name ().c_str (), publisher);
}

//
// configure_subscriber
//
void CoreDX_Servant::
configure_subscriber (const ::iccm::SubscriberQos & value)
{
  ::DDS::Subscriber * subscriber = 0;

  if (0 == this->subscribers_.find (value.name ().c_str (), subscriber))
    return;

  // Set the subscriber's QoS properties, starting with the participant's default
  DDS::SubscriberQos qos;
  this->participant_->get_default_subscriber_qos (&qos);
  this->apply (qos, value);

  // Create a new subscriber, and save it for later usage.
  subscriber =
    this->participant_->create_subscriber (qos,
                                           0,
                                           0);

  this->subscribers_.bind (value.name ().c_str (), subscriber);
}

//
// configure_datareader
//
void CoreDX_Servant::
configure_datareader (const ::iccm::DataReaderQos & value)
{
  ::DDS::DataReaderQos * qos = 0;

  if (0 == this->datareader_qos_.find (value.name ().c_str (), qos))
    return;

  // Locate the data reader's subscriber. If we cannnot locate the
  // target publisher, then we are going to fall back to the default
  // publisher and its QoS. Of course, we are going to print a warning
  // message to the user so he/she can correct it! ;-)
  DDS::Subscriber * subscriber = 0;

  if (0 != this->subscribers_.find (value.subscriber ().c_str (), subscriber))
  {
    ACE_ERROR ((LM_WARNING,
                ACE_TEXT ("%T (%t) - %M - failed to locate subscriber <%s> ")
                ACE_TEXT ("in <%s>; using default subscriber\n"),
                value.subscriber ().c_str (),
                this->name_.c_str ()));
    subscriber = this->get_default_subscriber ();
  }

  ACE_NEW_THROW_EX (qos,
                    ::DDS::DataReaderQos (),
                    ::CORBA::NO_MEMORY ());
  ACE_Auto_Ptr < ::DDS::DataReaderQos > auto_clean (qos);

  subscriber->get_default_datareader_qos (qos);
  this->apply (*qos, value);

  if (0 == this->datareader_qos_.bind (value.name ().c_str (), qos))
    auto_clean.release ();
  else
    return;

  // Next, we need to locate the TopicQos object for this data writer.
  // If we cannot find the TopicQos object, we fallback to the default
  // data writer. Of course, we are going to notify the user via an exception.
  ::DDS::TopicQos * temp = 0;
  const ::DDS::TopicQos * topic_qos = 0;
  const std::string & topic = value.topic ();

  if (0 == this->topic_qos_.find (topic.c_str (), temp))
    topic_qos = temp;
  else
  {
    ACE_ERROR ((LM_WARNING,
                ACE_TEXT ("%T (%t) - %M - failed to locate topic qos <%s> ")
                ACE_TEXT ("in <%s>; using default qos\n"),
                value.topic ().c_str (),
                this->name_.c_str ()));
    topic_qos = CoreDX::topic_qos_default ();
  }

  // The way we configure the data reader's QoS parameters is different
  // from the data writer. This is because the a data reader is not
  // created until a connection is made between an input/output port.
  // We therefore need to initialize the data reader's QoS parameters
  // and the consumer will use it when instantiating the data readers.
  this->configure_eventconsumer (value.name ().c_str (),
                                 qos,
                                 topic_qos,
                                 subscriber,
                                 value.isprivate ());
}

//
// get_default_subscriber
//
::DDS::Subscriber * CoreDX_Servant::
get_default_subscriber (void)
{
  ::DDS::Subscriber * subscriber = 0;
  if (0 != this->subscribers_.find (ICCM_DDS_DEFAULT_SUBSCRIBER, subscriber))
  {
    // Create a new subscriber, and save it for later usage.
    subscriber =
      this->participant_->create_subscriber (CoreDX::subscriber_qos_default (),
                                             0,
                                             0);

    this->subscribers_.bind (ICCM_DDS_DEFAULT_SUBSCRIBER, subscriber);
  }

  return subscriber;
}

//
// configure_datawriter
//
void CoreDX_Servant::
configure_datawriter (const ::iccm::DataWriterQos & value)
{
  ::DDS::DataWriterQos * qos = 0;

  if (0 == this->datawriter_qos_.find (value.name ().c_str (), qos))
    return;

  // Locate the data writer's publisher. If we cannnot locate the
  // target publisher, then we are going to fall back to the default
  // publisher and its QoS. Of course, we are going to print a warning
  // message to the user so he/she can correct it! ;-)
  ::DDS::Publisher * publisher = 0;

  if (0 != this->publishers_.find (value.publisher ().c_str (), publisher))
  {
    ACE_ERROR ((LM_WARNING,
                ACE_TEXT ("%T (%t) - %M - failed to locate publisher <%s> ")
                ACE_TEXT ("in <%s>; using default publisher\n"),
                value.publisher ().c_str (),
                this->name_.c_str ()));

    publisher = this->get_default_publisher ();
  }

  ACE_NEW_THROW_EX (qos,
                    ::DDS::DataWriterQos (),
                    ::CORBA::NO_MEMORY ());
  ACE_Auto_Ptr < ::DDS::DataWriterQos > auto_clean (qos);

  publisher->get_default_datawriter_qos (qos);
  this->apply (*qos, value);

  if (0 != this->datawriter_qos_.bind (value.name ().c_str (), qos))
    return;

  // Next, we need to locate the TopicQos object for this data writer.
  // If we cannot find the TopicQos object, we fallback to the default
  // data writer. Of course, we are going to notify the user via an exception.
  ::DDS::TopicQos * temp = 0;
  const ::DDS::TopicQos * topic_qos = 0;
  const std::string & topic = value.topic ();

  if (0 == this->topic_qos_.find (topic.c_str (), temp))
    topic_qos = temp;
  else
  {
    ACE_ERROR ((LM_WARNING,
                ACE_TEXT ("%T (%t) - %M - failed to locate topic qos <%s> ")
                ACE_TEXT ("in <%s>; using default qos\n"),
                value.topic ().c_str (),
                this->name_.c_str ()));
    topic_qos = CoreDX::topic_qos_default ();
  }

  /// If topic_name is specified, use it.  Otherwise use the writer's name.
  std::string topic_name = value.name ();
  if (value.topic_name_p ())
    topic_name = value.topic_name ();

  ACE_ERROR ((LM_DEBUG,
              ACE_TEXT ("%T (%t) - %M - configuring data writer ")
              ACE_TEXT ("<%s> of <%s>\n"),
              value.name ().c_str (),
              this->name_.c_str ()));

  // Create the DDS writer entity.
  ::DDS::DataWriter * writer =
    this->create_datawriter (value.name ().c_str (),
                             *qos,
                             topic_name.c_str (),
                             *topic_qos,
                             publisher,
                             value.isprivate (),
                             value.isinstance ());

  if (CORBA::is_nil (writer))
    ACE_ERROR ((LM_WARNING,
                ACE_TEXT ("%T (%t) - %M - failed to create data writer ")
                ACE_TEXT ("for <%s> port\n"),
                value.name ().c_str ()));
}

//
// get_default_publisher
//
::DDS::Publisher * CoreDX_Servant::
get_default_publisher (void)
{
  ::DDS::Publisher * publisher = 0;
  if (0 != this->publishers_.find (ICCM_DDS_DEFAULT_PUBLISHER, publisher))
  {
    // Create a new publisher, and save it for later usage.
    publisher =
      this->participant_->create_publisher (CoreDX::publisher_qos_default (),
                                            0,
                                            0);

    this->publishers_.bind (ICCM_DDS_DEFAULT_PUBLISHER, publisher);
  }

  return publisher;
}

}
