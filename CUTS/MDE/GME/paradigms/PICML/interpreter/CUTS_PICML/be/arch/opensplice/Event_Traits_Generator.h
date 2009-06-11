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

#ifndef _CUTS_OPENSPLICE_BE_EVENTS_TRAITS_GENERATOR_H_
#define _CUTS_OPENSPLICE_BE_EVENTS_TRAITS_GENERATOR_H_

#include "PICML/PICML.h"
#include <ostream>

namespace CUTS_BE_OpenSplice
{
/**
 * @class Event_Traits_Generator
 */
class Event_Traits_Generator : public PICML::Visitor
{
public:
  Event_Traits_Generator (std::ostream & out, const std::string & export);

  virtual ~Event_Traits_Generator (void);

  virtual void Visit_Event (const PICML::Event & event);

private:
  /// Target output stream for the traits.
  std::ostream & out_;

  std::string export_;
};

}

#endif  // !defined _CUTS_OPENSPLICE_BE_EVENTS_TRAITS_GENERATOR_H_
