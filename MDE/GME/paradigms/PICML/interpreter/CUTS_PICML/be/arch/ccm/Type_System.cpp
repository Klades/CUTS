// $Id$

#include "Type_System.h"

#if !defined (__CUTS_INLINE__)
#include "Type_System.inl"
#endif

namespace CUTS_BE_CCM
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
  this->predefined_types_.insert <PICML::Char> ();
  this->predefined_types_.insert <PICML::WideChar> ();

  this->predefined_types_.insert <PICML::GenericObject> ();
  this->predefined_types_.insert <PICML::GenericValue> ();
  this->predefined_types_.insert <PICML::GenericValueObject> ();

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
// generate
//
void Type_System::generate (const PICML::MemberType & mt)
{
  if (Udm::IsDerivedFrom (mt.type (), PICML::PredefinedType::meta))
  {
    PICML::PredefinedType ptype = PICML::PredefinedType::Cast (mt);
    this->predefined_types_.dispatch (ptype);
  }
}

}
