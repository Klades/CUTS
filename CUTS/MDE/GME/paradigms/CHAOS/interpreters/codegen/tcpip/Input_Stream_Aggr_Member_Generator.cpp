// $Id$

#include "StdAfx.h"
#include "Input_Stream_Aggr_Member_Generator.h"
#include "Uml.h"

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
Visit_Member (const CHAOS::Member & member)
{
  CHAOS::MemberType type = member.ref ();
  std::string name (member.name ());

  if (CHAOS::String::meta == type.type ())
  {
    std::string varname ("val_");
    varname += member.name ();

    this->out_
      << "ACE_CString " << varname << ";"
      << "stream >> " << varname << ";"
      << "val." << name << " = " << varname << ".c_str ();"
      << std::endl;
  }
  else if (CHAOS::Boolean::meta == type.type ())
  {
    this->out_
      << "stream >> CUTS_TCPIP_InputCDR::to_boolean (val."
      << name << ");";
  }
  else
  {
    this->out_ << "stream >> val." << member.name () << ";";
  }


}

}
