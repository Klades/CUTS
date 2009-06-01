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

#include <string>
#include <fstream>
#include "PICML/PICML.h"

/**
 * @class CUTS_BE_TCPIP_Ctx
 *
 * Application context for the TCP/IP backend generator.
 */
class CUTS_BE_TCPIP_Ctx
{
public:
  static std::ofstream header_;

  static std::ofstream source_;

  static std::string monoimpl_;
};

#endif  // !defined _CUTS_BE_TCPIP_CTX_H_
