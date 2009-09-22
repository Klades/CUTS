// -*- C++ -*-

//=============================================================================
/**
 * @file          Event_Traits_Generator.h
 *
 * $Id$
 *
 * @author        James H. Hill
 */
//=============================================================================

#ifndef _CUTS_BE_CHAOS_OPENSPLICE_EVENTS_TRAITS_GENERATOR_H_
#define _CUTS_BE_CHAOS_OPENSPLICE_EVENTS_TRAITS_GENERATOR_H_

#include "../../../paradigms/CHAOS.h"
#include <ostream>

namespace CUTS_CHAOS
{
namespace OpenSplice
{
/**
 * @class Event_Traits_Generator
 */
class Event_Traits_Generator : public CHAOS::Visitor
{
public:
  Event_Traits_Generator (std::ostream & out, const std::string & exp);

  virtual ~Event_Traits_Generator (void);

  virtual void Visit_Event (const CHAOS::Event & event);

private:
  /// Target output stream for the traits.
  std::ostream & out_;

  std::string export_;
};
}
}

#endif  // !defined _CUTS_BE_CHAOS_OPENSPLICE_EVENTS_TRAITS_GENERATOR_H_
