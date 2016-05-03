// $Id$

#include "CHAOS_Component_Instance_Handler.h"

#if !defined (__CUTS_INLINE__)
#include "CHAOS_Component_Instance_Handler.inl"
#endif

#if defined (ICCM_CHAOS_HAS_TAO)
#include "cuts/iccm/arch/tao/deployment/TAO_Component_Instance_Handler.h"
#endif

namespace iCCM
{

//
// CHAOS_Component_Instance_Handler
//
CHAOS_Component_Instance_Handler::CHAOS_Component_Instance_Handler (void)
{
#if defined (ICCM_CHAOS_HAS_TAO)
  TAO_Component_Instance_Handler * tao_instance_handler = new TAO_Component_Instance_Handler ();
  this->known_handlers_.insert (std::make_pair ("tao", tao_instance_handler));
#endif
}

//
// configure
//
void CHAOS_Component_Instance_Handler::
configure (const ::Deployment::Properties & config)
{
  // Pass control to the base class. If this method is empty, then it
  // is recommendend that you remove it completely from this class.
  this->base_type::configure (config);

  // NOTE: The Properties passed to this method are those that are
  // attached to a locality manager. In PICML, this would be the Property
  // elements attached to a CollocationGroup.
  for (auto entry : this->known_handlers_)
    entry.second->configure (config);
}

//
// close
//
void CHAOS_Component_Instance_Handler::close (void)
{
  // Pass control to the base class. If this method is empty, then it
  // is recommendend that you remove it completely from this class.
  this->base_type::close ();

  // Close all the loaded handlers, then empty our collection.
  for (auto entry : this->known_handlers_)
    entry.second->close ();

  this->known_handlers_.clear ();
}

}

//
// create_CHAOS_Component_Instance_Handler
//
extern "C"
::DAnCE::InstanceDeploymentHandler_ptr
create_iCCM_CHAOS_Component_Instance_Handler (void)
{
  iCCM::CHAOS_Component_Instance_Handler * handler = 0;
  ACE_NEW_RETURN (handler,
                  iCCM::CHAOS_Component_Instance_Handler (),
                  handler);

  return handler;
}
