// -*- C++ -*-

#ifndef _CUTS_BE_TCPIP_GENERATOR_H_
#define _CUTS_BE_TCPIP_GENERATOR_H_

#include "../../BE_Generators_T.h"
#include "TCPIP_Ctx.h"

/**
 * @struct CUTS_BE_Finalize_T <CUTS_BE_TCPIP_Ctx>
 */
template < >
struct CUTS_BE_Finalize_T <CUTS_BE_TCPIP_Ctx>
{
public:
  static void generate (const PICML::RootFolder & folder);
};

#endif  // !defined _CUTS_BE_TCPIP_GENERATOR_H_
