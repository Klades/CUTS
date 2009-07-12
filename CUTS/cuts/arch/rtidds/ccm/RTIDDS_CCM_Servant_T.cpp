// $Id$

#if !defined (__CUTS_INLINE__)
#include "RTIDDS_CCM_Servant_T.inl"
#endif

#include "RTIDDS_EventConsumer.h"
#include "RTIDDS_Subscriber.h"
#include "RTIDDS_Subscriber_Table.h"

//
// configure
//
template <typename T, typename CONTEXT, typename EXECUTOR, typename POA_EXEC>
void CUTS_RTIDDS_CCM_Servant_T <T, CONTEXT, EXECUTOR, POA_EXEC>::
configure (::DDSDomainParticipant * participant)
{
  typename consumer_map_type::ITERATOR consumer_iter (this->consumers_);
  CUTS_RTIDDS_CCM_EventConsumer * consumer = 0;

  for (; !consumer_iter.done (); ++ consumer_iter)
    {
      // Try and cast the object to a RTIDDS event consumer.
      consumer = dynamic_cast <CUTS_RTIDDS_CCM_EventConsumer *> (consumer_iter->item ());

      if (0 != consumer)
  {
    // Now, configure the servant for this participant.
    consumer->configure (participant,
             "James",
             consumer_iter->key ().c_str ());
  }
    }

  typename emits_map_type::ITERATOR emits_iter (this->emits_);
  CUTS_RTIDDS_CCM_Subscriber * subscriber = 0;

  for (; !emits_iter.done (); ++ emits_iter)
    {
      // Try and cast the object to an RTIDDS subscriber.
      subscriber = dynamic_cast <CUTS_RTIDDS_CCM_Subscriber *> (emits_iter->item ());

      if (0 != subscriber)
  subscriber->configure (participant);
    }

  typename publishes_map_type::ITERATOR publishes_iter (this->publishes_);
  CUTS_RTIDDS_CCM_Subscriber_Table * subscriber_table = 0;

  for (; !publishes_iter.done (); ++ publishes_iter)
    {
      // Try to cast the object to an RTIDDS subscriber table.
      subscriber_table =
  dynamic_cast <CUTS_RTIDDS_CCM_Subscriber_Table *> (publishes_iter->item ());

      if (0 != subscriber_table)
  subscriber_table->configure (participant);
    }

  // Pass control to the base class.
  CUTS_RTIDDS_CCM_Servant::configure (participant);
}
