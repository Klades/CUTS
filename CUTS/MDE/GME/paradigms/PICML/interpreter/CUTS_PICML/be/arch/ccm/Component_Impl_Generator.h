// -*- C++ -*-

//=============================================================================
/**
 * @file            Component_Impl_Generator.h
 *
 * $Id$
 *
 * @author          James H. Hill
 */
//=============================================================================

#ifndef _CUTS_BE_CCM_COMPONENT_IMPL_GENERATOR_H_
#define _CUTS_BE_CCM_COMPONENT_IMPL_GENERATOR_H_

#include "PICML/PICML.h"
#include "../../UDM_Abstract_Type_Dispatcher_T.h"
#include "CCM_export.h"

namespace CUTS_BE_CCM
{
/**
 * @class Type_System
 *
 * Base class for all the type generators.
 */
class CUTS_BE_CCM_Export Type_System : public PICML::Visitor
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
 * @class In_Type_Generator
 */
class CUTS_BE_CCM_Export In_Type_Generator : public Type_System
{
public:
  In_Type_Generator (std::ostream & out);

  virtual ~In_Type_Generator (void);

  virtual void Visit_Boolean (const PICML::Boolean & value);

  virtual void Visit_Byte (const PICML::Byte & byte);

  virtual void Visit_LongInteger (const PICML::LongInteger & value);

  virtual void Visit_ShortInteger (const PICML::ShortInteger & value);

  virtual void Visit_String (const PICML::String & value);

  virtual void Visit_RealNumber (const PICML::RealNumber & value);

  virtual void Visit_GenericValue (const PICML::GenericValue & value);

  virtual void Visit_GenericObject (const PICML::GenericObject & value);

  virtual void Visit_TypeKind (const PICML::TypeKind & value);

  virtual void Visit_TypeEncoding (const PICML::TypeEncoding & value);
};

/**
 * @class Out_Type_Generator
 */
class CUTS_BE_CCM_Export Out_Type_Generator : public Type_System
{
public:
  Out_Type_Generator (std::ostream & out);

  virtual ~Out_Type_Generator (void);

  virtual void Visit_Boolean (const PICML::Boolean & value);

  virtual void Visit_Byte (const PICML::Byte & byte);

  virtual void Visit_LongInteger (const PICML::LongInteger & value);

  virtual void Visit_ShortInteger (const PICML::ShortInteger & value);

  virtual void Visit_String (const PICML::String & value);

  virtual void Visit_RealNumber (const PICML::RealNumber & value);

  virtual void Visit_GenericValue (const PICML::GenericValue & value);

  virtual void Visit_GenericObject (const PICML::GenericObject & value);

  virtual void Visit_TypeKind (const PICML::TypeKind & value);

  virtual void Visit_TypeEncoding (const PICML::TypeEncoding & value);
};

/**
 * @class In_Out_Type_Generator
 */
class CUTS_BE_CCM_Export In_Out_Type_Generator : public Type_System
{
public:
  In_Out_Type_Generator (std::ostream & out);

  virtual ~In_Out_Type_Generator (void);

  virtual void Visit_Boolean (const PICML::Boolean & value);

  virtual void Visit_Byte (const PICML::Byte & byte);

  virtual void Visit_LongInteger (const PICML::LongInteger & value);

  virtual void Visit_ShortInteger (const PICML::ShortInteger & value);

  virtual void Visit_String (const PICML::String & value);

  virtual void Visit_RealNumber (const PICML::RealNumber & value);

  virtual void Visit_GenericValue (const PICML::GenericValue & value);

  virtual void Visit_GenericObject (const PICML::GenericObject & value);

  virtual void Visit_TypeKind (const PICML::TypeKind & value);

  virtual void Visit_TypeEncoding (const PICML::TypeEncoding & value);
};

/**
 * @class Retn_Type_Generator
 *
 * Visitor responsible for generating the return type.
 */
class CUTS_BE_CCM_Export Retn_Type_Generator : public Type_System
{
public:
  Retn_Type_Generator (std::ostream & out);

  virtual ~Retn_Type_Generator (void);

  virtual void generate (const PICML::MemberType & type);

  virtual void Visit_Boolean (const PICML::Boolean & value);

  virtual void Visit_Byte (const PICML::Byte & byte);

  virtual void Visit_LongInteger (const PICML::LongInteger & value);

  virtual void Visit_ShortInteger (const PICML::ShortInteger & value);

  virtual void Visit_String (const PICML::String & value);

  virtual void Visit_RealNumber (const PICML::RealNumber & value);

  virtual void Visit_GenericValue (const PICML::GenericValue & value);

  virtual void Visit_GenericObject (const PICML::GenericObject & value);

  virtual void Visit_TypeKind (const PICML::TypeKind & value);

  virtual void Visit_TypeEncoding (const PICML::TypeEncoding & value);

private:
  bool is_variable_type (const PICML::MemberType & type);
};

/**
 * @class Attribute_Method_Generator
 */
class CUTS_BE_CCM_Export Attribute_Method_Generator : public PICML::Visitor
{
public:
  Attribute_Method_Generator (std::ostream & out);

  virtual ~Attribute_Method_Generator (void);

  virtual void Visit_Attribute (const PICML::Attribute & attr);

  virtual void Visit_AttributeMember (const PICML::AttributeMember & member);

  virtual void Visit_ReadonlyAttribute (const PICML::ReadonlyAttribute & attr);

private:
  std::ostream & out_;
};

/**
 * @class InEvent_Method_Generator
 */
class CUTS_BE_CCM_Export InEvent_Method_Generator : public PICML::Visitor
{
public:
  InEvent_Method_Generator (std::ostream & out);

  virtual ~InEvent_Method_Generator (void);

  virtual void Visit_InEventPort (const PICML::InEventPort & port);

private:
  std::ostream & out_;
};

};

#endif // !defined _CUTS_BE_CCM_COMPONENT_IMPL_GENERATOR_H_
