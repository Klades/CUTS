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
#include "../../UDM_Abstract_Type_Dispatcher_T.h"
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
  virtual void generate (const PICML::MemberType & mt);

protected:
  /// Default constructor.
  Type_System (std::ostream & out);

  /// Target output stream.
  std::ostream & out_;

  /// Help for dispatching predefined type objects.
  UDM_Abstract_Type_Dispatcher_T <PICML::Visitor> predefined_types_;
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

  virtual void Visit_Boolean (const PICML::Boolean & value);

  virtual void Visit_Byte (const PICML::Byte & byte);

  virtual void Visit_LongInteger (const PICML::LongInteger & value);

  virtual void Visit_ShortInteger (const PICML::ShortInteger & value);

  virtual void Visit_String (const PICML::String & value);

  virtual void Visit_DoubleNumber (const PICML::DoubleNumber & value);

  virtual void Visit_FloatNumber (const PICML::FloatNumber & value);

  virtual void Visit_GenericValue (const PICML::GenericValue & value);

  virtual void Visit_GenericObject (const PICML::GenericObject & value);

  virtual void Visit_TypeKind (const PICML::TypeKind & value);

  virtual void Visit_TypeEncoding (const PICML::TypeEncoding & value);
};
}

#if defined (__CUTS_INLINE__)
#include "Java_Variable_Type.inl"
#endif


#endif  // !defined _CUTS_BE_CPP_VARIABLE_TYPE_
