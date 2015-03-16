// -*- C++ -*-

//=============================================================================
/**
 * @file          InOut_Type_Generator.h
 *
 * $Id$
 *
 * @author        James H. Hill
 */
//=============================================================================

#ifndef _CUTS_BE_CCM_INOUT_TYPE_GENERATOR_H_
#define _CUTS_BE_CCM_INOUT_TYPE_GENERATOR_H_

#include "Type_System.h"

namespace CUTS_BE_CCM
{
namespace Cpp
{

/**
 * @class InOut_Type_Generator
 *
 * Visitor that generates an inout parameter type.
 */
class CUTS_BE_CCM_Export InOut_Type_Generator : public CUTS_BE_CCM::Type_System
{
public:
  InOut_Type_Generator (std::ostream & out);

  virtual ~InOut_Type_Generator (void);

  virtual void Visit_Boolean (const PICML::Boolean_in value);

  virtual void Visit_Byte (const PICML::Byte_in byte);
  virtual void Visit_Char (const PICML::Char_in ch);
  virtual void Visit_WideChar (const PICML::WideChar_in ch);

  virtual void Visit_ShortInteger (const PICML::ShortInteger_in value);
  virtual void Visit_UnsignedShortInteger (const PICML::UnsignedShortInteger_in value);

  virtual void Visit_LongInteger (const PICML::LongInteger_in value);
  virtual void Visit_UnsignedLongInteger (const PICML::UnsignedLongInteger_in value);

  virtual void Visit_LongLongInteger (const PICML::LongLongInteger_in value);
  virtual void Visit_UnsignedLongLongInteger (const PICML::UnsignedLongLongInteger_in value);

  virtual void Visit_String (const PICML::String_in value);
  virtual void Visit_WideString (const PICML::WideString_in value);

  virtual void Visit_FloatNumber (const PICML::FloatNumber_in value);
  virtual void Visit_DoubleNumber (const PICML::DoubleNumber_in value);
  virtual void Visit_LongDoubleNumber (const PICML::LongDoubleNumber_in value);

  virtual void Visit_GenericValue (const PICML::GenericValue_in value);
  virtual void Visit_GenericObject (const PICML::GenericObject_in value);
  virtual void Visit_GenericValueObject (const PICML::GenericValueObject_in value);

  virtual void Visit_TypeKind (const PICML::TypeKind_in value);
  virtual void Visit_TypeEncoding (const PICML::TypeEncoding_in value);
};

}
}

#if defined (__CUTS_INLINE__)
#include "InOut_Type_Generator.inl"
#endif

#endif  // !defined _CUTS_BE_CCM_INOUT_TYPE_GENERATOR_H_
