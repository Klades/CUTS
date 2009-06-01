// -*- C++ -*-

//=============================================================================
/**
 * @file      TCPIP_Generator.h
 *
 * $Id$
 *
 * @author    James H. Hill
 */
//=============================================================================

#ifndef _CUTS_BE_TCPIP_GENERATOR_H_
#define _CUTS_BE_TCPIP_GENERATOR_H_

#include "Component_Impl_Generator.h"
#include "TCPIP_Ctx.h"

/**
 * @class CUTS_BE_Finalize_T
 */
template < >
class CUTS_BE_Finalize_T <CUTS_BE_TCPIP_Ctx> :
  public CUTS_BE_Visitor_T <CUTS_BE_TCPIP_Ctx, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE_TCPIP_Ctx, PICML::Visitor> visitor_type;

  CUTS_BE_Finalize_T (CUTS_BE_TCPIP_Ctx & context);

  virtual ~CUTS_BE_Finalize_T (void);

  void generate (const PICML::RootFolder & folder);
};

#if defined (__CUTS_INLINE__)
#include "TCPIP_Generator.inl"
#endif

#endif  // !defined _CUTS_BE_TCPIP_GENERATOR_H_
