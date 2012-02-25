// $Id$

#include "cuts/iccm/servant/Cookie.h"

#if !defined (__CUTS_INLINE__)
#include "DDS_Publisher_Table_T.inl"
#endif

#include "ace/OS_NS_unistd.h"

namespace iCCM
{

//
// allocate_event
//
template <typename T, typename EVENT>
EVENT * DDS_Publisher_Table_T <T, EVENT>::allocate_event (void)
{
  typedef typename event_traits_type::downcall_event_type downcall_event_type;

  downcall_event_type * ev = 0;
  ACE_NEW_THROW_EX (ev,
                    downcall_event_type (),
                    ::CORBA::NO_MEMORY ());

  return ev;
}

//
// configure
//
template <typename T, typename EVENT>
void DDS_Publisher_Table_T <T, EVENT>::
configure (publisher_ptr_type publisher,
           const topicqos_type & topic_qos,
           const char * topic_name)
{
  // Make sure the type is registered with the participant. This requires
  // us allocating a type support object from the event. Then, we are
  // going to use the type support to get the actual type name. Finally,
  // we are going to register to type with the publisher's participant.
  typedef typename T::domainparticipant_var_type domainparticipant_var_type;
  typedef typename T::returncode_type returncode_type;
  typedef typename event_traits_type::dds_typesupport_type dds_typesupport_type;
  typedef typename T::topic_var_type topic_var_type;

  ACE_CString type_name;
  domainparticipant_var_type participant = publisher->get_participant ();
  returncode_type status = T::register_type <dds_typesupport_type> (participant, type_name);

  if (status != 0)
  {
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - failed to register type [retcode=%d]\n"),
                status));

    throw ::CORBA::INTERNAL ();
  }

  ACE_CString normalized (topic_name);
  std::replace (normalized.begin (), normalized.end (), '.', '_');

  // Create a topic for the publisher. This will be a combination of the
  // type we just registered and the provided topic name.
  topic_var_type topic =
    participant->create_topic (normalized.c_str (),
                               type_name.c_str (),
                               topic_qos,
                               0, /* ::DDS::TopicListener::_nil () */
                               T::ANY_STATUS);

  if (T::_is_nil (topic))
  {
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - failed to create topic %s [type=%s]\n"),
                topic_name,
                type_name));

    throw ::CORBA::INTERNAL ();
  }

  // Finally, pass control to the base class. It will finish configuring
  // this provider object.
  DDS_Publisher_Table::configure (publisher, topic);

  // Finally, store the concrete writer type.
  typedef typename event_traits_type::writer_type writer_type;
  this->writer_ = T::_writer_cast < writer_type > (this->abs_writer_);
}

//
// subscribe
//
template <typename T, typename EVENT>
::Components::Cookie *
DDS_Publisher_Table_T <T, EVENT>::
subscribe (::Components::EventConsumerBase_ptr consumer_base)
{
  ::Components::DDS::EventConsumer_var consumer =
    ::Components::DDS::EventConsumer::_narrow (consumer_base);

  if (T::_is_nil (consumer))
  {
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - not a DDS event consumer [type=%s]\n"),
                consumer_base->_interface_repository_id ()));

    throw ::CORBA::INTERNAL ();
  }

  // Pass control to the base class.
  ::Components::Cookie_var cookie = this->base_type::subscribe (consumer_base);

  // Notify the event consumer what event they are observing as
  // part of this connection.
  typedef typename T::topic_var_type topic_var_type;
  topic_var_type topic = this->writer_->get_topic ();
  consumer->add_topic (topic->get_name ());

  return cookie._retn ();
}

//
// unsubscribe
//
template <typename T, typename EVENT>
::Components::EventConsumerBase_ptr
DDS_Publisher_Table_T <T, EVENT>::unsubscribe (::Components::Cookie * c)
{
  // Pass control to the base class.
  ::Components::EventConsumerBase_ptr consumer_base = this->base_type::unsubscribe (c);

  // Notify the event consumer they no longer need to observe
  // events from this publisher.
  ::Components::DDS::EventConsumer_var consumer =
    ::Components::DDS::EventConsumer::_narrow (consumer_base);

  if (!::CORBA::is_nil (consumer.in ()))
  {
    typedef typename T::topic_var_type topic_var_type;

    topic_var_type topic = this->writer_->get_topic ();
    consumer->remove_topic (topic->get_name ());
  }

  return consumer_base;
}

//
// send_event
//
template <typename T, typename EVENT>
void DDS_Publisher_Table_T <T, EVENT>::send_event (EVENT * ev)
{
  // Convert the CORBA event into a DDS event.
  typedef typename event_traits_type::downcall_event_type downcall_event_type;
  downcall_event_type * downcall = dynamic_cast <downcall_event_type *> (ev);

  if (0 != ev)
  {
    typedef typename T::returncode_type returncode_type;

    returncode_type retcode =
      this->writer_->write (downcall->dds_event (), this->inst_);

    if (0 != T::RETCODE_OK)
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
