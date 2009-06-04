// $Id$

#include "CCM_Container_T.h"

#if !defined (__CUTS_INLINE__)
#include "CCM_Container_T.inl"
#endif

#include "ace/OS_NS_unistd.h"

/**
 * @struct config_name_equals
 *
 * Functor that determines the equality of a configuration name.
 */
struct config_name_equals
{
  /**
   * Initializing consturctor
   *
   * @param[in]         name          Name to search for.
   */
  config_name_equals (const char * name)
    : name_ (name)
  {

  }

  bool operator () (const ::Components::ConfigValue * cv) const
  {
    return 0 == ACE_OS::strcmp (this->name_, cv->name ());
  }

private:
  /// Target configuration name.
  const char * name_;
};

//
// CUTS_CCM_Container_T
//
template <typename CONTAINER, typename STRATEGY, typename SERVANT_BASE>
CUTS_INLINE
CUTS_CCM_Container_T <CONTAINER, STRATEGY, SERVANT_BASE>::
CUTS_CCM_Container_T (CONTAINER * container,
                      const Components::ConfigValues & config,
                      ::PortableServer::POA_ptr poa,
                      ::Components::Deployment::ComponentInstallation_ptr installer)
: container_ (container),
  poa_ (::PortableServer::POA::_duplicate (poa)),
  installer_ (::Components::Deployment::ComponentInstallation::_duplicate (installer))
{
  // Create the strategy for the container.
  STRATEGY * strategy = 0;

  ACE_NEW_THROW_EX (strategy,
                    STRATEGY (this->container_),
                    ::CORBA::NO_MEMORY ());

  this->strategy_.reset (strategy);

  // Save the configuration.
  ::Components::ConfigValues * temp = 0;
  CORBA::ULong length = config.length ();

  ACE_NEW_THROW_EX (temp,
                    ::Components::ConfigValues (length),
                    ::CORBA::NO_MEMORY ());

  this->config_ = temp;
  this->copy (this->config_, config);
}

//
// copy
//
template <typename CONTAINER, typename STRATEGY, typename SERVANT_BASE>
void CUTS_CCM_Container_T <CONTAINER, STRATEGY, SERVANT_BASE>::
copy (::Components::ConfigValues & dst,
      const ::Components::ConfigValues & src)
{
  CORBA::ULong length = src.length ();
  dst.length (length);

  for (CORBA::ULong i = 0; i < length; ++ i)
  {
    dst[i]->name (src[i]->name ());
    dst[i]->value (src[i]->value ());
  }
}

//
// configuration
//
template <typename CONTAINER, typename STRATEGY, typename SERVANT_BASE>
Components::ConfigValues *
CUTS_CCM_Container_T <CONTAINER, STRATEGY, SERVANT_BASE>::configuration (void)
{
  ::Components::ConfigValues * temp = 0;
  CORBA::ULong length = this->config_->length ();

  ACE_NEW_THROW_EX (temp,
                    ::Components::ConfigValues (length),
                    ::CORBA::NO_MEMORY ());

  ::Components::ConfigValues_var config = temp;
  this->copy (*temp, this->config_);

  return config._retn ();
}

//
// get_component_server
//
template <typename CONTAINER, typename STRATEGY, typename SERVANT_BASE>
::Components::Deployment::ComponentServer_ptr
CUTS_CCM_Container_T <CONTAINER, STRATEGY, SERVANT_BASE>::get_component_server (void)
{
  ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("get_component_server (void)\n")));

  throw CORBA::NO_IMPLEMENT ();
}

//
// install_home
//
template <typename CONTAINER, typename STRATEGY, typename SERVANT_BASE>
::Components::CCMHome_ptr CUTS_CCM_Container_T <CONTAINER, STRATEGY, SERVANT_BASE>::
install_home (const char * , const char * , const ::Components::ConfigValues & )
{
  ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("install_home (const char * , const char * , ")
              ACE_TEXT ("const ::Components::ConfigValues & )\n")));

  throw CORBA::NO_IMPLEMENT ();
}

//
// remove_home
//
template <typename CONTAINER, typename STRATEGY, typename SERVANT_BASE>
void CUTS_CCM_Container_T <CONTAINER, STRATEGY, SERVANT_BASE>::remove_home (::Components::CCMHome_ptr)
{
  ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("remove_home (::Components::CCMHome_ptr)")));

  throw CORBA::NO_IMPLEMENT ();
}

//
// get_homes
//
template <typename CONTAINER, typename STRATEGY, typename SERVANT_BASE>
Components::CCMHomes * CUTS_CCM_Container_T <CONTAINER, STRATEGY, SERVANT_BASE>::get_homes (void)
{
  ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("get_homes (void)\n")));

  throw CORBA::NO_IMPLEMENT ();
}

//
// remove
//
template <typename CONTAINER, typename STRATEGY, typename SERVANT_BASE>
void CUTS_CCM_Container_T <CONTAINER, STRATEGY, SERVANT_BASE>::remove (void)
{
  ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("%T (%t) - %M - removing all components in the container\n")));

  components_type::ITERATOR iter (this->components_);

  for (; !iter.done (); ++ iter)
  {
    SERVANT_BASE * servant = dynamic_cast <SERVANT_BASE *> (iter->item ().in ());

    if (0 == servant)
      continue;

    servant->passivate_component ();
    servant->remove ();
  }

  // Remove all components from the collection.
  this->components_.unbind_all ();
}

//
// install_component
//
template <typename CONTAINER, typename STRATEGY, typename SERVANT_BASE>
::Components::CCMObject_ptr CUTS_CCM_Container_T <CONTAINER, STRATEGY, SERVANT_BASE>::
install_component (const char * id,
                   const char * entrypt,
                   const ::Components::ConfigValues & config)
{
  ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("%T (%t) - %M - installing <%s> with entrypoint <%s>\n"),
              id,
              entrypt));

  ::Components::ConfigValues::const_value_type
    * iter = config.get_buffer (),
    * iter_end = iter + config.length ();

  // Locate the configuration value for the executor artifact.
  ::Components::ConfigValues::const_value_type * exec_artifact =
    std::find_if (iter,
                  iter_end,
                  config_name_equals (ACE_TEXT ("edu.vanderbilt.dre.CIAO.ExecutorArtifact")));

  if (exec_artifact == iter_end)
  {
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - failed to locate executor artifact\n")));

    throw ::Components::Deployment::InvalidConfiguration ();
  }

  // Locate the configuration value for the servant artifact.
  ::Components::ConfigValues::const_value_type * svnt_artifact =
    std::find_if (iter,
                  iter_end,
                  config_name_equals (ACE_TEXT ("edu.vanderbilt.dre.CIAO.ServantArtifact")));

  if (svnt_artifact == iter_end)
  {
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - failed to locate servant artifact\n")));

    throw ::Components::Deployment::InvalidConfiguration ();
  }

  // Locate the configuration value for the servant entrypoint.
  ::Components::ConfigValues::const_value_type * svnt_entrypt =
    std::find_if (iter,
                  iter_end,
                  config_name_equals (ACE_TEXT ("edu.vanderbilt.dre.CIAO.ServantEntrypoint")));

  if (svnt_entrypt == iter_end)
  {
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - failed to locate servant entry point\n")));

    throw ::Components::Deployment::InvalidConfiguration ();
  }

  // Load the executor from its shared library.
  ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("%T - %M - loading the component's implementation\n")));

  const char * temp_str;
  (*exec_artifact)->value () >>= temp_str;
  ::Components::Deployment::UUID_var exec_uuid = temp_str;

  ::Components::Deployment::Location_var location =
    this->installer_->get_implementation (exec_uuid.in ());

  ::Components::EnterpriseComponent_var executor =
    this->strategy_->load_executor (location.in (), entrypt);

  if (::CORBA::is_nil (executor.in ()))
    throw ::Components::CreateFailure ();

  // Load the servant from its shared library.
  ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("%T - %M - loading the component's servant\n")));

  (*svnt_artifact)->value () >>= temp_str;
  ::Components::Deployment::UUID_var svnt_uuid = temp_str;

  location = this->installer_->get_implementation (svnt_uuid.in ());

  (*svnt_entrypt)->value () >>= temp_str;
  ::CORBA::String_var svnt_entrypt_str = temp_str;

  ::PortableServer::ServantBase_var servant =
    this->strategy_->load_servant (id,
                                   location.in (),
                                   svnt_entrypt_str.in (),
                                   executor.in ());

  // Activate the servant under the provided POA.
  PortableServer::ObjectId_var oid = this->poa_->activate_object (servant.in ());
  this->components_.bind (id, servant);

  // Get a reference for to the servant.
  ::CORBA::Object_var obj = this->poa_->id_to_reference (oid.in ());
  ::Components::CCMObject_var component = ::Components::CCMObject::_narrow (obj.in ());

  return component._retn ();
}

//
// activate_component
//
template <typename CONTAINER, typename STRATEGY, typename SERVANT_BASE>
void CUTS_CCM_Container_T <CONTAINER, STRATEGY, SERVANT_BASE>::
activate_component (::Components::CCMObject_ptr comp)
{
  // Locate the servant for the object reference.
  ::PortableServer::ServantBase_var base = this->poa_->reference_to_servant (comp);
  SERVANT_BASE * servant = dynamic_cast <SERVANT_BASE *> (base.in ());

  if (0 == servant)
    throw ::CORBA::INTERNAL ();

  // Activate the component.
  ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("%T (%t) - %M - activating %s\n"),
              servant->name ().c_str ()));

  servant->activate_component ();
}

//
// passivate_component
//
template <typename CONTAINER, typename STRATEGY, typename SERVANT_BASE>
void CUTS_CCM_Container_T <CONTAINER, STRATEGY, SERVANT_BASE>::passivate_component (::Components::CCMObject_ptr comp)
{
  // Locate the servant for the object reference.
  PortableServer::ServantBase_var base = this->poa_->reference_to_servant (comp);
  SERVANT_BASE * servant = dynamic_cast <SERVANT_BASE *> (base.in ());

  if (0 == servant)
    throw ::CORBA::INTERNAL ();

  // Passivate the component.
  ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("%T (%t) - %M - passivating %s\n"),
              servant->name ().c_str ()));

  servant->passivate_component ();
}

//
// remove_component
//
template <typename CONTAINER, typename STRATEGY, typename SERVANT_BASE>
void CUTS_CCM_Container_T <CONTAINER, STRATEGY, SERVANT_BASE>::remove_component (::Components::CCMObject_ptr cref)
{
  // Locate the servant for the object reference.
  PortableServer::ServantBase_var base = this->poa_->reference_to_servant (cref);
  SERVANT_BASE * servant = dynamic_cast <SERVANT_BASE *> (base.in ());

  if (0 == servant)
    throw ::CORBA::INTERNAL ();

  // Signal the component that is about to be removed.
  ACE_DEBUG ((LM_DEBUG,
            ACE_TEXT ("%T (%t) - %M - removing %s\n"),
            servant->name ().c_str ()));

  servant->remove ();

  // Remove the component from the collection.
  this->components_.unbind (servant->name ());

  // Deactivate the component.
  PortableServer::ObjectId_var oid = this->poa_->servant_to_id (base.in ());
  this->poa_->deactivate_object (oid.in ());
}

//
// get_components
//
template <typename CONTAINER, typename STRATEGY, typename SERVANT_BASE>
::Components::CCMObjectSeq *
CUTS_CCM_Container_T <CONTAINER, STRATEGY, SERVANT_BASE>::get_components (void)
{
  ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("get_components (void)\n")));

  throw ::CORBA::NO_IMPLEMENT ();
}
