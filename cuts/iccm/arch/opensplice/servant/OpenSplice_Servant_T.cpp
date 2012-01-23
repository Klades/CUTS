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
  {
    ACE_DEBUG ((LM_DEBUG,
                ACE_TEXT ("%T (%t) - %M - creating a subscriber for %s\n"),
                this->name_.c_str ()));

    this->subscriber_ =
      this->participant_->create_subscriber (SUBSCRIBER_QOS_DEFAULT,
                                             ::DDS::SubscriberListener::_nil (),
                                             ::DDS::ANY_STATUS);
  }

  if (0 != this->emits_.current_size () ||
      0 != this->publishes_.current_size ())
  {
    ACE_DEBUG ((LM_DEBUG,
                ACE_TEXT ("%T (%t) - %M - creating a publisher for %s\n"),
                this->name_.c_str ()));

    this->publisher_ =
      this->participant_->create_publisher (PUBLISHER_QOS_DEFAULT,
                                            ::DDS::PublisherListener::_nil (),
                                            ::DDS::ANY_STATUS);
  }

  // Configure each consumer port in this servant using the subscriber
  // interface for this servant, and its port information.
  typename consumer_map_type::ITERATOR consumer_iter (this->consumers_);

  for (; !consumer_iter.done (); ++ consumer_iter)
    consumer_iter->item ()->configure (this->subscriber_.in ());

  typename emits_map_type::ITERATOR emits_iter (this->emits_);

  for (; !emits_iter.done (); ++ emits_iter)
  {
    ACE_CString topic_name (this->name_);
    topic_name += ".";
    topic_name += emits_iter->key ();

    emits_iter->item ()->configure (this->publisher_.in (), topic_name);
  }

  typename publishes_map_type::ITERATOR publishes_iter (this->publishes_);

  for (; !publishes_iter.done (); ++ publishes_iter)
  {
    ACE_CString topic_name (this->name_);
    topic_name += ".";
    topic_name += publishes_iter->key ();

    publishes_iter->item ()->configure (this->publisher_.in (), topic_name);
  }
}

}
