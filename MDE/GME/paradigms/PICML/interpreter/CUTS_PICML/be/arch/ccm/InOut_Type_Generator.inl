// -*- C++ -*-
// $Id$

namespace CUTS_BE_CCM
{
namespace Cpp
{


//
// InOut_Type_Generator
//
CUTS_INLINE
InOut_Type_Generator::InOut_Type_Generator (std::ostream & out)
: Type_System (out)
{

}

//
// ~InOut_Type_Generator
//
CUTS_INLINE
InOut_Type_Generator::~InOut_Type_Generator (void)
{

}

//
// Visit_Boolean
//
CUTS_INLINE
void InOut_Type_Generator::
Visit_Boolean (const PICML::Boolean & value)
{
  this->out_ << "::CORBA::Boolean &";
}

//
// Visit_Byte
//
CUTS_INLINE
void InOut_Type_Generator::
Visit_Byte (const PICML::Byte & )
{
  this->out_ << "::CORBA::Octet &";
}

//
// Visit_Char
//
CUTS_INLINE
void InOut_Type_Generator::
Visit_Char (const PICML::Char & )
{
  this->out_ << "char &";
}

//
// Visit_WideChar
//
CUTS_INLINE
void InOut_Type_Generator::
Visit_WideChar (const PICML::WideChar & )
{
  this->out_ << "wchar_t &";
}

//
// Visit_LongInteger
//
CUTS_INLINE
void InOut_Type_Generator::
Visit_LongInteger (const PICML::LongInteger & value)
{
  this->out_ << "::CORBA::Long &";
}

//
// Visit_UnsignedLongInteger
//
CUTS_INLINE
void InOut_Type_Generator::
Visit_UnsignedLongInteger (const PICML::UnsignedLongInteger & value)
{
  this->out_ << "::CORBA::ULong &";
}

//
// Visit_LongLongInteger
//
CUTS_INLINE
void InOut_Type_Generator::
Visit_LongLongInteger (const PICML::LongLongInteger & value)
{
  this->out_ << "::CORBA::LongLong &";
}

//
// Visit_UnsignedLongInteger
//
CUTS_INLINE
void InOut_Type_Generator::
Visit_UnsignedLongLongInteger (const PICML::UnsignedLongLongInteger & value)
{
  this->out_ << "::CORBA::ULongLong &";
}

//
// Visit_ShortInteger
//
CUTS_INLINE
void InOut_Type_Generator::
Visit_ShortInteger (const PICML::ShortInteger & value)
{
  this->out_ << "::CORBA::Short &";
}

//
// Visit_UnsignedShortInteger
//
CUTS_INLINE
void InOut_Type_Generator::
Visit_UnsignedShortInteger (const PICML::UnsignedShortInteger & value)
{
  this->out_ << "::CORBA::UShort &";
}

//
// Visit_String
//
CUTS_INLINE
void InOut_Type_Generator::
Visit_String (const PICML::String & value)
{
  this->out_ << "::CORBA::String * &";
}

//
// Visit_WideString
//
CUTS_INLINE
void InOut_Type_Generator::
Visit_WideString (const PICML::WideString & value)
{
  this->out_ << "::CORBA::WString * &";
}

//
// Visit_FloatNumber
//
CUTS_INLINE
void InOut_Type_Generator::
Visit_FloatNumber (const PICML::FloatNumber & value)
{
  this->out_ << "::CORBA::Float &";
}

//
// Visit_DoubleNumber
//
CUTS_INLINE
void InOut_Type_Generator::
Visit_DoubleNumber (const PICML::DoubleNumber & value)
{
  this->out_ << "::CORBA::Double &";
}

//
// Visit_LongDoubleNumber
//
CUTS_INLINE
void InOut_Type_Generator::
Visit_LongDoubleNumber (const PICML::LongDoubleNumber & value)
{
  this->out_ << "::CORBA::LongDouble &";
}

//
// Visit_GenericValue
//
CUTS_INLINE
void InOut_Type_Generator::
Visit_GenericValue (const PICML::GenericValue & value)
{
  this->out_ << "::CORBA::Any &";
}

//
// Visit_GenericValueObject
//
CUTS_INLINE
void InOut_Type_Generator::
Visit_GenericValueObject (const PICML::GenericValueObject & value)
{

}

//
// Visit_GenericObject
//
CUTS_INLINE
void InOut_Type_Generator::
Visit_GenericObject (const PICML::GenericObject & value)
{
  this->out_ << "::CORBA::Object_ptr &";
}

//
// Visit_TypeKind
//
CUTS_INLINE
void InOut_Type_Generator::
Visit_TypeKind (const PICML::TypeKind & value)
{
  this->out_ << "::CORBA::TCKind &";
}

//
// Visit_TypeEncoding
//
CUTS_INLINE
void InOut_Type_Generator::
Visit_TypeEncoding (const PICML::TypeEncoding & value)
{
  this->out_ << "::CORBA::TypeCode_ptr &";
}

}
}
