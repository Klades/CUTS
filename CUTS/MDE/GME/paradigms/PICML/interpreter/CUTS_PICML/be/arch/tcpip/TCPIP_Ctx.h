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

/**
 * @class CUTS_BE_TCPIP_Ctx
 *
 * Application context for the TCP/IP backend generator.
 */
class CUTS_BE_TCPIP_Ctx
{
public:
  static std::string include (const std::string & filename);

  static std::string single_line_comment (const std::string & comment);
};

#endif  // !defined _CUTS_BE_TCPIP_CTX_H_
