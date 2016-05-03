// -*- C++ -*-

//=============================================================================
/**
 * @file          CCM_Component_Instance_Handler_T.h
 *
 * $Id$
 *
 * @author        James H. Hill
 */
//=============================================================================

#ifndef _CUTS_ICCM_COMPONENT_INSTANCE_HANDLER_H_
#define _CUTS_ICCM_COMPONENT_INSTANCE_HANDLER_H_

#include "dance/Deployment/Deployment_BaseC.h"
#include "dance/DAnCE_LocalityManagerC.h"

#include "ciao/Containers/Container_BaseC.h"
#include "ccm/CCM_CookieC.h"
#include "tao/PortableServer/PortableServer.h"
#include "tao/LocalObject.h"

#include "cuts/config.h"

#include "Deployment_Handlers_export.h"

namespace iCCM
{

class Container;

class ICCM_DEPLOYENT_HANDLERS_Export Component_Instance_Handler :
  public virtual ::CORBA::LocalObject
{
public:
  Component_Instance_Handler (void);
  virtual ~Component_Instance_Handler (void);

  virtual Container * get_container (void) const = 0;
  virtual void configure (const Deployment::Properties & config) = 0;
  virtual void close (void)= 0;
};

}

#if defined (__CUTS_INLINE__)
#include "Component_Instance_Handler.inl"
#endif

#endif  // !defined _CUTS_ICCM_COMPONENT_INSTANCE_HANDLER_H_
