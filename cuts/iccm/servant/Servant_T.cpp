// $Id$

#if !defined (__CUTS_INLINE__)
#include "Servant_T.inl"
#endif

#include "EventConsumer.h"
#include "Publisher.h"
#include "Publisher_Table.h"

//
// Servant_T
//
template <typename T, typename CONTEXT, typename EXECUTOR, typename POA_EXEC, typename SERVANT_BASE>
Servant_T <T, CONTEXT, EXECUTOR, POA_EXEC, SERVANT_BASE>::
Servant_T (T * this_,
                    const char * name,
                    ::PortableServer::POA_ptr poa,
                    typename EXECUTOR::_ptr_type exec)
: SERVANT_BASE (name),
  impl_ (EXECUTOR::_duplicate (exec))
{
  // Initialize the port POA.
  this->initialize_the_port_POA (name, poa);

  // Create the context for the servant/executor.
  CONTEXT * context = 0;
  ACE_NEW_THROW_EX (context,
                    CONTEXT (*this_),
                    ::CORBA::NO_MEMORY ());

  // Set the session context of the implementation
  this->ctx_.reset (context);

  if (0 != this->impl_)
    this->impl_->set_session_context (this->ctx_.get ());
}

//
// ~Servant_T
//
template <typename T, typename CONTEXT, typename EXECUTOR, typename POA_EXEC, typename SERVANT_BASE>
CUTS_INLINE
Servant_T <T, CONTEXT, EXECUTOR, POA_EXEC, SERVANT_BASE>::~Servant_T (void)
{
}

//
// configuration_complete
//
template <typename T, typename CONTEXT, typename EXECUTOR, typename POA_EXEC, typename SERVANT_BASE>
CUTS_INLINE void
Servant_T <T, CONTEXT, EXECUTOR, POA_EXEC, SERVANT_BASE>::configuration_complete (void)
{
  if (0 != this->impl_)
    this->impl_->configuration_complete ();
}

//
// activate_component
//
template <typename T, typename CONTEXT, typename EXECUTOR, typename POA_EXEC, typename SERVANT_BASE>
void Servant_T <T, CONTEXT, EXECUTOR, POA_EXEC, SERVANT_BASE>::activate_component (void)
{
  if (0 != this->impl_)
    this->impl_->ccm_activate ();
}

//
// passivate_component
//
template <typename T, typename CONTEXT, typename EXECUTOR, typename POA_EXEC, typename SERVANT_BASE>
void Servant_T <T, CONTEXT, EXECUTOR, POA_EXEC, SERVANT_BASE>::passivate_component (void)
{
  if (0 != this->impl_)
    this->impl_->ccm_passivate ();
}

//
// remove
//
template <typename T, typename CONTEXT, typename EXECUTOR, typename POA_EXEC, typename SERVANT_BASE>
void Servant_T <T, CONTEXT, EXECUTOR, POA_EXEC, SERVANT_BASE>::remove (void)
{
  if (0 != this->impl_)
    this->impl_->ccm_remove ();

  // Since we are removing the component, it is safe to deactivate
  // all its ports.
  this->deactivate_ports ();

  // We are also going to destroy the port POA.
  if (!::CORBA::is_nil (this->port_POA_.in ()))
    this->port_POA_->destroy (0, 0);
}

//
// get_consumer
//
template <typename T, typename CONTEXT, typename EXECUTOR, typename POA_EXEC, typename SERVANT_BASE>
CUTS_INLINE
::Components::EventConsumerBase_ptr
Servant_T <T, CONTEXT, EXECUTOR, POA_EXEC, SERVANT_BASE>::get_consumer (const char * name)
{
  eventconsumer_type * consumer = 0;

  if (0 != this->consumers_.find (name, consumer))
    throw ::Components::InvalidName ();

  // Let's see if the servant has already been activated.
  ::PortableServer::ObjectId_var oid = ::PortableServer::string_to_ObjectId (name);
  ::CORBA::Object_var obj;

  try
  {
    obj = this->port_POA_->id_to_reference (oid.in ());
  }
  catch (const ::PortableServer::POA::ObjectNotActive &)
  {
    this->port_POA_->activate_object_with_id (oid.in (), consumer);
    obj = this->port_POA_->id_to_reference (oid.in ());
  }

  // Retern a reference to the EventConsumerBase object.
  ::Components::EventConsumerBase_var ecb =
    ::Components::EventConsumerBase::_narrow (obj.in ());

  return ecb._retn ();
}

//
// connect_consumer
//
template <typename T, typename CONTEXT, typename EXECUTOR, typename POA_EXEC, typename SERVANT_BASE>
CUTS_INLINE
void Servant_T <T, CONTEXT, EXECUTOR, POA_EXEC, SERVANT_BASE>::
connect_consumer (const char * name, Components::EventConsumerBase_ptr consumer)
{
  // Locate the endpoint for this consumer.
  publisher_type * publisher = 0;

  if (0 != this->emits_.find (name, publisher))
    throw ::Components::InvalidName ();

  // Now, signal the endpoint to connect.
  publisher->connect (consumer);
}

//
// disconnect_consumer
//
template <typename T, typename CONTEXT, typename EXECUTOR, typename POA_EXEC, typename SERVANT_BASE>
CUTS_INLINE
Components::EventConsumerBase_ptr
Servant_T <T, CONTEXT, EXECUTOR, POA_EXEC, SERVANT_BASE>::
disconnect_consumer (const char * name)
{
  // Locate the endpoint for this consumer.
  publisher_type * publisher = 0;

  if (0 != this->emits_.find (name, publisher))
    throw ::Components::InvalidName ();

  // Now, signal the endpoint to disconnect.
  return publisher->disconnect ();
}

//
// subscribe
//
template <typename T, typename CONTEXT, typename EXECUTOR, typename POA_EXEC, typename SERVANT_BASE>
::Components::Cookie *
Servant_T <T, CONTEXT, EXECUTOR, POA_EXEC, SERVANT_BASE>::
subscribe (const char * publisher_name, ::Components::EventConsumerBase_ptr subscriber)
{
  publisher_table_type * table = 0;

  if (0 != this->publishes_.find (publisher_name, table))
    throw ::Components::InvalidName ();

  return table->subscribe (subscriber);
}

//
// unsubscribe
//
template <typename T, typename CONTEXT, typename EXECUTOR, typename POA_EXEC, typename SERVANT_BASE>
::Components::EventConsumerBase_ptr
Servant_T <T, CONTEXT, EXECUTOR, POA_EXEC, SERVANT_BASE>::
unsubscribe (const char * publisher_name, ::Components::Cookie * cookie)
{
  publisher_table_type * table = 0;

  if (0 != this->publishes_.find (publisher_name, table))
    throw ::Components::InvalidName ();

  return table->unsubscribe (cookie);
}

//
// initialize_the_port_POA
//
template <typename T, typename CONTEXT, typename EXECUTOR, typename POA_EXEC, typename SERVANT_BASE>
void Servant_T <T, CONTEXT, EXECUTOR, POA_EXEC, SERVANT_BASE>::
initialize_the_port_POA (const char * name, ::PortableServer::POA_ptr poa)
{
  CORBA::PolicyList policies (6);
  policies.length (6);

  policies[0] = poa->create_thread_policy (PortableServer::ORB_CTRL_MODEL);
  policies[1] = poa->create_servant_retention_policy (PortableServer::RETAIN);
  policies[2] = poa->create_id_assignment_policy (PortableServer::USER_ID);
  policies[3] = poa->create_id_uniqueness_policy (PortableServer::UNIQUE_ID);
  policies[4] = poa->create_lifespan_policy (PortableServer::TRANSIENT);
  policies[5] = poa->create_request_processing_policy (PortableServer::USE_ACTIVE_OBJECT_MAP_ONLY);

  // Use the policies above to create the child POA that will be
  // used when activating servants.
  this->port_POA_ = poa->create_POA (name,
                                     ::PortableServer::POAManager::_nil (),
                                     policies);

  // Activate the POA manager.
  ::PortableServer::POAManager_var mgr = this->port_POA_->the_POAManager ();
  mgr->activate ();

  // Destroy the POA policies
  for (::CORBA::ULong i = 0; i < policies.length (); ++ i)
    policies[i]->destroy ();
}

//
// deactivate_ports
//
template <typename T, typename CONTEXT, typename EXECUTOR, typename POA_EXEC, typename SERVANT_BASE>
void Servant_T <T, CONTEXT, EXECUTOR, POA_EXEC, SERVANT_BASE>::
deactivate_ports (void)
{
  ::PortableServer::ObjectId_var oid;
  consumer_map_type::ITERATOR iter (this->consumers_);

  for (; !iter.done (); ++ iter)
  {
    try
    {
      // Locate the object id for this servant.
      oid = this->port_POA_->servant_to_id (iter->item ());
      this->port_POA_->deactivate_object (oid.in ());
    }
    catch (const ::PortableServer::POA::ObjectNotActive &)
    {
      // Ingore this exception.
    }
  }
}

//
// create_servant
//
template <typename EXECUTOR, typename SERVANT>
::PortableServer::Servant
create_servant (const char * name,
                ::PortableServer::POA_ptr port_POA,
                ::Components::EnterpriseComponent_ptr p)
{
  // First, convert the pointer to its concrete type.
  typename EXECUTOR::_var_type executor = EXECUTOR::_narrow (p);

  if (::CORBA::is_nil (executor.in ()))
    return 0;

  // Now, create the servant for the executor.
  SERVANT * servant = 0;

  ACE_NEW_RETURN (servant,
                  SERVANT (name, port_POA, executor.in ()),
                  0);

  return servant;
}
