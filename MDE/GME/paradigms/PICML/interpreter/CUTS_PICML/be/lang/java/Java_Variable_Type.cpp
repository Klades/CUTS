// $Id$

#include "Java_Variable_Type.h"

#if !defined (__CUTS_INLINE__)
#include "Java_Variable_Type.inl"
#endif

#include "Java.h"

namespace CUTS_BE_Java
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
    PICML::NamedType named = PICML::NamedType::_narrow (mt);
    this->out_ << CUTS_BE_Java::fq_type (named);
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
Visit_Boolean (PICML::Boolean_in value)
{
  this->out_ << "boolean";
}

//
// Visit_Byte
//
void Variable_Type::
Visit_Byte (PICML::Byte_in byte)
{
  this->out_ << "char";
}

//
// Visit_LongInteger
//
void Variable_Type::
Visit_LongInteger (PICML::LongInteger_in value)
{
  this->out_ << "long";
}

//
// Visit_UnsignedLongInteger
//
void Variable_Type::
Visit_UnsignedLongInteger (PICML::UnsignedLongInteger_in value)
{
  this->out_ << "long";
}

//
// Visit_ShortInteger
//
void Variable_Type::
Visit_ShortInteger (PICML::ShortInteger_in value)
{
  this->out_ << "short";
}

//
// Visit_UnsignedShortInteger
//
void Variable_Type::
Visit_UnsignedShortInteger (PICML::UnsignedShortInteger_in value)
{
  this->out_ << "short";
}

//
// Visit_String
//
void Variable_Type::
Visit_String (PICML::String_in value)
{
  this->out_ << "String";
}

//
// Visit_DoubleNumber
//
void Variable_Type::
Visit_DoubleNumber (PICML::DoubleNumber_in value)
{
  this->out_ << "double";
}

//
// Visit_FloatNumber
//
void Variable_Type::
Visit_FloatNumber (PICML::FloatNumber_in value)
{
  this->out_ << "float";
}

//
// Visit_GenericValue
//
void Variable_Type::
Visit_GenericValue (PICML::GenericValue_in value)
{
  this->out_ << "Object";
}

//
// Visit_GenericObject
//
void Variable_Type::
Visit_GenericObject (PICML::GenericObject_in value)
{
  this->out_ << "Object";
}

//
// Visit_TypeKind
//
void Variable_Type::
Visit_TypeKind (PICML::TypeKind_in value)
{

}

//
// Visit_TypeEncoding
//
void Variable_Type::
Visit_TypeEncoding (PICML::TypeEncoding_in value)
{

}

}
