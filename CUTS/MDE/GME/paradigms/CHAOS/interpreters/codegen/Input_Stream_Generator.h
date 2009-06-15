// -*- C++ -*-

//=============================================================================
/**
 * @file          Input_Stream_Generator.h
 *
 * $Id$
 *
 * @author        James H. Hill
 */
//=============================================================================

#ifndef _CUTS_OPENSPLICE_BE_INPUT_STREAM_GENERATOR_H_
#define _CUTS_OPENSPLICE_BE_INPUT_STREAM_GENERATOR_H_

#include "../../paradigms/CHAOS.h"
#include <ostream>

namespace CUTS_CHAOS
{
/**
 * @class Input_Stream_Generator
 */
class Input_Stream_Generator : public CHAOS::Visitor
{
public:
  Input_Stream_Generator (std::ostream & out, bool aggr);

  virtual ~Input_Stream_Generator (void);

  virtual void Visit_Member (const CHAOS::Member & member);

private:
  /// Referene to the target output stream.
  ostream & out_;

  bool aggr_;
};

}

#endif  // !defined _CUTS_OPENSPLICE_BE_INPUT_STREAM_GENERATOR_H_
