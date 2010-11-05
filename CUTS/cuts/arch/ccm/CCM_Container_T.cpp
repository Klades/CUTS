// $Id$

#include "CCM_Container_T.h"

#if !defined (__CUTS_INLINE__)
#include "CCM_Container_T.inl"
#endif

#include "ace/UUID.h"
#include <sstream>

//
// ~CUTS_CCM_Container_T
//
template <typename T, typename SERVER, typename STRATEGY, typename SERVANT_BASE>
CUTS_CCM_Container_T <T, SERVER, STRATEGY, SERVANT_BASE>::~CUTS_CCM_Container_T (void)
{
  if (!::CORBA::is_nil (this->poa_.in ()))
    this->poa_->destroy (1, 1);

  if (!::CORBA::is_nil (this->port_poa_.in ()))
    this->poa_->destroy (1, 1);
}

//
// CUTS_CCM_Container_T
//
template <typename T, typename SERVER, typename STRATEGY, typename SERVANT_BASE>
CUTS_INLINE
CUTS_CCM_Container_T <T, SERVER, STRATEGY, SERVANT_BASE>::
CUTS_CCM_Container_T (SERVER * server, ::PortableServer::POA_ptr poa)
: server_ (server)
{
  this->initialize_the_POA (poa);
  this->initialize_the_port_POA (poa);

  // Create the strategy for the container.
  STRATEGY * strategy = 0;
  T * self = reinterpret_cast <T *> (this);

  ACE_NEW_THROW_EX (strategy,
                    STRATEGY (*self),
                    ::CORBA::NO_MEMORY ());

  this->strategy_.reset (strategy);
}

//
// configuration
//
template <typename T, typename SERVER, typename STRATEGY, typename SERVANT_BASE>
Components::ConfigValues *
CUTS_CCM_Container_T <T, SERVER, STRATEGY, SERVANT_BASE>::configuration (void)
{
  ACE_ERROR ((LM_ERROR,
              ACE_TEXT ("%T - %M - configuration ()\n")));

  throw CORBA::NO_IMPLEMENT ();
}

//
// get_component_server
//
template <typename T, typename SERVER, typename STRATEGY, typename SERVANT_BASE>
::Components::Deployment::ComponentServer_ptr
CUTS_CCM_Container_T <T, SERVER, STRATEGY, SERVANT_BASE>::get_component_server (void)
{
  ACE_ERROR ((LM_DEBUG,
              ACE_TEXT ("get_component_server (void)\n")));

  throw CORBA::NO_IMPLEMENT ();
}

//
// install_home
//
template <typename T, typename SERVER, typename STRATEGY, typename SERVANT_BASE>
::Components::CCMHome_ptr CUTS_CCM_Container_T <T, SERVER, STRATEGY, SERVANT_BASE>::
install_home (const char * primary_artifact,
              const char * entry_point,
              const char * servant_artifact,
              const char * servant_entrypoint,
              const char * name)
{
  ACE_ERROR ((LM_DEBUG,
              ACE_TEXT ("install_home ()\n")));

  throw CORBA::NO_IMPLEMENT ();
}

//
// remove_home
//
template <typename T, typename SERVER, typename STRATEGY, typename SERVANT_BASE>
void CUTS_CCM_Container_T <T, SERVER, STRATEGY, SERVANT_BASE>::
uninstall_home (::Components::CCMHome_ptr)
{
  ACE_ERROR ((LM_ERROR,
              ACE_TEXT ("remove_home (::Components::CCMHome_ptr)")));

  throw CORBA::NO_IMPLEMENT ();
}

//
// get_homes
//
template <typename T, typename SERVER, typename STRATEGY, typename SERVANT_BASE>
Components::CCMHomes * CUTS_CCM_Container_T <T, SERVER, STRATEGY, SERVANT_BASE>::get_homes (void)
{
  ACE_ERROR ((LM_DEBUG,
              ACE_TEXT ("get_homes (void)\n")));

  throw CORBA::NO_IMPLEMENT ();
}

//
// remove
//
template <typename T, typename SERVER, typename STRATEGY, typename SERVANT_BASE>
void CUTS_CCM_Container_T <T, SERVER, STRATEGY, SERVANT_BASE>::remove (void)
{
  ACE_ERROR ((LM_DEBUG,
              ACE_TEXT ("%T (%t) - %M - removing all components in the container\n")));

  servant_map::ITERATOR iter (this->components_);

  for (; !iter.done (); ++ iter)
  {
    SERVANT_BASE * servant = dynamic_cast <SERVANT_BASE *> (iter->item ().in ());

    if (0 == servant)
      continue;

    servant->passivate_component ();

    // Notify the strategy of the servant's removal.
    this->strategy_->remove_servant (servant);
    servant->remove ();
  }

  // Remove all components from the collection.
  this->components_.unbind_all ();
}

//
// install_component
//
template <typename T, typename SERVER, typename STRATEGY, typename SERVANT_BASE>
::Components::CCMObject_ptr CUTS_CCM_Container_T <T, SERVER, STRATEGY, SERVANT_BASE>::
install_component (const char * primary_artifact,
                   const char * entry_point,
                   const char * servant_artifact,
                   const char * servant_entrypoint,
                   const char * name)
{
  ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("%T (%t) - %M - installing %s\n"),
              name));

  // Load the executor from its shared library.
  ::Components::EnterpriseComponent_var executor =
    this->strategy_->load_executor (primary_artifact, entry_point);

  if (::CORBA::is_nil (executor.in ()))
    throw ::Components::CreateFailure ();

  // Load the servant from its shared library.
  PortableServer::Servant servant =
    this->strategy_->load_servant (name,
                                   servant_artifact,
                                   servant_entrypoint,
                                   executor.in ());

  if (::CORBA::is_nil (servant))
    throw ::Components::CreateFailure ();

  ::PortableServer::ServantBase_var safe_servant (servant);

  ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("%T (%t) - %M - activating the component's servant\n")));

  ::PortableServer::ObjectId_var oid = ::PortableServer::string_to_ObjectId (name);
  this->poa_->activate_object_with_id (oid.in (), servant);

  if (0 != this->strategy_.get ())
    this->strategy_->install_servant (servant);

  // Get a reference for to the servant.
  ::CORBA::Object_var obj = this->poa_->id_to_reference (oid.in ());
  return ::Components::CCMObject::_narrow (obj.in ());
}

//
// activate_component
//
template <typename T, typename SERVER, typename STRATEGY, typename SERVANT_BASE>
void CUTS_CCM_Container_T <T, SERVER, STRATEGY, SERVANT_BASE>::
activate_component (::Components::CCMObject_ptr ref)
{
  // Locate the id of this reference.
  ::PortableServer::ObjectId_var oid = this->poa_->reference_to_id (ref);
  ::CORBA::String_var idstr = ::PortableServer::ObjectId_to_string (oid.in ());

  ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("%T (%t) - %M - activating component %s\n"),
              idstr.in ()));

  // Also, get the servant for this reference.
  ::PortableServer::ServantBase_var base = this->poa_->id_to_servant (oid.in ());
  SERVANT_BASE * servant = dynamic_cast <SERVANT_BASE *> (base.in ());

  if (0 == servant)
    throw ::CIAO::InvalidComponent ();

  servant->activate_component ();
}

//
// passivate_component
//
template <typename T, typename SERVER, typename STRATEGY, typename SERVANT_BASE>
void CUTS_CCM_Container_T <T, SERVER, STRATEGY, SERVANT_BASE>::
passivate_component (::Components::CCMObject_ptr ref)
{
  // Locate the id of this reference.
  ::PortableServer::ObjectId_var oid = this->poa_->reference_to_id (ref);
  ::CORBA::String_var idstr = ::PortableServer::ObjectId_to_string (oid.in ());

  ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("%T (%t) - %M - passivating component %s\n"),
              idstr.in ()));

  // Also, get the servant for this reference.
  ::PortableServer::ServantBase_var base = this->poa_->id_to_servant (oid.in ());
  SERVANT_BASE * servant = dynamic_cast <SERVANT_BASE *> (base.in ());

  if (0 == servant)
    throw ::CIAO::InvalidComponent ();

  servant->passivate_component ();
}

//
// uninstall_component
//
template <typename T, typename SERVER, typename STRATEGY, typename SERVANT_BASE>
void CUTS_CCM_Container_T <T, SERVER, STRATEGY, SERVANT_BASE>::
uninstall_component (::Components::CCMObject_ptr ref)
{
  // Locate the id of this reference.
  ::PortableServer::ObjectId_var oid = this->poa_->reference_to_id (ref);
  ::CORBA::String_var idstr = ::PortableServer::ObjectId_to_string (oid.in ());

  ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("%T (%t) - %M - uninstalling component %s\n"),
              idstr.in ()));

  // Also, get the servant for this reference.
  ::PortableServer::ServantBase_var base = this->poa_->id_to_servant (oid.in ());
  SERVANT_BASE * servant = dynamic_cast <SERVANT_BASE *> (base.in ());

  if (0 == servant)
    throw ::CIAO::InvalidComponent ();

  servant->remove ();

  // Uninstall the domain-specific servant.
  if (0 != this->strategy_.get ())
    this->strategy_->remove_servant (servant);

  // Finally, deactivate the object within the POA.
  this->poa_->deactivate_object (oid.in ());
}

//
// get_components
//
template <typename T, typename SERVER, typename STRATEGY, typename SERVANT_BASE>
::Components::CCMObjectSeq *
CUTS_CCM_Container_T <T, SERVER, STRATEGY, SERVANT_BASE>::get_components (void)
{
  ACE_ERROR ((LM_ERROR,
              ACE_TEXT ("get_components (void)\n")));

  throw ::CORBA::NO_IMPLEMENT ();
}

//
// set_attributes
//
template <typename T, typename SERVER, typename STRATEGY, typename SERVANT_BASE>
void CUTS_CCM_Container_T <T, SERVER, STRATEGY, SERVANT_BASE>::
set_attributes (::CORBA::Object_ptr ref,
                const ::Components::ConfigValues & values)
{
  // Locate the id of this reference.
  ::PortableServer::ObjectId_var oid = this->poa_->reference_to_id (ref);
  ::CORBA::String_var idstr = ::PortableServer::ObjectId_to_string (oid.in ());

  // Also, get the servant for this reference.
  ::PortableServer::ServantBase_var base = this->poa_->id_to_servant (oid.in ());
  SERVANT_BASE * servant = dynamic_cast <SERVANT_BASE *> (base.in ());

  ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("%T (%t) - %M - setting attributes for %s\n"),
              idstr.in ()));

  servant->set_attributes (values);
}

//
// install_servant
//
template <typename T, typename SERVER, typename STRATEGY, typename SERVANT_BASE>
::CORBA::Object_ptr
CUTS_CCM_Container_T <T, SERVER, STRATEGY, SERVANT_BASE>::
install_servant (::PortableServer::Servant svnt,
                 ::CIAO::Container_Types::OA_Type type,
                 ::PortableServer::ObjectId_out oid)
{
  ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("install_servant ()\n")));

  throw ::CORBA::NO_IMPLEMENT ();
}

//
// uninstall_servant
//
template <typename T, typename SERVER, typename STRATEGY, typename SERVANT_BASE>
void CUTS_CCM_Container_T <T, SERVER, STRATEGY, SERVANT_BASE>::
uninstall_servant (::PortableServer::Servant compptr,
                   ::CIAO::Container_Types::OA_Type type,
                   ::PortableServer::ObjectId_out oid)
{
  throw ::CORBA::NO_IMPLEMENT ();
}

//
// ports_servant_activator
//
template <typename T, typename SERVER, typename STRATEGY, typename SERVANT_BASE>
::CIAO::Servant_Activator_ptr
CUTS_CCM_Container_T <T, SERVER, STRATEGY, SERVANT_BASE>::
ports_servant_activator (void)
{
  ACE_ERROR ((LM_ERROR,
              ACE_TEXT ("%T - %M - ports_servant_activator (...)\n")));

  throw ::CORBA::NO_IMPLEMENT ();
}

//
// generate_reference
//
template <typename T, typename SERVER, typename STRATEGY, typename SERVANT_BASE>
::CORBA::Object_ptr
CUTS_CCM_Container_T <T, SERVER, STRATEGY, SERVANT_BASE>::
generate_reference (const char * obj_id,
                    const char * repo_id,
                    ::CIAO::Container_Types::OA_Type type)
{
  ::PortableServer::ObjectId_var oid = ::PortableServer::string_to_ObjectId (obj_id);

  switch (type)
  {
  case ::CIAO::Container_Types::COMPONENT_t:
    return this->poa_->id_to_reference (oid);
    break;

  case ::CIAO::Container_Types::FACET_CONSUMER_t:
    return this->port_poa_->id_to_reference (oid);
    break;

  default:
    throw ::CIAO::InvalidComponent ();
  }
}

//
// get_objref
//
template <typename T, typename SERVER, typename STRATEGY, typename SERVANT_BASE>
::CORBA::Object_ptr
CUTS_CCM_Container_T <T, SERVER, STRATEGY, SERVANT_BASE>::
get_objref (::PortableServer::Servant p)
{
  ACE_ERROR ((LM_ERROR,
              ACE_TEXT ("%T - %M - generate_reference (...)\n")));

  throw ::CORBA::NO_IMPLEMENT ();
}

//
// the_POA
//
template <typename T, typename SERVER, typename STRATEGY, typename SERVANT_BASE>
::PortableServer::POA_ptr
CUTS_CCM_Container_T <T, SERVER, STRATEGY, SERVANT_BASE>::the_POA (void)
{
  return ::PortableServer::POA::_duplicate (this->poa_.in ());
}

//
// the_port_POA
//
template <typename T, typename SERVER, typename STRATEGY, typename SERVANT_BASE>
::PortableServer::POA_ptr
CUTS_CCM_Container_T <T, SERVER, STRATEGY, SERVANT_BASE>::the_port_POA (void)
{
  return ::PortableServer::POA::_duplicate (this->port_poa_.in ());
}

//
// resolve_service_reference
//
template <typename T, typename SERVER, typename STRATEGY, typename SERVANT_BASE>
::CORBA::Object_ptr
CUTS_CCM_Container_T <T, SERVER, STRATEGY, SERVANT_BASE>::
resolve_service_reference (const char * service_id)
{
  ACE_ERROR ((LM_ERROR,
              ACE_TEXT ("%T (%t) - %M - resolve_service_reference (...)\n")));

  throw ::CORBA::NO_IMPLEMENT ();
}

//
// initialize_to_POA
//
template <typename T, typename SERVER, typename STRATEGY, typename SERVANT_BASE>
void CUTS_CCM_Container_T <T, SERVER, STRATEGY, SERVANT_BASE>::
initialize_the_POA (::PortableServer::POA_ptr poa)
{
  using ACE_Utils::UUID_GENERATOR;
  ACE_Utils::UUID uuid;

  // Generate the unique id for the container POA.
  UUID_GENERATOR::instance ()->generate_UUID (uuid);
  std::ostringstream strid;
  strid << "ContainerPOA-" << *uuid.to_string ();

  ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("%T (%t) - %M - initializing the container POA (%s)\n"),
              strid.str ().c_str ()));

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
  this->poa_ = poa->create_POA (strid.str ().c_str (),
                                ::PortableServer::POAManager::_nil (),
                                policies);

  // Activate the POA manager.
  ::PortableServer::POAManager_var mgr = this->poa_->the_POAManager ();
  mgr->activate ();

  // Destroy the POA policies
  for (::CORBA::ULong i = 0; i < policies.length (); ++ i)
    policies[i]->destroy ();
}

//
// initialize_to_port_POA
//
template <typename T, typename SERVER, typename STRATEGY, typename SERVANT_BASE>
void CUTS_CCM_Container_T <T, SERVER, STRATEGY, SERVANT_BASE>::
initialize_the_port_POA (::PortableServer::POA_ptr poa)
{
  using ACE_Utils::UUID_GENERATOR;
  ACE_Utils::UUID uuid;

  // Generate the unique id for the container POA.
  UUID_GENERATOR::instance ()->generate_UUID (uuid);
  std::ostringstream strid;
  strid << "PortPOA-" << *uuid.to_string ();

  ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("%T (%t) - %M - initializing the container port POA (%s)\n"),
              strid.str ().c_str ()));

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
  this->port_poa_ = poa->create_POA (strid.str ().c_str (),
                                     ::PortableServer::POAManager::_nil (),
                                     policies);

  // Activate the POA manager.
  ::PortableServer::POAManager_var mgr = this->port_poa_->the_POAManager ();
  mgr->activate ();

  // Destroy the POA policies
  for (::CORBA::ULong i = 0; i < policies.length (); ++ i)
    policies[i]->destroy ();
}
