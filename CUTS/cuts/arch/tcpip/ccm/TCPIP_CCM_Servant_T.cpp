// $Id$

#if !defined (__CUTS_INLINE__)
#include "TCPIP_CCM_Servant_T.inl"
#endif

//
// CUTS_TCPIP_CCM_Servant_T
//
template <typename T, typename CTX, typename EXEC, typename POA_EXEC>
CUTS_TCPIP_CCM_Servant_T <T, CTX, EXEC, POA_EXEC>::
CUTS_TCPIP_CCM_Servant_T (T * servant,
                          CUTS_TCPIP_Servant_Manager & svnt_mgr,
                          typename EXEC::_ptr_type executor)
: base_type (servant, executor),
  svnt_mgr_ (svnt_mgr)
{
  this->svnt_mgr_.activate_object (this);
}

//
// remove
//
template <typename T, typename CTX, typename EXEC, typename POA_EXEC>
CUTS_INLINE void
CUTS_TCPIP_CCM_Servant_T <T, CTX, EXEC, POA_EXEC>::remove (void)
{
  this->svnt_mgr_.deactivate_object (this->the_UUID ());

  if (this->impl_)
    this->impl_->ccm_remove ();
}

//
// activate_component
//
template <typename T, typename CTX, typename EXEC, typename POA_EXEC>
CUTS_INLINE
void CUTS_TCPIP_CCM_Servant_T <T, CTX, EXEC, POA_EXEC>::activate_component (void)
{
  if (this->impl_)
    this->impl_->ccm_activate ();
}

//
// passivate_component
//
template <typename T, typename CTX, typename EXEC, typename POA_EXEC>
CUTS_INLINE
void CUTS_TCPIP_CCM_Servant_T <T, CTX, EXEC, POA_EXEC>::passivate_component (void)
{
  if (this->impl_)
    this->impl_->ccm_passivate ();
}

//
// get_consumer
//
template <typename T, typename CTX, typename EXEC, typename POA_EXEC>
CUTS_INLINE
Components::EventConsumerBase_ptr
CUTS_TCPIP_CCM_Servant_T <T, CTX, EXEC, POA_EXEC>::get_consumer (const char * name)
{
  CUTS_TCPIP_CCM_EventConsumer * consumer = 0;

  if (0 != this->consumers_.find (name, consumer))
    throw ::Components::InvalidName ();

  return consumer->_this ();
}

//
// connect_consumer
//
template <typename T, typename CTX, typename EXEC, typename POA_EXEC>
CUTS_INLINE
void CUTS_TCPIP_CCM_Servant_T <T, CTX, EXEC, POA_EXEC>::
connect_consumer (const char * name, Components::EventConsumerBase_ptr consumer)
{
  // Locate the endpoint for this consumer.
  CUTS_TCPIP_CCM_Remote_Endpoint * endpoint = 0;

  if (0 != this->emits_.find (name, endpoint))
    throw ::Components::InvalidName ();

  // Now, signal the endpoint to connect.
  endpoint->connect (consumer);
}

//
// disconnect_consumer
//
template <typename T, typename CTX, typename EXEC, typename POA_EXEC>
CUTS_INLINE
Components::EventConsumerBase_ptr
CUTS_TCPIP_CCM_Servant_T <T, CTX, EXEC, POA_EXEC>::
disconnect_consumer (const char * name)
{
  // Locate the endpoint for this consumer.
  CUTS_TCPIP_CCM_Remote_Endpoint * endpoint = 0;

  if (0 != this->emits_.find (name, endpoint))
    throw ::Components::InvalidName ();

  // Now, signal the endpoint to disconnect.
  return endpoint->disconnect ();
}

//
// subscribe
//
template <typename T, typename CTX, typename EXEC, typename POA_EXEC>
::Components::Cookie * CUTS_TCPIP_CCM_Servant_T <T, CTX, EXEC, POA_EXEC>::
subscribe (const char * publisher_name, ::Components::EventConsumerBase_ptr subscriber)
{
  CUTS_TCPIP_CCM_Subscriber_Table * table = 0;

  if (0 != this->publishes_.find (publisher_name, table))
    throw ::Components::InvalidName ();

  return table->subscribe (subscriber);
}

//
// unsubscribe
//
template <typename T, typename CTX, typename EXEC, typename POA_EXEC>
::Components::EventConsumerBase_ptr CUTS_TCPIP_CCM_Servant_T <T, CTX, EXEC, POA_EXEC>::
unsubscribe (const char * publisher_name, ::Components::Cookie * cookie)
{
  CUTS_TCPIP_CCM_Subscriber_Table * table = 0;

  if (0 != this->publishes_.find (publisher_name, table))
    throw ::Components::InvalidName ();

  return table->unsubscribe (cookie);
}

