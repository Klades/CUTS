// -*- C++ -*-

//=============================================================================
/**
 * @file            Component_Implementation.h
 *
 * $Id$
 *
 * @author          James H. Hill
 */
//=============================================================================

#ifndef _CUTS_BE_CCM_COMPONENT_IMPLEMENTATION_H_
#define _CUTS_BE_CCM_COMPONENT_IMPLEMENTATION_H_

#include "../../BE_Generators_T.h"
#include "../../UDM_Abstract_Type_Dispatcher_T.h"
#include "PICML/PICML.h"
#include "CCM.h"

/**
 * @class CUTS_BE_File_Open_T <CUTS_BE_CCM::Cpp::Context>
 *
 * Specialization of the CUTS_BE_File_Open_T class.
 */
template < >
class CUTS_BE_CCM_Export CUTS_BE_File_Open_T <CUTS_BE_CCM::Cpp::Context> :
  public CUTS_BE_Visitor_T <CUTS_BE_CCM::Cpp::Context, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE_CCM::Cpp::Context, PICML::Visitor> visitor_type;

  CUTS_BE_File_Open_T (CUTS_BE_CCM::Cpp::Context & context);

  virtual ~CUTS_BE_File_Open_T (void);

  void generate (const PICML::ComponentImplementationContainer & container,
                 const PICML::MonolithicImplementation & impl);
};


/**
 * @class CUTS_BE_File_Close_T
 */
template < >
class CUTS_BE_CCM_Export CUTS_BE_File_Close_T <CUTS_BE_CCM::Cpp::Context> :
  public CUTS_BE_Visitor_T <CUTS_BE_CCM::Cpp::Context, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE_CCM::Cpp::Context, PICML::Visitor> visitor_type;

  CUTS_BE_File_Close_T (CUTS_BE_CCM::Cpp::Context & context);

  virtual ~CUTS_BE_File_Close_T (void);

  void generate (const PICML::ComponentImplementationContainer & container,
                 const PICML::MonolithicImplementation & impl);
};

/**
 * @class CUTS_BE_Prologue_T
 */
template < >
class CUTS_BE_CCM_Export CUTS_BE_Prologue_T <CUTS_BE_CCM::Cpp::Context> :
  public CUTS_BE_Visitor_T <CUTS_BE_CCM::Cpp::Context, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE_CCM::Cpp::Context, PICML::Visitor> visitor_type;

  CUTS_BE_Prologue_T (CUTS_BE_CCM::Cpp::Context & context);

  virtual ~CUTS_BE_Prologue_T (void);

  void generate (const PICML::ComponentImplementationContainer & container,
                 const PICML::MonolithicImplementation & impl);
};

/**
 * @class CUTS_BE_Epilogue_T
 */
template < >
class CUTS_BE_CCM_Export CUTS_BE_Epilogue_T <CUTS_BE_CCM::Cpp::Context> :
  public CUTS_BE_Visitor_T <CUTS_BE_CCM::Cpp::Context, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE_CCM::Cpp::Context, PICML::Visitor> visitor_type;

  CUTS_BE_Epilogue_T (CUTS_BE_CCM::Cpp::Context & context);

  virtual ~CUTS_BE_Epilogue_T (void);

  void generate (const PICML::ComponentImplementationContainer & container,
                 const PICML::MonolithicImplementation & impl);
};

/**
 * @class CUTS_BE_Component_Impl_Begin_T
 *
 * Specialization of the CUTS_BE_Component_Impl_Begin_T class
 */
template < >
class CUTS_BE_CCM_Export CUTS_BE_Component_Impl_Begin_T <CUTS_BE_CCM::Cpp::Context> :
  public CUTS_BE_Visitor_T <CUTS_BE_CCM::Cpp::Context, PICML::Visitor>
{
public:
  typedef public CUTS_BE_Visitor_T <CUTS_BE_CCM::Cpp::Context, PICML::Visitor> visitor_type;

  CUTS_BE_Component_Impl_Begin_T (CUTS_BE_CCM::Cpp::Context & context);

  virtual ~CUTS_BE_Component_Impl_Begin_T (void);

  void generate (const PICML::MonolithicImplementation & monoimpl,
                 const PICML::Component & component);

  virtual void Visit_ProvidedRequestPort (const PICML::ProvidedRequestPort & facet);

  virtual void Visit_OutEventPort (const PICML::OutEventPort & port);
};

/**
 * @class CUTS_BE_Component_Impl_End_T
 *
 * Specialization of the CUTS_BE_Component_Impl_End_T class
 */
template < >
class CUTS_BE_CCM_Export CUTS_BE_Component_Impl_End_T <CUTS_BE_CCM::Cpp::Context> :
  public CUTS_BE_Visitor_T <CUTS_BE_CCM::Cpp::Context, PICML::Visitor>
{
public:
  typedef public CUTS_BE_Visitor_T <CUTS_BE_CCM::Cpp::Context, PICML::Visitor> visitor_type;

  CUTS_BE_Component_Impl_End_T (CUTS_BE_CCM::Cpp::Context & context);

  virtual ~CUTS_BE_Component_Impl_End_T (void);

  void generate (const PICML::MonolithicImplementation & monoimpl,
                 const PICML::Component & component);

  virtual void Visit_InEventPort (const PICML::InEventPort & port);

  virtual void Visit_Input (const PICML::Input & input);

  virtual void Visit_InputAction (const PICML::InputAction & action);

  virtual void Visit_PeriodicEvent (const PICML::PeriodicEvent & periodic);

  virtual void Visit_Property (const PICML::Property & property);

private:
  std::string sink_name_;
};

/**
 * @class CUTS_BE_Environment_Method_Begin_T
 *
 * Specialization of the CUTS_BE_Environment_Method_Begin_T method.
 */
template < >
class CUTS_BE_CCM_Export CUTS_BE_Environment_Method_Begin_T <CUTS_BE_CCM::Cpp::Context> :
  public CUTS_BE_Visitor_T <CUTS_BE_CCM::Cpp::Context, PICML::Visitor>
{
public:
  typedef public CUTS_BE_Visitor_T <CUTS_BE_CCM::Cpp::Context, PICML::Visitor> visitor_type;

  CUTS_BE_Environment_Method_Begin_T (CUTS_BE_CCM::Cpp::Context & context);

  virtual ~CUTS_BE_Environment_Method_Begin_T (void);

  void generate (const PICML::MultiInputAction & action);
};

/**
 * @class CUTS_BE_Environment_Method_End_T
 *
 * Specialization of the CUTS_BE_Environment_Method_End_T method.
 */
template < >
class CUTS_BE_CCM_Export CUTS_BE_Environment_Method_End_T <CUTS_BE_CCM::Cpp::Context> :
  public CUTS_BE_Visitor_T <CUTS_BE_CCM::Cpp::Context, PICML::Visitor>
{
public:
  typedef public CUTS_BE_Visitor_T <CUTS_BE_CCM::Cpp::Context, PICML::Visitor> visitor_type;

  CUTS_BE_Environment_Method_End_T (CUTS_BE_CCM::Cpp::Context & context);

  virtual ~CUTS_BE_Environment_Method_End_T (void);

  void generate (const PICML::MultiInputAction & action);
};

/**
 * @class CUTS_BE_ReadonlyAttribute_Begin_T
 */
template < >
class CUTS_BE_CCM_Export CUTS_BE_ReadonlyAttribute_Begin_T <CUTS_BE_CCM::Cpp::Context> :
  public CUTS_BE_Visitor_T <CUTS_BE_CCM::Cpp::Context, PICML::Visitor>
{
public:
  typedef public CUTS_BE_Visitor_T <CUTS_BE_CCM::Cpp::Context, PICML::Visitor> visitor_type;

  CUTS_BE_ReadonlyAttribute_Begin_T (CUTS_BE_CCM::Cpp::Context & context);

  virtual ~CUTS_BE_ReadonlyAttribute_Begin_T (void);

  void generate (const PICML::ReadonlyAttribute & readonly);
};

/**
 * @class CUTS_BE_ReadonlyAttribute_End_T
 */
template < >
class CUTS_BE_CCM_Export CUTS_BE_ReadonlyAttribute_End_T <CUTS_BE_CCM::Cpp::Context> :
  public CUTS_BE_Visitor_T <CUTS_BE_CCM::Cpp::Context, PICML::Visitor>
{
public:
  typedef public CUTS_BE_Visitor_T <CUTS_BE_CCM::Cpp::Context, PICML::Visitor> visitor_type;

  CUTS_BE_ReadonlyAttribute_End_T (CUTS_BE_CCM::Cpp::Context & context);

  virtual ~CUTS_BE_ReadonlyAttribute_End_T (void);

  void generate (const PICML::ReadonlyAttribute & readonly);
};

/**
 * @class CUTS_BE_Attribute_Begin_T
 */
template < >
class CUTS_BE_CCM_Export CUTS_BE_Attribute_Begin_T <CUTS_BE_CCM::Cpp::Context>  :
  public CUTS_BE_Visitor_T <CUTS_BE_CCM::Cpp::Context, PICML::Visitor>
{
public:
  typedef public CUTS_BE_Visitor_T <CUTS_BE_CCM::Cpp::Context, PICML::Visitor> visitor_type;

  CUTS_BE_Attribute_Begin_T (CUTS_BE_CCM::Cpp::Context & context);

  virtual ~CUTS_BE_Attribute_Begin_T (void);

  void generate (const PICML::Attribute & attr);
};

/**
 * @class CUTS_BE_Attribute_End_T
 */
template < >
class CUTS_BE_CCM_Export CUTS_BE_Attribute_End_T <CUTS_BE_CCM::Cpp::Context> :
  public CUTS_BE_Visitor_T <CUTS_BE_CCM::Cpp::Context, PICML::Visitor>
{
public:
  typedef public CUTS_BE_Visitor_T <CUTS_BE_CCM::Cpp::Context, PICML::Visitor> visitor_type;

  CUTS_BE_Attribute_End_T (CUTS_BE_CCM::Cpp::Context & context);

  virtual ~CUTS_BE_Attribute_End_T (void);

  void generate (const PICML::Attribute & attr);

private:
  CUTS_BE_ReadonlyAttribute_Begin_T <CUTS_BE_CCM::Cpp::Context> readonly_begin_;

  CUTS_BE_ReadonlyAttribute_End_T <CUTS_BE_CCM::Cpp::Context> readonly_end_;
};

/**
 * @class CUTS_BE_Component_Impl_Entrypoint_T
 */
template < >
class CUTS_BE_CCM_Export CUTS_BE_Component_Impl_Entrypoint_T <CUTS_BE_CCM::Cpp::Context> :
  public CUTS_BE_Visitor_T <CUTS_BE_CCM::Cpp::Context, PICML::Visitor>
{
public:
  typedef public CUTS_BE_Visitor_T <CUTS_BE_CCM::Cpp::Context, PICML::Visitor> visitor_type;

  CUTS_BE_Component_Impl_Entrypoint_T (CUTS_BE_CCM::Cpp::Context & context);

  virtual ~CUTS_BE_Component_Impl_Entrypoint_T (void);

  void generate (const PICML::MonolithicImplementation & monoimpl,
                 const PICML::ComponentImplementationArtifact & artifact);

  virtual void Visit_Implements (const PICML::Implements & implements);

  virtual void Visit_Component (const PICML::Component & component);
};

/**
 * @class CUTS_BE_PeriodicEvent_Begin_T
 */
template < >
class CUTS_BE_CCM_Export CUTS_BE_PeriodicEvent_Begin_T <CUTS_BE_CCM::Cpp::Context> :
  public CUTS_BE_Visitor_T <CUTS_BE_CCM::Cpp::Context, PICML::Visitor>
{
public:
  typedef public CUTS_BE_Visitor_T <CUTS_BE_CCM::Cpp::Context, PICML::Visitor> visitor_type;

  CUTS_BE_PeriodicEvent_Begin_T (CUTS_BE_CCM::Cpp::Context & context);

  virtual ~CUTS_BE_PeriodicEvent_Begin_T (void);

  void generate (const PICML::PeriodicEvent & periodic);
};

/**
 * @class CUTS_BE_PeriodicEvent_End_T
 */
template < >
class CUTS_BE_CCM_Export CUTS_BE_PeriodicEvent_End_T <CUTS_BE_CCM::Cpp::Context> :
  public CUTS_BE_Visitor_T <CUTS_BE_CCM::Cpp::Context, PICML::Visitor>
{
public:
  typedef public CUTS_BE_Visitor_T <CUTS_BE_CCM::Cpp::Context, PICML::Visitor> visitor_type;

  CUTS_BE_PeriodicEvent_End_T (CUTS_BE_CCM::Cpp::Context & context);

  virtual ~CUTS_BE_PeriodicEvent_End_T (void);

  void generate (const PICML::PeriodicEvent & periodic);
};

/**
 * @class CUTS_BE_Include_File_T <CUTS_BE_CCM::Cpp::Context>
 *
 * Specialization of the CUTS_BE_Include_File_T class.
 */
template < >
class CUTS_BE_CCM_Export CUTS_BE_Include_File_T <CUTS_BE_CCM::Cpp::Context> :
  public CUTS_BE_Visitor_T <CUTS_BE_CCM::Cpp::Context, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE_CCM::Cpp::Context, PICML::Visitor> visitor_type;

  CUTS_BE_Include_File_T (CUTS_BE_CCM::Cpp::Context & context);

  virtual ~CUTS_BE_Include_File_T (void);

  virtual void generate (const std::string & include);
};

/**
 * @class CUTS_BE_InEventPort_Begin_T
 */
template < >
class CUTS_BE_CCM_Export CUTS_BE_InEventPort_Begin_T <CUTS_BE_CCM::Cpp::Context> :
  public CUTS_BE_Visitor_T <CUTS_BE_CCM::Cpp::Context, PICML::Visitor>
{
public:
  typedef public CUTS_BE_Visitor_T <CUTS_BE_CCM::Cpp::Context, PICML::Visitor> visitor_type;

  CUTS_BE_InEventPort_Begin_T (CUTS_BE_CCM::Cpp::Context & context);

  virtual ~CUTS_BE_InEventPort_Begin_T (void);

  void generate (const PICML::InEventPort & sink,
                 const std::vector <PICML::Property> & properties);
};

/**
 * @class CUTS_BE_InEventPort_End_T
 */
template < >
class CUTS_BE_CCM_Export CUTS_BE_InEventPort_End_T <CUTS_BE_CCM::Cpp::Context> :
  public CUTS_BE_Visitor_T <CUTS_BE_CCM::Cpp::Context, PICML::Visitor>
{
public:
  typedef public CUTS_BE_Visitor_T <CUTS_BE_CCM::Cpp::Context, PICML::Visitor> visitor_type;

  CUTS_BE_InEventPort_End_T (CUTS_BE_CCM::Cpp::Context & context);

  virtual ~CUTS_BE_InEventPort_End_T (void);

  void generate (const PICML::InEventPort & sink,
                 const std::vector <PICML::Property> & properties);
};

/**
 * @class CUTS_BE_ProvidedRequestPort_Begin_T
 */
template < >
class CUTS_BE_CCM_Export CUTS_BE_ProvidedRequestPort_Begin_T <CUTS_BE_CCM::Cpp::Context> :
  public CUTS_BE_Visitor_T <CUTS_BE_CCM::Cpp::Context, PICML::Visitor>
{
public:
  typedef public CUTS_BE_Visitor_T <CUTS_BE_CCM::Cpp::Context, PICML::Visitor> visitor_type;

  CUTS_BE_ProvidedRequestPort_Begin_T (CUTS_BE_CCM::Cpp::Context & context);

  virtual ~CUTS_BE_ProvidedRequestPort_Begin_T (void);

  void generate (const PICML::ProvidedRequestPort & source);
};

/**
 * @class CUTS_BE_ProvidedRequestPort_End_T
 */
template < >
class CUTS_BE_CCM_Export CUTS_BE_ProvidedRequestPort_End_T <CUTS_BE_CCM::Cpp::Context> :
  public CUTS_BE_Visitor_T <CUTS_BE_CCM::Cpp::Context, PICML::Visitor>
{
public:
  typedef public CUTS_BE_Visitor_T <CUTS_BE_CCM::Cpp::Context, PICML::Visitor> visitor_type;

  CUTS_BE_ProvidedRequestPort_End_T (CUTS_BE_CCM::Cpp::Context & context);

  virtual ~CUTS_BE_ProvidedRequestPort_End_T (void);

  void generate (const PICML::ProvidedRequestPort & source);
};

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

namespace Cpp
{
/**
 * @class In_Type_Generator
 */
class CUTS_BE_CCM_Export In_Type_Generator : public CUTS_BE_CCM::Type_System
{
public:
  In_Type_Generator (std::ostream & out);

  virtual ~In_Type_Generator (void);

  virtual void Visit_Boolean (const PICML::Boolean & value);

  virtual void Visit_Byte (const PICML::Byte & byte);

  virtual void Visit_LongInteger (const PICML::LongInteger & value);

  virtual void Visit_ShortInteger (const PICML::ShortInteger & value);

  virtual void Visit_String (const PICML::String & value);

  virtual void Visit_DoubleNumber (const PICML::DoubleNumber & value);

  virtual void Visit_GenericValue (const PICML::GenericValue & value);

  virtual void Visit_GenericObject (const PICML::GenericObject & value);

  virtual void Visit_TypeKind (const PICML::TypeKind & value);

  virtual void Visit_TypeEncoding (const PICML::TypeEncoding & value);
};

/**
 * @class Out_Type_Generator
 */
class CUTS_BE_CCM_Export Out_Type_Generator : public CUTS_BE_CCM::Type_System
{
public:
  Out_Type_Generator (std::ostream & out);

  virtual ~Out_Type_Generator (void);

  virtual void Visit_Boolean (const PICML::Boolean & value);

  virtual void Visit_Byte (const PICML::Byte & byte);

  virtual void Visit_LongInteger (const PICML::LongInteger & value);

  virtual void Visit_ShortInteger (const PICML::ShortInteger & value);

  virtual void Visit_String (const PICML::String & value);

  virtual void Visit_DoubleNumber (const PICML::DoubleNumber & value);

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

  virtual void Visit_DoubleNumber (const PICML::DoubleNumber & value);

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
class CUTS_BE_CCM_Export Retn_Type_Generator : public CUTS_BE_CCM::Type_System
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

  virtual void Visit_DoubleNumber (const PICML::DoubleNumber & value);

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

} // namespace Cpp
} // namespace CUTS_BE_CCM

#if defined (__CUTS_INLINE__)
#include "Component_Implementation.inl"
#endif

#endif // !defined _CUTS_BE_CCM_COMPONENT_IMPLEMENTATION_H_
