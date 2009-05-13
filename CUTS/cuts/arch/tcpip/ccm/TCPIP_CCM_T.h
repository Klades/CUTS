// -*- C++ -*-

//=============================================================================
/**
 *  @file         TCPIP_CCM_T.h
 *
 *  $Id$
 *
 *  @author       James H. Hill
 */
//=============================================================================

#ifndef _CUTS_TCPIP_CCM_T_H_
#define _CUTS_TCPIP_CCM_T_H_

namespace CUTS_TCPIP
{
namespace CCM
{
  template <typename EXEC, typename SVNT>
  ::PortableServer::Servant
  create_servant (const char * name,
                  CUTS_TCPIP_Servant_Manager * svnt_mgr,
                  ::Components::EnterpriseComponent_ptr p);
}
}

#include "TCPIP_CCM_T.cpp"

#endif

