// $Id$

#if !defined (__CUTS_INLINE__)
#include "RTIDDS_CCM_Servant_T.inl"
#endif

#include "RTIDDS_EventConsumer.h"
#include "RTIDDS_Publisher.h"
#include "RTIDDS_Publisher_Table.h"

//
// configure
//
template <typename T, typename CONTEXT, typename EXECUTOR, typename POA_EXEC>
void CUTS_RTIDDS_CCM_Servant_T <T, CONTEXT, EXECUTOR, POA_EXEC>::
configure (::DDSDomainParticipant * participant)
{
  // Pass control to the base class.
  CUTS_RTIDDS_CCM_Servant::configure (participant);

  if (0 != this->consumers_.current_size ())
  {
    // First, we need to create a subscriber for this servant since
    // it is able to receive events.
    this->subscriber_ =
      participant->create_subscriber (DDS_SUBSCRIBER_QOS_DEFAULT,
                                      0,
                                      DDS_STATUS_MASK_NONE);

    typename consumer_map_type::ITERATOR consumer_iter (this->consumers_);
    CUTS_RTIDDS_CCM_EventConsumer * consumer = 0;

    for (; !consumer_iter.done (); ++ consumer_iter)
    {
      // Try and cast the object to a RTIDDS event consumer.
      consumer = dynamic_cast <CUTS_RTIDDS_CCM_EventConsumer *> (consumer_iter->item ());

      if (0 != consumer)
        consumer->configure (this->subscriber_,
                             this->name_.c_str (),
                             consumer_iter->key ().c_str ());
    }
  }

  if (0 != this->publishes_.current_size () ||
      0 != this->emits_.current_size ())
  {
    // First, we need to create a publisher for this servant since
    // it is able to receive events.
    this->publisher_ =
      participant->create_publisher (DDS_PUBLISHER_QOS_DEFAULT,
                                     0,
                                     DDS_STATUS_MASK_NONE);

    typename emits_map_type::ITERATOR emits_iter (this->emits_);
    CUTS_RTIDDS_CCM_Publisher * publisher = 0;

    for (; !emits_iter.done (); ++ emits_iter)
    {
      // Try and cast the object to an RTIDDS publisher.
      publisher = dynamic_cast <CUTS_RTIDDS_CCM_Publisher *> (emits_iter->item ());

      if (0 != publisher)
        publisher->configure (this->publisher_);
    }

    typename publishes_map_type::ITERATOR publishes_iter (this->publishes_);
    CUTS_RTIDDS_CCM_Publisher_Table * publisher_table = 0;

    for (; !publishes_iter.done (); ++ publishes_iter)
    {
      // Try to cast the object to an RTIDDS subscriber table.
      publisher_table =
        dynamic_cast <CUTS_RTIDDS_CCM_Publisher_Table *> (publishes_iter->item ());

      if (0 != publisher_table)
        publisher_table->configure (this->publisher_);
    }
  }
}
