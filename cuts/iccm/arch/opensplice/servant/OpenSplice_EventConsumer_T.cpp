// $Id$

#include "ccpp_dds_dcps.h"

namespace iCCM
{

//
// OpenSplice_EventConsumer_T
//
template <typename SERVANT, typename EVENT>
OpenSplice_EventConsumer_T <SERVANT, EVENT>::
OpenSplice_EventConsumer_T (SERVANT * servant, DESERIALIZE_METHOD callback)
: servant_ (servant),
  callback_ (callback)
{

}

//
// ~OpenSplice_EventConsumer_T
//
template <typename SERVANT, typename EVENT>
OpenSplice_EventConsumer_T <SERVANT, EVENT>::
~OpenSplice_EventConsumer_T (void)
{

}

//
// configure
//
template <typename SERVANT, typename EVENT>
void OpenSplice_EventConsumer_T <SERVANT, EVENT>::
configure (::DDS::Subscriber_ptr subscriber)
{
  // Make sure the type is registered with the participant. This requires
  // us allocating a type support object from the event. Then, we are
  // going to use the type support to get the actual type name. Finally,
  // we are going to register to type with the publisher's participant.
  typename traits_type::dds_typesupport_type_var type_support;

  ACE_NEW_THROW_EX (type_support,
                    typename traits_type::dds_typesupport_type (),
                    ::CORBA::NO_MEMORY ());

  ::DDS::DomainParticipant_var participant = subscriber->get_participant ();
  ::CORBA::String_var type_name = type_support->get_type_name ();

  ::DDS::ReturnCode_t status =
    type_support->register_type (participant.in (), type_name);

  if (::DDS::RETCODE_OK != status)
  {
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - failed to register type %s [retcode=%d]\n"),
                type_name,
                status));

    throw ::CORBA::INTERNAL ();
  }

  // Save the subscriber for when we create the topic, which happens
  // when set_topic () is called.
  this->subscriber_ = ::DDS::Subscriber::_duplicate (subscriber);
}

//
// add_topic
//
template <typename SERVANT, typename EVENT>
void OpenSplice_EventConsumer_T <SERVANT, EVENT>::
add_topic (const char * topic_name)
{
  // Now, we need to create a topic object for this type name. We have
  // already registered the type with the participant. Now, we need to
  // combine the type name with the topic name to create the topic.
  typedef typename traits_type::dds_typesupport_type dds_typesupport_type;
  typename traits_type::dds_typesupport_type_var type_support;

  ACE_NEW_THROW_EX (type_support,
                    dds_typesupport_type (),
                    ::CORBA::NO_MEMORY ());

  ::DDS::DomainParticipant_var participant = this->subscriber_->get_participant ();
  ::CORBA::String_var type_name = type_support->get_type_name ();

  ::DDS::Topic_var topic =
    participant->create_topic (topic_name,
                               type_name.in (),
                               TOPIC_QOS_DEFAULT,
                               ::DDS::TopicListener::_nil (),
                               ::DDS::ANY_STATUS);

  // Create a new data reader object. Right now this work if we only
  // have one connection. If there are multiple connections into this
  // consumer, then we will overwrite the <abstract_reader_> each
  // time. So, we need to fix this!!
  listener_type * listener = 0;

  if (0 == this->listeners_.find (topic_name, listener))
  {
    // Since we know about this type, we only need to increment it
    // reference count. This will prevent us from accidently deleting
    // the object when we remove a topic, but there are still connections
    // associated with the topic.
    listener->_add_ref ();
  }
  else
  {
    // Allocate a new listener since this is the first time we have seen
    // this topic name.
    ACE_NEW_THROW_EX (listener,
                      listener_type (this->servant_, this->callback_),
                      ::CORBA::NO_MEMORY ());

    this->listeners_.bind (topic_name, listener);

    // Use the listener to create a new data reader.
    this->subscriber_->create_datareader (topic.in (),
                                          DATAREADER_QOS_DEFAULT,
                                          listener,
                                          ::DDS::ANY_STATUS);
  }
}

//
// add_topic
//
template <typename SERVANT, typename EVENT>
void OpenSplice_EventConsumer_T <SERVANT, EVENT>::
remove_topic (const char * topic_name)
{

}

}
