// $Id$

#include "OpenSplice_EventConsumer.h"

#if !defined (__CUTS_INLINE__)
#include "OpenSplice_EventConsumer.inl"
#endif

//
// open_i
//
int CUTS_OpenSplice_CCM_EventConsumer::
open_i (::DDS::TypeSupport_ptr type_support, const char * topic)
{
  // First, we need to open the endpoint for this consumer.
  ::DDS::DomainParticipant_var participant = this->subscriber_->get_participant ();

  int retval = this->endpoint_.open (participant.in (),
                                     type_support,
                                     topic);

  if (0 != retval)
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - failed to activate endpoint for ")
                       ACE_TEXT ("an event consumer [topic = %s]\n"),
                       topic),
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
    this->subscriber_ = ::DDS::Subscriber::_nil ();

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
