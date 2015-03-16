// -*- C++ -*-

//=============================================================================
/**
 * @file          Context_Generator.h
 *
 * $Id$
 *
 * @author        James H. Hill
 */
//=============================================================================

#ifndef _CUTS_BE_CCM_CONTEXT_GENERATOR_H_
#define _CUTS_BE_CCM_CONTEXT_GENERATOR_H_

#include <ostream>
#include "PICML/PICML.h"
#include "PICML/Visitor.h"
#include "Traits.h"

namespace CUTS_BE_CCM
{
namespace Cpp
{
/**
 * @class Context_Generator
 */
class Context_Generator : public PICML::Visitor
{
public:
  Context_Generator (std::ostream & header,
                     std::ostream & source,
                     Traits * const traits);

  /// Destructor.
  virtual ~Context_Generator (void);

  virtual void Visit_Component (
    const PICML::Component_in component);

  virtual void Visit_OutEventPort (
    const PICML::OutEventPort_in port);

  const std::string & context (void) const;

private:
  /// The target header file.
  std::ostream & header_;

  /// The target source file.
  std::ostream & source_;

  /// The name of the context.
  std::string context_;

  /// The CCM++ traits definition.
  Traits * const traits_;
};

}
}

#if defined (__CUTS_INLINE__)
#include "Context_Generator.inl"
#endif

#endif  // _CUTS_BE_RTIDDS_CONTEXT_GENERATOR_H_
