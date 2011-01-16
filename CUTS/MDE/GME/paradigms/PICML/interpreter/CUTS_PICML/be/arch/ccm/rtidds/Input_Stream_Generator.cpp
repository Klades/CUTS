// -*- C++ -*-

#include "Input_Stream_Generator.h"
#include "Uml.h"

namespace CUTS_BE_RTIDDS
{
Input_Stream_Generator::
Input_Stream_Generator (std::ostream & out, bool aggr)
: out_ (out),
  aggr_ (aggr)
{

}

Input_Stream_Generator::~Input_Stream_Generator (void)
{

}

//
// Visit_Event
//
void Input_Stream_Generator::Visit_Member (const PICML::Member & member)
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
          << "corba." << name << " = ::CORBA::string_dup (dds." << name << ");";
      }
      else
      {
        this->out_
          << "corba." << name << " = dds." << name << ";";
      }
    }
    else
    {
      this->out_
        << "corba." << name << " (dds." << name << ");";
    }
  }
  else
  {
    this->out_
      << "corba." << name << " () <<= dds." << name << ";";
  }
}
}
