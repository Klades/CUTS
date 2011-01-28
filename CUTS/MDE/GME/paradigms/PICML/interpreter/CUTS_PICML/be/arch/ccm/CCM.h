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

#include "../../lang/cpp/Cpp.h"
#include <fstream>

#include "Traits.h"

namespace CUTS_BE_CCM
{
namespace Cpp
{

/**
 * @struct Context
 *
 * The context for the CCM++ bindings.
 */
struct CUTS_BE_CCM_Export Context : public CUTS_BE_CPP::Context
{
  /// Initializing constructor.
  Context (Traits * const t)
    : traits_ (t) { }

  /// The target workspace file.
  std::ofstream workspace_;

  /// The target project file.
  std::ofstream project_;

  /// Traits for the backend implementation.
  Traits * const traits_;

  static bool is_dds_event_wrapper (const PICML::Event & ev);
  static bool is_dds_event_wrapper (const PICML::Event & ev, PICML::Aggregate & dds_event);
};

}
}

#endif  // !defined _CUTS_BE_CCM_H_
