// $Id$

#include "cuts/arch/ccm/CCM_Cookie.h"

template <typename EVENT>
CUTS_RTIDDS_CCM_Subscriber_Table_T <EVENT>::
CUTS_RTIDDS_CCM_Subscriber_Table_T (void)
{

}

template <typename EVENT>
CUTS_RTIDDS_CCM_Subscriber_Table_T <EVENT>::
~CUTS_RTIDDS_CCM_Subscriber_Table_T (void)
{

}

//
// subscribe
//
template <typename EVENT>
::Components::Cookie *
CUTS_RTIDDS_CCM_Subscriber_Table_T <EVENT>::
subscribe (::Components::EventConsumerBase_ptr consumer)
{
  // Generate a new UUID for the subscriber.
  ACE_Utils::UUID uuid;
  ACE_Utils::UUID_GENERATOR::instance ()->generate_UUID (uuid);

  ACE_DEBUG ((LM_DEBUG,
              "%T (%t) - %M - consumer cookie value is <%s>\n",
              uuid.to_string ()->c_str ()));

  // Allocate a new data type and connect the consumer.
  subscriber_type * subscriber = 0;

  ACE_NEW_THROW_EX (subscriber,
                    subscriber_type (),
                    ::CORBA::NO_MEMORY ());

  ACE_Auto_Ptr < subscriber_type > auto_clean (subscriber);
  subscriber->configure (this->participant_);

  // Cache the subscriber.
  if (0 != this->table_.bind (uuid, subscriber))
    throw ::CORBA::INTERNAL ();

  // Connect to the consumer of the event.
  auto_clean.release ();
  subscriber->connect (consumer);

  // Allocate a new cookie for the subscriber.
  OBV_Components::Cookie * cookie = 0;

  ACE_NEW_THROW_EX (cookie,
                    CUTS_CCM_Cookie (uuid),
                    ::CORBA::NO_MEMORY ());

  return cookie;
}

//
// unsubscribe
//
template <typename EVENT>
::Components::EventConsumerBase_ptr
CUTS_RTIDDS_CCM_Subscriber_Table_T <EVENT>::
unsubscribe (::Components::Cookie * c)
{
  // Extract the UUID from the cookie.
  CUTS_CCM_Cookie * cookie = dynamic_cast <CUTS_CCM_Cookie *> (c);

  ACE_Utils::UUID uuid;
  cookie->extract (uuid);

  ACE_DEBUG ((LM_DEBUG,
              "%T (%t) - %M - unsubscribing consumer with cookie value <%s>\n",
              uuid.to_string ()->c_str ()));

  // Locate the consumer for this subscription.
  subscriber_type * subscriber = 0;
  ::Components::EventConsumerBase_var consumer;

  if (0 == this->table_.unbind (uuid, subscriber))
    consumer = subscriber->disconnect ();

  // Delete the return map item.
  if (0 != subscriber)
    delete subscriber;

  return consumer._retn ();
}

//
// send_event
//
template <typename EVENT>
void CUTS_RTIDDS_CCM_Subscriber_Table_T <EVENT>::
send_event (typename traits_type::corba_event_type * ev)
{
  // First, convert the CORBA event to a DDS event.
  typename traits_type::dds_event_type dds_event;
  *ev >>= dds_event;

  typedef typename table_type::lock_type lock_type;
  ACE_READ_GUARD (lock_type, guard, this->table_.mutex ());

  // Send the event to all the subscribers.
  typename table_type::ITERATOR iter (this->table_);

  for (; !iter.done (); ++ iter)
    iter->item ()->send_event (&dds_event);
}

