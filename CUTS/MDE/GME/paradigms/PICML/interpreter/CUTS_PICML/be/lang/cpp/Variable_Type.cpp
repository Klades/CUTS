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
  this->predefined_types_.insert <PICML::Byte> ();
  this->predefined_types_.insert <PICML::GenericObject> ();
  this->predefined_types_.insert <PICML::GenericValue> ();
  this->predefined_types_.insert <PICML::LongInteger> ();
  this->predefined_types_.insert <PICML::RealNumber> ();
  this->predefined_types_.insert <PICML::ShortInteger> ();
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
Visit_Boolean (const PICML::Boolean & value)
{
  this->out_ << "::CORBA::Boolean";
}

//
// Visit_Byte
//
void Variable_Type::
Visit_Byte (const PICML::Byte & byte)
{
  this->out_ << "::CORBA::Octet";
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
// Visit_ShortInteger
//
void Variable_Type::
Visit_ShortInteger (const PICML::ShortInteger & value)
{
  this->out_ << "::CORBA::Short";
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
// Visit_RealNumber
//
void Variable_Type::
Visit_RealNumber (const PICML::RealNumber & value)
{
  this->out_ << "::CORBA::Double";
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
