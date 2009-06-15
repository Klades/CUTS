// $Id$

#include "StdAfx.h"
#include "Input_Stream_Event_Member_Generator.h"
#include "../cpp/Cpp.h"

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
  this->predefined_types_.insert <CHAOS::Boolean> ();
  this->predefined_types_.insert <CHAOS::Byte> ();
  this->predefined_types_.insert <CHAOS::LongInteger> ();
  this->predefined_types_.insert <CHAOS::RealNumber> ();
  this->predefined_types_.insert <CHAOS::ShortInteger> ();
  this->predefined_types_.insert <CHAOS::String> ();
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
Visit_Member (const CHAOS::Member & member)
{
  CHAOS::MemberType mt = member.ref ();
  std::string name = member.name ();

  if (Udm::IsDerivedFrom (mt.type (), CHAOS::PredefinedType::meta))
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

    if (CHAOS::String::meta == mt.type ())
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
Visit_Boolean (const CHAOS::Boolean & val)
{
  this->out_ << "ACE_CDR::Boolean";
}

void Input_Stream_Event_Member_Generator::
Visit_Byte (const CHAOS::Byte & val)
{
  this->out_ << "ACE_CDR::Octet";
}

void Input_Stream_Event_Member_Generator::
Visit_LongInteger (const CHAOS::LongInteger & val)
{
  this->out_ << "ACE_CDR::Long";
}

void Input_Stream_Event_Member_Generator::
Visit_RealNumber (const CHAOS::RealNumber & val)
{
  this->out_ << "double";
}

void Input_Stream_Event_Member_Generator::
Visit_ShortInteger (const CHAOS::ShortInteger & val)
{
  this->out_ << "ACE_CDR::Short";
}

void Input_Stream_Event_Member_Generator::
Visit_String (const CHAOS::String & val)
{
  this->out_ << "ACE_CString";
}

}
