// $Id$

#if !defined (__CUTS_INLINE__)
#include "OpenSplice_Publisher_T.inl"
#endif

namespace iCCM
{

//
// configure
//
template <typename EVENT>
void OpenSplice_Publisher_T <EVENT>::
configure (::DDS::Publisher_ptr pub, const ACE_CString & topic_name)
{
  ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("configuring publisher %s\n"),
              topic_name.c_str ()));

  // Make sure the type is registered with the participant. This requires
  // us allocating a type support object from the event. Then, we are
  // going to use the type support to get the actual type name. Finally,
  // we are going to register to type with the publisher's participant.
  typename traits_type::dds_typesupport_type_var type_support;

  ACE_NEW_THROW_EX (type_support,
                    typename traits_type::dds_typesupport_type (),
                    ::CORBA::NO_MEMORY ());

  ::DDS::DomainParticipant_var participant = pub->get_participant ();
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

  // Create a topic for the publisher. This will be a combination of the
  // type we just registered and the provided topic name.
  ::DDS::Topic_var topic =
    participant->create_topic (topic_name.c_str (),
                               type_name,
                               TOPIC_QOS_DEFAULT,
                               ::DDS::TopicListener::_nil (),
                               ::DDS::ANY_STATUS);

  // Finally, pass control to the base class. It will finish configuring
  // this provider object.
  OpenSplice_Publisher::configure (pub, topic.in ());

  // Finally, store the concrete writer type.
  this->writer_ = traits_type::writer_type::_narrow (this->abstract_writer_.in ());
}

//
// allocate_event
//
template <typename EVENT>
EVENT * OpenSplice_Publisher_T <EVENT>::allocate_event (void)
{
  typedef typename traits_type::downcall_event_type downcall_event_type;

  downcall_event_type * ev = 0;
  ACE_NEW_THROW_EX (ev,
                    downcall_event_type (),
                    ::CORBA::NO_MEMORY ());

  return ev;
}

//
// connect
//
template <typename EVENT>
void OpenSplice_Publisher_T <EVENT>::
connect (::Components::EventConsumerBase_ptr p)
{
  // Narrow this to an OpenSplice event consumer. We are then going to
  // tell the consumer what topic to listen.
  ::Components::OpenSplice::EventConsumer_var consumer =
      ::Components::OpenSplice::EventConsumer::_narrow (p);

  if (::CORBA::is_nil (consumer.in ()))
  {
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - object is not an OpenSplice ")
                ACE_TEXT ("event consumer\n")));

    throw ::CORBA::INTERNAL ();
  }

  ::DDS::Topic_var topic = this->writer_->get_topic ();
  consumer->add_topic (topic->get_name ());
}

//
// send_event
//
template <typename EVENT>
void OpenSplice_Publisher_T <EVENT>::send_event (EVENT * ev)
{
  // Convert the CORBA event into a DDS event.
  typedef typename traits_type::downcall_event_type downcall_event_type;
  downcall_event_type * downcall = dynamic_cast <downcall_event_type *> (ev);

  if (0 != ev)
    this->send_event (downcall->dds_event ());
}

//                                                                                                                                                                                 // send_event
// send_event
//
template <typename EVENT>
void OpenSplice_Publisher_T <EVENT>::
send_event (typename traits_type::dds_event_type & ev)
{
  ::DDS::ReturnCode_t status = this->writer_->write (ev, ::DDS::HANDLE_NIL);
  ACE_UNUSED_ARG (status);
}

}
