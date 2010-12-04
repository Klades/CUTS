// $Id$

#include "RTIDDS_EventConsumer.h"

#if !defined (__CUTS_INLINE__)
#include "RTIDDS_EventConsumer.inl"
#endif

//
// configure_i
//
int
CUTS_RTIDDS_CCM_EventConsumer::
open (::DDSDomainParticipant * participant,
      const char * type_name,
      const char * topic_name)
{
  // Open the underlying endpoint for the consumer.
  int retval = this->endpoint_.open (participant,
                                     type_name,
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
    participant->create_subscriber (DDS_SUBSCRIBER_QOS_DEFAULT,
                                    0,
                                    DDS_STATUS_MASK_NONE);

  if (0 == this->subscriber_)
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to create subscriber\n")),
                         -1);

  // Save the participant.
  this->participant_ = participant;

  ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("%T (%t) - %M - creating a datareader for the topic\n")));

  // The last part is to create a data reader.
  this->abstract_reader_ =
    this->subscriber_->create_datareader (this->endpoint_.topic (),
                                          DDS_DATAREADER_QOS_DEFAULT,
                                          this,
                                          DDS_STATUS_MASK_ALL);

  if (0 == this->abstract_reader_)
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - failed to create abstract datareader\n")),
                       -1);

  return 0;
}

//
// close
//
int CUTS_RTIDDS_CCM_EventConsumer::close (void)
{
  DDS_ReturnCode_t retcode;

  if (0 != this->abstract_reader_)
  {
    // Delete the data reader.
    retcode = this->subscriber_->delete_datareader (this->abstract_reader_);

    if (retcode == DDS_RETCODE_OK)
      this->abstract_reader_ = 0;
    else
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to delete data")
                         ACE_TEXT (" reader (retcode=%d)\n")),
                         -1);
  }

  if (0 != this->subscriber_)
  {
    // Delete the subscriber.
    retcode = this->participant_->delete_subscriber (this->subscriber_);

    if (retcode == DDS_RETCODE_OK)
      this->subscriber_ = 0;
    else
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to delete subscriber")
                         ACE_TEXT (" (retcode=%d)\n")),
                         -1);
  }

  if (this->endpoint_.is_open ())
  {
    if (0 != this->endpoint_.close ())
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to close endpoint\n")),
                         -1);
  }

  return 0;
}

//
// topic_description
//
::Components::RTIDDS::TopicDescription *
CUTS_RTIDDS_CCM_EventConsumer::topic_description (void)
{
  // Allocate a new topic description.
  ::Components::RTIDDS::TopicDescription * topic_desc = 0;

  ACE_NEW_THROW_EX (topic_desc,
                    ::Components::RTIDDS::TopicDescription (),
                    ::CORBA::NO_MEMORY ());

  ::Components::RTIDDS::TopicDescription_var auto_clean (topic_desc);

  // Copy information about the topic.
  DDSTopic * dds_topic = this->endpoint_.topic ();
  topic_desc->name = ::CORBA::string_dup (dds_topic->get_name ());
  topic_desc->type_name = ::CORBA::string_dup (dds_topic->get_type_name ());

  // Return the description to the client.
  return auto_clean._retn ();
}
