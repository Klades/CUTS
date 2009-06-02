// $Id$

#if !defined (__CUTS_INLINE__)
#include "CCM_Servant_T.inl"
#endif

//
// CUTS_CCM_Servant_T
//
template <typename POA_EXEC>
CUTS_CCM_Servant_T <POA_EXEC>::CUTS_CCM_Servant_T (const char * name)
: CUTS_CCM_Servant (name)
{
}

//
// remove
//
template <typename POA_EXEC>
CUTS_INLINE void
CUTS_CCM_Servant_T <POA_EXEC>::remove (void)
{
  throw CORBA::NO_IMPLEMENT ();
}

//
// activate_component
//
template <typename POA_EXEC>
CUTS_INLINE
void CUTS_CCM_Servant_T <POA_EXEC>::activate_component (void)
{

}

//
// passivate_component
//
template <typename POA_EXEC>
CUTS_INLINE
void CUTS_CCM_Servant_T <POA_EXEC>::passivate_component (void)
{

}

//
// get_consumer
//
template <typename POA_EXEC>
CUTS_INLINE
Components::EventConsumerBase_ptr
CUTS_CCM_Servant_T <POA_EXEC>::get_consumer (const char * name)
{
  CUTS_CCM_EventConsumer * consumer = 0;

  if (0 != this->consumers_.find (name, consumer))
    throw ::Components::InvalidName ();

  return consumer->_this ();
}

//
// connect_consumer
//
template <typename POA_EXEC>
CUTS_INLINE
void CUTS_CCM_Servant_T <POA_EXEC>::
connect_consumer (const char * name, Components::EventConsumerBase_ptr consumer)
{
  // Locate the endpoint for this consumer.
  CUTS_CCM_Single_Subscriber * single = 0;

  if (0 != this->emits_.find (name, single))
    throw ::Components::InvalidName ();

  // Now, signal the endpoint to connect.
  single->connect (consumer);
}

//
// disconnect_consumer
//
template <typename POA_EXEC>
CUTS_INLINE
Components::EventConsumerBase_ptr
CUTS_CCM_Servant_T <POA_EXEC>::
disconnect_consumer (const char * name)
{
  // Locate the endpoint for this consumer.
  CUTS_CCM_Single_Subscriber * single = 0;

  if (0 != this->emits_.find (name, single))
    throw ::Components::InvalidName ();

  // Now, signal the endpoint to disconnect.
  return single->disconnect ();
}

//
// subscribe
//
template <typename POA_EXEC>
::Components::Cookie * CUTS_CCM_Servant_T <POA_EXEC>::
subscribe (const char * publisher_name, ::Components::EventConsumerBase_ptr subscriber)
{
  CUTS_CCM_Subscriber_Table * table = 0;

  if (0 != this->publishes_.find (publisher_name, table))
    throw ::Components::InvalidName ();

  return table->subscribe (subscriber);
}

//
// unsubscribe
//
template <typename POA_EXEC>
::Components::EventConsumerBase_ptr CUTS_CCM_Servant_T <POA_EXEC>::
unsubscribe (const char * publisher_name, ::Components::Cookie * cookie)
{
  CUTS_CCM_Subscriber_Table * table = 0;

  if (0 != this->publishes_.find (publisher_name, table))
    throw ::Components::InvalidName ();

  return table->unsubscribe (cookie);
}

