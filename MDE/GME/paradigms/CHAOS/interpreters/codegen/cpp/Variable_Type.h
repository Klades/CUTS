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
#include "../../paradigms/CHAOS.h"
#include "../UDM_Abstract_Type_Dispatcher_T.h"

namespace CUTS_BE_CPP
{
/**
 * @class Type_System
 *
 * Base class for all the type generators.
 */
class Type_System : public CHAOS::Visitor
{
public:
  /// Destructor.
  virtual ~Type_System (void);

  /**
   * Generate the type information for the member type.
   *
   * @param[in]       mt        Member type of interest.
   */
  virtual void generate (const CHAOS::MemberType & mt);

protected:
  /// Default constructor.
  Type_System (std::ostream & out);

  /// Target output stream.
  std::ostream & out_;

  /// Help for dispatching predefined type objects.
  UDM_Abstract_Type_Dispatcher_T <CHAOS::Visitor> predefined_types_;
};

/**
 * @class Var_Type_Generator
 *
 * Visitor responsible for generating the return type.
 */
class Variable_Type : public Type_System
{
public:
  Variable_Type (std::ostream & out);

  virtual ~Variable_Type (void);

  virtual void Visit_Boolean (const CHAOS::Boolean & value);

  virtual void Visit_Byte (const CHAOS::Byte & byte);

  virtual void Visit_LongInteger (const CHAOS::LongInteger & value);

  virtual void Visit_ShortInteger (const CHAOS::ShortInteger & value);

  virtual void Visit_String (const CHAOS::String & value);

  virtual void Visit_RealNumber (const CHAOS::RealNumber & value);

  virtual void Visit_GenericValue (const CHAOS::GenericValue & value);

  virtual void Visit_GenericObject (const CHAOS::GenericObject & value);

  virtual void Visit_TypeKind (const CHAOS::TypeKind & value);

  virtual void Visit_TypeEncoding (const CHAOS::TypeEncoding & value);
};
}

#if defined (__CUTS_INLINE__)
#include "Variable_Type.inl"
#endif


#endif  // !defined _CUTS_BE_CPP_VARIABLE_TYPE_
