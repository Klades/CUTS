// $Id$

#if !defined (__CUTS_INLINE__)
#include "CCM_Servant_T.inl"
#endif

#include "CCM_EventConsumer.h"
#include "CCM_Single_Subscriber.h"
#include "CCM_Subscriber_Table.h"

//
// CUTS_CCM_Servant_T
//
template <typename T, typename CONTEXT, typename EXECUTOR, typename POA_EXEC, typename SERVANT_BASE>
CUTS_CCM_Servant_T <T, CONTEXT, EXECUTOR, POA_EXEC, SERVANT_BASE>::
CUTS_CCM_Servant_T (const char * name, typename EXECUTOR::_ptr_type exec)
  : SERVANT_BASE (name),
    impl_ (EXECUTOR::_duplicate (exec))
{
  // Create the context for the servant/executor.
  CONTEXT * context = 0;
  T * self = dynamic_cast <T *> (this);

  ACE_NEW_THROW_EX (context,
                    CONTEXT (*self),
                    ::CORBA::NO_MEMORY ());

  // Set the session context of the implementation
  this->ctx_.reset (context);

  if (this->impl_)
    this->impl_->set_session_context (this->ctx_.get ());
}

template <typename T, typename CONTEXT, typename EXECUTOR, typename POA_EXEC, typename SERVANT_BASE>
CUTS_INLINE void
CUTS_CCM_Servant_T <T, CONTEXT, EXECUTOR, POA_EXEC, SERVANT_BASE>::configuration_complete (void)
{
  if (this->impl_)
    this->impl_->configuration_complete ();
}

//
// activate_component
//
template <typename T, typename CONTEXT, typename EXECUTOR, typename POA_EXEC, typename SERVANT_BASE>
void CUTS_CCM_Servant_T <T, CONTEXT, EXECUTOR, POA_EXEC, SERVANT_BASE>::activate_component (void)
{
  if (this->impl_)
    this->impl_->ccm_activate ();
}

//
// passivate_component
//
template <typename T, typename CONTEXT, typename EXECUTOR, typename POA_EXEC, typename SERVANT_BASE>
void CUTS_CCM_Servant_T <T, CONTEXT, EXECUTOR, POA_EXEC, SERVANT_BASE>::passivate_component (void)
{
  if (this->impl_)
    this->impl_->ccm_passivate ();
}

//
// remove
//
template <typename T, typename CONTEXT, typename EXECUTOR, typename POA_EXEC, typename SERVANT_BASE>
void CUTS_CCM_Servant_T <T, CONTEXT, EXECUTOR, POA_EXEC, SERVANT_BASE>::remove (void)
{
  if (this->impl_)
    this->impl_->ccm_remove ();
}

//
// get_consumer
//
template <typename T, typename CONTEXT, typename EXECUTOR, typename POA_EXEC, typename SERVANT_BASE>
CUTS_INLINE
Components::EventConsumerBase_ptr
CUTS_CCM_Servant_T <T, CONTEXT, EXECUTOR, POA_EXEC, SERVANT_BASE>::get_consumer (const char * name)
{
  CUTS_CCM_EventConsumer * consumer = 0;

  if (0 != this->consumers_.find (name, consumer))
    throw ::Components::InvalidName ();

  return consumer->_this ();
}

//
// connect_consumer
//
template <typename T, typename CONTEXT, typename EXECUTOR, typename POA_EXEC, typename SERVANT_BASE>
CUTS_INLINE
void CUTS_CCM_Servant_T <T, CONTEXT, EXECUTOR, POA_EXEC, SERVANT_BASE>::
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
template <typename T, typename CONTEXT, typename EXECUTOR, typename POA_EXEC, typename SERVANT_BASE>
CUTS_INLINE
Components::EventConsumerBase_ptr
CUTS_CCM_Servant_T <T, CONTEXT, EXECUTOR, POA_EXEC, SERVANT_BASE>::
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
template <typename T, typename CONTEXT, typename EXECUTOR, typename POA_EXEC, typename SERVANT_BASE>
::Components::Cookie *
CUTS_CCM_Servant_T <T, CONTEXT, EXECUTOR, POA_EXEC, SERVANT_BASE>::
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
template <typename T, typename CONTEXT, typename EXECUTOR, typename POA_EXEC, typename SERVANT_BASE>
::Components::EventConsumerBase_ptr
CUTS_CCM_Servant_T <T, CONTEXT, EXECUTOR, POA_EXEC, SERVANT_BASE>::
unsubscribe (const char * publisher_name, ::Components::Cookie * cookie)
{
  CUTS_CCM_Subscriber_Table * table = 0;

  if (0 != this->publishes_.find (publisher_name, table))
    throw ::Components::InvalidName ();

  return table->unsubscribe (cookie);
}

