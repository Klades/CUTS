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

#include "../ccm/CCM.h"

/**
 * @struct CUTS_BE_TCPIP_Ctx
 *
 * Application context for the TCP/IP backend generator.
 */
struct CUTS_BE_TCPIP_Ctx : public CUTS_BE_CCM::Cpp::Context
{
  typedef CUTS_BE_CCM::Cpp::Context arch_type;

  typedef CUTS_BE_CPP::Context behavior_type;

  std::ofstream project_;

  std::ofstream workspace_;
};

#endif  // !defined _CUTS_BE_TCPIP_CTX_H_
