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

#include "../CCM.h"
#include "Traits.h"

/**
 * @struct CUTS_BE_TCPIP_Ctx
 *
 * Application context for the TCP/IP backend generator.
 */
struct CUTS_BE_TCPIP_Ctx : public CUTS_BE_CCM::Cpp::Context
{
  /// Default constructor.
  CUTS_BE_TCPIP_Ctx (void)
    : CUTS_BE_CCM::Cpp::Context (new CUTS_BE_TCPIP_Traits ())
  {

  }

  /// Type definition of the architecture type.
  typedef CUTS_BE_CCM::Cpp::Context architecture_type;

  /// Type definition of the behavior type.
  typedef CUTS_BE_CPP::Context behavior_type;
};

#endif  // !defined _CUTS_BE_TCPIP_CTX_H_
