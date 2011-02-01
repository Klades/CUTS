// $Id$

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
Visit_Member (const PICML::Member & member)
{
  PICML::MemberType type = member.ref ();
  const std::string name = member.name ();

  // Make sure we have the concrete type since the alias is just
  // another name for the concrete type.
  while (PICML::Alias::meta == type.type ())
  {
    // Get the alias type, and its type information.
    PICML::Alias alias = PICML::Alias::Cast (type);
    type = alias.ref ();
  }

  const Uml::Class & uml_type = type.type ();

  if (PICML::String::meta == uml_type)
  {
    const std::string varname = "_val_" + name + "_";

    this->out_
      << "ACE_CString " << varname << ";"
      << "stream >> " << varname << ";"
      << "val." << name << " = " << varname << ".c_str ();"
      << std::endl;
  }
  else if (PICML::Byte::meta == uml_type)
  {
    this->out_ << "stream >> ACE_InputCDR::to_octet (val." << name << ");";
  }
  else if (PICML::Boolean::meta == uml_type)
  {
    this->out_ << "stream >> ACE_InputCDR::to_boolean (val." << name << ");";
  }
  else
  {
    // We can assume the default case with everything else.
    this->out_ << "stream >> val." << name << ";";
  }
}

}
