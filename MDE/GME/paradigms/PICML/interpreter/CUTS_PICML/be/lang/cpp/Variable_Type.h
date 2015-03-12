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
#include "Cpp_export.h"

namespace CUTS_BE_CPP
{
/**
 * @class Type_System
 *
 * Base class for all the type generators.
 */
class CUTS_BE_CPP_Export Type_System : public PICML::Visitor
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

  /// Help for dispatching predefined type objects.
  //UDM_Abstract_Type_Dispatcher_T <PICML::Visitor> predefined_types_;
};

/**
 * @class Var_Type_Generator
 *
 * Visitor responsible for generating the return type.
 */
class CUTS_BE_CPP_Export Variable_Type : public Type_System
{
public:
  Variable_Type (std::ostream & out);

  virtual ~Variable_Type (void);

  virtual void Visit_Boolean (const PICML::Boolean_in value);

  virtual void Visit_Byte (const PICML::Byte_in );
  virtual void Visit_Char (const PICML::Char_in );

  virtual void Visit_ShortInteger (const PICML::ShortInteger_in);
  virtual void Visit_UnsignedShortInteger (const PICML::UnsignedShortInteger_in);

  virtual void Visit_LongInteger (const PICML::LongInteger_in);
  virtual void Visit_UnsignedLongInteger (const PICML::UnsignedLongInteger_in);

  virtual void Visit_LongLongInteger (const PICML::LongLongInteger_in);
  virtual void Visit_UnsignedLongLongInteger (const PICML::UnsignedLongLongInteger_in);

  virtual void Visit_String (const PICML::String_in);
  virtual void Visit_WideString (const PICML::WideString_in);

  virtual void Visit_FloatNumber (const PICML::FloatNumber_in);
  virtual void Visit_DoubleNumber (const PICML::DoubleNumber_in);
  virtual void Visit_LongDoubleNumber (const PICML::LongDoubleNumber_in);

  virtual void Visit_GenericValue (const PICML::GenericValue_in);
  virtual void Visit_GenericObject (const PICML::GenericObject_in);

  virtual void Visit_TypeKind (const PICML::TypeKind_in);
  virtual void Visit_TypeEncoding (const PICML::TypeEncoding_in);
};
}

#if defined (__CUTS_INLINE__)
#include "Variable_Type.inl"
#endif


#endif  // !defined _CUTS_BE_CPP_VARIABLE_TYPE_
