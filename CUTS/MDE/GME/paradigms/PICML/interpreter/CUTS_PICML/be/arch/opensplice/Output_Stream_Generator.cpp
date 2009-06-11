// -*- C++ -*-

#include "Output_Stream_Generator.h"
#include "Uml.h"

namespace CUTS_BE_OpenSplice
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
void Output_Stream_Generator::Visit_Member (const PICML::Member & member)
{
  std::string name = member.name ();
  PICML::MemberType mt = member.ref ();

  if (Udm::IsDerivedFrom (mt.type (), PICML::PredefinedType::meta))
  {
    if (this->aggr_)
    {
      if (mt.type () == PICML::String::meta)
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
