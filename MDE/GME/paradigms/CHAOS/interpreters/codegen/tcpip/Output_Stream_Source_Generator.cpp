// $Id$

#include "StdAfx.h"
#include "Output_Stream_Source_Generator.h"
#include "Output_Stream_Aggr_Member_Generator.h"
#include "Output_Stream_Event_Member_Generator.h"
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
void Output_Stream_Source_Generator::Visit_Event (const CHAOS::Event & ev)
{
  this->out_ << "ACE_CDR::Boolean operator << (CUTS_TCPIP_OutputCDR & stream, const " << ev.name () << " & ev)"
             << "{";

  std::set <CHAOS::Member> members = ev.Member_children ();
  Output_Stream_Event_Member_Generator emg (this->out_);

  for (auto member : members)
    member.Accept (emg);

  this->out_ << "return stream.good_bit ();"
             << "}";
}

//
// Visit_Aggregate
//
void Output_Stream_Source_Generator::
Visit_Aggregate (const CHAOS::Aggregate & aggr)
{
  this->out_ << "ACE_CDR::Boolean operator << (CUTS_TCPIP_OutputCDR & stream, const " << aggr.name () << " & val)"
             << "{";

  Output_Stream_Aggr_Member_Generator amg (this->out_);
  std::set <CHAOS::Member> members = aggr.Member_children ();

  for (auto member : members)
    member.Accept (amg);

  this->out_ << "return stream.good_bit ();"
             << "}";
}

//
// Visit_Collection
//
void Output_Stream_Source_Generator::
Visit_Collection (const CHAOS::Collection & coll)
{
  std::string name = coll.name ();

  this->out_ << "ACE_CDR::Boolean operator << (CUTS_TCPIP_OutputCDR & stream, const " << coll.name () << " & coll)"
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