// -*- C++ -*-

//=============================================================================
/**
 *  @file         TCPIP_CCM_Container_Strategy.h
 *
 *  $Id$
 *
 *  @author       James H. Hill
 */
//=============================================================================

#ifndef _CUTS_TCPIP_CCM_CONTAINER_STRATEGY_H_
#define _CUTS_TCPIP_CCM_CONTAINER_STRATEGY_H_

#include "cuts/arch/ccm/CCM_Container_Strategy_T.h"

// Forward decl.
class CUTS_TCPIP_CCM_ComponentServer;

/**
 * @class CUTS_TCPIP_CCM_Container_Strategy
 *
 * Implementation of the CCM container startegy for TCP/IP.
 */
class CUTS_TCPIP_CCM_Container_Strategy :
  public CUTS_CCM_Container_Strategy_T <CUTS_TCPIP_CCM_ComponentServer>
{
public:
  typedef CUTS_CCM_Container_Strategy_T <CUTS_TCPIP_CCM_ComponentServer> base_type;

  CUTS_TCPIP_CCM_Container_Strategy (CUTS_TCPIP_CCM_ComponentServer * server);

  virtual ~CUTS_TCPIP_CCM_Container_Strategy (void);

  virtual ::Components::EnterpriseComponent_ptr
    load_executor (const char * artifact,
                   const char * entrypt);

  virtual ::PortableServer::Servant
    load_servant (const char * name,
                  const char * artifact,
                  const char * entrypt,
                  ::Components::EnterpriseComponent_ptr executor);
};

#if defined (__CUTS_INLINE__)
#include "TCPIP_CCM_Container_Strategy.inl"
#endif

#endif  // !defined _CUTS_TCPIP_CCM_CONTAINER_STRATEGY_H_
