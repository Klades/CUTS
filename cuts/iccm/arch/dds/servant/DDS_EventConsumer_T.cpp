// $Id$

#if !defined (__CUTS_INLINE__)
#include "DDS_EventConsumer_T.inl"
#endif

namespace iCCM
{

//
// configure
//
template <typename T, typename SERVANT, typename EVENT>
void DDS_EventConsumer_T <T, SERVANT, EVENT>::
configure (subscriber_ptr_type subscriber,
           const topicqos_type & topic_qos,
           const datareaderqos_type & qos)
{
  // Make sure the type is registered with the participant. This requires
  // us allocating a type support object from the event. Then, we are
  // going to use the type support to get the actual type name. Finally,
  // we are going to register to type with the publisher's participant.
  typename event_traits_type::dds_typesupport_var_type type_support;

  ACE_NEW_THROW_EX (type_support,
                    typename event_traits_type::dds_typesupport_type (),
                    ::CORBA::NO_MEMORY ());

  typedef typename T::domainparticipant_var_type domainparticipant_var_type;
  typedef typename T::returncode_type returncode_type;

  const char * type_name = type_support->get_type_name ();
  domainparticipant_var_type participant = subscriber->get_participant ();
  returncode_type status = type_support->register_type (participant, type_name);

  if (0 != status)
  {
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - failed to register type %s [retcode=%d]\n"),
                type_name,
                status));

    throw ::CORBA::INTERNAL ();
  }

  // Save the subscriber for when we create the topic, which happens
  // when set_topic () is called.
  this->subscriber_ = T::_duplicate (subscriber);

  this->reader_qos_ = &qos;
  this->topic_qos_ = &topic_qos;
}

//
// add_topic
//
template <typename T, typename SERVANT, typename EVENT>
void DDS_EventConsumer_T <T, SERVANT, EVENT>::add_topic (const char * topic_name)
{
  // Now, we need to create a topic object for this type name. We have
  // already registered the type with the participant. Now, we need to
  // combine the type name with the topic name to create the topic.
  typedef typename event_traits_type::dds_typesupport_type dds_typesupport_type;
  typename event_traits_type::dds_typesupport_var_type type_support;

  ACE_NEW_THROW_EX (type_support,
                    dds_typesupport_type (),
                    ::CORBA::NO_MEMORY ());

  typedef typename T::domainparticipant_var_type domainparticipant_var_type;
  typedef typename T::returncode_type returncode_type;
  typedef typename T::topic_var_type topic_var_type;

  domainparticipant_var_type participant = this->subscriber_->get_participant ();
  const char * type_name = type_support->get_type_name ();

  topic_var_type topic =
    participant->create_topic (topic_name,
                               type_name,
                               *this->topic_qos_,
                               0, /*::DDS::TopicListener::_nil ()*/
                               T::ANY_STATUS);

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
    this->subscriber_->create_datareader (topic,
                                          *this->reader_qos_,
                                          listener,
                                          T::ANY_STATUS);
  }
}

//
// add_topic
//
template <typename T, typename SERVANT, typename EVENT>
void DDS_EventConsumer_T <T, SERVANT, EVENT>::
remove_topic (const char * topic_name)
{

}

}
