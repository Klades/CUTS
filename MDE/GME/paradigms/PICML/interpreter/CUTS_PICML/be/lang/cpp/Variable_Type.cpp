// $Id$

#include "Variable_Type.h"

#if !defined (__CUTS_INLINE__)
#include "Variable_Type.inl"
#endif

#include "Cpp.h"

namespace CUTS_BE_CPP
{
//
// Type_System
//
Type_System::Type_System (std::ostream & out)
: out_ (out)
{

}

//
// ~Type_System
//
Type_System::~Type_System (void)
{
}

//
// generate
//
void Type_System::generate (const PICML::MemberType_in mt)
{
  try
  {
    PICML::NamedType nt = mt;
    this->out_ << CUTS_BE_CPP::fq_type (nt);
  }
  catch (GAME::Mga::Invalid_Cast &)
  {
    mt->accept (this);
  }
}

///////////////////////////////////////////////////////////////////////////////
// Variable_Type

//
// Variable_Type
//
Variable_Type::Variable_Type (std::ostream & out)
: Type_System (out)
{

}

//
// ~Variable_Type
//
Variable_Type::~Variable_Type (void)
{

}

//
// Visit_Boolean
//
void Variable_Type::
Visit_Boolean (const PICML::Boolean_in )
{
  this->out_ << "::CORBA::Boolean";
}

//
// Visit_Byte
//
void Variable_Type::
Visit_Byte (const PICML::Byte_in )
{
  this->out_ << "::CORBA::Octet";
}

//
// Visit_Char
//
void Variable_Type::
Visit_Char (const PICML::Char_in )
{
  this->out_ << "::CORBA::Char";
}

//
// Visit_LongInteger
//
void Variable_Type::
Visit_LongInteger (const PICML::LongInteger_in value)
{
  this->out_ << "::CORBA::Long";
}

//
// Visit_UnsignedLongInteger
//
void Variable_Type::
Visit_UnsignedLongInteger (const PICML::UnsignedLongInteger_in value)
{
  this->out_ << "::CORBA::ULong";
}

//
// Visit_LongLongInteger
//
void Variable_Type::
Visit_LongLongInteger (const PICML::LongLongInteger_in)
{
  this->out_ << "::CORBA::LongLong";
}

//
// Visit_UnsignedLongLongInteger
//
void Variable_Type::
Visit_UnsignedLongLongInteger (const PICML::UnsignedLongLongInteger_in)
{
  this->out_ << "::CORBA::ULongLong";
}

//
// Visit_ShortInteger
//
void Variable_Type::
Visit_ShortInteger (const PICML::ShortInteger_in value)
{
  this->out_ << "::CORBA::Short";
}

//
// Visit_ShortInteger
//
void Variable_Type::
Visit_UnsignedShortInteger (const PICML::UnsignedShortInteger_in value)
{
  this->out_ << "::CORBA::UShort";
}

//
// Visit_String
//
void Variable_Type::
Visit_String (const PICML::String_in value)
{
  this->out_ << "ACE_CString";
}

//
// Visit_WideString
//
void Variable_Type::
Visit_WideString (const PICML::WideString_in value)
{
  this->out_ << "ACE_WString";
}

//
// Visit_FloatNumber
//
void Variable_Type::
Visit_FloatNumber (const PICML::FloatNumber_in value)
{
  this->out_ << "::CORBA::Float";
}

//
// Visit_DoubleNumber
//
void Variable_Type::
Visit_DoubleNumber (const PICML::DoubleNumber_in value)
{
  this->out_ << "::CORBA::Double";
}

//
// Visit_LongDoubleNumber
//
void Variable_Type::
Visit_LongDoubleNumber (const PICML::LongDoubleNumber_in value)
{
  this->out_ << "::CORBA::LongDouble";
}

//
// Visit_GenericValue
//
void Variable_Type::
Visit_GenericValue (const PICML::GenericValue_in value)
{
  this->out_ << "::CORBA::Any";
}

//
// Visit_GenericObject
//
void Variable_Type::
Visit_GenericObject (const PICML::GenericObject_in value)
{
  this->out_ << "::CORBA::Object_var";
}

//
// Visit_TypeKind
//
void Variable_Type::
Visit_TypeKind (const PICML::TypeKind_in value)
{
  this->out_ << "::CORBA::TCKind";
}

//
// Visit_TypeEncoding
//
void Variable_Type::
Visit_TypeEncoding (const PICML::TypeEncoding_in value)
{
  this->out_ << "::CORBA::TypeCode_var";
}

}
