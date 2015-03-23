// -*- C++ -*-

//=============================================================================
/**
 * @file          Out_Type_Generator.h
 *
 * $Id$
 *
 * @author        James H. Hill
 */
//=============================================================================

#ifndef _CUTS_BE_CCM_OUT_TYPE_GENERATOR_H_
#define _CUTS_BE_CCM_OUT_TYPE_GENERATOR_H_

#include "Type_System.h"

namespace CUTS_BE_CCM
{
namespace Cpp
{

/**
 * @class Out_Type_Generator
 *
 * Visitor that generates the output parameter for a type.
 */
class CUTS_BE_CCM_Export Out_Type_Generator : public CUTS_BE_CCM::Type_System
{
public:
  Out_Type_Generator (std::ostream & out);

  virtual ~Out_Type_Generator (void);

  virtual void visit_Boolean (PICML::Boolean_in value);

  virtual void visit_Byte (PICML::Byte_in );
  virtual void visit_Char (PICML::Char_in );
  virtual void visit_WideChar (PICML::WideChar_in );

  virtual void visit_ShortInteger (PICML::ShortInteger_in );
  virtual void visit_UnsignedShortInteger (PICML::UnsignedShortInteger_in);

  virtual void visit_LongInteger (PICML::LongInteger_in );
  virtual void visit_UnsignedLongInteger (PICML::UnsignedLongInteger_in);

  virtual void visit_LongLongInteger (PICML::LongLongInteger_in );
  virtual void visit_UnsignedLongLongInteger (PICML::UnsignedLongLongInteger_in );

  virtual void visit_String (PICML::String_in );
  virtual void visit_WideString (PICML::WideString_in );

  virtual void visit_FloatNumber (PICML::FloatNumber_in );
  virtual void visit_DoubleNumber (PICML::DoubleNumber_in );
  virtual void visit_LongDoubleNumber (PICML::LongDoubleNumber_in );

  virtual void visit_GenericValue (PICML::GenericValue_in);
  virtual void visit_GenericObject (PICML::GenericObject_in );
  virtual void visit_GenericValueObject (PICML::GenericValueObject_in);

  virtual void visit_TypeKind (PICML::TypeKind_in );
  virtual void visit_TypeEncoding (PICML::TypeEncoding_in );
};

}
}

#if defined (__CUTS_INLINE__)
#include "Out_Type_Generator.inl"
#endif

#endif  // !defined _CUTS_BE_CCM_OUT_TYPE_GENERATOR_H_
