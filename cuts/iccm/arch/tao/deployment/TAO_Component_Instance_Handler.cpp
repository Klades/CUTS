// $Id$

#include "TAO_Component_Instance_Handler.h"

#if !defined (__CUTS_INLINE__)
#include "TAO_Component_Instance_Handler.inl"
#endif

namespace iCCM
{

//
// configure
//
void TAO_Component_Instance_Handler::
configure (const ::Deployment::Properties & config)
{
  // Pass control to the base class. If this method is empty, then it
  // is recommendend that you remove it completely from this class.
  this->base_type::configure (config);

  // NOTE: The Properties passed to this method are those that are
  // attached to a locality manager. In PICML, this would be the Property
  // elements attached to a CollocationGroup.
}


//
// close
//
void TAO_Component_Instance_Handler::close (void)
{
  // Pass control to the base class. If this method is empty, then it
  // is recommendend that you remove it completely from this class.
  this->base_type::close ();
}

}

//
// create_TAO_Component_Instance_Handler
//
extern "C"
::DAnCE::InstanceDeploymentHandler_ptr
create_iCCM_TAO_Component_Instance_Handler (void)
{
  iCCM::TAO_Component_Instance_Handler * handler = 0;
  ACE_NEW_RETURN (handler,
                  iCCM::TAO_Component_Instance_Handler (),
                  handler);

  return handler;
}