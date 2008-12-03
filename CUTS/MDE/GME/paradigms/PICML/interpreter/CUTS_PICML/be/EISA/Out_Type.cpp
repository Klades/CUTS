// $Id$

#include "Out_Type.h"

#if !defined (__CUTS_INLINE__)
#include "Out_Type.inl"
#endif

//
// CUTS_EISA_Out_Type
//
CUTS_EISA_Out_Type::CUTS_EISA_Out_Type (void)
{
  this->predefined_type_map_.insert (
    Type_Map::value_type (PICML::String::meta, "::CORBA::String_out"));

  this->predefined_type_map_.insert (
    Type_Map::value_type (PICML::Boolean::meta, "::CORBA::Boolean_out"));

  this->predefined_type_map_.insert (
    Type_Map::value_type (PICML::LongInteger::meta, "::CORBA::Long_out"));

  this->predefined_type_map_.insert (
    Type_Map::value_type (PICML::ShortInteger::meta, "::CORBA::Short_out"));

  this->predefined_type_map_.insert (
    Type_Map::value_type (PICML::Byte::meta, "::CORBA::Octet_out"));

  this->predefined_type_map_.insert (
    Type_Map::value_type (PICML::RealNumber::meta, "::CORBA::Double_out"));

  this->predefined_type_map_.insert (
    Type_Map::value_type (PICML::GenericObject::meta, "::CORBA::Object_out"));

  this->predefined_type_map_.insert (
    Type_Map::value_type (PICML::GenericValue::meta, "const ::CORBA::Any_out"));

  this->predefined_type_map_.insert (
    Type_Map::value_type (PICML::TypeKind::meta, "::CORBA::TCKind_out"));

  this->predefined_type_map_.insert (
    Type_Map::value_type (PICML::TypeEncoding::meta, "::CORBA::TypeCode_out"));
}
