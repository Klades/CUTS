// -*- C++ -*--
// $Id$

namespace CUTS_BE_CCM
{
namespace Cpp
{

//
// In_Type_Generator
//
CUTS_INLINE
In_Type_Generator::In_Type_Generator (std::ostream & out)
: Type_System (out)

{
}

//
// ~In_Type_Generator
//
CUTS_INLINE
In_Type_Generator::~In_Type_Generator (void)
{

}

//
// Visit_Boolean
//
CUTS_INLINE
void In_Type_Generator::
Visit_Boolean (const PICML::Boolean_in value)
{
  this->out_ << "::CORBA::Boolean";
}

//
// Visit_Byte
//
CUTS_INLINE
void In_Type_Generator::Visit_Byte (const PICML::Byte_in)
{
  this->out_ << "::CORBA::Octet";
}

//
// Visit_Char
//
CUTS_INLINE
void In_Type_Generator::Visit_Char (const PICML::Char_in)
{
  this->out_ << "char";
}

//
// Visit_WideChar
//
CUTS_INLINE
void In_Type_Generator::Visit_WideChar (const PICML::WideChar_in)
{
  this->out_ << "wchar_t";
}

//
// Visit_LongInteger
//
CUTS_INLINE
void In_Type_Generator::
Visit_LongInteger (const PICML::LongInteger_in )
{
  this->out_ << "::CORBA::Long";
}

//
// Visit_UnsignedLongInteger
//
CUTS_INLINE
void In_Type_Generator::
Visit_UnsignedLongInteger (const PICML::UnsignedLongInteger_in )
{
  this->out_ << "::CORBA::ULong";
}


//
// Visit_LongLongInteger
//
CUTS_INLINE
void In_Type_Generator::
Visit_LongLongInteger (const PICML::LongLongInteger_in )
{
  this->out_ << "::CORBA::LongLong";
}

//
// Visit_UnsignedLongLongInteger
//
CUTS_INLINE
void In_Type_Generator::
Visit_UnsignedLongLongInteger (const PICML::UnsignedLongLongInteger_in )
{
  this->out_ << "::CORBA::ULongLong";
}

//
// Visit_ShortInteger
//
CUTS_INLINE
void In_Type_Generator::
Visit_ShortInteger (const PICML::ShortInteger_in )
{
  this->out_ << "::CORBA::Short";
}

//
// Visit_UnsignedShortInteger
//
CUTS_INLINE
void In_Type_Generator::
Visit_UnsignedShortInteger (const PICML::UnsignedShortInteger_in )
{
  this->out_ << "::CORBA::UShort";
}

//
// Visit_String
//
CUTS_INLINE
void In_Type_Generator::
Visit_String (const PICML::String_in value)
{
  this->out_ << "const char *";
}

//
// Visit_WideString
//
CUTS_INLINE
void In_Type_Generator::
Visit_WideString (const PICML::WideString_in )
{
  this->out_ << "const wchar_t *";
}

//
// Visit_FloatNumber
//
CUTS_INLINE
void In_Type_Generator::
Visit_FloatNumber (const PICML::FloatNumber_in)
{
  this->out_ << "::CORBA::Float";
}

//
// Visit_DoubleNumber
//
CUTS_INLINE
void In_Type_Generator::
Visit_DoubleNumber (const PICML::DoubleNumber_in)
{
  this->out_ << "::CORBA::Double";
}

//
// Visit_LongDoubleNumber
//
CUTS_INLINE
void In_Type_Generator::
Visit_LongDoubleNumber (const PICML::LongDoubleNumber_in)
{
  this->out_ << "::CORBA::LongDouble";
}

//
// Visit_GenericValue
//
CUTS_INLINE
void In_Type_Generator::
Visit_GenericValue (const PICML::GenericValue_in)
{
  this->out_ << "const ::CORBA::Any &";
}

//
// Visit_GenericValue
//
CUTS_INLINE
void In_Type_Generator::
Visit_GenericValueObject (const PICML::GenericValueObject_in)
{

}

//
// Visit_GenericObject
//
CUTS_INLINE
void In_Type_Generator::
Visit_GenericObject (const PICML::GenericObject_in)
{
  this->out_ << "::CORBA::Object_ptr";
}

//
// Visit_TypeKind
//
CUTS_INLINE
void In_Type_Generator::
Visit_TypeKind (const PICML::TypeKind_in value)
{
  this->out_ << "::CORBA::TCKind";
}

//
// Visit_TypeEncoding
//
CUTS_INLINE
void In_Type_Generator::
Visit_TypeEncoding (const PICML::TypeEncoding_in value)
{
  this->out_ << "::CORBA::TypeCode_ptr";
}

}
}
