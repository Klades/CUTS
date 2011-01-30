// -*- C++ -*-
// $Id$

namespace CUTS_BE_CCM
{
namespace Cpp
{

//
// Context_Generator
//
CUTS_INLINE
Context_Generator::
Context_Generator (std::ostream & header,
                   std::ostream & source,
                   Traits * const traits)
: header_ (header),
  source_ (source),
  traits_ (traits)
{

}

//
// ~Context_Generator
//
CUTS_INLINE
Context_Generator::~Context_Generator (void)
{

}

//
// ~Context_Generator
//
CUTS_INLINE
const std::string & Context_Generator::context (void) const
{
  return this->context_;
}

}
}
