// $Id$

#include "Input_Stream_Event_Member_Generator.h"
#include "TCPIP_Ctx.h"

#include "../../lang/cpp/Cpp.h"

#include <sstream>

namespace CUTS_BE_TCPIP
{
//
// Input_Stream_Event_Member_Generator
//
Input_Stream_Event_Member_Generator::
Input_Stream_Event_Member_Generator (std::ostream & out)
: out_ (out),
  predefined_types_ (this)
{
  this->predefined_types_.insert <PICML::Boolean> ();
  this->predefined_types_.insert <PICML::Byte> ();
  this->predefined_types_.insert <PICML::LongInteger> ();
  this->predefined_types_.insert <PICML::RealNumber> ();
  this->predefined_types_.insert <PICML::ShortInteger> ();
  this->predefined_types_.insert <PICML::String> ();
}

//
// ~Input_Stream_Event_Member_Generator
//
Input_Stream_Event_Member_Generator::
~Input_Stream_Event_Member_Generator (void)
{

}

//
// Visit_Member
//
void Input_Stream_Event_Member_Generator::
Visit_Member (const PICML::Member & member)
{
  PICML::MemberType mt = member.ref ();
  std::string name = member.name ();

  if (Udm::IsDerivedFrom (mt.type (), PICML::PredefinedType::meta))
  {
    // Write the first part of the extraction code.
    this->predefined_types_.dispatch (mt);

    std::ostringstream ostr;
    ostr << "_val_" << member.uniqueId ();
    std::string varname = ostr.str ();

    // Write the remainder of the extraction code.
    this->out_ << " " << varname << ";"
               << "stream >> " << varname << ";"
               << "ev." << name << " (" << varname;

    if (PICML::String::meta == mt.type ())
      this->out_ << ".c_str ()";

    this->out_ << ");"
               << std::endl;
  }
  else
  {
    this->out_ << "stream >> ev." << name << " ();";
  }
}

//
// Visit_Boolean
//
void Input_Stream_Event_Member_Generator::
Visit_Boolean (const PICML::Boolean & val)
{
  this->out_ << "ACE_CDR::Boolean";
}

void Input_Stream_Event_Member_Generator::
Visit_Byte (const PICML::Byte & val)
{
  this->out_ << "ACE_CDR::Octet";
}

void Input_Stream_Event_Member_Generator::
Visit_LongInteger (const PICML::LongInteger & val)
{
  this->out_ << "ACE_CDR::Long";
}

void Input_Stream_Event_Member_Generator::
Visit_RealNumber (const PICML::RealNumber & val)
{
  this->out_ << "double";
}

void Input_Stream_Event_Member_Generator::
Visit_ShortInteger (const PICML::ShortInteger & val)
{
  this->out_ << "ACE_CDR::Short";
}

void Input_Stream_Event_Member_Generator::
Visit_String (const PICML::String & val)
{
  this->out_ << "ACE_CString";
}

}
