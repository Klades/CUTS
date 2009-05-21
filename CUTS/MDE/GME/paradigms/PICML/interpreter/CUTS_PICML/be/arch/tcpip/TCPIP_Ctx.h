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
#include "PICML/PICML.h"

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

  static std::string scope (const PICML::NamedType & type,
                            const std::string & separator = "::",
                            bool leading = true);

  static std::string fq_type (const PICML::NamedType & type,
                              const std::string & separator = "::",
                              bool leading = true);

  static std::string function_header (const std::string & func);
};

#endif  // !defined _CUTS_BE_TCPIP_CTX_H_
