// -*- C++ -*-

//=============================================================================
/**
 * @file        Variable_Type.h
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _CUTS_BE_CPP_VARIABLE_TYPE_
#define _CUTS_BE_CPP_VARIABLE_TYPE_

#include <ostream>
#include "PICML/PICML.h"
#include "PICML/Visitor.h"
#include "Java_export.h"

namespace CUTS_BE_Java
{
/**
 * @class Type_System
 *
 * Base class for all the type generators.
 */
class CUTS_BE_JAVA_Export Type_System : public PICML::Visitor
{
public:
  /// Destructor.
  virtual ~Type_System (void);

  /**
   * Generate the type information for the member type.
   *
   * @param[in]       mt        Member type of interest.
   */
  virtual void generate (const PICML::MemberType_in mt);

protected:
  /// Default constructor.
  Type_System (std::ostream & out);

  /// Target output stream.
  std::ostream & out_;
};

/**
 * @class Var_Type_Generator
 *
 * Visitor responsible for generating the return type.
 */
class CUTS_BE_JAVA_Export Variable_Type : public Type_System
{
public:
  Variable_Type (std::ostream & out);

  virtual ~Variable_Type (void);

  virtual void Visit_Boolean (PICML::Boolean_in value);

  virtual void Visit_Byte (PICML::Byte_in byte);

  virtual void Visit_LongInteger (PICML::LongInteger_in value);
  virtual void Visit_UnsignedLongInteger (PICML::UnsignedLongInteger_in value);

  virtual void Visit_ShortInteger (PICML::ShortInteger_in value);
  virtual void Visit_UnsignedShortInteger (PICML::UnsignedShortInteger_in value);

  virtual void Visit_String (PICML::String_in value);

  virtual void Visit_DoubleNumber (PICML::DoubleNumber_in value);
  virtual void Visit_FloatNumber (PICML::FloatNumber_in value);

  virtual void Visit_GenericValue (PICML::GenericValue_in value);

  virtual void Visit_GenericObject (PICML::GenericObject_in value);

  virtual void Visit_TypeKind (PICML::TypeKind_in value);

  virtual void Visit_TypeEncoding (PICML::TypeEncoding_in value);
};
}

#if defined (__CUTS_INLINE__)
#include "Java_Variable_Type.inl"
#endif


#endif  // !defined _CUTS_BE_CPP_VARIABLE_TYPE_
