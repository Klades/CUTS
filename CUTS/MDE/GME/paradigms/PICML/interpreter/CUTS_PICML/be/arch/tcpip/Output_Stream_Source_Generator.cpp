// $Id$

#include "Output_Stream_Source_Generator.h"
#include "Output_Stream_Aggr_Member_Generator.h"
#include "Output_Stream_Event_Member_Generator.h"
#include "../../lang/cpp/Cpp.h"
#include "boost/bind.hpp"
#include <algorithm>

namespace CUTS_BE_TCPIP
{
//
// Output_Stream_Source_Generator
//
Output_Stream_Source_Generator::
Output_Stream_Source_Generator (std::ofstream & out)
: out_ (out)
{

}

//
// ~Output_Stream_Source_Generator
//
Output_Stream_Source_Generator::~Output_Stream_Source_Generator (void)
{

}

//
// Visit_Event
//
void Output_Stream_Source_Generator::Visit_Event (const PICML::Event & ev)
{
  this->out_ << "ACE_CDR::Boolean operator << (CUTS_TCPIP_OutputCDR & stream, const "
             << CUTS_BE_CPP::fq_type (ev, "::") << " & ev)"
             << "{";

  std::set <PICML::Member> members = ev.Member_children ();
  Output_Stream_Event_Member_Generator emg (this->out_);

  std::for_each (members.begin (),
                 members.end (),
                 boost::bind (&PICML::Member::Accept, _1, boost::ref (emg)));

  this->out_ << "return stream.good_bit ();"
             << "}";
}

//
// Visit_Aggregate
//
void Output_Stream_Source_Generator::
Visit_Aggregate (const PICML::Aggregate & aggr)
{
  this->out_ << "ACE_CDR::Boolean operator << (CUTS_TCPIP_OutputCDR & stream, const "
             << CUTS_BE_CPP::fq_type (aggr) << " & val)"
             << "{";

  Output_Stream_Aggr_Member_Generator amg (this->out_);
  std::set <PICML::Member> members = aggr.Member_children ();

  std::for_each (members.begin (),
                 members.end (),
                 boost::bind (&PICML::Member::Accept, _1, boost::ref (amg)));

  this->out_ << "return stream.good_bit ();"
             << "}";
}

//
// Visit_Collection
//
void Output_Stream_Source_Generator::
Visit_Collection (const PICML::Collection & coll)
{
  std::string name = CUTS_BE_CPP::fq_type (coll, "::");

  this->out_ << "ACE_CDR::Boolean operator << (CUTS_TCPIP_OutputCDR & stream, const " << name << " & coll)"
             << "{"
             << "size_t length = coll.length ();"
             << name << "::const_value_type * iter = coll.get_buffer ();"
             << name << "::const_value_type * iter_end = iter + length;"
             << std::endl
             << "stream << length;"
             << "while (iter != iter_end)" << std::endl
             << "  stream << *iter ++;"
             << std::endl
             << "return stream.good_bit ();"
             << "}";
}

}