// $Id$

#include "Input_Stream_Aggr_Member_Generator.h"

namespace CUTS_BE_TCPIP
{
//
// Input_Stream_Aggr_Member_Generator
//
Input_Stream_Aggr_Member_Generator::
Input_Stream_Aggr_Member_Generator (std::ostream & out)
: out_ (out)
{

}

//
// ~Input_Stream_Aggr_Member_Generator
//
Input_Stream_Aggr_Member_Generator::
~Input_Stream_Aggr_Member_Generator (void)
{

}

//
// Visit_Member
//
void Input_Stream_Aggr_Member_Generator::
Visit_Member (const PICML::Member & member)
{
  this->out_ << "stream >> val." << member.name () << ";";
}

}
