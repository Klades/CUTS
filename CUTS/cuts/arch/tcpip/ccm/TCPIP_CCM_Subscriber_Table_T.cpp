// $Id$

#if !defined (__CUTS_INLINE__)
#include "TCPIP_CCM_Subscriber_Table_T.inl"
#endif

#include "TCPIP_CCM_Cookie.h"

//
// subscribe
//
template <typename T>
::Components::Cookie *
CUTS_TCPIP_CCM_Subscriber_Table_T <T>::
subscribe (::Components::EventConsumerBase_ptr consumer)
{
  // Generate a new UUID for the subscriber.
  ACE_Utils::UUID uuid;
  ACE_Utils::UUID_GENERATOR::instance ()->generate_UUID (uuid);

  ACE_DEBUG ((LM_DEBUG,
              "%T (%t) - %M - consumer cookie value is <%s>\n",
              uuid.to_string ()->c_str ()));

  // Allocate a new data type and connect the consumer.
  CUTS_TCPIP_CCM_Remote_Endpoint_T <T> * data = 0;

  ACE_NEW_THROW_EX (data,
                    CUTS_TCPIP_CCM_Remote_Endpoint_T <T> (),
                    ::CORBA::NO_MEMORY ());

  ACE_Auto_Ptr < CUTS_TCPIP_CCM_Remote_Endpoint_T <T> > auto_clean (data);

  // Cache the subscriber.
  if (0 != this->table_.bind (uuid, data))
    throw ::CORBA::INTERNAL ();

  // Connect to the consumer of the event.
  auto_clean.release ();
  data->connect (consumer);

  // Allocate a new cookie for the subscriber.
  OBV_Components::Cookie * cookie = 0;

  ACE_NEW_THROW_EX (cookie,
                    CUTS_TCPIP_CCM_Cookie (uuid),
                    ::CORBA::NO_MEMORY ());

  return cookie;
}

//
// unsubscribe
//
template <typename T>
::Components::EventConsumerBase_ptr
CUTS_TCPIP_CCM_Subscriber_Table_T <T>::unsubscribe (::Components::Cookie * c)
{
  // Extract the UUID from the cookie.
  CUTS_TCPIP_CCM_Cookie * cookie = dynamic_cast <CUTS_TCPIP_CCM_Cookie *> (c);

  ACE_Utils::UUID uuid;
  cookie->extract (uuid);

  ACE_DEBUG ((LM_DEBUG,
              "%T (%t) - %M - unsubscribing consumer with cookie value <%s>\n",
              uuid.to_string ()->c_str ()));

  // Locate the consumer for this subscription.
  CUTS_TCPIP_CCM_Remote_Endpoint_T <T> * data = 0;
  ::Components::EventConsumerBase_var consumer;

  if (0 == this->table_.unbind (uuid, data))
    consumer = data->disconnect ();

  // Delete the return map item.
  if (0 != data)
    delete data;

  return consumer._retn ();
}

//
// unsubscribe
//
template <typename T>
void CUTS_TCPIP_CCM_Subscriber_Table_T <T>::send_event (T * ev)
{
  typename table_type::ITERATOR iter (this->table_);

  for ( ; !iter.done (); ++ iter)
    iter->item ()->send_event (ev);
}
