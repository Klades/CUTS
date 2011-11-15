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

  virtual void Visit_Boolean (const PICML::Boolean & value);

  virtual void Visit_Byte (const PICML::Byte & );
  virtual void Visit_Char (const PICML::Char & );
  virtual void Visit_WideChar (const PICML::WideChar & );

  virtual void Visit_ShortInteger (const PICML::ShortInteger & );
  virtual void Visit_UnsignedShortInteger (const PICML::UnsignedShortInteger &);

  virtual void Visit_LongInteger (const PICML::LongInteger & );
  virtual void Visit_UnsignedLongInteger (const PICML::UnsignedLongInteger &);

  virtual void Visit_LongLongInteger (const PICML::LongLongInteger & );
  virtual void Visit_UnsignedLongLongInteger (const PICML::UnsignedLongLongInteger & );

  virtual void Visit_String (const PICML::String & );
  virtual void Visit_WideString (const PICML::WideString & );

  virtual void Visit_FloatNumber (const PICML::FloatNumber & );
  virtual void Visit_DoubleNumber (const PICML::DoubleNumber & );
  virtual void Visit_LongDoubleNumber (const PICML::LongDoubleNumber & );

  virtual void Visit_GenericValue (const PICML::GenericValue &);
  virtual void Visit_GenericObject (const PICML::GenericObject & );
  virtual void Visit_GenericValueObject (const PICML::GenericValueObject &);

  virtual void Visit_TypeKind (const PICML::TypeKind & );
  virtual void Visit_TypeEncoding (const PICML::TypeEncoding & );
};

}
}

#if defined (__CUTS_INLINE__)
#include "Out_Type_Generator.inl"
#endif

#endif  // !defined _CUTS_BE_CCM_OUT_TYPE_GENERATOR_H_
