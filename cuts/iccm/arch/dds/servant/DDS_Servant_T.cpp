// $Id$

#if !defined (__CUTS_INLINE__)
#include "DDS_Servant_T.inl"
#endif

namespace iCCM
{

//
// configure
//
template <typename TRAIT, typename T, typename CONTEXT, typename EXECUTOR, typename POA_EXEC>
void DDS_Servant_T <TRAIT, T, CONTEXT, EXECUTOR, POA_EXEC>::
configure (const ::iccm::DomainParticipantQos & qos)
{
  this->do_default_configure ();
}

//
// configure
//
template <typename TRAIT, typename T, typename CONTEXT, typename EXECUTOR, typename POA_EXEC>
void DDS_Servant_T <TRAIT, T, CONTEXT, EXECUTOR, POA_EXEC>::configure (void)
{
  // Perform the default configuration.
  this->do_default_configure ();

  // Configure each consumer port in this servant using the subscriber
  // interface for this servant, and its port information.
  typename consumer_map_type::ITERATOR consumer_iter (this->consumers_);

  for (; !consumer_iter.done (); ++ consumer_iter)
  {
    typename consumer_map_type::VALUE consumer = consumer_iter->item ();

    if (!consumer->is_configured ())
    {
      // Configure the consumer with the default configuration. This
      // includes using the default DDS::Subscriber entity and the
      // default TOPIC_QOS_DEFAULT.
      ACE_ERROR ((LM_DEBUG,
                  ACE_TEXT ("%T (%t) - %M - using default configuration ")
                  ACE_TEXT ("for data reader <%s> in <%s>\n"),
                  consumer_iter->key ().c_str (),
                  this->name_.c_str ()));

      consumer->configure (this->subscriber_,
                           TRAIT::topic_qos_default (),
                           TRAIT::datareader_qos_default ());
    }
  }

  typename emits_map_type::ITERATOR emits_iter (this->emits_);

  for (; !emits_iter.done (); ++ emits_iter)
  {
    typename emits_map_type::VALUE emits = emits_iter->item ();

    ACE_CString topic_name (this->name_);
    topic_name += ".";
    topic_name += emits_iter->key ();

    if (!emits->is_configured ())
    {
      // Configure the publisher with the default configuration. This
      // includes using the default DDS::Publisher entity and the
      // default TOPIC_QOS_DEFAULT.
      ACE_ERROR ((LM_DEBUG,
                  ACE_TEXT ("%T (%t) - %M - using default configuration ")
                  ACE_TEXT ("for <%s>\n"),
                  emits_iter->key ().c_str ()));

      emits->configure (this->publisher_,
                        TRAIT::topic_qos_default (),
                        topic_name.c_str ());
    }
  }

  typename publishes_map_type::ITERATOR publishes_iter (this->publishes_);

  for (; !publishes_iter.done (); ++ publishes_iter)
  {
    typename publishes_map_type::VALUE pub_table = publishes_iter->item ();

    ACE_CString topic_name (this->name_);
    topic_name += ".";
    topic_name += publishes_iter->key ();

    if (!pub_table->is_configured ())
    {
      // Configure the publisher table with the default configuration.
      // This includes using the default DDS::Publisher entity and the
      // default TOPIC_QOS_DEFAULT.
      ACE_ERROR ((LM_DEBUG,
                  ACE_TEXT ("%T (%t) - %M - using default configuration ")
                  ACE_TEXT ("for <%s>\n"),
                  publishes_iter->key ().c_str ()));

      pub_table->configure (this->publisher_,
                            TRAIT::topic_qos_default (),
                            topic_name.c_str ());
    }
  }
}

//
// create_datawriter
//
template <typename TRAIT, typename T, typename CONTEXT, typename EXECUTOR, typename POA_EXEC>
typename TRAIT::datawriter_ptr_type
DDS_Servant_T <TRAIT, T, CONTEXT, EXECUTOR, POA_EXEC>::
create_datawriter (const char * name,
                   const typename TRAIT::topicqos_type & topic_qos,
                   typename TRAIT::publisher_ptr_type publisher)
{
  // Locate the target publisher, or publisher table.
  typename TRAIT::publisher_type * emits = 0;
  typename TRAIT::publisher_table_type * publishes = 0;
  typename TRAIT::datawriter_var_type data_writer;

  ACE_CString topic_name (this->name_);
  topic_name += ".";
  topic_name += name;

  if (0 == this->emits_.find (name, emits))
  {
    emits->configure (publisher, topic_qos, topic_name.c_str ());
    data_writer = emits->get_datawriter ();
  }
  else if (0 == this->publishes_.find (name, publishes))
  {
    publishes->configure (publisher, topic_qos, topic_name.c_str ());
    data_writer = publishes->get_datawriter ();
  }
  else
  {
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - <%s> does not have <%s> port\n"),
                this->name_.c_str (),
                name));

    throw ::CORBA::INTERNAL ();
  }

  return TRAIT::_retn (data_writer);
}

//
// create_datareader
//
template <typename TRAIT, typename T, typename CONTEXT, typename EXECUTOR, typename POA_EXEC>
void DDS_Servant_T <TRAIT, T, CONTEXT, EXECUTOR, POA_EXEC>::
configure_eventconsumer (const char * name,
                         const typename TRAIT::datareaderqos_type & reader_qos,
                         const typename TRAIT::topicqos_type & topic_qos,
                         typename TRAIT::subscriber_ptr_type publisher)
{
  typename TRAIT::eventconsumer_type * consumer = 0;

  if (0 == this->consumers_.find (name, consumer))
  {
    consumer->configure (publisher, topic_qos, reader_qos);
  }
  else
  {
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - <%s> does not have <%s> port\n"),
                this->name_.c_str (),
                name));

    throw ::CORBA::INTERNAL ();
  }
}

}
