// -*- C++ -*-

//=============================================================================
/**
 * @file      CIAO_Generators.h
 *
 * $Id$
 *
 * @author    James H. Hill
 */
//=============================================================================

#ifndef _CUTS_BE_CIAO_GENERATORS_H_
#define _CUTS_BE_CIAO_GENERATORS_H_

#include "../../BE_Workspace_Generators_T.h"
#include "../../BE_Project_Generators_T.h"
#include "../../String_Set.h"
#include "../../lang/cpp/Behavior_Generator.h"
#include "CIAO_Ctx.h"

// Forward decl.
struct CUTS_BE_Impl_Node;

// Forward decl.
struct CUTS_BE_IDL_Node;

/**
 * @class CUTS_BE_File_Open_T <CUTS_BE_Ciao>
 *
 * Specialization of the CUTS_BE_File_Open_T class.
 */
template < >
class CUTS_BE_File_Open_T <CUTS_BE_Ciao> :
  public CUTS_BE_Visitor_T <CUTS_BE_Ciao, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE_Ciao, PICML::Visitor> visitor_type;

  CUTS_BE_File_Open_T (CUTS_BE_Ciao & context);

  virtual ~CUTS_BE_File_Open_T (void);

  void generate (const PICML::ComponentImplementationContainer & container,
                 const PICML::MonolithicImplementation & impl);
};

/**
 * @class CUTS_BE_File_Close_T
 */
template < >
class CUTS_BE_File_Close_T <CUTS_BE_Ciao> :
  public CUTS_BE_Visitor_T <CUTS_BE_Ciao, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE_Ciao, PICML::Visitor> visitor_type;

  CUTS_BE_File_Close_T (CUTS_BE_Ciao & context);

  virtual ~CUTS_BE_File_Close_T (void);

  void generate (const PICML::ComponentImplementationContainer & container,
                 const PICML::MonolithicImplementation & impl);
};

/**
 * @class CUTS_BE_Prologue_T
 */
template < >
class CUTS_BE_Prologue_T <CUTS_BE_Ciao> :
  public CUTS_BE_Visitor_T <CUTS_BE_Ciao, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE_Ciao, PICML::Visitor> visitor_type;

  CUTS_BE_Prologue_T (CUTS_BE_Ciao & context);

  virtual ~CUTS_BE_Prologue_T (void);

  void generate (const PICML::ComponentImplementationContainer & container,
                 const PICML::MonolithicImplementation & impl);
};

/**
 * @class CUTS_BE_Epilogue_T
 */
template < >
class CUTS_BE_Epilogue_T <CUTS_BE_Ciao> :
  public CUTS_BE_Visitor_T <CUTS_BE_Ciao, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE_Ciao, PICML::Visitor> visitor_type;

  CUTS_BE_Epilogue_T (CUTS_BE_Ciao & context);

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
class CUTS_BE_Component_Impl_Begin_T <CUTS_BE_Ciao> :
  public CUTS_BE_Visitor_T <CUTS_BE_Ciao, PICML::Visitor>
{
public:
  typedef public CUTS_BE_Visitor_T <CUTS_BE_Ciao, PICML::Visitor> visitor_type;

  CUTS_BE_Component_Impl_Begin_T (CUTS_BE_Ciao & context);

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
class CUTS_BE_Component_Impl_End_T <CUTS_BE_Ciao> :
  public CUTS_BE_Visitor_T <CUTS_BE_Ciao, PICML::Visitor>
{
public:
  typedef public CUTS_BE_Visitor_T <CUTS_BE_Ciao, PICML::Visitor> visitor_type;

  CUTS_BE_Component_Impl_End_T (CUTS_BE_Ciao & context);

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
class CUTS_BE_Environment_Method_Begin_T <CUTS_BE_Ciao> :
  public CUTS_BE_Visitor_T <CUTS_BE_Ciao, PICML::Visitor>
{
public:
  typedef public CUTS_BE_Visitor_T <CUTS_BE_Ciao, PICML::Visitor> visitor_type;

  CUTS_BE_Environment_Method_Begin_T (CUTS_BE_Ciao & context);

  virtual ~CUTS_BE_Environment_Method_Begin_T (void);

  void generate (const PICML::MultiInputAction & action);
};

/**
 * @class CUTS_BE_Environment_Method_End_T
 *
 * Specialization of the CUTS_BE_Environment_Method_End_T method.
 */
template < >
class CUTS_BE_Environment_Method_End_T <CUTS_BE_Ciao> :
  public CUTS_BE_Visitor_T <CUTS_BE_Ciao, PICML::Visitor>
{
public:
  typedef public CUTS_BE_Visitor_T <CUTS_BE_Ciao, PICML::Visitor> visitor_type;

  CUTS_BE_Environment_Method_End_T (CUTS_BE_Ciao & context);

  virtual ~CUTS_BE_Environment_Method_End_T (void);

  void generate (const PICML::MultiInputAction & action);
};

/**
 * @class CUTS_BE_ReadonlyAttribute_Begin_T
 */
template < >
class CUTS_BE_ReadonlyAttribute_Begin_T <CUTS_BE_Ciao> :
  public CUTS_BE_Visitor_T <CUTS_BE_Ciao, PICML::Visitor>
{
public:
  typedef public CUTS_BE_Visitor_T <CUTS_BE_Ciao, PICML::Visitor> visitor_type;

  CUTS_BE_ReadonlyAttribute_Begin_T (CUTS_BE_Ciao & context);

  virtual ~CUTS_BE_ReadonlyAttribute_Begin_T (void);

  void generate (const PICML::ReadonlyAttribute & readonly);
};

/**
 * @class CUTS_BE_ReadonlyAttribute_End_T
 */
template < >
class CUTS_BE_ReadonlyAttribute_End_T <CUTS_BE_Ciao> :
  public CUTS_BE_Visitor_T <CUTS_BE_Ciao, PICML::Visitor>
{
public:
  typedef public CUTS_BE_Visitor_T <CUTS_BE_Ciao, PICML::Visitor> visitor_type;

  CUTS_BE_ReadonlyAttribute_End_T (CUTS_BE_Ciao & context);

  virtual ~CUTS_BE_ReadonlyAttribute_End_T (void);

  void generate (const PICML::ReadonlyAttribute & readonly);
};

/**
 * @class CUTS_BE_Attribute_Begin_T
 */
template < >
class CUTS_BE_Attribute_Begin_T <CUTS_BE_Ciao>  :
  public CUTS_BE_Visitor_T <CUTS_BE_Ciao, PICML::Visitor>
{
public:
  typedef public CUTS_BE_Visitor_T <CUTS_BE_Ciao, PICML::Visitor> visitor_type;

  CUTS_BE_Attribute_Begin_T (CUTS_BE_Ciao & context);

  virtual ~CUTS_BE_Attribute_Begin_T (void);

  void generate (const PICML::Attribute & attr);
};

/**
 * @class CUTS_BE_Attribute_End_T
 */
template < >
class CUTS_BE_Attribute_End_T <CUTS_BE_Ciao> :
  public CUTS_BE_Visitor_T <CUTS_BE_Ciao, PICML::Visitor>
{
public:
  typedef public CUTS_BE_Visitor_T <CUTS_BE_Ciao, PICML::Visitor> visitor_type;

  CUTS_BE_Attribute_End_T (CUTS_BE_Ciao & context);

  virtual ~CUTS_BE_Attribute_End_T (void);

  void generate (const PICML::Attribute & attr);

private:
  CUTS_BE_ReadonlyAttribute_Begin_T <CUTS_BE_Ciao> readonly_begin_;

  CUTS_BE_ReadonlyAttribute_End_T <CUTS_BE_Ciao> readonly_end_;
};

/**
 * @class CUTS_BE_Component_Impl_Entrypoint_T
 */
template < >
class CUTS_BE_Component_Impl_Entrypoint_T <CUTS_BE_Ciao> :
  public CUTS_BE_Visitor_T <CUTS_BE_Ciao, PICML::Visitor>
{
public:
  typedef public CUTS_BE_Visitor_T <CUTS_BE_Ciao, PICML::Visitor> visitor_type;

  CUTS_BE_Component_Impl_Entrypoint_T (CUTS_BE_Ciao & context);

  virtual ~CUTS_BE_Component_Impl_Entrypoint_T (void);

  void generate (const PICML::MonolithicImplementation & monoimpl,
                 const PICML::ComponentImplementationArtifact & artifact);

  virtual void Visit_Implements (const PICML::Implements & implements);

  virtual void Visit_Component (const PICML::Component & component);
};

//template < >
//struct CUTS_BE_Factory_Impl_Begin_T <CUTS_BE_Ciao>
//{
//  bool
//  generate (const PICML::ComponentFactory & factory,
//            const PICML::MonolithicImplementation & monoimpl,
//            const PICML::Component & component)
//  {
//    CIAO_EXEC_HEADER_GENERATOR ()->
//      write_factory_impl_begin (factory, monoimpl, component);
//    CIAO_EXEC_SOURCE_GENERATOR ()->
//      write_factory_impl_begin (factory, monoimpl, component);
//
//    CIAO_PROXY_HEADER_GENERATOR ()->
//      write_factory_impl_begin (factory, monoimpl, component);
//    CIAO_PROXY_SOURCE_GENERATOR ()->
//      write_factory_impl_begin (factory, monoimpl, component);
//
//    return true;
//  }
//};

//template < >
//struct CUTS_BE_Factory_Impl_End_T <CUTS_BE_Ciao>
//{
//  bool generate (const PICML::ComponentFactory & factory,
//                        const PICML::MonolithicImplementation & monoimpl,
//                        const PICML::Component & component)
//  {
//    CIAO_EXEC_HEADER_GENERATOR ()->
//      write_factory_impl_end (factory, monoimpl, component);
//    CIAO_EXEC_SOURCE_GENERATOR ()->
//      write_factory_impl_end (factory, monoimpl, component);
//
//    CIAO_PROXY_HEADER_GENERATOR ()->
//      write_factory_impl_end (factory, monoimpl, component);
//    CIAO_PROXY_SOURCE_GENERATOR ()->
//      write_factory_impl_end (factory, monoimpl, component);
//
//    return true;
//  }
//};

//template < >
//struct CUTS_BE_Object_Impl_Begin_T <CUTS_BE_Ciao>
//{
//  bool generate (const PICML::Component & component,
//                        const PICML::ProvidedRequestPort & facet)
//  {
//    CIAO_EXEC_HEADER_GENERATOR ()->write_object_impl_begin (component, facet);
//    CIAO_EXEC_SOURCE_GENERATOR ()->write_object_impl_begin (component, facet);
//
//    CIAO_PROXY_HEADER_GENERATOR ()->write_object_impl_begin (component, facet);
//    CIAO_PROXY_SOURCE_GENERATOR ()->write_object_impl_begin (component, facet);
//    return true;
//  }
//};

//template < >
//struct CUTS_BE_Object_Impl_End_T <CUTS_BE_Ciao>
//{
//  bool generate (const PICML::Component & component,
//                        const PICML::ProvidedRequestPort & facet)
//  {
//    CIAO_EXEC_HEADER_GENERATOR ()->write_object_impl_end (component, facet);
//    CIAO_EXEC_SOURCE_GENERATOR ()->write_object_impl_end (component, facet);
//
//    CIAO_PROXY_HEADER_GENERATOR ()->write_object_impl_end (component, facet);
//    CIAO_PROXY_SOURCE_GENERATOR ()->write_object_impl_end (component, facet);
//    return true;
//  }
//};

/**
 * @class CUTS_BE_PeriodicEvent_Begin_T
 */
template < >
class CUTS_BE_PeriodicEvent_Begin_T <CUTS_BE_Ciao> :
  public CUTS_BE_Visitor_T <CUTS_BE_Ciao, PICML::Visitor>
{
public:
  typedef public CUTS_BE_Visitor_T <CUTS_BE_Ciao, PICML::Visitor> visitor_type;

  CUTS_BE_PeriodicEvent_Begin_T (CUTS_BE_Ciao & context);

  virtual ~CUTS_BE_PeriodicEvent_Begin_T (void);

  void generate (const PICML::PeriodicEvent & periodic);
};

/**
 * @class CUTS_BE_PeriodicEvent_End_T
 */
template < >
class CUTS_BE_PeriodicEvent_End_T <CUTS_BE_Ciao> :
  public CUTS_BE_Visitor_T <CUTS_BE_Ciao, PICML::Visitor>
{
public:
  typedef public CUTS_BE_Visitor_T <CUTS_BE_Ciao, PICML::Visitor> visitor_type;

  CUTS_BE_PeriodicEvent_End_T (CUTS_BE_Ciao & context);

  virtual ~CUTS_BE_PeriodicEvent_End_T (void);

  void generate (const PICML::PeriodicEvent & periodic);
};

/**
 * @class CUTS_BE_Include_File_T <CUTS_BE_Ciao>
 *
 * Specialization of the CUTS_BE_Include_File_T class.
 */
template < >
class CUTS_BE_Include_File_T <CUTS_BE_Ciao> :
  public CUTS_BE_Visitor_T <CUTS_BE_Ciao, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE_Ciao, PICML::Visitor> visitor_type;

  CUTS_BE_Include_File_T (CUTS_BE_Ciao & context);

  virtual ~CUTS_BE_Include_File_T (void);

  virtual void generate (const std::string & include);
};

/**
 * @class CUTS_BE_InEventPort_Begin_T
 */
template < >
class CUTS_BE_InEventPort_Begin_T <CUTS_BE_Ciao> :
  public CUTS_BE_Visitor_T <CUTS_BE_Ciao, PICML::Visitor>
{
public:
  typedef public CUTS_BE_Visitor_T <CUTS_BE_Ciao, PICML::Visitor> visitor_type;

  CUTS_BE_InEventPort_Begin_T (CUTS_BE_Ciao & context);

  virtual ~CUTS_BE_InEventPort_Begin_T (void);

  void generate (const PICML::InEventPort & sink,
                 const std::vector <PICML::Property> & properties);
};

/**
 * @class CUTS_BE_InEventPort_End_T
 */
template < >
class CUTS_BE_InEventPort_End_T <CUTS_BE_Ciao> :
  public CUTS_BE_Visitor_T <CUTS_BE_Ciao, PICML::Visitor>
{
public:
  typedef public CUTS_BE_Visitor_T <CUTS_BE_Ciao, PICML::Visitor> visitor_type;

  CUTS_BE_InEventPort_End_T (CUTS_BE_Ciao & context);

  virtual ~CUTS_BE_InEventPort_End_T (void);

  void generate (const PICML::InEventPort & sink,
                 const std::vector <PICML::Property> & properties);
};

/**
 * @class CUTS_BE_ProvidedRequestPort_Begin_T
 */
template < >
class CUTS_BE_ProvidedRequestPort_Begin_T <CUTS_BE_Ciao> :
  public CUTS_BE_Visitor_T <CUTS_BE_Ciao, PICML::Visitor>
{
public:
  typedef public CUTS_BE_Visitor_T <CUTS_BE_Ciao, PICML::Visitor> visitor_type;

  CUTS_BE_ProvidedRequestPort_Begin_T (CUTS_BE_Ciao & context);

  virtual ~CUTS_BE_ProvidedRequestPort_Begin_T (void);

  void generate (const PICML::ProvidedRequestPort & source);
};

/**
 * @class CUTS_BE_ProvidedRequestPort_End_T
 */
template < >
class CUTS_BE_ProvidedRequestPort_End_T <CUTS_BE_Ciao> :
  public CUTS_BE_Visitor_T <CUTS_BE_Ciao, PICML::Visitor>
{
public:
  typedef public CUTS_BE_Visitor_T <CUTS_BE_Ciao, PICML::Visitor> visitor_type;

  CUTS_BE_ProvidedRequestPort_End_T (CUTS_BE_Ciao & context);

  virtual ~CUTS_BE_ProvidedRequestPort_End_T (void);

  void generate (const PICML::ProvidedRequestPort & source);
};

//template < >
//struct CUTS_BE_OnewayOperation_Begin_T <CUTS_BE_Ciao>
//{
//  bool generate (const PICML::OnewayOperation & oneway)
//  {
//    CIAO_EXEC_HEADER_GENERATOR ()->write_OnewayOperation_begin (oneway);
//    CIAO_EXEC_SOURCE_GENERATOR ()->write_OnewayOperation_begin (oneway);
//
//    CIAO_PROXY_HEADER_GENERATOR ()->write_OnewayOperation_begin (oneway);
//    CIAO_PROXY_SOURCE_GENERATOR ()->write_OnewayOperation_begin (oneway);
//    return true;
//  }
//};

//template < >
//struct CUTS_BE_OnewayOperation_End_T <CUTS_BE_Ciao>
//{
//  bool generate (const PICML::OnewayOperation & oneway)
//  {
//    CIAO_EXEC_HEADER_GENERATOR ()->write_OnewayOperation_end  (oneway);
//    CIAO_EXEC_SOURCE_GENERATOR ()->write_OnewayOperation_end  (oneway);
//
//    CIAO_PROXY_HEADER_GENERATOR ()->write_OnewayOperation_end  (oneway);
//    CIAO_PROXY_SOURCE_GENERATOR ()->write_OnewayOperation_end  (oneway);
//    return true;
//  }
//};

//template < >
//struct CUTS_BE_TwowayOperation_Begin_T <CUTS_BE_Ciao>
//{
//  bool generate (const PICML::TwowayOperation & twoway)
//  {
//    CIAO_EXEC_HEADER_GENERATOR ()->write_TwowayOperation_begin (twoway);
//    CIAO_EXEC_SOURCE_GENERATOR ()->write_TwowayOperation_begin (twoway);
//
//    CIAO_PROXY_HEADER_GENERATOR ()->write_TwowayOperation_begin (twoway);
//    CIAO_PROXY_SOURCE_GENERATOR ()->write_TwowayOperation_begin (twoway);
//    return true;
//  }
//};

//template < >
//struct CUTS_BE_TwowayOperation_End_T <CUTS_BE_Ciao>
//{
//  bool generate (const PICML::TwowayOperation & twoway)
//  {
//    CIAO_EXEC_HEADER_GENERATOR ()->write_TwowayOperation_end  (twoway);
//    CIAO_EXEC_SOURCE_GENERATOR ()->write_TwowayOperation_end  (twoway);
//
//    CIAO_PROXY_HEADER_GENERATOR ()->write_TwowayOperation_end  (twoway);
//    CIAO_PROXY_SOURCE_GENERATOR ()->write_TwowayOperation_end  (twoway);
//    return true;
//  }
//};

//template < >
//struct CUTS_BE_FactoryOperation_Begin_T <CUTS_BE_Ciao>
//{
//  bool generate (const PICML::FactoryOperation & fop)
//  {
//    CIAO_EXEC_HEADER_GENERATOR ()->write_FactoryOperation_begin (fop);
//    CIAO_EXEC_SOURCE_GENERATOR ()->write_FactoryOperation_begin (fop);
//
//    CIAO_PROXY_HEADER_GENERATOR ()->write_FactoryOperation_begin (fop);
//    CIAO_PROXY_SOURCE_GENERATOR ()->write_FactoryOperation_begin (fop);
//    return true;
//  }
//};

//template < >
//struct CUTS_BE_FactoryOperation_End_T <CUTS_BE_Ciao>
//{
//  bool generate (const PICML::FactoryOperation & fop)
//  {
//    CIAO_EXEC_HEADER_GENERATOR ()->write_FactoryOperation_end (fop);
//    CIAO_EXEC_SOURCE_GENERATOR ()->write_FactoryOperation_end (fop);
//
//    CIAO_PROXY_HEADER_GENERATOR ()->write_FactoryOperation_end (fop);
//    CIAO_PROXY_SOURCE_GENERATOR ()->write_FactoryOperation_end (fop);
//    return true;
//  }
//};

/**
 * @class CUTS_BE_Workspace_File_Open_T
 */
template < >
class CUTS_BE_Workspace_File_Open_T <CUTS_BE_Ciao> :
  public CUTS_BE_Visitor_T <CUTS_BE_Ciao, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE_Ciao, PICML::Visitor> visitor_type;

  CUTS_BE_Workspace_File_Open_T (CUTS_BE_Ciao & context);

  virtual ~CUTS_BE_Workspace_File_Open_T (void);

  void generate (const std::string & name);
};

/**
 * @class CUTS_BE_Workspace_Begin_T
 */
template < >
class CUTS_BE_Workspace_Begin_T <CUTS_BE_Ciao>:
  public CUTS_BE_Visitor_T <CUTS_BE_Ciao, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE_Ciao, PICML::Visitor> visitor_type;

  CUTS_BE_Workspace_Begin_T (CUTS_BE_Ciao & context);

  virtual ~CUTS_BE_Workspace_Begin_T (void);

  void generate (const std::string & name);
};

/**
 * @class CUTS_BE_Workspace_Project_Include_T
 */
template < >
class CUTS_BE_Workspace_Project_Include_T <CUTS_BE_Ciao, CUTS_BE_Impl_Node> :
  public CUTS_BE_Visitor_T <CUTS_BE_Ciao, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE_Ciao, PICML::Visitor> visitor_type;

  CUTS_BE_Workspace_Project_Include_T (CUTS_BE_Ciao & context);

  virtual ~CUTS_BE_Workspace_Project_Include_T (void);

  void generate (const CUTS_BE_Impl_Node & node);
};

/**
 * @class CUTS_BE_Workspace_Project_Include_T
 */
template < >
class CUTS_BE_Workspace_Project_Include_T <CUTS_BE_Ciao, CUTS_BE_IDL_Node> :
  public CUTS_BE_Visitor_T <CUTS_BE_Ciao, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE_Ciao, PICML::Visitor> visitor_type;

  CUTS_BE_Workspace_Project_Include_T (CUTS_BE_Ciao & context);

  virtual ~CUTS_BE_Workspace_Project_Include_T (void);

  void generate (const CUTS_BE_IDL_Node & node);
};

/**
 * @class CUTS_BE_Workspace_End_T
 */
template < >
class CUTS_BE_Workspace_End_T <CUTS_BE_Ciao> :
  public CUTS_BE_Visitor_T <CUTS_BE_Ciao, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE_Ciao, PICML::Visitor> visitor_type;

  CUTS_BE_Workspace_End_T (CUTS_BE_Ciao & context);

  virtual ~CUTS_BE_Workspace_End_T (void);

  void generate (const std::string & name);
};

/**
 * @class CUTS_BE_Workspace_File_Close_T
 */
template < >
class CUTS_BE_Workspace_File_Close_T <CUTS_BE_Ciao> :
  public CUTS_BE_Visitor_T <CUTS_BE_Ciao, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE_Ciao, PICML::Visitor> visitor_type;

  CUTS_BE_Workspace_File_Close_T (CUTS_BE_Ciao & context);

  virtual ~CUTS_BE_Workspace_File_Close_T (void);

  void generate (void);
};

///////////////////////////////////////////////////////////////////////////////
// project generators [CUTS_BE_Impl_Node]

/**
 * @class CUTS_BE_Project_File_Open_T
 */
template < >
class CUTS_BE_Project_File_Open_T <CUTS_BE_Ciao, CUTS_BE_Impl_Node> :
  public CUTS_BE_Visitor_T <CUTS_BE_Ciao, PICML::Visitor>
{
public:
  /// Type definition of the visitor type.
  typedef CUTS_BE_Visitor_T <CUTS_BE_Ciao, PICML::Visitor> visitor_type;

  CUTS_BE_Project_File_Open_T (CUTS_BE_Ciao & context);

  virtual ~CUTS_BE_Project_File_Open_T (void);

  void generate (const CUTS_BE_Impl_Node & node);
};

/**
 * @class CUTS_BE_Project_File_Begin_T
 */
template < >
class CUTS_BE_Project_File_Begin_T <CUTS_BE_Ciao, CUTS_BE_Impl_Node> :
  public CUTS_BE_Visitor_T <CUTS_BE_Ciao, PICML::Visitor>
{
public:
  /// Type definition of the visitor type.
  typedef CUTS_BE_Visitor_T <CUTS_BE_Ciao, PICML::Visitor> visitor_type;

  CUTS_BE_Project_File_Begin_T (CUTS_BE_Ciao & context);

  virtual ~CUTS_BE_Project_File_Begin_T (void);

  void generate (const CUTS_BE_Impl_Node & node);
};

/**
 *
 */
template < >
class CUTS_BE_Project_Write_T <CUTS_BE_Ciao, CUTS_BE_Impl_Node> :
  public CUTS_BE_Visitor_T <CUTS_BE_Ciao, PICML::Visitor>
{
public:
  /// Type definition of the visitor type.
  typedef CUTS_BE_Visitor_T <CUTS_BE_Ciao, PICML::Visitor> visitor_type;

  CUTS_BE_Project_Write_T (CUTS_BE_Ciao & context);

  virtual ~CUTS_BE_Project_Write_T (void);

  void generate (const CUTS_BE_Impl_Node & node);

private:
  void generate_exec_project (const CUTS_BE_Impl_Node & node);

  void generate_svnt_project (const CUTS_BE_Impl_Node & node);

  void generate_skel_project (const CUTS_BE_Impl_Node & node);

  void generate_stub_listing (const CUTS_BE_IDL_Node * node);

  void generate_mpc_i (const CUTS_BE_Impl_Node & node);

  void generate_mpc_values (const std::string & heading,
                            const CUTS_String_Set & listing);

  typedef std::set <const CUTS_BE_IDL_Node *> IDL_Node_Set;

  IDL_Node_Set visited_nodes_;
};

/**
 *
 */
template < >
class CUTS_BE_Project_File_End_T <CUTS_BE_Ciao, CUTS_BE_Impl_Node> :
  public CUTS_BE_Visitor_T <CUTS_BE_Ciao, PICML::Visitor>
{
public:
  /// Type definition of the visitor type.
  typedef CUTS_BE_Visitor_T <CUTS_BE_Ciao, PICML::Visitor> visitor_type;

  CUTS_BE_Project_File_End_T (CUTS_BE_Ciao & context);

  virtual ~CUTS_BE_Project_File_End_T (void);

  void generate (const CUTS_BE_Impl_Node & node);
};

/**
 *
 */
template <  >
class CUTS_BE_Project_File_Close_T <CUTS_BE_Ciao, CUTS_BE_Impl_Node> :
  public CUTS_BE_Visitor_T <CUTS_BE_Ciao, PICML::Visitor>
{
public:
  /// Type definition of the visitor type.
  typedef CUTS_BE_Visitor_T <CUTS_BE_Ciao, PICML::Visitor> visitor_type;

  CUTS_BE_Project_File_Close_T (CUTS_BE_Ciao & context);

  virtual ~CUTS_BE_Project_File_Close_T (void);

  void generate (void);
};

///////////////////////////////////////////////////////////////////////////////
// project generators [CUTS_BE_IDL_Node]

/**
 * @class CUTS_BE_Project_File_Open_T
 */
template < >
class CUTS_BE_Project_File_Open_T <CUTS_BE_Ciao, CUTS_BE_IDL_Node> :
  public CUTS_BE_Visitor_T <CUTS_BE_Ciao, PICML::Visitor>
{
public:
  /// Type definition of the visitor type.
  typedef CUTS_BE_Visitor_T <CUTS_BE_Ciao, PICML::Visitor> visitor_type;

  CUTS_BE_Project_File_Open_T (CUTS_BE_Ciao & context);

  virtual ~CUTS_BE_Project_File_Open_T (void);

  void generate (const CUTS_BE_IDL_Node & node);
};

/**
 * @class CUTS_BE_Project_File_Begin_T
 */
template < >
class CUTS_BE_Project_File_Begin_T <CUTS_BE_Ciao, CUTS_BE_IDL_Node> :
  public CUTS_BE_Visitor_T <CUTS_BE_Ciao, PICML::Visitor>
{
public:
  /// Type definition of the visitor type.
  typedef CUTS_BE_Visitor_T <CUTS_BE_Ciao, PICML::Visitor> visitor_type;

  CUTS_BE_Project_File_Begin_T (CUTS_BE_Ciao & context);

  virtual ~CUTS_BE_Project_File_Begin_T (void);

  void generate (const CUTS_BE_IDL_Node & node);
};

/**
 *
 */
template < >
class CUTS_BE_Project_Write_T <CUTS_BE_Ciao, CUTS_BE_IDL_Node> :
  public CUTS_BE_Visitor_T <CUTS_BE_Ciao, PICML::Visitor>
{
public:
  /// Type definition of the visitor type.
  typedef CUTS_BE_Visitor_T <CUTS_BE_Ciao, PICML::Visitor> visitor_type;

  CUTS_BE_Project_Write_T (CUTS_BE_Ciao & context);

  virtual ~CUTS_BE_Project_Write_T (void);

  void generate (const CUTS_BE_IDL_Node & node);

private:
  void generate_stub_listing (const CUTS_BE_IDL_Node * node);

  typedef std::set <const CUTS_BE_IDL_Node *> IDL_Node_Set;

  IDL_Node_Set visited_nodes_;
};

/**
 *
 */
template <  >
class CUTS_BE_Project_File_End_T <CUTS_BE_Ciao, CUTS_BE_IDL_Node> :
  public CUTS_BE_Visitor_T <CUTS_BE_Ciao, PICML::Visitor>
{
public:
  /// Type definition of the visitor type.
  typedef CUTS_BE_Visitor_T <CUTS_BE_Ciao, PICML::Visitor> visitor_type;

  CUTS_BE_Project_File_End_T (CUTS_BE_Ciao & context);

  virtual ~CUTS_BE_Project_File_End_T (void);

  bool generate (const CUTS_BE_IDL_Node & node);
};

/**
 *
 */
template <  >
class CUTS_BE_Project_File_Close_T <CUTS_BE_Ciao, CUTS_BE_IDL_Node> :
  public CUTS_BE_Visitor_T <CUTS_BE_Ciao, PICML::Visitor>
{
public:
  /// Type definition of the visitor type.
  typedef CUTS_BE_Visitor_T <CUTS_BE_Ciao, PICML::Visitor> visitor_type;

  CUTS_BE_Project_File_Close_T (CUTS_BE_Ciao & context);

  virtual ~CUTS_BE_Project_File_Close_T (void);

  void generate (void);
};

#if defined (__CUTS_INLINE__)
#include "CIAO_Generators.inl"
#endif

#endif  // !defined _CUTS_BE_CIAO_TRAITS_H_
