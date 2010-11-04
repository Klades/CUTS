// $Id$

#include "Output_Stream_Aggr_Member_Generator.h"

namespace CUTS_BE_TCPIP
{
//
// Output_Stream_Aggr_Member_Generator
//
Output_Stream_Aggr_Member_Generator::
Output_Stream_Aggr_Member_Generator (std::ostream & out)
: out_ (out)
{

}

//
// ~Output_Stream_Aggr_Member_Generator
//
Output_Stream_Aggr_Member_Generator::
~Output_Stream_Aggr_Member_Generator (void)
{

}

//
// Visit_Member
//
void Output_Stream_Aggr_Member_Generator::
Visit_Member (const PICML::Member & member)
{
  this->out_ << "stream << val." << member.name () << ";";
}

}
