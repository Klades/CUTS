// -*- C++ -*-

//=============================================================================
/**
 * @file          CCM.h
 *
 * $Id$
 *
 * @author        James H. Hill
 */
//=============================================================================

#ifndef _CUTS_BE_CCM_H_
#define _CUTS_BE_CCM_H_

#include "CCM_export.h"
#include "../../lang/cpp/Cpp.h"

namespace CUTS_BE_CCM
{
namespace Cpp
{
  /**
   * @struct Context
   *
   * The context for the C++ CCM bindings.
   */
  struct CUTS_BE_CCM_Export Context : public CUTS_BE_CPP::Context
  {

  };
}
}

#endif  // !defined _CUTS_BE_CCM_H_
