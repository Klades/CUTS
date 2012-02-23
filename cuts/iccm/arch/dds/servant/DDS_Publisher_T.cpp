// $Id$

#if !defined (__CUTS_INLINE__)
#include "DDS_Publisher_T.inl"
#endif

namespace iCCM
{

//
// configure
//
template <typename T, typename EVENT>
void DDS_Publisher_T <T, EVENT>::
configure (publisher_ptr_type publisher,
           const topicqos_type & topic_qos,
           const char * topic_name)
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
  typedef typename T::topic_var_type topic_var_type;

  domainparticipant_var_type participant = publisher->get_participant ();
  const char * type_name = type_support->get_type_name ();
  returncode_type status = type_support->register_type (participant, type_name);

  if (status != 0)
  {
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - failed to register type %s [retcode=%d]\n"),
                type_name,
                status));

    throw ::CORBA::INTERNAL ();
  }

  ACE_CString normalized (topic_name);
  std::replace (normalized.begin (), normalized.end (), '.', '_');

  // Create a topic for the publisher. This will be a combination of the
  // type we just registered and the provided topic name.
  topic_var_type topic =
    participant->create_topic (normalized.c_str (),
                               type_name,
                               topic_qos,
                               0, /* ::DDS::TopicListener::_nil () */
                               T::ANY_STATUS);

  // Finally, pass control to the base class. It will finish configuring
  // this provider object.
  DDS_Publisher::configure (publisher, topic);

  // Finally, store the concrete writer type.
  typedef typename event_traits_type::writer_type writer_type;
  this->writer_ = T::_writer_cast < writer_type > (this->abs_writer_);
}

//
// allocate_event
//
template <typename T, typename EVENT>
EVENT * DDS_Publisher_T <T, EVENT>::allocate_event (void)
{
  typedef typename event_traits_type::downcall_event_type downcall_event_type;

  downcall_event_type * ev = 0;
  ACE_NEW_THROW_EX (ev,
                    downcall_event_type (),
                    ::CORBA::NO_MEMORY ());

  return ev;
}

//
// connect
//
template <typename T, typename EVENT>
void DDS_Publisher_T <T, EVENT>::connect (::Components::EventConsumerBase_ptr p)
{
  // Narrow this to an DDS event consumer. We are then going to
  // tell the consumer what topic to listen.
  ::Components::DDS::EventConsumer_var consumer =
      ::Components::DDS::EventConsumer::_narrow (p);

  if (::CORBA::is_nil (consumer.in ()))
  {
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - object is not an DDS ")
                ACE_TEXT ("event consumer\n")));

    throw ::CORBA::INTERNAL ();
  }

  // Add a topic to the consumer.
  typedef typename T::topic_var_type topic_var_type;

  topic_var_type topic = this->writer_->get_topic ();
  consumer->add_topic (topic->get_name ());
}

//
// send_event
//
template <typename T, typename EVENT>
void DDS_Publisher_T <T, EVENT>::send_event (EVENT * ev)
{
  // Convert the CORBA event into a DDS event.
  typedef typename event_traits_type::downcall_event_type downcall_event_type;
  downcall_event_type * downcall = dynamic_cast <downcall_event_type *> (ev);

  if (0 != ev)
  {
    typedef typename T::returncode_type returncode_type;
    returncode_type retcode =
      this->writer_->write (downcall->dds_event (),
                            this->inst_);

    if (0 != retcode)
      ACE_ERROR ((LM_ERROR,
                  ACE_TEXT ("%T (%t) - %M - failed to write event [retcode=%d]\n"),
                  retcode));
  }
  else
  {
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - invalid event type\n")));
  }
}

}
