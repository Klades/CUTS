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
class CUTS_BE_CPP_Export Variable_Type : public Type_System
{
public:
  Variable_Type (std::ostream & out);

  virtual ~Variable_Type (void);

  virtual void Visit_Boolean (const PICML::Boolean & value);

  virtual void Visit_Byte (const PICML::Byte & );
  virtual void Visit_Char (const PICML::Char & );

  virtual void Visit_ShortInteger (const PICML::ShortInteger &);
  virtual void Visit_UnsignedShortInteger (const PICML::UnsignedShortInteger &);

  virtual void Visit_LongInteger (const PICML::LongInteger &);
  virtual void Visit_UnsignedLongInteger (const PICML::UnsignedLongInteger &);

  virtual void Visit_LongLongInteger (const PICML::LongLongInteger &);
  virtual void Visit_UnsignedLongLongInteger (const PICML::UnsignedLongLongInteger &);

  virtual void Visit_String (const PICML::String &);
  virtual void Visit_WideString (const PICML::WideString &);

  virtual void Visit_FloatNumber (const PICML::FloatNumber &);
  virtual void Visit_DoubleNumber (const PICML::DoubleNumber &);
  virtual void Visit_LongDoubleNumber (const PICML::LongDoubleNumber &);

  virtual void Visit_GenericValue (const PICML::GenericValue &);
  virtual void Visit_GenericObject (const PICML::GenericObject &);

  virtual void Visit_TypeKind (const PICML::TypeKind &);
  virtual void Visit_TypeEncoding (const PICML::TypeEncoding &);
};
}

#if defined (__CUTS_INLINE__)
#include "Variable_Type.inl"
#endif


#endif  // !defined _CUTS_BE_CPP_VARIABLE_TYPE_
