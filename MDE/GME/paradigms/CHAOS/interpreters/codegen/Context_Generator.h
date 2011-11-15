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

#ifndef _CUTS_BE_OPENSPLICE_CONTEXT_GENERATOR_H_
#define _CUTS_BE_OPENSPLICE_CONTEXT_GENERATOR_H_

#include <ostream>
#include "../../paradigms/CHAOS.h"

namespace CUTS_CHAOS
{
class Context_Generator : public CHAOS::Visitor
{
public:
  Context_Generator (std::ostream & header, std::ostream & source);

  /// Destructor.
  virtual ~Context_Generator (void);

  virtual void Visit_Component (
    const CHAOS::Component & component);

  virtual void Visit_OutEventPort (
    const CHAOS::OutEventPort & port);

  const std::string & context (void) const;

private:
  std::ostream & header_;

  std::ostream & source_;

  std::string context_;
};

}

#endif  // _CUTS_BE_OPENSPLICE_CONTEXT_GENERATOR_H_
