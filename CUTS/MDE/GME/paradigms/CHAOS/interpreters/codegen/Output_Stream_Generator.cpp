// -*- C++ -*-

#include "StdAfx.h"
#include "Output_Stream_Generator.h"
#include "Uml.h"

namespace CUTS_CHAOS
{
Output_Stream_Generator::
Output_Stream_Generator (std::ostream & out, bool aggr)
: out_ (out),
  aggr_ (aggr)
{

}

Output_Stream_Generator::~Output_Stream_Generator (void)
{

}

//
// Visit_Member
//
void Output_Stream_Generator::Visit_Member (const CHAOS::Member & member)
{
  std::string name = member.name ();
  CHAOS::MemberType mt = member.ref ();

  if (Udm::IsDerivedFrom (mt.type (), CHAOS::PredefinedType::meta))
  {
    if (this->aggr_)
    {
      if (mt.type () == CHAOS::String::meta)
      {
        this->out_
          << "dds." << name << " = ::CORBA::string_dup (corba." << name << ");";
      }
      else
      {
        this->out_
          << "dds." << name << " = corba." << name << ";";
      }
    }
    else
    {
      this->out_
        << "dds." << name << " = corba." << name << " ();";
    }
  }
  else
  {
    this->out_
      << "corba." << name << " () >>= dds." << name << ";";
  }
}
}
