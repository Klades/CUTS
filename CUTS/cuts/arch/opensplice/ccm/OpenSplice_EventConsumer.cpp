// $Id$

#include "OpenSplice_EventConsumer.h"

#if !defined (__CUTS_INLINE__)
#include "OpenSplice_EventConsumer.inl"
#endif

//
// configure_i
//
int
CUTS_OpenSplice_CCM_EventConsumer::
open (::DDS::DomainParticipant_ptr participant,
      ::DDS::TypeSupport_ptr type_support,
      const char * topic_name)
{
  // Open the underlying endpoint for the consumer.
  this->participant_ = ::DDS::DomainParticipant::_duplicate (participant);
  int retval = this->endpoint_.open (this->participant_.in (),
                                     type_support,
                                     topic_name);

  if (0 != retval)
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - failed to activate endpoint for ")
                       ACE_TEXT ("an event consumer [topic = %s]\n"),
                       topic_name),
                       -1);

  // Now, subscribe to the topic so components can send
  // events to this event consumer.
  this->subscriber_ =
    participant->create_subscriber (SUBSCRIBER_QOS_DEFAULT,
                                    ::DDS::SubscriberListener::_nil (),
                                    ::DDS::ANY_STATUS);

  if (::CORBA::is_nil (this->subscriber_.in ()))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to create subscriber\n")),
                         -1);

  ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("%T (%t) - %M - creating a datareader for the topic\n")));

  // The last part is to create a data reader.
  ::DDS::Topic_var dds_topic = this->endpoint_.topic ();

  this->abstract_reader_ =
      this->subscriber_->create_datareader (dds_topic.in (),
                                            DATAREADER_QOS_DEFAULT,
                                            this,
                                            ::DDS::ANY_STATUS);

  if (::CORBA::is_nil (this->abstract_reader_.in ()))
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - failed to create abstract datareader\n")),
                       -1);

  return 0;
}

//
// close
//
int CUTS_OpenSplice_CCM_EventConsumer::close (void)
{
  ::DDS::ReturnCode_t retcode;

  if (!::CORBA::is_nil (this->abstract_reader_.in ()))
  {
    // Delete the data reader.
    retcode = this->subscriber_->delete_datareader (this->abstract_reader_.in ());

    if (retcode == ::DDS::RETCODE_OK)
      this->abstract_reader_ = ::DDS::DataReader::_nil ();
    else
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to delete data reader (retcode=%d)\n"),
                         retcode),
                         -1);
  }

  if (!::CORBA::is_nil (this->subscriber_.in ()))
  {
    // Delete the subscriber.
    retcode = this->participant_->delete_subscriber (this->subscriber_.in ());

    if (retcode == ::DDS::RETCODE_OK)
      this->subscriber_ = ::DDS::Subscriber::_nil ();
    else
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to delete subscriber (retcode=%d)\n"),
                         retcode),
                         -1);
  }

  // Finally, close the endpoint.
  if (this->endpoint_.is_open ())
  {
    if (0 != this->endpoint_.close ())
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to close consumer endpoint\n")),
                         -1);
  }

  return 0;
}

//
// topic_description
//
::Components::OpenSplice::TopicDescription *
CUTS_OpenSplice_CCM_EventConsumer::topic_description (void)
{
  // Allocate a new topic description.
  ::Components::OpenSplice::TopicDescription * topic_desc = 0;

  ACE_NEW_THROW_EX (topic_desc,
                    ::Components::OpenSplice::TopicDescription (),
                    ::CORBA::NO_MEMORY ());

  ::Components::OpenSplice::TopicDescription_var auto_clean (topic_desc);

  // Copy information about the topic.
  ::DDS::Topic_var dds_topic = this->endpoint_.topic ();
  topic_desc->name = ::CORBA::string_dup (dds_topic->get_name ());
  topic_desc->type_name = ::CORBA::string_dup (dds_topic->get_type_name ());

  // Return the description to the client.
  return auto_clean._retn ();
}
