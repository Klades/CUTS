// $Id$

#include "TCPIP_CCM_Container_Strategy.h"

#if !defined (__CUTS_INLINE__)
#include "TCPIP_CCM_Container_Strategy.inl"
#endif

#include "TCPIP_CCM_ComponentServer.h"

//
// load_executor
//
::Components::EnterpriseComponent_ptr
CUTS_TCPIP_CCM_Container_Strategy::
load_executor (const char * artifact,
               const char * entrypt)
{
  // Load the executor from its shared library.
  ACE_DLL module;

  if (0 != module.open (artifact, ACE_DEFAULT_SHLIB_MODE, false))
  {
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - error loading opening %s; %m\n"),
                artifact));

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
CUTS_TCPIP_CCM_Container_Strategy::
load_servant (const char * name,
              const char * artifact,
              const char * entrypt,
              ::Components::EnterpriseComponent_ptr executor)
{
  // Load the servant from its shared library.
  ACE_DLL module;

  if (0 != module.open (artifact, ACE_DEFAULT_SHLIB_MODE, false))
  {
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - failed to open module %s; %m\n"),
                artifact));

    throw ::Components::Deployment::InvalidConfiguration ();
  }

  // Load the symbol from the library.
  void * symbol = module.symbol (entrypt);

  if (0 == symbol)
    throw ::Components::Deployment::ImplEntryPointNotFound ();

  // Load the executor from the executor artifact.
  typedef ::PortableServer::Servant (*ServantFactoryMethod)
    (const char *, CUTS_TCPIP_Servant_Manager *, ::Components::EnterpriseComponent_ptr);

  ptrdiff_t tmp_ptr = reinterpret_cast <ptrdiff_t> (symbol);
  ServantFactoryMethod factory_method = reinterpret_cast <ServantFactoryMethod> (tmp_ptr);

  return factory_method (name, &this->server_->the_ORB ().the_OM (), executor);
}

