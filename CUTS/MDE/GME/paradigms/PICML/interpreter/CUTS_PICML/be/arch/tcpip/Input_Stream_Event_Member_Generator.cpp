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
  this->predefined_types_.insert <PICML::Char> ();

  this->predefined_types_.insert <PICML::ShortInteger> ();
  this->predefined_types_.insert <PICML::UnsignedShortInteger> ();

  this->predefined_types_.insert <PICML::LongInteger> ();
  this->predefined_types_.insert <PICML::UnsignedLongInteger> ();

  this->predefined_types_.insert <PICML::LongLongInteger> ();
  this->predefined_types_.insert <PICML::UnsignedLongLongInteger> ();

  this->predefined_types_.insert <PICML::FloatNumber> ();
  this->predefined_types_.insert <PICML::DoubleNumber> ();
  this->predefined_types_.insert <PICML::LongDoubleNumber> ();

  this->predefined_types_.insert <PICML::String> ();
}

//
// ~Input_Stream_Event_Member_Generator
//
Input_Stream_Event_Member_Generator::~Input_Stream_Event_Member_Generator (void)
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
               << "alias >> " << varname << ";"
               << "ev." << name << " (" << varname;

    if (PICML::String::meta == mt.type ())
      this->out_ << ".c_str ()";

    this->out_ << ");"
               << std::endl;
  }
  else
  {
    this->out_ << "alias >> ev." << name << " ();";
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

//
// Visit_Byte
//
void Input_Stream_Event_Member_Generator::
Visit_Byte (const PICML::Byte & val)
{
  this->out_ << "ACE_CDR::Octet";
}

//
// Visit_Char
//
void Input_Stream_Event_Member_Generator::
Visit_Char (const PICML::Char & val)
{
  this->out_ << "ACE_CDR::Char";
}

//
// Visit_ShortInteger
//
void Input_Stream_Event_Member_Generator::
Visit_ShortInteger (const PICML::ShortInteger & )
{
  this->out_ << "ACE_CDR::Short";
}

//
// Visit_UnsignedShortInteger
//
void Input_Stream_Event_Member_Generator::
Visit_UnsignedShortInteger (const PICML::UnsignedShortInteger & )
{
  this->out_ << "ACE_CDR::UShort";
}

//
// Visit_LongInteger
//
void Input_Stream_Event_Member_Generator::
Visit_LongInteger (const PICML::LongInteger & )
{
  this->out_ << "ACE_CDR::Long";
}

//
// Visit_UnsignedLongInteger
//
void Input_Stream_Event_Member_Generator::
Visit_UnsignedLongInteger (const PICML::UnsignedLongInteger & )
{
  this->out_ << "ACE_CDR::ULong";
}

//
// Visit_LongLongInteger
//
void Input_Stream_Event_Member_Generator::
Visit_LongLongInteger (const PICML::LongLongInteger & )
{
  this->out_ << "ACE_CDR::LongLong";
}

//
// Visit_UnsignedLongLongInteger
//
void Input_Stream_Event_Member_Generator::
Visit_UnsignedLongLongInteger (const PICML::UnsignedLongLongInteger & )
{
  this->out_ << "ACE_CDR::ULongLong";
}

//
// Visit_FloatNumber
//
void Input_Stream_Event_Member_Generator::
Visit_FloatNumber (const PICML::FloatNumber & val)
{

  this->out_ << "ACE_CDR::Float";
}

//
// Visit_DoubleNumber
//
void Input_Stream_Event_Member_Generator::
Visit_DoubleNumber (const PICML::DoubleNumber & val)
{
  this->out_ << "ACE_CDR::Double";
}

//
// Visit_LongDoubleNumber
//
void Input_Stream_Event_Member_Generator::
Visit_LongDoubleNumber (const PICML::LongDoubleNumber & val)
{
  this->out_ << "ACE_CDR::LongDouble";
}

//
// Visit_String
//
void Input_Stream_Event_Member_Generator::
Visit_String (const PICML::String & val)
{
  this->out_ << "ACE_CString";
}

}
