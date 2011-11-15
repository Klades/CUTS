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

  virtual void Visit_Boolean (const PICML::Boolean & value);

  virtual void Visit_Byte (const PICML::Byte & byte);
  virtual void Visit_Char (const PICML::Char & ch);
  virtual void Visit_WideChar (const PICML::WideChar & ch);

  virtual void Visit_ShortInteger (const PICML::ShortInteger & value);
  virtual void Visit_UnsignedShortInteger (const PICML::UnsignedShortInteger & value);

  virtual void Visit_LongInteger (const PICML::LongInteger & value);
  virtual void Visit_UnsignedLongInteger (const PICML::UnsignedLongInteger & value);

  virtual void Visit_LongLongInteger (const PICML::LongLongInteger & value);
  virtual void Visit_UnsignedLongLongInteger (const PICML::UnsignedLongLongInteger & value);

  virtual void Visit_String (const PICML::String & value);
  virtual void Visit_WideString (const PICML::WideString & value);

  virtual void Visit_FloatNumber (const PICML::FloatNumber & value);
  virtual void Visit_DoubleNumber (const PICML::DoubleNumber & value);
  virtual void Visit_LongDoubleNumber (const PICML::LongDoubleNumber & value);

  virtual void Visit_GenericValue (const PICML::GenericValue & value);
  virtual void Visit_GenericObject (const PICML::GenericObject & value);
  virtual void Visit_GenericValueObject (const PICML::GenericValueObject & value);

  virtual void Visit_TypeKind (const PICML::TypeKind & value);
  virtual void Visit_TypeEncoding (const PICML::TypeEncoding & value);
};

}
}

#if defined (__CUTS_INLINE__)
#include "InOut_Type_Generator.inl"
#endif

#endif  // !defined _CUTS_BE_CCM_INOUT_TYPE_GENERATOR_H_
