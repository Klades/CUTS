// $Id$

#include "cuts/iccm/servant/Cookie.h"

namespace iCCM
{

//
// OpenSplice_Publisher_Table_T
//
template <typename EVENT>
OpenSplice_Publisher_Table_T <EVENT>::OpenSplice_Publisher_Table_T (void)
{

}

//
// ~OpenSplice_Publisher_Table_T
//
template <typename EVENT>
OpenSplice_Publisher_Table_T <EVENT>::~OpenSplice_Publisher_Table_T (void)
{

}

//
// allocate_event
//
template <typename EVENT>
EVENT * OpenSplice_Publisher_Table_T <EVENT>::allocate_event (void)
{
  typedef typename traits_type::downcall_event_type downcall_event_type;

  downcall_event_type * ev = 0;
  ACE_NEW_THROW_EX (ev,
                    downcall_event_type (),
                    ::CORBA::NO_MEMORY ());

  return ev;
}

//
// configure
//
template <typename EVENT>
void OpenSplice_Publisher_Table_T <EVENT>::
configure (::DDS::Publisher_ptr pub, const ACE_CString & topic_name)
{
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

  ACE_CString normalized (topic_name);
  std::replace (normalized.begin (), normalized.end (), '.', '_');

  // Create a topic for the publisher. This will be a combination of the
  // type we just registered and the provided topic name.
  ::DDS::Topic_var topic =
    participant->create_topic (normalized.c_str (),
                               type_name,
                               TOPIC_QOS_DEFAULT,
                               ::DDS::TopicListener::_nil (),
                               ::DDS::ANY_STATUS);

  if (CORBA::is_nil (topic.in ()))
  {
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - failed to create topic %s [type=%s]\n"),
                topic_name.c_str (),
                type_name));

    throw ::CORBA::INTERNAL ();
  }

  // Finally, pass control to the base class. It will finish configuring
  // this provider object.
  OpenSplice_Publisher_Table::configure (pub, topic.in ());

  // Finally, store the concrete writer type.
  this->writer_ = traits_type::writer_type::_narrow (this->abstract_writer_.in ());
}

//
// subscribe
//
template <typename EVENT>
::Components::Cookie *
OpenSplice_Publisher_Table_T <EVENT>::
subscribe (::Components::EventConsumerBase_ptr consumer_base)
{
  ::Components::OpenSplice::EventConsumer_var consumer =
    ::Components::OpenSplice::EventConsumer::_narrow (consumer_base);

  if (::CORBA::is_nil (consumer.in ()))
  {
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - object is not an OpenSplice ")
                ACE_TEXT ("event consumer\n")));

    throw ::CORBA::INTERNAL ();
  }

  // Pass control to the base class.
  ::Components::Cookie_var cookie = this->base_type::subscribe (consumer_base);

  // Notify the event consumer what event they are observing as
  // part of this connection.
  ::DDS::Topic_var topic = this->writer_->get_topic ();
  consumer->add_topic (topic->get_name ());

  return cookie._retn ();
}

//
// unsubscribe
//
template <typename EVENT>
::Components::EventConsumerBase_ptr
OpenSplice_Publisher_Table_T <EVENT>::unsubscribe (::Components::Cookie * c)
{
  // Pass control to the base class.
  ::Components::EventConsumerBase_ptr consumer_base = this->base_type::unsubscribe (c);

  // Notify the event consumer they no longer need to observe
  // events from this publisher.
  ::Components::OpenSplice::EventConsumer_var consumer =
    ::Components::OpenSplice::EventConsumer::_narrow (consumer_base);

  if (!::CORBA::is_nil (consumer.in ()))
  {
    ::DDS::Topic_var topic = this->writer_->get_topic ();
    consumer->remove_topic (topic->get_name ());
  }

  return consumer_base;
}

//
// send_event
//
template <typename EVENT>
void OpenSplice_Publisher_Table_T <EVENT>::send_event (EVENT * ev)
{
  // Convert the CORBA event into a DDS event.
  typedef typename traits_type::downcall_event_type downcall_event_type;
  downcall_event_type * downcall_event = dynamic_cast <downcall_event_type *> (ev);


  if (0 != downcall_event)
  {
    ::DDS::ReturnCode_t status =
      this->writer_->write (downcall_event->dds_event (),
                            ::DDS::HANDLE_NIL);

    if (::DDS::RETCODE_OK != status)
    {
      ::DDS::Topic_var topic = this->writer_->get_topic ();
      ::CORBA::String_var topic_name = topic->get_name ();

      ACE_ERROR ((LM_ERROR,
                  ACE_TEXT ("%T (%t) - %M - failed to publish event on ")
                  ACE_TEXT ("topic <%s>\n"),
                  topic_name.in ()));
    }
  }
}

}
