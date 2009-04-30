// -*- C++ -*-

//=============================================================================
/**
 *  @file         TCPIP_Component.h
 *
 *  $Id$
 *
 *  @author       James H. Hill
 */
//=============================================================================

#ifndef _CUTS_TCPIP_COMPONENT_H_
#define _CUTS_TCPIP_COMPONENT_H_

#include "TCPIP_Object_T.h"

// Forward decl.
class CUTS_TCPIP_Context;

/**
 * @class CUTS_TCPIP_Component
 */
class CUTS_TCPIP_Export CUTS_TCPIP_Component :
  public CUTS_TCPIP_MT_Object
{
public:
  virtual ~CUTS_TCPIP_Component (void) = 0;

  virtual void set_session_context (CUTS_TCPIP_Context * ctx) = 0;

  virtual void configuration_complete (void) = 0;

  virtual void ccm_activate (void) = 0;

  virtual void ccm_passivate (void) = 0;

  virtual void ccm_remove (void) = 0;

protected:
  CUTS_TCPIP_Component (void);
};

#if defined (__CUTS_INLINE__)
#include "TCPIP_Component.inl"
#endif

#endif  // !defined _CUTS_TCPIP_COMPONENT_H_
