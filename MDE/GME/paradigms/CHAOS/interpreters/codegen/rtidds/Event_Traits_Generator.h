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

#ifndef _CUTS_CHAOS_RTIDDS_EVENTS_TRAITS_GENERATOR_H_
#define _CUTS_CHAOS_RTIDDS_EVENTS_TRAITS_GENERATOR_H_

#include "../../../paradigms/CHAOS.h"
#include <ostream>

namespace CUTS_CHAOS
{
namespace RTIDDS
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

#endif  // !defined _CUTS_CHAOS_RTIDDS_EVENTS_TRAITS_GENERATOR_H_
