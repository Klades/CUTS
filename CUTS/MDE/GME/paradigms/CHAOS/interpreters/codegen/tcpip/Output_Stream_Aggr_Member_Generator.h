// -*- C++ -*-

#ifndef _CUTS_BE_TCPIP_OUTPUT_AGGR_MEMBER_GENERATOR_H_
#define _CUTS_BE_TCPIP_OUTPUT_AGGR_MEMBER_GENERATOR_H_

#include "../../../paradigms/CHAOS.h"
#include <ostream>

namespace CUTS_BE_TCPIP
{
/**
 * @class Output_Stream_Aggr_Member_Generator
 */
class Output_Stream_Aggr_Member_Generator : public CHAOS::Visitor
{
public:
  Output_Stream_Aggr_Member_Generator (std::ostream & out);

  virtual ~Output_Stream_Aggr_Member_Generator (void);

  virtual void Visit_Member (const CHAOS::Member & member);

private:
  std::ostream & out_;
};

}

#endif  // !defined _CUTS_BE_TCPIP_OUTPUT_AGGR_MEMBER_GENERATOR_H_
