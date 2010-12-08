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
: out_ (out),
  predefined_types_ (this)
{
  this->predefined_types_.insert <PICML::Boolean> ();
  this->predefined_types_.insert <PICML::Byte> ();
  this->predefined_types_.insert <PICML::GenericObject> ();
  this->predefined_types_.insert <PICML::GenericValue> ();
  this->predefined_types_.insert <PICML::LongInteger> ();
  this->predefined_types_.insert <PICML::UnsignedLongInteger> ();
  this->predefined_types_.insert <PICML::DoubleNumber> ();
  this->predefined_types_.insert <PICML::FloatNumber> ();
  this->predefined_types_.insert <PICML::ShortInteger> ();
  this->predefined_types_.insert <PICML::UnsignedShortInteger> ();
  this->predefined_types_.insert <PICML::String> ();
  this->predefined_types_.insert <PICML::TypeEncoding> ();
  this->predefined_types_.insert <PICML::TypeKind> ();
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
void Type_System::generate (const PICML::MemberType & mt)
{
  if (Udm::IsDerivedFrom (mt.type (), PICML::PredefinedType::meta))
  {
    PICML::PredefinedType ptype = PICML::PredefinedType::Cast (mt);
    this->predefined_types_.dispatch (ptype);
  }
  else
  {
    PICML::NamedType named = PICML::NamedType::Cast (mt);
    this->out_ << CUTS_BE_Java::fq_type (named);
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
Visit_Boolean (const PICML::Boolean & value)
{
  this->out_ << "boolean";
}

//
// Visit_Byte
//
void Variable_Type::
Visit_Byte (const PICML::Byte & byte)
{
  this->out_ << "char";
}

//
// Visit_LongInteger
//
void Variable_Type::
Visit_LongInteger (const PICML::LongInteger & value)
{
  this->out_ << "long";
}

//
// Visit_UnsignedLongInteger
//
void Variable_Type::
Visit_UnsignedLongInteger (const PICML::UnsignedLongInteger & value)
{
  this->out_ << "long";
}

//
// Visit_ShortInteger
//
void Variable_Type::
Visit_ShortInteger (const PICML::ShortInteger & value)
{
  this->out_ << "short";
}

//
// Visit_UnsignedShortInteger
//
void Variable_Type::
Visit_UnsignedShortInteger (const PICML::UnsignedShortInteger & value)
{
  this->out_ << "short";
}

//
// Visit_String
//
void Variable_Type::
Visit_String (const PICML::String & value)
{
  this->out_ << "String";
}

//
// Visit_DoubleNumber
//
void Variable_Type::
Visit_DoubleNumber (const PICML::DoubleNumber & value)
{
  this->out_ << "double";
}

//
// Visit_FloatNumber
//
void Variable_Type::
Visit_FloatNumber (const PICML::FloatNumber & value)
{
  this->out_ << "float";
}

//
// Visit_GenericValue
//
void Variable_Type::
Visit_GenericValue (const PICML::GenericValue & value)
{
  this->out_ << "Object";
}

//
// Visit_GenericObject
//
void Variable_Type::
Visit_GenericObject (const PICML::GenericObject & value)
{
  this->out_ << "Object";
}

//
// Visit_TypeKind
//
void Variable_Type::
Visit_TypeKind (const PICML::TypeKind & value)
{

}

//
// Visit_TypeEncoding
//
void Variable_Type::
Visit_TypeEncoding (const PICML::TypeEncoding & value)
{

}

}
