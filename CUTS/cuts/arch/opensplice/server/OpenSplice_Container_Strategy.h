// -*- C++ -*-

//=============================================================================
/**
 *  @file         OpenSplice_CCM_Container_Strategy.h
 *
 *  $Id$
 *
 *  @author       James H. Hill
 */
//=============================================================================

#ifndef _CUTS_OPENSPLICE_CCM_CONTAINER_STRATEGY_H_
#define _CUTS_OPENSPLICE_CCM_CONTAINER_STRATEGY_H_

#include "cuts/arch/ccm/CCM_Container_Strategy_T.h"

// Forward decl.
class CUTS_OpenSplice_CCM_Container;

/**
 * @class CUTS_OpenSplice_CCM_Container_Strategy
 *
 * Implementation of the CCM container startegy for OpenSplice.
 */
class CUTS_OpenSplice_CCM_Container_Strategy :
  public CUTS_CCM_Container_Strategy_T <CUTS_OpenSplice_CCM_Container>
{
public:
  typedef CUTS_CCM_Container_Strategy_T <CUTS_OpenSplice_CCM_Container> base_type;

  CUTS_OpenSplice_CCM_Container_Strategy (CUTS_OpenSplice_CCM_Container * container);

  virtual ~CUTS_OpenSplice_CCM_Container_Strategy (void);

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
#include "OpenSplice_Container_Strategy.inl"
#endif

#endif  // !defined _CUTS_OPENSPLICE_CCM_CONTAINER_STRATEGY_H_
