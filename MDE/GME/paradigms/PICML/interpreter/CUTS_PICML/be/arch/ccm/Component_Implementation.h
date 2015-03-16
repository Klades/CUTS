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
#include "PICML/PICML.h"
#include "PICML/Visitor.h"
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

  void generate (const PICML::ComponentImplementationContainer_in container,
                 const PICML::MonolithicImplementation_in impl);
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

  void generate (const PICML::ComponentImplementationContainer_in container,
                 const PICML::MonolithicImplementation_in impl);
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

  void generate (const PICML::ComponentImplementationContainer_in container,
                 const PICML::MonolithicImplementation_in impl);
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

  void generate (const PICML::ComponentImplementationContainer_in container,
                 const PICML::MonolithicImplementation_in impl);
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

  void generate (const PICML::MonolithicImplementation_in monoimpl,
                 const PICML::Component_in component);

  virtual void Visit_ProvidedRequestPort (const PICML::ProvidedRequestPort_in facet);

  virtual void Visit_OutEventPort (const PICML::OutEventPort_in port);
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

  void generate (const PICML::MonolithicImplementation_in monoimpl,
                 const PICML::Component_in component);

  virtual void Visit_InEventPort (const PICML::InEventPort_in port);

  virtual void Visit_Input (const PICML::Input_in input);

  virtual void Visit_InputAction (const PICML::InputAction_in action);

  virtual void Visit_PeriodicEvent (const PICML::PeriodicEvent_in periodic);

  virtual void Visit_Property (const PICML::Property_in property);

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

  void generate (const PICML::MultiInputAction_in action);
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

  void generate (const PICML::MultiInputAction_in action);
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

  void generate (const PICML::ReadonlyAttribute_in readonly);
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

  void generate (const PICML::ReadonlyAttribute_in readonly);
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

  void generate (const PICML::Attribute_in attr);
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

  void generate (const PICML::Attribute_in attr);

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

  void generate (const PICML::MonolithicImplementation_in monoimpl,
                 const PICML::ComponentImplementationArtifact_in artifact);

  virtual void Visit_Implements (const PICML::Implements_in implements);

  virtual void Visit_Component (const PICML::Component_in component);
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

  void generate (const PICML::PeriodicEvent_in periodic);
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

  void generate (const PICML::PeriodicEvent_in periodic);
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

  void generate (const PICML::InEventPort_in sink,
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

  void generate (const PICML::InEventPort_in sink,
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

  void generate (const PICML::ProvidedRequestPort_in source);
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

  void generate (const PICML::ProvidedRequestPort_in source);
};

namespace CUTS_BE_CCM
{

namespace Cpp
{
/**
 * @class Attribute_Method_Generator
 */
class CUTS_BE_CCM_Export Attribute_Method_Generator : public PICML::Visitor
{
public:
  Attribute_Method_Generator (std::ostream & out);

  virtual ~Attribute_Method_Generator (void);

  virtual void Visit_Attribute (const PICML::Attribute_in attr);

  virtual void Visit_AttributeMember (const PICML::AttributeMember_in member);

  virtual void Visit_ReadonlyAttribute (const PICML::ReadonlyAttribute_in attr);

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

  virtual void Visit_InEventPort (const PICML::InEventPort_in port);

private:
  std::ostream & out_;
};

} // namespace Cpp
} // namespace CUTS_BE_CCM

#if defined (__CUTS_INLINE__)
#include "Component_Implementation.inl"
#endif

#endif // !defined _CUTS_BE_CCM_COMPONENT_IMPLEMENTATION_H_
