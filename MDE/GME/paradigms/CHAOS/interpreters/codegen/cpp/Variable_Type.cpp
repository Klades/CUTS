// $Id$

#include "StdAfx.h"
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
  this->predefined_types_.insert <CHAOS::Boolean> ();
  this->predefined_types_.insert <CHAOS::Byte> ();
  this->predefined_types_.insert <CHAOS::GenericObject> ();
  this->predefined_types_.insert <CHAOS::GenericValue> ();
  this->predefined_types_.insert <CHAOS::LongInteger> ();
  this->predefined_types_.insert <CHAOS::RealNumber> ();
  this->predefined_types_.insert <CHAOS::ShortInteger> ();
  this->predefined_types_.insert <CHAOS::String> ();
  this->predefined_types_.insert <CHAOS::TypeEncoding> ();
  this->predefined_types_.insert <CHAOS::TypeKind> ();
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
void Type_System::generate (const CHAOS::MemberType & mt)
{
  if (Udm::IsDerivedFrom (mt.type (), CHAOS::PredefinedType::meta))
  {
    CHAOS::PredefinedType ptype = CHAOS::PredefinedType::Cast (mt);
    this->predefined_types_.dispatch (ptype);
  }
  else
  {
    CHAOS::NamedType named = CHAOS::NamedType::Cast (mt);
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
Visit_Boolean (const CHAOS::Boolean & value)
{
  this->out_ << "::CORBA::Boolean";
}

//
// Visit_Byte
//
void Variable_Type::
Visit_Byte (const CHAOS::Byte & byte)
{
  this->out_ << "::CORBA::Octet";
}

//
// Visit_LongInteger
//
void Variable_Type::
Visit_LongInteger (const CHAOS::LongInteger & value)
{
  this->out_ << "::CORBA::Long";
}

//
// Visit_ShortInteger
//
void Variable_Type::
Visit_ShortInteger (const CHAOS::ShortInteger & value)
{
  this->out_ << "::CORBA::Short";
}

//
// Visit_String
//
void Variable_Type::
Visit_String (const CHAOS::String & value)
{
  this->out_ << "ACE_CString";
}

//
// Visit_RealNumber
//
void Variable_Type::
Visit_RealNumber (const CHAOS::RealNumber & value)
{
  this->out_ << "::CORBA::Double";
}

//
// Visit_GenericValue
//
void Variable_Type::
Visit_GenericValue (const CHAOS::GenericValue & value)
{
  this->out_ << "::CORBA::Any";
}

//
// Visit_GenericObject
//
void Variable_Type::
Visit_GenericObject (const CHAOS::GenericObject & value)
{
  this->out_ << "::CORBA::Object_var";
}

//
// Visit_TypeKind
//
void Variable_Type::
Visit_TypeKind (const CHAOS::TypeKind & value)
{
  this->out_ << "::CORBA::TCKind";
}

//
// Visit_TypeEncoding
//
void Variable_Type::
Visit_TypeEncoding (const CHAOS::TypeEncoding & value)
{
  this->out_ << "::CORBA::TypeCode_var";
}

}
