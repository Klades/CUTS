// -*- C++ -*-

//=============================================================================
/**
 * @file          CIAO_Ctx.h
 *
 * $Id$
 *
 * @author        James H. Hill
 */
//=============================================================================

#ifndef _CUTS_BE_RTIDDS_CTX_H_
#define _CUTS_BE_RTIDDS_CTX_H_

#include "../CCM.h"
#include "Traits.h"

namespace CUTS_BE_RTIDDS
{
/**
 * Context for the RTIDDS backend generator. This is based on
 * integrating RTIDDS into CIAO.
 */
struct Context : public CUTS_BE_CCM::Cpp::Context
{
  Context (void)
    : CUTS_BE_CCM::Cpp::Context (new Traits ())
  {

  }

  /// Type definition of the architecture type.
  typedef CUTS_BE_CCM::Cpp::Context architecture_type;

  /// Type definition of the behavior type.
  typedef CUTS_BE_CPP::Context behavior_type;
};

}

#endif  // !defined _CUTS_BE_RTIDDS_CTX_H_
