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
           const topicqos_type * topic_qos,
           const datareaderqos_type * qos)
{
  // Make sure the type is registered with the participant. This requires
  // us allocating a type support object from the event. Then, we are
  // going to use the type support to get the actual type name. Finally,
  // we are going to register to type with the publisher's participant.
  typedef typename T::domainparticipant_var_type domainparticipant_var_type;
  typedef typename T::returncode_type returncode_type;
  typedef typename event_traits_type::dds_typesupport_type dds_typesupport_type;

  domainparticipant_var_type participant = subscriber->get_participant ();
  returncode_type status = T::template register_type <dds_typesupport_type> (participant, this->type_name_);

  if (0 != status)
  {
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - failed to register type [retcode=%d]\n"),
                status));

    throw ::CORBA::INTERNAL ();
  }

  // Save the subscriber for when we create the topic, which happens
  // when set_topic () is called.
  this->subscriber_ = T::_duplicate (subscriber);

  this->reader_qos_ = qos;
  this->topic_qos_ = topic_qos;
}

//
// configure
//
template <typename T, typename SERVANT, typename EVENT>
void DDS_EventConsumer_T <T, SERVANT, EVENT>::
configure (subscriber_ptr_type subscriber,
           const topicqos_type * topic_qos,
           const datareaderqos_type * qos,
           const char * topic_name)
{
  // Configure the event consumer, then manually add the topic.
  ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("%T (%t) - %M - configuring event consumer to listen ")
              ACE_TEXT ("to global topic <%s>\n"),
              topic_name));

  this->configure (subscriber, topic_qos, qos);
  this->add_topic (topic_name);
}

//
// add_topic
//
template <typename T, typename SERVANT, typename EVENT>
void DDS_EventConsumer_T <T, SERVANT, EVENT>::add_topic (const char * topic_name)
{
  typedef typename T::domainparticipant_var_type domainparticipant_var_type;
  typedef typename T::topic_var_type topic_var_type;

  // First, try to locate the topic. If we cannot find it, then we need
  // to create a new one for this participant.
  listener_type * listener = 0;

  if (0 == this->listeners_.find (topic_name, listener))
  {
    ACE_DEBUG ((LM_DEBUG,
                ACE_TEXT ("%T (%t) - %M - incrementing refcount for ")
                ACE_TEXT ("topic listener <%s>\n"),
                topic_name));

    // Since we know about this type, we only need to increment it
    // reference count. This will prevent us from accidently deleting
    // the object when we remove a topic, but there are still connections
    // associated with the topic.
    T::_add_ref (listener);
    return;
  }

  // Create a new data reader object. Right now this work if we only
  // have one connection. If there are multiple connections into this
  // consumer, then we will overwrite the <abstract_reader_> each
  // time. So, we need to fix this!!
  ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("%T (%t) - %M - creating new listener for ")
              ACE_TEXT ("topic <%s>\n"),
              topic_name));

  // Allocate a new listener since this is the first time we have seen
  // this topic name.
  ACE_NEW_THROW_EX (listener,
                    listener_type (this->servant_, this->callback_),
                    ::CORBA::NO_MEMORY ());

  this->listeners_.bind (topic_name, listener);

  // If the component isn't activated, we might not have the right
  // qos for the topic or data reader yet.  Rather than creating
  // the topic and data reader now, let's delay the creation
  // until the component is activated.
  if (!this->is_active_)
    return;

  domainparticipant_var_type participant = this->subscriber_->get_participant ();

  topic_var_type topic = this->create_topic (topic_name, participant);

  if (T::_is_nil (topic))
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - Failed to create topic\n")));

  // Use the listener to create a new data reader. We should use
  // the listener to create the data reader. In other words, put a
  // configuration method on the listener object.
  typename T::datareader_var_type reader =
    this->create_datareader (topic, listener);

  if (!T::_is_nil (reader))
    listener->configure (reader);
  else
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - failed to configure listener ")
                ACE_TEXT ("for topic <%s>\n"),
                topic_name));
}

//
// create_topic
//
template <typename T, typename SERVANT, typename EVENT>
typename T::topic_var_type
DDS_EventConsumer_T <T, SERVANT, EVENT>::
create_topic (const char * topic_name,
              domainparticipant_var_type & participant)
{
  #ifdef ICCM_DDS_LACKS_TOPIC_QOS
  return participant->create_topic (topic_name,
                                    this->type_name_.c_str (),
                                    *T::topic_qos_default (),
                                    0,
                                    T::STATUS_MASK_NONE);
  #else
  if (!this->topic_qos_)
    return participant->create_topic (topic_name,
                                      this->type_name_.c_str (),
                                      *T::topic_qos_default (),
                                      0,
                                      T::STATUS_MASK_NONE);
  else
    return participant->create_topic (topic_name,
                                      this->type_name_.c_str (),
                                      *this->topic_qos_,
                                      0,
                                      T::STATUS_MASK_NONE);
  #endif
}

//
// create_datareader
//
template <typename T, typename SERVANT, typename EVENT>
typename T::datareader_var_type
DDS_EventConsumer_T <T, SERVANT, EVENT>::
create_datareader (typename T::topic_var_type topic,
                   listener_type * listener)
{
  #ifdef ICCM_DDS_LACKS_READER_QOS
    return this->subscriber_->create_datareader (topic,
                                                 *T::datareader_qos_default (),
                                                 listener,
                                                 T::STATUS_MASK_DATA_AVAILABLE);
  #else
  if (!this->reader_qos_)
    return this->subscriber_->create_datareader (topic,
                                                 *T::datareader_qos_default (),
                                                 listener,
                                                 T::STATUS_MASK_DATA_AVAILABLE);
  else
    return this->subscriber_->create_datareader (topic,
                                                 *this->reader_qos_,
                                                 listener,
                                                 T::STATUS_MASK_DATA_AVAILABLE);
  #endif
}

//
// remove_topic
//
template <typename T, typename SERVANT, typename EVENT>
void DDS_EventConsumer_T <T, SERVANT, EVENT>::
remove_topic (const char * topic_name)
{
  typename T::datareader_var_type reader =
    this->subscriber_->lookup_datareader (topic_name);

  if (!T::_is_nil (reader))
    this->subscriber_->delete_datareader (reader);
}

//
// activate
//
template <typename T, typename SERVANT, typename EVENT>
void DDS_EventConsumer_T <T, SERVANT, EVENT>::activate (void)
{
  typedef typename T::domainparticipant_var_type domainparticipant_var_type;
  typedef typename T::topic_var_type topic_var_type;

  typename listeners_map_type::ITERATOR iter (this->listeners_);

  domainparticipant_var_type participant = this->subscriber_->get_participant ();

  // Create a listener/datawriter for each topic
  for (; !iter.done (); ++ iter)
  {
    const char * topic_name = iter->key ().c_str ();
    listener_type * listener = iter->item ();

    // If the reader exists, dont recreate it
    typename T::datareader_var_type reader =
      this->subscriber_->lookup_datareader (topic_name);

    if (!T::_is_nil (reader))
      continue;

    ACE_ERROR ((LM_DEBUG,
                ACE_TEXT ("%T (%t) - %M - Creating datareader for topic <%s>\n"),
                topic_name));

    topic_var_type topic = this->create_topic (topic_name, participant);

    if (T::_is_nil (topic))
      ACE_ERROR ((LM_ERROR,
                  ACE_TEXT ("%T (%t) - %M - Failed to create topic\n")));

    // Create the datareader
    reader = this->create_datareader (topic, listener);

    if (!T::_is_nil (reader))
      listener->configure (reader);
    else
      ACE_ERROR ((LM_ERROR,
                  ACE_TEXT ("%T (%t) - %M - failed to configure listener ")
                  ACE_TEXT ("for topic <%s>\n"),
                  topic_name));
  }

  this->is_active_ = true;
}

//
// passivate
//
template <typename T, typename SERVANT, typename EVENT>
void DDS_EventConsumer_T <T, SERVANT, EVENT>::passivate (void)
{
  base_type::passivate ();

  typename listeners_map_type::ITERATOR iter (this->listeners_);

  // We must delete all the data readers
  for (; !iter.done (); ++ iter)
  {
    typename T::datareader_var_type reader =
      this->subscriber_->lookup_datareader (iter->key ().c_str ());

    if (!T::_is_nil (reader))
      this->subscriber_->delete_datareader (reader);
  }

  this->is_active_ = false;
}

}
