// $Id$

#include "cuts/arch/ccm/CCM_Cookie.h"

#if !defined (__CUTS_INLINE__)
#include "RTIDDS_Publisher_Table_T.inl"
#endif

//
// subscribe
//
template <typename EVENT>
::Components::Cookie *
CUTS_RTIDDS_CCM_Publisher_Table_T <EVENT>::
subscribe (::Components::EventConsumerBase_ptr consumer)
{
  // Generate a new UUID for the subscriber.
  ACE_Utils::UUID uuid;
  ACE_Utils::UUID_GENERATOR::instance ()->generate_UUID (uuid);

  ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("%T (%t) - %M - consumer cookie value is <%s>\n"),
              uuid.to_string ()->c_str ()));

  // Allocate a new data type and connect the consumer.
  publisher_type * publisher = 0;

  ACE_NEW_THROW_EX (publisher,
                    publisher_type (),
                    ::CORBA::NO_MEMORY ());

  ACE_Auto_Ptr < publisher_type > auto_clean (publisher);
  publisher->configure (this->publisher_);

  // Cache the subscriber.
  if (0 != this->table_.bind (uuid, publisher))
    throw ::CORBA::INTERNAL ();

  // Connect to the consumer of the event.
  auto_clean.release ();
  publisher->connect (consumer);

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
CUTS_RTIDDS_CCM_Publisher_Table_T <EVENT>::unsubscribe (::Components::Cookie * c)
{
  // Extract the UUID from the cookie.
  CUTS_CCM_Cookie * cookie = dynamic_cast <CUTS_CCM_Cookie *> (c);

  ACE_Utils::UUID uuid;
  cookie->extract (uuid);

  ACE_DEBUG ((LM_DEBUG,
              "%T (%t) - %M - unsubscribing consumer with cookie value <%s>\n",
              uuid.to_string ()->c_str ()));

  // Locate the consumer for this subscription.
  publisher_type * publisher = 0;
  ::Components::EventConsumerBase_var consumer;

  if (0 == this->table_.unbind (uuid, publisher))
    consumer = publisher->disconnect ();

  // Delete the return map item.
  if (0 != publisher)
    delete publisher;

  return consumer._retn ();
}

//
// send_event
//
template <typename EVENT>
void CUTS_RTIDDS_CCM_Publisher_Table_T <EVENT>::
send_event (typename traits_type::corba_event_type * ev)
{
  typedef typename publisher_table::lock_type lock_type;
  ACE_READ_GUARD (lock_type, guard, this->table_.mutex ());

  // Send the event to all the subscribers.
  typename publisher_table::ITERATOR iter (this->table_);

  for (; !iter.done (); ++ iter)
    iter->item ()->send_event (ev->content ());
}

