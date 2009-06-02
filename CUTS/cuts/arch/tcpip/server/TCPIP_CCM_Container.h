// -*- C++ -*-

//=============================================================================
/**
 *  @file         TCPIP_CCM_Container.h
 *
 *  $Id$
 *
 *  @author       James H. Hill
 */
//=============================================================================

#ifndef _CUTS_TCPIP_CCM_CONTAINER_H_
#define _CUTS_TCPIP_CCM_CONTAINER_H_

#include "ciao/ComponentServer/CIAO_ComponentServerS.h"
#include "ccm/CCM_ContainerC.h"
#include "ace/Hash_Map_Manager.h"
#include "ace/RW_Thread_Mutex.h"
#include "ace/SString.h"
#include "cuts/arch/ccm/CCM_Container_T.h"
#include "cuts/arch/tcpip/config.h"
#include "TCPIP_CCM_Container_Strategy.h"
#include "TCPIP_CCM_ComponentServer.h"

class CUTS_TCPIP_CCM_ComponentServer;

/**
 * @class CUTS_TCPIP_CCM_Container
 */
class CUTS_TCPIP_CCM_Container :
  public CUTS_CCM_Container_T <CUTS_TCPIP_CCM_ComponentServer,
                               CUTS_TCPIP_CCM_Container_Strategy>
{
public:
  typedef
    CUTS_CCM_Container_T <CUTS_TCPIP_CCM_ComponentServer,
                          CUTS_TCPIP_CCM_Container_Strategy> base_type;

  CUTS_TCPIP_CCM_Container (CUTS_TCPIP_CCM_ComponentServer * parent,
                            const Components::ConfigValues & config,
                            ::PortableServer::POA_ptr poa,
                            ::Components::Deployment::ComponentInstallation_ptr installer);

  virtual ~CUTS_TCPIP_CCM_Container (void);
};

#if defined (__CUTS_INLINE__)
#include "TCPIP_CCM_Container.inl"
#endif

#endif  // !defined _CUTS_TCPIP_CCM_CONTAINER_H_
