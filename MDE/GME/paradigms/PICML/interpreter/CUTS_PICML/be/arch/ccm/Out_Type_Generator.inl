// -*- C++ -*-
// $Id$

namespace CUTS_BE_CCM
{
namespace Cpp
{

//
// Out_Type_Generator
//
CUTS_INLINE
Out_Type_Generator::Out_Type_Generator (std::ostream & out)
: Type_System (out)
{

}

//
// ~Out_Type_Generator
//
CUTS_INLINE
Out_Type_Generator::~Out_Type_Generator (void)
{

}

//
// visit_Boolean
//
CUTS_INLINE
void Out_Type_Generator::
visit_Boolean (PICML::Boolean_in)
{
  this->out_ << "::CORBA::Boolean_out";
}

//
// visit_Char
//
CUTS_INLINE
void Out_Type_Generator::
visit_Char (PICML::Char_in )
{
  this->out_ << "::CORBA::Char_out";
}

//
// visit_WideChar
//
CUTS_INLINE
void Out_Type_Generator::
visit_WideChar (PICML::WideChar_in )
{
  this->out_ << "::CORBA::WChar_out";
}

//
// visit_Byte
//
CUTS_INLINE
void Out_Type_Generator::
visit_Byte (PICML::Byte_in)
{
  this->out_ << "::CORBA::Octet_out";
}

//
// visit_UnsignedShortInteger
//
CUTS_INLINE
void Out_Type_Generator::
visit_UnsignedShortInteger (PICML::UnsignedShortInteger_in)
{
  this->out_ << "::CORBA::UnsignedShort_out";
}

//
// visit_ShortInteger
//
CUTS_INLINE
void Out_Type_Generator::
visit_ShortInteger (PICML::ShortInteger_in)
{
  this->out_ << "::CORBA::Short_out";
}

//
// visit_LongInteger
//
CUTS_INLINE
void Out_Type_Generator::
visit_LongInteger (PICML::LongInteger_in)
{
  this->out_ << "::CORBA::Long_out";
}

//
// visit_UnsignedLongInteger
//
CUTS_INLINE
void Out_Type_Generator::
visit_UnsignedLongInteger (PICML::UnsignedLongInteger_in)
{
  this->out_ << "::CORBA::UnsignedLong_out";
}

//
// visit_LongLongInteger
//
CUTS_INLINE
void Out_Type_Generator::
visit_LongLongInteger (PICML::LongLongInteger_in)
{
  this->out_ << "::CORBA::LongLong_out";
}

//
// visit_UnsignedLongLongInteger
//
CUTS_INLINE
void Out_Type_Generator::
visit_UnsignedLongLongInteger (PICML::UnsignedLongLongInteger_in)
{
  this->out_ << "::CORBA::UnsignedLongLong_out";
}

//
// visit_String
//
CUTS_INLINE
void Out_Type_Generator::
visit_String (PICML::String_in)
{
  this->out_ << "::CORBA::String_out";
}

//
// visit_WideString
//
CUTS_INLINE
void Out_Type_Generator::
visit_WideString (PICML::WideString_in)
{
  this->out_ << "::CORBA::WString_out";
}

//
// visit_FloatNumber
//
CUTS_INLINE
void Out_Type_Generator::
visit_FloatNumber (PICML::FloatNumber_in)
{
  this->out_ << "::CORBA::Float_out";
}

//
// visit_DoubleNumber
//
CUTS_INLINE
void Out_Type_Generator::
visit_DoubleNumber (PICML::DoubleNumber_in)
{
  this->out_ << "::CORBA::Double_out";
}

//
// visit_LongDoubleNumber
//
CUTS_INLINE
void Out_Type_Generator::
visit_LongDoubleNumber (PICML::LongDoubleNumber_in)
{
  this->out_ << "::CORBA::LongDouble_out";
}

//
// visit_GenericValue
//
CUTS_INLINE
void Out_Type_Generator::
visit_GenericValue (PICML::GenericValue_in)
{
  this->out_ << "::CORBA::Any_out";
}

//
// visit_GenericValueObject
//
CUTS_INLINE
void Out_Type_Generator::
visit_GenericValueObject (PICML::GenericValueObject_in)
{

}

//
// visit_GenericObject
//
CUTS_INLINE
void Out_Type_Generator::
visit_GenericObject (PICML::GenericObject_in)
{
  this->out_ << "::CORBA::Object_out";
}

//
// visit_TypeKind
//
CUTS_INLINE
void Out_Type_Generator::
visit_TypeKind (PICML::TypeKind_in)
{
  this->out_ << "::CORBA::TCKind_out";
}

//
// visit_TypeEncoding
//
CUTS_INLINE
void Out_Type_Generator::
visit_TypeEncoding (PICML::TypeEncoding_in)
{
  this->out_ << "::CORBA::TypeCode_out";
}

}
}
