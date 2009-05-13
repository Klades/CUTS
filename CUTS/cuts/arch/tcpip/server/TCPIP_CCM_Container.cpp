// $Id$

#include "TCPIP_CCM_Container.h"

#if !defined (__CUTS_INLINE__)
#include "TCPIP_CCM_Container.inl"
#endif

#include "TCPIP_CCM_ComponentServer.h"
#include "cuts/arch/tcpip/ccm/TCPIP_CCM_Servant.h"
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
// init
//
void CUTS_TCPIP_CCM_Container::init (const Components::ConfigValues & config)
{
  ::Components::ConfigValues * temp = 0;
  CORBA::ULong length = config.length ();

  ACE_NEW_THROW_EX (temp,
                    ::Components::ConfigValues (length),
                    ::CORBA::NO_MEMORY ());

  this->config_ = temp;

  // Copy the configuration.
  this->copy (this->config_, config);
}

//
// copy
//
void CUTS_TCPIP_CCM_Container::
copy (::Components::ConfigValues & dst, const ::Components::ConfigValues & src)
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
Components::ConfigValues * CUTS_TCPIP_CCM_Container::configuration (void)
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
::Components::Deployment::ComponentServer_ptr
CUTS_TCPIP_CCM_Container::get_component_server (void)
{
  throw CORBA::NO_IMPLEMENT ();
}

//
// install_home
//
::Components::CCMHome_ptr CUTS_TCPIP_CCM_Container::
install_home (const char * id, const char * entry, const ::Components::ConfigValues & config)
{
  throw CORBA::NO_IMPLEMENT ();
}

//
// remove_home
//
void CUTS_TCPIP_CCM_Container::remove_home (::Components::CCMHome_ptr home)
{
  throw CORBA::NO_IMPLEMENT ();
}

//
// get_homes
//
Components::CCMHomes * CUTS_TCPIP_CCM_Container::get_homes (void)
{
  throw CORBA::NO_IMPLEMENT ();
}

//
// remove
//
void CUTS_TCPIP_CCM_Container::remove (void)
{
  ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("%T (%t) - %M - removing all components in the container\n")));

  components_type::ITERATOR iter (this->components_);

  for (; !iter.done (); ++ iter)
  {
    CUTS_TCPIP_CCM_Servant * servant =
      dynamic_cast <CUTS_TCPIP_CCM_Servant *> (iter->item ().in ());

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
::Components::CCMObject_ptr CUTS_TCPIP_CCM_Container::
install_component (const char * id,
                   const char * entrypt,
                   const ::Components::ConfigValues & config)
{
  ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("%T (%t) - %M - installing <%s> from <%s>\n"),
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
  ::Components::EnterpriseComponent_var executor =
    this->load_executor (*(*exec_artifact), entrypt);

  if (::CORBA::is_nil (executor.in ()))
    throw ::Components::CreateFailure ();

  // Load the servant from its shared library.
  ::PortableServer::ServantBase_var servant =
    this->load_servant (id, *(*svnt_artifact), *(*svnt_entrypt), executor.in ());

  this->components_.bind (id, servant);

  // Activate the servant under the provided POA.
  PortableServer::ObjectId_var oid = this->poa_->activate_object (servant.in ());

  // Get a reference for to the servant.
  ::CORBA::Object_var obj = this->poa_->id_to_reference (oid.in ());
  ::Components::CCMObject_var component = ::Components::CCMObject::_narrow (obj.in ());

  return component._retn ();
}

//
// load_executor
//
::Components::EnterpriseComponent_ptr
CUTS_TCPIP_CCM_Container::
load_executor (const ::Components::ConfigValue & artifact, const char * entrypt)
{
  // Load the executor from its shared library.
  ACE_DLL module;

  const char * exec_module = 0;
  artifact.value () >>= exec_module;

  if (0 != module.open (exec_module, ACE_DEFAULT_SHLIB_MODE, false))
  {
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - %m\n")));

    throw ::Components::Deployment::InvalidConfiguration ();
  }

  // Load the symbol from the library.
  void * symbol = module.symbol (entrypt);

  if (0 == symbol)
    throw ::Components::Deployment::ImplEntryPointNotFound ();

  // Load the executor from the executor artifact.
  typedef ::Components::EnterpriseComponent_ptr (*ExecutorFactoryMethod) (void);
  ptrdiff_t tmp_ptr = reinterpret_cast <ptrdiff_t> (symbol);
  ExecutorFactoryMethod factory_method = reinterpret_cast <ExecutorFactoryMethod> (tmp_ptr);

  return factory_method ();
}

//
// load_servant
//
::PortableServer::Servant
CUTS_TCPIP_CCM_Container::load_servant (const char * name,
                                        const ::Components::ConfigValue & artifact,
                                        const ::Components::ConfigValue & entrypt,
                                        ::Components::EnterpriseComponent_ptr executor)
{
  const char * svnt_module = 0;
  artifact.value () >>= svnt_module;

  const char * svnt_entrypt_symbol = 0;
  entrypt.value () >>= svnt_entrypt_symbol;

  // Load the servant from its shared library.
  ACE_DLL module;

  if (0 != module.open (svnt_module, ACE_DEFAULT_SHLIB_MODE, false))
  {
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - %m\n")));

    throw ::Components::Deployment::InvalidConfiguration ();
  }

  // Load the symbol from the library.
  void * symbol = module.symbol (svnt_entrypt_symbol);

  if (0 == symbol)
    throw ::Components::Deployment::ImplEntryPointNotFound ();

  // Load the executor from the executor artifact.
  typedef ::PortableServer::Servant (*ServantFactoryMethod)
    (const char *, CUTS_TCPIP_Servant_Manager *, ::Components::EnterpriseComponent_ptr);

  ptrdiff_t tmp_ptr = reinterpret_cast <ptrdiff_t> (symbol);
  ServantFactoryMethod factory_method = reinterpret_cast <ServantFactoryMethod> (tmp_ptr);

  return factory_method (name, &this->parent_.the_ORB ().the_OM (), executor);
}

//
// activate_component
//
void CUTS_TCPIP_CCM_Container::activate_component (::Components::CCMObject_ptr comp)
{
  // Locate the servant for the object reference.
  PortableServer::ServantBase_var base = this->poa_->reference_to_servant (comp);

  // Convert the servant to a CCM servant object.
  CUTS_TCPIP_CCM_Servant * servant =
    dynamic_cast <CUTS_TCPIP_CCM_Servant *> (base.in ());

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
void CUTS_TCPIP_CCM_Container::passivate_component (::Components::CCMObject_ptr comp)
{
  // Locate the servant for the object reference.
  PortableServer::ServantBase_var base = this->poa_->reference_to_servant (comp);

  // Convert the servant to a CCM servant object.
  CUTS_TCPIP_CCM_Servant * servant =
    dynamic_cast <CUTS_TCPIP_CCM_Servant *> (base.in ());

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
void CUTS_TCPIP_CCM_Container::remove_component (::Components::CCMObject_ptr cref)
{
  // Locate the servant for the object reference.
  PortableServer::ServantBase_var base = this->poa_->reference_to_servant (cref);

  // Convert the servant to a CCM servant object.
  CUTS_TCPIP_CCM_Servant * servant =
    dynamic_cast <CUTS_TCPIP_CCM_Servant *> (base.in ());

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
::Components::CCMObjectSeq *
CUTS_TCPIP_CCM_Container::get_components (void)
{
  ACE_DEBUG ((LM_DEBUG,
              "get_components (...)\n"));

  throw CORBA::NO_IMPLEMENT ();
}
