// $Id$

#include "TCPIP_CCM_ComponentServer.h"

#if !defined (__CUTS_INLINE__)
#include "TCPIP_CCM_ComponentServer.inl"
#endif

#include "TCPIP_CCM_ComponentServer_App.h"
#include "TCPIP_CCM_Container.h"

//
// shutdown
//
void CUTS_TCPIP_CCM_ComponentServer::shutdown (bool notify)
{
  if (notify && 0 != this->app_)
    this->app_->shutdown ();

  // Pass control to the base class.
  CUTS_TCPIP_ComponentServer::shutdown ();
}

//
// init
//
void CUTS_TCPIP_CCM_ComponentServer::
configure (::CIAO::Deployment::ServerActivator_ptr activator,
           ::Components::ConfigValues * config,
           ::PortableServer::POA_ptr poa)
{
  this->activator_ = ::CIAO::Deployment::ServerActivator::_duplicate (activator);
  this->config_ = config;
  this->poa_ = PortableServer::POA::_duplicate (poa);
}

//
// shutdown
//
void CUTS_TCPIP_CCM_ComponentServer::shutdown (void)
{
  this->shutdown (true);
}

//
// configuration
//
::Components::ConfigValues *
CUTS_TCPIP_CCM_ComponentServer::configuration (void)
{
  // Instantiate a new set of configuration values.
  ::Components::ConfigValues * temp = 0;
  CORBA::ULong length = this->config_->length ();

  ACE_NEW_THROW_EX (temp,
                    ::Components::ConfigValues (length),
                    ::CORBA::NO_MEMORY ());

  // Copy the configuration values.
  ::Components::ConfigValues_var config (temp);
  config->length (length);

  for (CORBA::ULong i = 0; i < length; ++ i)
  {
    (*config)[i]->name ((*this->config_)[i]->name ());
    (*config)[i]->value ((*this->config_)[i]->value ());
  }

  return config._retn ();
}

//
// get_server_activator
//
::Components::Deployment::ServerActivator_ptr
CUTS_TCPIP_CCM_ComponentServer::get_server_activator (void)
{
  ::Components::Deployment::ServerActivator_var activator =
    ::Components::Deployment::ServerActivator::_duplicate (this->activator_.in ());

  return activator._retn ();
}

//
// create_container
//
Components::Deployment::Container_ptr
CUTS_TCPIP_CCM_ComponentServer::
create_container (const Components::ConfigValues & config)
{
  CUTS_TCPIP_CCM_Container * servant = 0;

  ACE_NEW_THROW_EX (servant,
                    CUTS_TCPIP_CCM_Container (*this, config, this->poa_.in ()),
                    ::CORBA::NO_MEMORY ());

  // Activate the servant.
  ::PortableServer::ObjectId_var oid = this->poa_->activate_object (servant);

  // Retrun a reference to the object.
  ::CORBA::Object_var obj = this->poa_->id_to_reference (oid.in ());
  ::Components::Deployment::Container_var container =
    ::Components::Deployment::Container::_narrow (obj.in ());

  // Cache the container.
  this->containers_.insert (servant);
  return container._retn ();
}

//
// remove_container
//
void CUTS_TCPIP_CCM_ComponentServer::
remove_container (Components::Deployment::Container_ptr c)
{
  // Get the servant from the reference.
  PortableServer::ServantBase_var servant =
    this->poa_->reference_to_servant (c);

  // Notify the container to remove itself.
  CUTS_TCPIP_CCM_Container * container =
    dynamic_cast <CUTS_TCPIP_CCM_Container *> (servant.in ());

  container->remove ();

  // Deactivate the object.
  PortableServer::ObjectId_var oid = this->poa_->servant_to_id (servant.in ());
  this->poa_->deactivate_object (oid.in ());

  // Remove the container from the collection.
  this->containers_.remove (container);
}

//
// get_containers
//
Components::Deployment::Containers *
CUTS_TCPIP_CCM_ComponentServer::get_containers (void)
{
  ::Components::Deployment::Containers * temp = 0;
  ::CORBA::ULong length = this->containers_.size ();

  ACE_NEW_THROW_EX (temp,
                    Components::Deployment::Containers (length),
                    CORBA::NO_MEMORY ());

  Components::Deployment::Containers_var containers = temp;
  containers->length (length);

  container_set::CONST_ITERATOR iter (this->containers_);
  CORBA::ULong i = 0;

  CORBA::Object_var obj;
  ::Components::Deployment::Container_var container;

  for (; !iter.done (); ++ iter)
  {
    // Convert the servant into a reference
    obj = this->poa_->servant_to_reference (*iter);
    container = ::Components::Deployment::Container::_narrow (obj.in ());

    // Store the container in the collection.
    if (!CORBA::is_nil (container.in ()))
      (*containers)[++ i] = container._retn ();
  }

  // Set the final length of the containers.
  containers->length (i);
  return containers._retn ();
}

//
// remove
//
void CUTS_TCPIP_CCM_ComponentServer::remove (void)
{
  this->destroy ();
}
