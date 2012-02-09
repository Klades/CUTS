// $Id$

#if !defined (__CUTS_INLINE__)
#include "OpenSplice_Servant_T.inl"
#endif

#include "OpenSplice_EventConsumer.h"
#include "OpenSplice_Publisher.h"
#include "OpenSplice_Publisher_Table.h"

namespace iCCM
{

//
// configure
//
template <typename T, typename CONTEXT, typename EXECUTOR, typename POA_EXEC>
void OpenSplice_Servant_T <T, CONTEXT, EXECUTOR, POA_EXEC>::configure (void)
{
  // First, we need to create a subscriber and publisher depending on
  // if we have any consumer or emit/publish ports on this servant.
  if (0 != this->consumers_.current_size ())
    this->subscriber_ =
      this->participant_->create_subscriber (SUBSCRIBER_QOS_DEFAULT,
                                             ::DDS::SubscriberListener::_nil (),
                                             ::DDS::ANY_STATUS);

  if (0 != this->emits_.current_size () || 0 != this->publishes_.current_size ())
    this->publisher_ =
      this->participant_->create_publisher (PUBLISHER_QOS_DEFAULT,
                                            ::DDS::PublisherListener::_nil (),
                                            ::DDS::ANY_STATUS);

  // Configure each consumer port in this servant using the subscriber
  // interface for this servant, and its port information.
  typename consumer_map_type::ITERATOR consumer_iter (this->consumers_);

  for (; !consumer_iter.done (); ++ consumer_iter)
    consumer_iter->item ()->configure (this->subscriber_.in ());

  typename emits_map_type::ITERATOR emits_iter (this->emits_);

  for (; !emits_iter.done (); ++ emits_iter)
  {
    OpenSplice_Publisher * emits = emits_iter->item ();

    ACE_CString topic_name (this->name_);
    topic_name += ".";
    topic_name += emits_iter->key ();

    if (!emits->is_configured ())
      emits->configure (this->publisher_.in (), topic_name);
  }

  typename publishes_map_type::ITERATOR publishes_iter (this->publishes_);

  for (; !publishes_iter.done (); ++ publishes_iter)
  {
    OpenSplice_Publisher_Table * pub_table = publishes_iter->item ();

    ACE_CString topic_name (this->name_);
    topic_name += ".";
    topic_name += publishes_iter->key ();

    if (!pub_table->is_configured ())
      pub_table->configure (this->publisher_.in (), topic_name);
  }
}

//
// create_datawriter
//
template <typename T, typename CONTEXT, typename EXECUTOR, typename POA_EXEC>
::DDS::DataWriter_ptr
OpenSplice_Servant_T <T, CONTEXT, EXECUTOR, POA_EXEC>::
create_datawriter (const char * name, ::DDS::Publisher_ptr publisher)
{
  // Locate the target publisher, or publisher table.
  OpenSplice_Publisher * emits = 0;
  OpenSplice_Publisher_Table * publishes = 0;

  ACE_CString topic_name (this->name_);
  topic_name += ".";
  topic_name += name;

  if (0 == this->emits_.find (name, emits))
  {
    emits->configure (publisher, topic_name);
    return emits->get_datawriter ();
  }
  else if (0 == this->publishes_.find (name, publishes))
  {
    publishes->configure (publisher, topic_name);
    return publishes->get_datawriter ();
  }
  else
  {
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - <%s> does not have <%s> port\n"),
                this->name_.c_str (),
                name));

    throw ::CORBA::INTERNAL ();
  }

  return ::DDS::DataWriter::_nil ();
}

//
// create_datareader
//
template <typename T, typename CONTEXT, typename EXECUTOR, typename POA_EXEC>
::DDS::DataReader_ptr
OpenSplice_Servant_T <T, CONTEXT, EXECUTOR, POA_EXEC>::
create_datareader (const char * name, ::DDS::Subscriber_ptr publisher)
{
  return ::DDS::DataReader::_nil ();
}

}
