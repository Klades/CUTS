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
  int retval = CUTS_OpenSplice_Endpoint::open (participant,
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
       "%T (%t) - %M - failed to create subscriber\n"),
      -1);

  ACE_DEBUG ((LM_DEBUG,
        "%T (%t) - %M - creating a datareader for the topic\n"));

  // The last part is to create a data reader.
  this->abstract_reader_ =
      this->subscriber_->create_datareader (this->dds_topic_.in (),
                                            DATAREADER_QOS_DEFAULT,
                                            this,
                                            ::DDS::ANY_STATUS);

  if (::CORBA::is_nil (this->abstract_reader_.in ()))
    ACE_ERROR_RETURN ((LM_ERROR,
           "%T (%t) - %M - failed to create abstract datareader\n"),
          -1);

  return 0;
}

//
// close
//
int CUTS_OpenSplice_CCM_EventConsumer::close (void)
{
  if (!::CORBA::is_nil (this->subscriber_.in ()))
    {
      if (!::CORBA::is_nil (this->abstract_reader_.in ()))
  {
    // Delete the data reader.
    this->subscriber_->delete_datareader (this->abstract_reader_.in ());
    this->abstract_reader_ = ::DDS::DataReader::_nil ();
  }

      // Then, delete the subscription.
      this->participant_->delete_subscriber (this->subscriber_.in ());
      this->subscriber_ = ::DDS::Subscriber::_nil ();
    }

  // Finally, close the endpoint.
  return CUTS_OpenSplice_Endpoint::close ();
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
  topic_desc->name = this->dds_topic_->get_name ();
  topic_desc->type_name = this->dds_topic_->get_type_name ();

  // Return the description to the client.
  return auto_clean._retn ();
}
