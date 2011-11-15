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
: out_ (out),
  predefined_types_ (this)
{
  this->predefined_types_.insert <PICML::Boolean> ();

  this->predefined_types_.insert <PICML::Char> ();
  this->predefined_types_.insert <PICML::Byte> ();

  this->predefined_types_.insert <PICML::GenericObject> ();
  this->predefined_types_.insert <PICML::GenericValue> ();

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
  this->predefined_types_.insert <PICML::WideString> ();

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
    this->out_ << CUTS_BE_CPP::fq_type (named);
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
Visit_Boolean (const PICML::Boolean & )
{
  this->out_ << "::CORBA::Boolean";
}

//
// Visit_Byte
//
void Variable_Type::
Visit_Byte (const PICML::Byte & )
{
  this->out_ << "::CORBA::Octet";
}

//
// Visit_Char
//
void Variable_Type::
Visit_Char (const PICML::Char & )
{
  this->out_ << "::CORBA::Char";
}

//
// Visit_LongInteger
//
void Variable_Type::
Visit_LongInteger (const PICML::LongInteger & value)
{
  this->out_ << "::CORBA::Long";
}

//
// Visit_UnsignedLongInteger
//
void Variable_Type::
Visit_UnsignedLongInteger (const PICML::UnsignedLongInteger & value)
{
  this->out_ << "::CORBA::ULong";
}

//
// Visit_LongLongInteger
//
void Variable_Type::
Visit_LongLongInteger (const PICML::LongLongInteger &)
{
  this->out_ << "::CORBA::LongLong";
}

//
// Visit_UnsignedLongLongInteger
//
void Variable_Type::
Visit_UnsignedLongLongInteger (const PICML::UnsignedLongLongInteger &)
{
  this->out_ << "::CORBA::ULongLong";
}

//
// Visit_ShortInteger
//
void Variable_Type::
Visit_ShortInteger (const PICML::ShortInteger & value)
{
  this->out_ << "::CORBA::Short";
}

//
// Visit_ShortInteger
//
void Variable_Type::
Visit_UnsignedShortInteger (const PICML::UnsignedShortInteger & value)
{
  this->out_ << "::CORBA::UShort";
}

//
// Visit_String
//
void Variable_Type::
Visit_String (const PICML::String & value)
{
  this->out_ << "ACE_CString";
}

//
// Visit_WideString
//
void Variable_Type::
Visit_WideString (const PICML::WideString & value)
{
  this->out_ << "ACE_WString";
}

//
// Visit_FloatNumber
//
void Variable_Type::
Visit_FloatNumber (const PICML::FloatNumber & value)
{
  this->out_ << "::CORBA::Float";
}

//
// Visit_DoubleNumber
//
void Variable_Type::
Visit_DoubleNumber (const PICML::DoubleNumber & value)
{
  this->out_ << "::CORBA::Double";
}

//
// Visit_LongDoubleNumber
//
void Variable_Type::
Visit_LongDoubleNumber (const PICML::LongDoubleNumber & value)
{
  this->out_ << "::CORBA::LongDouble";
}

//
// Visit_GenericValue
//
void Variable_Type::
Visit_GenericValue (const PICML::GenericValue & value)
{
  this->out_ << "::CORBA::Any";
}

//
// Visit_GenericObject
//
void Variable_Type::
Visit_GenericObject (const PICML::GenericObject & value)
{
  this->out_ << "::CORBA::Object_var";
}

//
// Visit_TypeKind
//
void Variable_Type::
Visit_TypeKind (const PICML::TypeKind & value)
{
  this->out_ << "::CORBA::TCKind";
}

//
// Visit_TypeEncoding
//
void Variable_Type::
Visit_TypeEncoding (const PICML::TypeEncoding & value)
{
  this->out_ << "::CORBA::TypeCode_var";
}

}
