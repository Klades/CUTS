// -*- C++ -*-

//=============================================================================
/**
 *  @file       TCPIP_Ctx.h
 *
 * $Id$
 *
 *  @author     James H. Hill
 */
//=============================================================================

#ifndef _CUTS_BE_TCPIP_CTX_H_
#define _CUTS_BE_TCPIP_CTX_H_

#include "../ciao/CIAO_Ctx.h"

/**
 * @struct CUTS_BE_TCPIP_Ctx
 *
 * Application context for the TCP/IP backend generator.
 */
struct CUTS_BE_TCPIP_Ctx : public CUTS_BE_CIAO::Context
{
  typedef CUTS_BE_CIAO::Context arch_type;

  typedef CUTS_BE_CPP::Context behavior_type;
};

#endif  // !defined _CUTS_BE_TCPIP_CTX_H_
