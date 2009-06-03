// $Id$

#if !defined (__CUTS_INLINE__)
#include "CCM_Servant_T.inl"
#endif

//
// get_consumer
//
template <typename CONTEXT, typename EXEC, typename POA_EXEC>
CUTS_INLINE
Components::EventConsumerBase_ptr
CUTS_CCM_Servant_T <CONTEXT, EXEC, POA_EXEC>::get_consumer (const char * name)
{
  CUTS_CCM_EventConsumer * consumer = 0;

  if (0 != this->consumers_.find (name, consumer))
    throw ::Components::InvalidName ();

  return consumer->_this ();
}

//
// connect_consumer
//
template <typename CONTEXT, typename EXEC, typename POA_EXEC>
CUTS_INLINE
void CUTS_CCM_Servant_T <CONTEXT, EXEC, POA_EXEC>::
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
template <typename CONTEXT, typename EXEC, typename POA_EXEC>
CUTS_INLINE
Components::EventConsumerBase_ptr
CUTS_CCM_Servant_T <CONTEXT, EXEC, POA_EXEC>::
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
template <typename CONTEXT, typename EXEC, typename POA_EXEC>
::Components::Cookie * CUTS_CCM_Servant_T <CONTEXT, EXEC, POA_EXEC>::
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
template <typename CONTEXT, typename EXEC, typename POA_EXEC>
::Components::EventConsumerBase_ptr CUTS_CCM_Servant_T <CONTEXT, EXEC, POA_EXEC>::
unsubscribe (const char * publisher_name, ::Components::Cookie * cookie)
{
  CUTS_CCM_Subscriber_Table * table = 0;

  if (0 != this->publishes_.find (publisher_name, table))
    throw ::Components::InvalidName ();

  return table->unsubscribe (cookie);
}

