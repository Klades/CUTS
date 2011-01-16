// -*- C++ -*-

#ifndef _CUTS_BE_TCPIP_INPUT_AGGR_MEMBER_GENERATOR_H_
#define _CUTS_BE_TCPIP_INPUT_AGGR_MEMBER_GENERATOR_H_

#include "PICML/PICML.h"
#include <ostream>

namespace CUTS_BE_TCPIP
{
/**
 * @class Input_Stream_Aggr_Member_Generator
 */
class Input_Stream_Aggr_Member_Generator : public PICML::Visitor
{
public:
  Input_Stream_Aggr_Member_Generator (std::ostream & out);

  virtual ~Input_Stream_Aggr_Member_Generator (void);

  virtual void Visit_Member (const PICML::Member & member);

private:
  std::ostream & out_;
};

}

#endif  // !defined _CUTS_BE_TCPIP_INPUT_AGGR_MEMBER_GENERATOR_H_
