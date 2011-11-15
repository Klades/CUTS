// $Id$

#if !defined (__CUTS_INLINE__)
#include "CCM_Subscriber_Table_T.inl"
#endif

#include "CCM_Cookie.h"

//
// subscribe
//
template <typename T>
::Components::Cookie *
CUTS_CCM_Publisher_Table_T <T>::
subscribe (::Components::EventConsumerBase_ptr consumer)
{
  // Generate a new UUID for the subscriber.
  ACE_Utils::UUID uuid;
  ACE_Utils::UUID_GENERATOR::instance ()->generate_UUID (uuid);

  ACE_DEBUG ((LM_DEBUG,
              "%T (%t) - %M - consumer cookie value is <%s>\n",
              uuid.to_string ()->c_str ()));

  // Allocate a new data type and connect the consumer.
  CUTS_CCM_Publisher_T <T> * publisher = 0;

  ACE_NEW_THROW_EX (publisher,
                    CUTS_CCM_Publisher_T <T> (),
                    ::CORBA::NO_MEMORY ());

  ACE_Auto_Ptr < CUTS_CCM_Publisher_T <T> > auto_clean (publisher);

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
template <typename T>
::Components::EventConsumerBase_ptr
CUTS_CCM_Publisher_Table_T <T>::unsubscribe (::Components::Cookie * c)
{
  // Extract the UUID from the cookie.
  CUTS_CCM_Cookie * cookie = dynamic_cast <CUTS_CCM_Cookie *> (c);

  ACE_Utils::UUID uuid;
  cookie->extract (uuid);

  ACE_DEBUG ((LM_DEBUG,
              "%T (%t) - %M - unsubscribing consumer with cookie value <%s>\n",
              uuid.to_string ()->c_str ()));

  // Locate the consumer for this subscription.
  CUTS_CCM_Publisher_T <T> * publisher = 0;
  ::Components::EventConsumerBase_var consumer;

  if (0 == this->table_.unbind (uuid, publisher))
    consumer = publisher->disconnect ();

  // Delete the return map item.
  if (0 != publisher)
    delete publisher;

  return consumer._retn ();
}

//
// unsubscribe
//
template <typename T>
void CUTS_CCM_Publisher_Table_T <T>::send_event (T * ev)
{
  typename table_type::ITERATOR iter (this->table_);

  for ( ; !iter.done (); ++ iter)
    iter->item ()->send_event (ev);
}
