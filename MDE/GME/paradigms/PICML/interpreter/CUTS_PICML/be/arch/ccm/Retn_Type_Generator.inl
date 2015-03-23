// -*- C++ -*-
// $Id$

namespace CUTS_BE_CCM
{
namespace Cpp
{

//
// Retn_Type_Generator
//
CUTS_INLINE
Retn_Type_Generator::Retn_Type_Generator (std::ostream & out)
: Type_System (out)
{

}

//
// ~Retn_Type_Generator
//
CUTS_INLINE
Retn_Type_Generator::~Retn_Type_Generator (void)
{

}

//
// visit_Boolean
//
CUTS_INLINE
void Retn_Type_Generator::
visit_Boolean (PICML::Boolean_in value)
{
  this->out_ << "::CORBA::Boolean";
}

//
// visit_Byte
//
CUTS_INLINE
void Retn_Type_Generator::
visit_Byte (PICML::Byte_in byte)
{
  this->out_ << "::CORBA::Octet";
}

//
// visit_Char
//
CUTS_INLINE
void Retn_Type_Generator::
visit_Char (PICML::Char_in byte)
{
  this->out_ << "char";
}

//
// visit_WideChar
//
CUTS_INLINE
void Retn_Type_Generator::
visit_WideChar (PICML::WideChar_in byte)
{
  this->out_ << "wchar_t";
}

//
// visit_LongInteger
//
CUTS_INLINE
void Retn_Type_Generator::
visit_LongInteger (PICML::LongInteger_in value)
{
  this->out_ << "::CORBA::Long";
}

//
// visit_UnsignedLongInteger
//
CUTS_INLINE
void Retn_Type_Generator::
visit_UnsignedLongInteger (PICML::UnsignedLongInteger_in value)
{
  this->out_ << "::CORBA::ULong";
}

//
// visit_LongLongInteger
//
CUTS_INLINE
void Retn_Type_Generator::
visit_LongLongInteger (PICML::LongLongInteger_in value)
{
  this->out_ << "::CORBA::LongLong";
}

//
// visit_UnsignedLongLongInteger
//
CUTS_INLINE
void Retn_Type_Generator::
visit_UnsignedLongLongInteger (PICML::UnsignedLongLongInteger_in value)
{
  this->out_ << "::CORBA::ULongLong";
}

//
// visit_ShortInteger
//
CUTS_INLINE
void Retn_Type_Generator::
visit_ShortInteger (PICML::ShortInteger_in value)
{
  this->out_ << "::CORBA::Short";
}

//
// visit_UnsignedShortInteger
//
CUTS_INLINE
void Retn_Type_Generator::
visit_UnsignedShortInteger (PICML::UnsignedShortInteger_in value)
{
  this->out_ << "::CORBA::UShort";
}

//
// visit_String
//
CUTS_INLINE
void Retn_Type_Generator::
visit_String (PICML::String_in value)
{
  this->out_ << "char *";
}

//
// visit_WideString
//
CUTS_INLINE
void Retn_Type_Generator::
visit_WideString (PICML::WideString_in value)
{
  this->out_ << "wchar_t *";
}

//
// visit_FloatNumber
//
CUTS_INLINE
void Retn_Type_Generator::
visit_FloatNumber (PICML::FloatNumber_in value)
{
  this->out_ << "::CORBA::Float";
}

//
// visit_DoubleNumber
//
CUTS_INLINE
void Retn_Type_Generator::
visit_DoubleNumber (PICML::DoubleNumber_in value)
{
  this->out_ << "::CORBA::Double";
}

//
// visit_LongDoubleNumber
//
CUTS_INLINE
void Retn_Type_Generator::
visit_LongDoubleNumber (PICML::LongDoubleNumber_in value)
{
  this->out_ << "::CORBA::LongDouble";
}

//
// visit_GenericValue
//
CUTS_INLINE
void Retn_Type_Generator::
visit_GenericValue (PICML::GenericValue_in value)
{
  this->out_ << "::CORBA::Any";
}

//
// visit_GenericObject
//
CUTS_INLINE
void Retn_Type_Generator::
visit_GenericObject (PICML::GenericObject_in value)
{
  this->out_ << "::CORBA::Object_ptr";
}


//
// visit_GenericObject
//
CUTS_INLINE
void Retn_Type_Generator::
visit_GenericValueObject (PICML::GenericValueObject_in)
{

}

//
// visit_TypeKind
//
CUTS_INLINE
void Retn_Type_Generator::
visit_TypeKind (PICML::TypeKind_in )
{
  this->out_ << "::CORBA::TCKind";
}

//
// visit_TypeEncoding
//
CUTS_INLINE
void Retn_Type_Generator::
visit_TypeEncoding (PICML::TypeEncoding_in)
{
  this->out_ << "::CORBA::TypeCode_ptr";
}

}
}
