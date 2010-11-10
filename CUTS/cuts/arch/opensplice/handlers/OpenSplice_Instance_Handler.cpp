// $Id$

#include "OpenSplice_Instance_Handler.h"

#if !defined (__CUTS_INLINE__)
#include "OpenSplice_Instance_Handler.inl"
#endif

//
// create_CUTS_OpenSplice_Component_Instance_Handler
//
extern "C"
::DAnCE::InstanceDeploymentHandler_ptr
create_CUTS_OpenSplice_Component_Instance_Handler (void)
{
  return new CUTS_OpenSplice_CCM_Instance_Handler ();
}
