// $Id$

#if !defined (__CUTS_INLINE__)
#include "Servant_T.inl"
#endif

#include "ace/OS_NS_unistd.h"

#include "EventConsumer.h"
#include "Publisher.h"
#include "Publisher_Table.h"
#include "Cookie.h"
#include "cuts/utils/Property_Map.h"
#include "cuts/utils/Property_Map_File.h"

#include <fstream>
#include "boost/spirit/include/classic_file_iterator.hpp"
namespace iCCM
{

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

  this->activate_ports ();
}

//
// passivate_component
//
template <typename T, typename CONTEXT, typename EXECUTOR, typename POA_EXEC, typename SERVANT_BASE>
void Servant_T <T, CONTEXT, EXECUTOR, POA_EXEC, SERVANT_BASE>::passivate_component (void)
{
  if (0 != this->impl_)
    this->impl_->ccm_passivate ();

  this->deactivate_ports ();
}

//
// handle_config
//
template <typename T, typename CONTEXT, typename EXECUTOR, typename POA_EXEC, typename SERVANT_BASE>
void Servant_T <T, CONTEXT, EXECUTOR, POA_EXEC, SERVANT_BASE>::handle_config (const ::Components::ConfigValues & values)
{
  // Find the PortConfig file and parse it
  const char * filename = 0;
  for (::CORBA::ULong index = 0; index < values.length (); ++index)
  {
    std::string name (values[index]->name ());
    if (name == "CUTS.PortConfig")
    {
      values[index]->value() >>= filename;
    }
  }
  
  if (filename) 
  {
    CUTS_Property_Map props;
    CUTS_Property_Map_File props_file (props);
    
    if (props_file.read(filename)) {
      std::cout << "Read file..." << std::endl;
    }
    else {
      std::cout << "File failure!" << std::endl;
    }

    typename CUTS_Property_Map::iterator prop_it = props.begin();

    std::cout << "Printing properties..." << std::endl;
    for (; prop_it != props.end(); ++prop_it) {
      std::cout << "Property: " << prop_it->key() << " " << prop_it->item() << std::endl;
    }
  }
  typename consumer_map_type::iterator it = consumers_.begin ();
  for (; it != consumers_.end(); ++it)
  {
    it->item()->configure_task(1, 0);    
    std::cout << "Configured " << it->key() << std::endl;
  }
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
void Servant_T <T, CONTEXT, EXECUTOR, POA_EXEC, SERVANT_BASE>::
connect_consumer (const char * name, Components::EventConsumerBase_ptr consumer)
{
  // Locate the endpoint for this consumer.
  publisher_type * publisher = 0;

  if (0 != this->emits_.find (name, publisher))
    throw ::Components::InvalidName ();

  ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("%T (%t) - %M - connecting consumer to <%s>\n"),
              name));

  // Now, signal the endpoint to connect.
  publisher->connect (consumer);

  ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("%T (%t) - %M - we are done making connection\n"),
              name,
              consumer->_interface_repository_id ()));
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
subscribe (const char * name, ::Components::EventConsumerBase_ptr consumer)
{
  ACE_DEBUG ((LM_DEBUG, "!!!!! subscribing !!!!!\n"));

  publisher_table_type * table = 0;

  if (0 != this->publishes_.find (name, table))
    throw ::Components::InvalidName ();

  return table->subscribe (consumer);
}

//
// unsubscribe
//
template <typename T, typename CONTEXT, typename EXECUTOR, typename POA_EXEC, typename SERVANT_BASE>
::Components::EventConsumerBase_ptr
Servant_T <T, CONTEXT, EXECUTOR, POA_EXEC, SERVANT_BASE>::
unsubscribe (const char * name, ::Components::Cookie * cookie)
{
  publisher_table_type * table = 0;

  if (0 != this->publishes_.find (name, table))
    throw ::Components::InvalidName ();

  return table->unsubscribe (cookie);
}

//
// connect
//
template <typename T, typename CONTEXT, typename EXECUTOR, typename POA_EXEC, typename SERVANT_BASE>
CUTS_INLINE
::Components::Cookie *
Servant_T <T, CONTEXT, EXECUTOR, POA_EXEC, SERVANT_BASE>::
connect (const char * name, ::CORBA::Object_ptr object_ptr)
{
  ::iCCM::Receptacle * rec;
  if (0 != this->receptacles_.find (name, rec))
    throw ::CORBA::INTERNAL ();
  return rec->connect (object_ptr);
}

//
// disconnect
//
template <typename T, typename CONTEXT, typename EXECUTOR, typename POA_EXEC, typename SERVANT_BASE>
CUTS_INLINE
::CORBA::Object_ptr
Servant_T <T, CONTEXT, EXECUTOR, POA_EXEC, SERVANT_BASE>::
disconnect (const char * name, ::Components::Cookie * c)
{
  ::iCCM::Receptacle * rec;
  if (0 != this->receptacles_.find (name, rec))
    throw ::CORBA::INTERNAL ();
  return rec->disconnect (c);
}

//
// provide_facet
//
template <typename T, typename CONTEXT, typename EXECUTOR, typename POA_EXEC, typename SERVANT_BASE>
CUTS_INLINE
::CORBA::Object_ptr
Servant_T <T, CONTEXT, EXECUTOR, POA_EXEC, SERVANT_BASE>::provide_facet (const char * name)
{
  facets_values_type value;
  if (0 != this->facets_.find (name, value))
    throw ::Components::InvalidName ();

  return ::CORBA::Object::_duplicate (value.first);
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
  typename consumer_map_type::ITERATOR iter (this->consumers_);

  for (; !iter.done (); ++ iter)
  {
    try
    {
      // Locate the object id for this servant.
      oid = this->port_POA_->servant_to_id (iter->item ());
      this->port_POA_->deactivate_object (oid.in ());
    }
    catch (const ::PortableServer::POA::ServantNotActive &)
    {
      // Ingore this exception.
    }

    // Passivate the EventConsumer
    iter->item ()->passivate ();
  }

  // Passivate the Publisher_Tables
  typename publishes_map_type::ITERATOR pub_iter (this->publishes_);
  for (; !pub_iter.done (); ++ pub_iter)
    pub_iter->item ()->passivate ();

  // Passivate the Publishers
  typename emits_map_type::ITERATOR emit_iter (this->emits_);
  for (; !emit_iter.done (); ++ emit_iter)
    emit_iter->item ()->passivate ();
}

//
// activate_ports
//
template <typename T, typename CONTEXT, typename EXECUTOR, typename POA_EXEC, typename SERVANT_BASE>
void Servant_T <T, CONTEXT, EXECUTOR, POA_EXEC, SERVANT_BASE>::
activate_ports (void)
{
  ::PortableServer::ObjectId_var oid;
  typename consumer_map_type::ITERATOR iter (this->consumers_);

  for (; !iter.done (); ++ iter)
  {
    try
    {
      // Locate the object id for this servant.
      oid = ::PortableServer::string_to_ObjectId (iter->key ().c_str ());
      this->port_POA_->activate_object_with_id (oid.in (), iter->item ());
    }
    catch (const ::PortableServer::POA::ServantAlreadyActive &)
    {
      // Ingore this exception.
    }
    catch (const ::PortableServer::POA::ObjectAlreadyActive &)
    {
      // Ignore this exception.
    }

    // Activate the EventConsumer
    iter->item ()->activate ();
  }

  // Activate the Publisher_Tables
  typename publishes_map_type::ITERATOR pub_iter (this->publishes_);
  for (; !pub_iter.done (); ++ pub_iter)
    pub_iter->item ()->activate ();

  // Activate the Publishers
  typename emits_map_type::ITERATOR emit_iter (this->emits_);
  for (; !emit_iter.done (); ++ emit_iter)
    emit_iter->item ()->activate ();
}

template <typename T, typename CONTEXT, typename EXECUTOR, typename POA_EXEC, typename SERVANT_BASE>
int Servant_T <T, CONTEXT, EXECUTOR, POA_EXEC, SERVANT_BASE>::
get_publisher (const char * name, Publisher * & publisher)
{
  typename SERVANT_BASE::publisher_type * pt = 0;

  if (0 != this->emits_.find (name, pt))
    return -1;

  publisher = pt;
  return 0;
}

template <typename T, typename CONTEXT, typename EXECUTOR, typename POA_EXEC, typename SERVANT_BASE>
int Servant_T <T, CONTEXT, EXECUTOR, POA_EXEC, SERVANT_BASE>::
get_publisher_table (const char * name, Publisher_Table * & table)
{
  typename SERVANT_BASE::publisher_table_type * tmp = 0;

  if (0 != this->publishes_.find (name, tmp))
    return -1;

  table = tmp;
  return 0;
}

template <typename T, typename CONTEXT, typename EXECUTOR, typename POA_EXEC, typename SERVANT_BASE>
int Servant_T <T, CONTEXT, EXECUTOR, POA_EXEC, SERVANT_BASE>::
get_event_consumer (const char * name, EventConsumer * & consumer)
{
  typename SERVANT_BASE::eventconsumer_type * tmp = 0;

  if (0 != this->consumers_.find (name, tmp))
    return -1;

  consumer = tmp;
  return 0;
}

template <typename EXECUTOR, typename SERVANT>
::PortableServer::Servant
create_servant (const char * name,
                ::PortableServer::POA_ptr port_POA,
                ::Components::EnterpriseComponent_ptr p)
{
  // First, convert the pointer to its concrete type.
  typename EXECUTOR::_var_type executor = EXECUTOR::_narrow (p);
  SERVANT * servant = 0;

  ACE_NEW_RETURN (servant,
                  SERVANT (name, port_POA, executor.in ()),
                  0);

  return servant;
}

}
