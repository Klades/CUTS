// $Id$

#if !defined (__CUTS_INLINE__)
#include "CCM_ComponentServer_T.inl"
#endif

#include "CCM_ComponentServer_Callback.h"

//
// CUTS_CCM_ComponentServer_T
//
template <typename T, typename CONTAINER>
CUTS_CCM_ComponentServer_T <T, CONTAINER>::
CUTS_CCM_ComponentServer_T (CUTS_CCM_ComponentServer_Callback * callback)
: callback_ (callback)
{

}

//
// shutdown
//
template <typename T, typename CONTAINER>
void CUTS_CCM_ComponentServer_T <T, CONTAINER>::shutdown (void)
{
  if (this->callback_)
    this->callback_->shutdown (false);
}

//
// configure
//
template <typename T, typename CONTAINER>
void CUTS_CCM_ComponentServer_T <T, CONTAINER>::
configure (::CIAO::Deployment::ServerActivator_ptr activator,
           ::Components::ConfigValues * config,
           ::PortableServer::POA_ptr poa)
{
  // Save a copy of all the configuration input variables.
  this->activator_ = ::CIAO::Deployment::ServerActivator::_duplicate (activator);
  this->poa_ = ::PortableServer::POA::_duplicate (poa);
  this->config_ = config;

  for (::CORBA::ULong i = 0; i < this->config_->length (); i ++)
  {
    // For the most part, we are mainly looking for the component
    // installation object. This will be used get the location of the
    // artifacts for each component.
    if (ACE_OS::strcmp ("edu.vanderbilt.dre.CIAO.ComponentInstallation",
                        this->config_[i]->name ()) == 0)
    {
      this->config_[i]->value () >>= this->installer_;
    }
  }
}

//
// configuration
//
template <typename T, typename CONTAINER>
::Components::ConfigValues *
CUTS_CCM_ComponentServer_T <T, CONTAINER>::configuration (void)
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
template <typename T, typename CONTAINER>
::Components::Deployment::ServerActivator_ptr
CUTS_CCM_ComponentServer_T <T, CONTAINER>::get_server_activator (void)
{
  ::Components::Deployment::ServerActivator_var activator =
    ::Components::Deployment::ServerActivator::_duplicate (this->activator_.in ());

  return activator._retn ();
}

//
// create_container
//
template <typename T, typename CONTAINER>
Components::Deployment::Container_ptr
CUTS_CCM_ComponentServer_T <T, CONTAINER>::
create_container (const Components::ConfigValues & config)
{
  CUTS_TCPIP_CCM_Container * servant = 0;
  T * self = dynamic_cast <T *> (this);

  ACE_NEW_THROW_EX (servant,
                    CONTAINER (self, config, this->poa_.in (), this->installer_.in ()),
                    ::CORBA::NO_MEMORY ());

  // Activate the servant.
  ::PortableServer::ObjectId_var oid = this->poa_->activate_object (servant);
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
template <typename T, typename CONTAINER>
void CUTS_CCM_ComponentServer_T <T, CONTAINER>::
remove_container (Components::Deployment::Container_ptr c)
{
  // Get the servant from the reference.
  PortableServer::ServantBase_var servant =
    this->poa_->reference_to_servant (c);

  // Notify the container to remove itself.
  CONTAINER * container = dynamic_cast <CONTAINER *> (servant.in ());
  container->remove ();

  // Deactivate the object.
  ::PortableServer::ObjectId_var oid = this->poa_->servant_to_id (servant.in ());
  this->poa_->deactivate_object (oid.in ());

  // Remove the container from the collection.
  this->containers_.remove (container);
}

//
// get_containers
//
template <typename T, typename CONTAINER>
Components::Deployment::Containers *
CUTS_CCM_ComponentServer_T <T, CONTAINER>::get_containers (void)
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
template <typename T, typename CONTAINER>
void CUTS_CCM_ComponentServer_T <T, CONTAINER>::remove (void)
{
  this->shutdown ();
}
