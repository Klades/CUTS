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
// visit_Boolean
//
void Variable_Type::
visit_Boolean (PICML::Boolean_in )
{
  this->out_ << "::CORBA::Boolean";
}

//
// visit_Byte
//
void Variable_Type::
visit_Byte (PICML::Byte_in )
{
  this->out_ << "::CORBA::Octet";
}

//
// visit_Char
//
void Variable_Type::
visit_Char (PICML::Char_in )
{
  this->out_ << "::CORBA::Char";
}

//
// visit_LongInteger
//
void Variable_Type::
visit_LongInteger (PICML::LongInteger_in value)
{
  this->out_ << "::CORBA::Long";
}

//
// visit_UnsignedLongInteger
//
void Variable_Type::
visit_UnsignedLongInteger (PICML::UnsignedLongInteger_in value)
{
  this->out_ << "::CORBA::ULong";
}

//
// visit_LongLongInteger
//
void Variable_Type::
visit_LongLongInteger (PICML::LongLongInteger_in)
{
  this->out_ << "::CORBA::LongLong";
}

//
// visit_UnsignedLongLongInteger
//
void Variable_Type::
visit_UnsignedLongLongInteger (PICML::UnsignedLongLongInteger_in)
{
  this->out_ << "::CORBA::ULongLong";
}

//
// visit_ShortInteger
//
void Variable_Type::
visit_ShortInteger (PICML::ShortInteger_in value)
{
  this->out_ << "::CORBA::Short";
}

//
// visit_ShortInteger
//
void Variable_Type::
visit_UnsignedShortInteger (PICML::UnsignedShortInteger_in value)
{
  this->out_ << "::CORBA::UShort";
}

//
// visit_String
//
void Variable_Type::
visit_String (PICML::String_in value)
{
  this->out_ << "ACE_CString";
}

//
// visit_WideString
//
void Variable_Type::
visit_WideString (PICML::WideString_in value)
{
  this->out_ << "ACE_WString";
}

//
// visit_FloatNumber
//
void Variable_Type::
visit_FloatNumber (PICML::FloatNumber_in value)
{
  this->out_ << "::CORBA::Float";
}

//
// visit_DoubleNumber
//
void Variable_Type::
visit_DoubleNumber (PICML::DoubleNumber_in value)
{
  this->out_ << "::CORBA::Double";
}

//
// visit_LongDoubleNumber
//
void Variable_Type::
visit_LongDoubleNumber (PICML::LongDoubleNumber_in value)
{
  this->out_ << "::CORBA::LongDouble";
}

//
// visit_GenericValue
//
void Variable_Type::
visit_GenericValue (PICML::GenericValue_in value)
{
  this->out_ << "::CORBA::Any";
}

//
// visit_GenericObject
//
void Variable_Type::
visit_GenericObject (PICML::GenericObject_in value)
{
  this->out_ << "::CORBA::Object_var";
}

//
// visit_TypeKind
//
void Variable_Type::
visit_TypeKind (PICML::TypeKind_in value)
{
  this->out_ << "::CORBA::TCKind";
}

//
// visit_TypeEncoding
//
void Variable_Type::
visit_TypeEncoding (PICML::TypeEncoding_in value)
{
  this->out_ << "::CORBA::TypeCode_var";
}

}
