// -*- C++ -*-

//=============================================================================
/**
 *  @file         TCPIP_Context.h
 *
 *  $Id$
 *
 *  @author       James H. Hill
 */
//=============================================================================

#ifndef _CUTS_TCPIP_CONTEXT_H_
#define _CUTS_TCPIP_CONTEXT_H_

#include "TCPIP_export.h"
#include "TCPIP_Object_T.h"

/**
 * @class CUTS_TCPIP_Context
 */
class CUTS_TCPIP_Export CUTS_TCPIP_Context :
  public CUTS_TCPIP_MT_Object
{
public:
  virtual ~CUTS_TCPIP_Context (void) = 0;

protected:
  CUTS_TCPIP_Context (void);
};

#if defined (__CUTS_INLINE__)
#include "TCPIP_Context.inl"
#endif

#endif  // !defined _CUTS_TCPIP_CONTEXT_H_
