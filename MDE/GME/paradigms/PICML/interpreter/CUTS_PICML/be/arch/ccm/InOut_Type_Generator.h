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

  virtual void visit_Boolean (PICML::Boolean_in value);

  virtual void visit_Byte (PICML::Byte_in byte);
  virtual void visit_Char (PICML::Char_in ch);
  virtual void visit_WideChar (PICML::WideChar_in ch);

  virtual void visit_ShortInteger (PICML::ShortInteger_in value);
  virtual void visit_UnsignedShortInteger (PICML::UnsignedShortInteger_in value);

  virtual void visit_LongInteger (PICML::LongInteger_in value);
  virtual void visit_UnsignedLongInteger (PICML::UnsignedLongInteger_in value);

  virtual void visit_LongLongInteger (PICML::LongLongInteger_in value);
  virtual void visit_UnsignedLongLongInteger (PICML::UnsignedLongLongInteger_in value);

  virtual void visit_String (PICML::String_in value);
  virtual void visit_WideString (PICML::WideString_in value);

  virtual void visit_FloatNumber (PICML::FloatNumber_in value);
  virtual void visit_DoubleNumber (PICML::DoubleNumber_in value);
  virtual void visit_LongDoubleNumber (PICML::LongDoubleNumber_in value);

  virtual void visit_GenericValue (PICML::GenericValue_in value);
  virtual void visit_GenericObject (PICML::GenericObject_in value);
  virtual void visit_GenericValueObject (PICML::GenericValueObject_in value);

  virtual void visit_TypeKind (PICML::TypeKind_in value);
  virtual void visit_TypeEncoding (PICML::TypeEncoding_in value);
};

}
}

#if defined (__CUTS_INLINE__)
#include "InOut_Type_Generator.inl"
#endif

#endif  // !defined _CUTS_BE_CCM_INOUT_TYPE_GENERATOR_H_
