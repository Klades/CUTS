// -*- C++ -*-

//=============================================================================
/**
 * @file      BE_Generators_T.h
 *
 * Defines generator objects for the CUTS backend
 *
 * $Id$
 *
 * @author    James H. Hill
 */
//=============================================================================

#ifndef _CUTS_BE_GENERATORS_T_H_
#define _CUTS_BE_GENERATORS_T_H_

#include "PICML/PICML.h"
#include "PICML/Visitor.h"
#include "BE_Visitor_T.h"

/**
 * @class CUTS_BE_Write_Variables_Last_T
 *
 * Determine when to generate the variables. By default variables are
 * generated last in the backend. If you want to generate variables in
 * the middle, then specialize the \a result_type to be true.
 */
template <typename CONTEXT>
struct CUTS_BE_Write_Variables_Last_T
{
  static const bool result_type = true;
};

/**
 * @class CUTS_BE_Parse_Precondition_T
 *
 * Determine if conditions should be parsed. The condition appears
 * in the outgoing connection of a branch state element, or the looping
 * attribute of a for , do while, or while loop in the behavior model.
 * Parsing the condition will cause the backend generator to call the
 * appropriate callbacks for converting text, such as comparison
 * operators, to their appropriate representation in the target backend.
 *
 * @note The name of this trait does not match it's intention because
 *       it remains around from a previous version of the backend
 *       generator architecture. In the future, the name of this
 *       method will change to something more meaningful.
 */
template <typename CONTEXT>
struct CUTS_BE_Parse_Precondition_T
{
  static const bool result_type = true;
};

/**
 * @class CUTS_BE_Initialize_T
 *
 * Initialize the backend.
 */
template <typename CONTEXT>
class CUTS_BE_Initialize_T :
  public CUTS_BE_Visitor_T <CUTS_BE::NIL, PICML::Visitor>
{
public:
  /// Type definition of the visitor type.
  typedef CUTS_BE_Visitor_T <CUTS_BE::NIL, PICML::Visitor> visitor_type;

  /**
   * Initializing conclassor.
   *
   * @param[in]       context         Context for the generator.
   */
  CUTS_BE_Initialize_T (CONTEXT & context);

  /// Destructor.
  virtual ~CUTS_BE_Initialize_T (void);

  void generate (const PICML::RootFolder_in folder);
};

/**
 * @class CUTS_BE_Finalize_T
 *
 * Finalize the backend.
 */
template <typename CONTEXT>
class CUTS_BE_Finalize_T :
  public CUTS_BE_Visitor_T <CUTS_BE::NIL, PICML::Visitor>
{
public:
  /// Type definition of the visitor type.
  typedef CUTS_BE_Visitor_T <CUTS_BE::NIL, PICML::Visitor> visitor_type;

  /**
   * Initializing conclassor.
   *
   * @param[in]       context         Context for the generator.
   */
  CUTS_BE_Finalize_T (CONTEXT & context);

  /// Destructor.
  virtual ~CUTS_BE_Finalize_T (void);

  void generate (const PICML::RootFolder_in folder);
};

/**
 * @class CUTS_BE_File_Open_T
 *
 * Open the file for the monolithic implemenation.
 */
template <typename CONTEXT>
class CUTS_BE_File_Open_T :
  public CUTS_BE_Visitor_T <CUTS_BE::NIL, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE::NIL, PICML::Visitor> visitor_type;

  CUTS_BE_File_Open_T (CONTEXT & context);

  virtual ~CUTS_BE_File_Open_T (void);

  void generate (const PICML::ComponentImplementationContainer_in,
                 const PICML::MonolithicImplementation_in);
};

/**
 * @class CUTS_BE_File_Close_T
 *
 * Close the file for the monolithic implementation.
 */
template <typename CONTEXT>
class CUTS_BE_File_Close_T :
  public CUTS_BE_Visitor_T <CUTS_BE::NIL, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE::NIL, PICML::Visitor> visitor_type;

  CUTS_BE_File_Close_T (CONTEXT & context);

  virtual ~CUTS_BE_File_Close_T (void);

  void generate (const PICML::ComponentImplementationContainer_in,
                 const PICML::MonolithicImplementation_in);
};

/**
 *
 */
template <typename CONTEXT>
struct CUTS_BE_ComponentAssembly_File_Open_T
{
  static bool generate (const PICML::ComponentImplementationContainer_in,
                        const PICML::ComponentAssembly_in)
  {
    return false;
  }
};

/**
 *
 */
template <typename CONTEXT>
struct CUTS_BE_ComponentAssembly_File_Close_T
{
  static bool generate (const PICML::ComponentImplementationContainer_in,
                        const PICML::ComponentAssembly_in)
  {
    return false;
  }
};

/**
 * @class CUTS_BE_Include_File_T
 *
 * Generate an include file for the specified string.
 */
template <typename CONTEXT>
class CUTS_BE_Include_File_T :
  public CUTS_BE_Visitor_T <CUTS_BE::NIL, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE::NIL, PICML::Visitor> visitor_type;

  CUTS_BE_Include_File_T (CONTEXT & context);

  virtual ~CUTS_BE_Include_File_T (void);

  void generate (const std::string & include);
};

/**
 * @class CUTS_BE_Prologue_T
 *
 * Generates the prologue for an implementation's file.
 */
template <typename CONTEXT>
class CUTS_BE_Prologue_T :
  public CUTS_BE_Visitor_T <CUTS_BE::NIL, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE::NIL, PICML::Visitor> visitor_type;

  CUTS_BE_Prologue_T (CONTEXT & context);

  virtual ~CUTS_BE_Prologue_T (void);

  void generate (const PICML::ComponentImplementationContainer_in,
                 const PICML::MonolithicImplementation_in);
};

/**
 * @class CUTS_BE_Prologue_T
 *
 * Generates the epilogue for an implementation's file.
 */
template <typename CONTEXT>
class CUTS_BE_Epilogue_T :
  public CUTS_BE_Visitor_T <CUTS_BE::NIL, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE::NIL, PICML::Visitor> visitor_type;

  CUTS_BE_Epilogue_T (CONTEXT & context);

  virtual ~CUTS_BE_Epilogue_T (void);

  void generate (const PICML::ComponentImplementationContainer_in,
                 const PICML::MonolithicImplementation_in);
};

/**
 *
 */
template <typename CONTEXT>
struct CUTS_BE_ComponentAssembly_Prologue_T
{
  static bool generate (const PICML::ComponentImplementationContainer_in,
                        const PICML::ComponentAssembly_in)
  {
    return false;
  }
};


/**
 *
 */
template <typename CONTEXT>
struct CUTS_BE_ComponentAssembly_Epilogue_T
{
  static bool generate (const PICML::ComponentImplementationContainer_in,
                        const PICML::ComponentAssembly_in)
  {
    return false;
  }
};

/**
 * @class CUTS_BE_Component_Impl_Begin_T
 *
 * Begin generation of the component's implementation.
 */
template <typename CONTEXT>
class CUTS_BE_Component_Impl_Begin_T :
  public CUTS_BE_Visitor_T <CUTS_BE::NIL, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE::NIL, PICML::Visitor> visitor_type;

  CUTS_BE_Component_Impl_Begin_T (CONTEXT & context);

  virtual ~CUTS_BE_Component_Impl_Begin_T (void);

  void generate (const PICML::MonolithicImplementation_in monoimpl,
                 const PICML::Component_in component);
};

/**
 * @class CUTS_BE_Component_Impl_End_T
 *
 * End generation of the component's implementation.
 */
template <typename CONTEXT>
class CUTS_BE_Component_Impl_End_T :
  public CUTS_BE_Visitor_T <CUTS_BE::NIL, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE::NIL, PICML::Visitor> visitor_type;

  CUTS_BE_Component_Impl_End_T (CONTEXT & context);

  virtual ~CUTS_BE_Component_Impl_End_T (void);

  void generate (const PICML::MonolithicImplementation_in monoimpl,
                 const PICML::Component_in component);
};

/**
 * @class CUTS_BE_Environment_Begin_T
 *
 * Begin generation of an environment action.
 */
template <typename CONTEXT>
class CUTS_BE_Environment_Begin_T :
  public CUTS_BE_Visitor_T <CUTS_BE::NIL, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE::NIL, PICML::Visitor> visitor_type;

  CUTS_BE_Environment_Begin_T (CONTEXT & context);

  virtual ~CUTS_BE_Environment_Begin_T (void);

  void generate (const PICML::Component_in component);
};

/**
 * @class CUTS_BE_Environment_Method_Begin_T
 *
 * Begin the generation of an environment method.
 */
template <typename CONTEXT>
class CUTS_BE_Environment_Method_Begin_T :
  public CUTS_BE_Visitor_T <CUTS_BE::NIL, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE::NIL, PICML::Visitor> visitor_type;

  CUTS_BE_Environment_Method_Begin_T (CONTEXT & context);

  virtual ~CUTS_BE_Environment_Method_Begin_T (void);

  void generate (const PICML::MultiInputAction_in action);
};

/**
 * @class CUTS_BE_Environment_Method_End_T
 *
 * End the generation of an environment method.
 */
template <typename CONTEXT>
class CUTS_BE_Environment_Method_End_T :
  public CUTS_BE_Visitor_T <CUTS_BE::NIL, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE::NIL, PICML::Visitor> visitor_type;

  CUTS_BE_Environment_Method_End_T (CONTEXT & context);

  virtual ~CUTS_BE_Environment_Method_End_T (void);

  void generate (const PICML::MultiInputAction_in action);
};

/**
 * @class CUTS_BE_Environment_End_T
 *
 * End of the environment for a component implementation.
 */
template <typename CONTEXT>
class CUTS_BE_Environment_End_T :
  public CUTS_BE_Visitor_T <CUTS_BE::NIL, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE::NIL, PICML::Visitor> visitor_type;

  CUTS_BE_Environment_End_T (CONTEXT & context);

  virtual ~CUTS_BE_Environment_End_T (void);

  void generate (const PICML::Component_in component);
};

/**
 * @class CUTS_BE_ReadonlyAttribute_Begin_T
 */
template <typename CONTEXT>
class CUTS_BE_ReadonlyAttribute_Begin_T :
  public CUTS_BE_Visitor_T <CUTS_BE::NIL, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE::NIL, PICML::Visitor> visitor_type;

  CUTS_BE_ReadonlyAttribute_Begin_T (CONTEXT & context);

  virtual ~CUTS_BE_ReadonlyAttribute_Begin_T (void);

  void generate (const PICML::ReadonlyAttribute_in readonly);
};

/**
 * @class CUTS_BE_ReadonlyAttribute_End_T
 */
template <typename CONTEXT>
class CUTS_BE_ReadonlyAttribute_End_T :
  public CUTS_BE_Visitor_T <CUTS_BE::NIL, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE::NIL, PICML::Visitor> visitor_type;

  CUTS_BE_ReadonlyAttribute_End_T (CONTEXT & context);

  virtual ~CUTS_BE_ReadonlyAttribute_End_T (void);

  void generate (const PICML::ReadonlyAttribute_in readonly);
};

/**
 * @class CUTS_BE_Attribute_Begin_T
 */
template <typename CONTEXT>
class CUTS_BE_Attribute_Begin_T :
  public CUTS_BE_Visitor_T <CUTS_BE::NIL, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE::NIL, PICML::Visitor> visitor_type;

  CUTS_BE_Attribute_Begin_T (CONTEXT & context);

  virtual ~CUTS_BE_Attribute_Begin_T (void);

  void generate (const PICML::Attribute_in attr);
};

/**
 * @class CUTS_BE_Attribute_End_T
 */
template <typename CONTEXT>
class CUTS_BE_Attribute_End_T :
  public CUTS_BE_Visitor_T <CUTS_BE::NIL, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE::NIL, PICML::Visitor> visitor_type;

  CUTS_BE_Attribute_End_T (CONTEXT & context);

  virtual ~CUTS_BE_Attribute_End_T (void);

  void generate (const PICML::Attribute_in attr);
};

/**
 * @class CUTS_BE_Component_Impl_Entrypoint_T
 */
template <typename CONTEXT>
class CUTS_BE_Component_Impl_Entrypoint_T :
  public CUTS_BE_Visitor_T <CUTS_BE::NIL, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE::NIL, PICML::Visitor> visitor_type;

  CUTS_BE_Component_Impl_Entrypoint_T (CONTEXT & context);

  virtual ~CUTS_BE_Component_Impl_Entrypoint_T (void);

  void generate (const PICML::MonolithicImplementation_in monoimpl,
                 const PICML::ComponentImplementationArtifact_in artifact);
};

/**
 *
 */
template <typename CONTEXT>
struct CUTS_BE_Factory_Impl_Begin_T
{
  static bool generate (const PICML::ComponentFactory_in factory,
                        const PICML::MonolithicImplementation_in monoimpl,
                        const PICML::Component_in component)
    { return false; }
};

/**
 *
 */
template <typename CONTEXT>
struct CUTS_BE_Factory_Impl_End_T
{
  static bool generate (const PICML::ComponentFactory_in factory,
                        const PICML::MonolithicImplementation_in monoimpl,
                        const PICML::Component_in component)
    { return false; }
};

/**
 *
 */
template <typename CONTEXT>
struct CUTS_BE_Object_Impl_Begin_T
{
  static bool generate (const PICML::Component_in component,
                        const PICML::ProvidedRequestPort_in facet)
    { return false; }
};

/**
 *
 */
template <typename CONTEXT>
struct CUTS_BE_Object_Impl_End_T
{
  static bool generate (const PICML::Component_in component,
                        const PICML::ProvidedRequestPort_in facet)
    { return false; }
};

/**
 * @class CUTS_BE_Variables_Begin_T
 */
template <typename CONTEXT>
class CUTS_BE_Variables_Begin_T :
  public CUTS_BE_Visitor_T <CUTS_BE::NIL, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE::NIL, PICML::Visitor> visitor_type;

  CUTS_BE_Variables_Begin_T (CONTEXT & context);

  virtual ~CUTS_BE_Variables_Begin_T (void);

  void generate (const PICML::Component_in component);
};

/**
 * @class CUTS_BE_Attribute_Variable_T
 */
template <typename CONTEXT>
class CUTS_BE_Attribute_Variable_T :
  public CUTS_BE_Visitor_T <CUTS_BE::NIL, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE::NIL, PICML::Visitor> visitor_type;

  CUTS_BE_Attribute_Variable_T (CONTEXT & context);

  virtual ~CUTS_BE_Attribute_Variable_T (void);

  void generate (const PICML::ReadonlyAttribute_in attr);
};

/**
 * @class CUTS_BE_Variable_T
 */
template <typename CONTEXT>
class CUTS_BE_Variable_T :
  public CUTS_BE_Visitor_T <CUTS_BE::NIL, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE::NIL, PICML::Visitor> visitor_type;

  CUTS_BE_Variable_T (CONTEXT & context);

  virtual ~CUTS_BE_Variable_T (void);

  void generate (const PICML::Variable_in variable);
};

/**
 * @class CUTS_BE_Worker_Variable_T
 */
template <typename CONTEXT>
class CUTS_BE_Worker_Variable_T :
  public CUTS_BE_Visitor_T <CUTS_BE::NIL, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE::NIL, PICML::Visitor> visitor_type;

  CUTS_BE_Worker_Variable_T (CONTEXT & context);

  virtual ~CUTS_BE_Worker_Variable_T (void);

  void generate (const PICML::WorkerType_in type, const PICML::Worker_in worker);
};

/**
 * @class CUTS_BE_PeriodicEvent_Variable_T
 */
template <typename CONTEXT>
class CUTS_BE_PeriodicEvent_Variable_T :
  public CUTS_BE_Visitor_T <CUTS_BE::NIL, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE::NIL, PICML::Visitor> visitor_type;

  CUTS_BE_PeriodicEvent_Variable_T (CONTEXT & context);

  virtual ~CUTS_BE_PeriodicEvent_Variable_T (void);

  void generate (const PICML::PeriodicEvent_in periodic);
};

/**
 * @class CUTS_BE_Variables_End_T
 */
template <typename CONTEXT>
class CUTS_BE_Variables_End_T :
  public CUTS_BE_Visitor_T <CUTS_BE::NIL, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE::NIL, PICML::Visitor> visitor_type;

  CUTS_BE_Variables_End_T (CONTEXT & context);

  virtual ~CUTS_BE_Variables_End_T (void);

  void generate (const PICML::Component_in component);
};

/**
 * @class CUTS_BE_InEventPort_Begin_T
 */
template <typename CONTEXT>
class CUTS_BE_InEventPort_Begin_T :
  public CUTS_BE_Visitor_T <CUTS_BE::NIL, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE::NIL, PICML::Visitor> visitor_type;

  CUTS_BE_InEventPort_Begin_T (CONTEXT & context);

  virtual ~CUTS_BE_InEventPort_Begin_T (void);

  void generate (const PICML::InEventPort_in sink,
                 GAME::Mga::Collection_T <PICML::Property> & properties);
};

/**
 * @class CUTS_BE_InEventPort_End_T
 */
template <typename CONTEXT>
class CUTS_BE_InEventPort_End_T :
  public CUTS_BE_Visitor_T <CUTS_BE::NIL, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE::NIL, PICML::Visitor> visitor_type;

  CUTS_BE_InEventPort_End_T (CONTEXT & context);

  virtual ~CUTS_BE_InEventPort_End_T (void);

  void generate (const PICML::InEventPort_in sink,
                 GAME::Mga::Collection_T <PICML::Property> & properties);
};

/**
 * @class CUTS_BE_ProvidedRequestPort_Begin_T
 */
template <typename CONTEXT>
class CUTS_BE_ProvidedRequestPort_Begin_T :
  public CUTS_BE_Visitor_T <CUTS_BE::NIL, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE::NIL, PICML::Visitor> visitor_type;

  CUTS_BE_ProvidedRequestPort_Begin_T (CONTEXT & context);

  virtual ~CUTS_BE_ProvidedRequestPort_Begin_T (void);

  void generate (const PICML::ProvidedRequestPort_in source);
};

/**
 * @class CUTS_BE_ProvidedRequestPort_End_T
 */
template <typename CONTEXT>
class CUTS_BE_ProvidedRequestPort_End_T :
  public CUTS_BE_Visitor_T <CUTS_BE::NIL, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE::NIL, PICML::Visitor> visitor_type;

  CUTS_BE_ProvidedRequestPort_End_T (CONTEXT & context);

  virtual ~CUTS_BE_ProvidedRequestPort_End_T (void);

  void generate (const PICML::ProvidedRequestPort_in source);
};

/**
 * @class CUTS_BE_PeriodicEvent_Begin_T
 */
template <typename CONTEXT>
class CUTS_BE_PeriodicEvent_Begin_T :
  public CUTS_BE_Visitor_T <CUTS_BE::NIL, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE::NIL, PICML::Visitor> visitor_type;

  CUTS_BE_PeriodicEvent_Begin_T (CONTEXT & context);

  virtual ~CUTS_BE_PeriodicEvent_Begin_T (void);

  void generate (const PICML::PeriodicEvent_in periodic);
};

/**
 * @class CUTS_BE_PeriodicEvent_End_T
 */
template <typename CONTEXT>
class CUTS_BE_PeriodicEvent_End_T :
  public CUTS_BE_Visitor_T <CUTS_BE::NIL, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE::NIL, PICML::Visitor> visitor_type;

  CUTS_BE_PeriodicEvent_End_T (CONTEXT & context);

  virtual ~CUTS_BE_PeriodicEvent_End_T (void);

  void generate (const PICML::PeriodicEvent_in periodic);
};

//=============================================================================
/**
 *
 */
//=============================================================================

template <typename CONTEXT>
struct CUTS_BE_OnewayOperation_Begin_T
{
  static bool generate (const PICML::OnewayOperation_in oneway)
    { return false; }
};

//=============================================================================
/**
 *
 */
//=============================================================================

template <typename CONTEXT>
struct CUTS_BE_OnewayOperation_End_T
{
  static bool generate (const PICML::OnewayOperation_in oneway)
    { return false; }
};

//=============================================================================
/**
 *
 */
//=============================================================================

template <typename CONTEXT>
struct CUTS_BE_TwowayOperation_Begin_T
{
  static bool generate (const PICML::TwowayOperation_in twoway)
    { return false; }
};

//=============================================================================
/**
 *
 */
//=============================================================================

template <typename CONTEXT>
struct CUTS_BE_TwowayOperation_End_T
{
  static bool generate (const PICML::TwowayOperation_in twoway)
    { return false; }
};

//=============================================================================
/**
 *
 */
//=============================================================================

template <typename CONTEXT>
struct CUTS_BE_FactoryOperation_Begin_T
{
  static bool generate (const PICML::FactoryOperation_in factory)
    { return false; }
};

//=============================================================================
/**
 *
 */
//=============================================================================

template <typename CONTEXT>
struct CUTS_BE_FactoryOperation_End_T
{
  static bool generate (const PICML::FactoryOperation_in factory)
    { return false; }
};

///////////////////////////////////////////////////////////////////////////////
// CBML

/**
 * @class CUTS_BE_RequestAction_Begin_T
 */
template <typename CONTEXT>
class CUTS_BE_RequestAction_Begin_T :
  public CUTS_BE_Visitor_T <CUTS_BE::NIL, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE::NIL, PICML::Visitor> visitor_type;

  CUTS_BE_RequestAction_Begin_T (CONTEXT & context);
  void generate (const PICML::RequestAction_in action);
};

/**
 * @class CUTS_BE_RequestAction_End_T
 */
template <typename CONTEXT>
class CUTS_BE_RequestAction_End_T :
  public CUTS_BE_Visitor_T <CUTS_BE::NIL, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE::NIL, PICML::Visitor> visitor_type;

  CUTS_BE_RequestAction_End_T (CONTEXT & context);
  void generate (const PICML::RequestAction_in action);
};

/**
 * @class CUTS_BE_Postcondition_T
 */
template <typename CONTEXT>
class CUTS_BE_Postcondition_T :
  public CUTS_BE_Visitor_T <CUTS_BE::NIL, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE::NIL, PICML::Visitor> visitor_type;

  CUTS_BE_Postcondition_T (CONTEXT & context);

  virtual ~CUTS_BE_Postcondition_T (void);

  void generate (const std::string & postcondition);
};

/**
 * @class CUTS_BE_Precondition_T
 */
template <typename CONTEXT>
class CUTS_BE_Precondition_T :
  public CUTS_BE_Visitor_T <CUTS_BE::NIL, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE::NIL, PICML::Visitor> visitor_type;

  CUTS_BE_Precondition_T (CONTEXT & context);

  virtual ~CUTS_BE_Precondition_T (void);

  void generate (const std::string & precondition);
};

/**
 * @class CUTS_BE_Branches_Begin_T
 */
template <typename CONTEXT>
class CUTS_BE_Branches_Begin_T :
  public CUTS_BE_Visitor_T <CUTS_BE::NIL, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE::NIL, PICML::Visitor> visitor_type;

  CUTS_BE_Branches_Begin_T (CONTEXT & context);

  virtual ~CUTS_BE_Branches_Begin_T (void);

  void generate (size_t branches);
};

/**
 * @class CUTS_BE_Branch_Begin_T
 */
template <typename CONTEXT>
class CUTS_BE_Branch_Begin_T :
  public CUTS_BE_Visitor_T <CUTS_BE::NIL, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE::NIL, PICML::Visitor> visitor_type;

  CUTS_BE_Branch_Begin_T (CONTEXT & context);

  virtual ~CUTS_BE_Branch_Begin_T (void);

  void generate (void);
};

/**
 * @class CUTS_BE_Branch_End_T
 */
template <typename CONTEXT>
class CUTS_BE_Branch_End_T :
  public CUTS_BE_Visitor_T <CUTS_BE::NIL, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE::NIL, PICML::Visitor> visitor_type;

  CUTS_BE_Branch_End_T (CONTEXT & context);

  virtual ~CUTS_BE_Branch_End_T (void);

  void generate (void);
};

/**
 * @class CUTS_BE_Branch_Condition_Begin_T
 */
template <typename CONTEXT>
class CUTS_BE_Branch_Condition_Begin_T :
  public CUTS_BE_Visitor_T <CUTS_BE::NIL, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE::NIL, PICML::Visitor> visitor_type;

  CUTS_BE_Branch_Condition_Begin_T (CONTEXT & context);

  virtual ~CUTS_BE_Branch_Condition_Begin_T (void);

  void generate (void);
};

/**
 * @class CUTS_BE_Branch_Condition_End_T
 */
template <typename CONTEXT>
class CUTS_BE_Branch_Condition_End_T :
  public CUTS_BE_Visitor_T <CUTS_BE::NIL, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE::NIL, PICML::Visitor> visitor_type;

  CUTS_BE_Branch_Condition_End_T (CONTEXT & context);

  virtual ~CUTS_BE_Branch_Condition_End_T (void);

  void generate (void);
};

/**
 * @class CUTS_BE_Branch_No_Condition_T
 */
template <typename CONTEXT>
class CUTS_BE_Branch_No_Condition_T :
  public CUTS_BE_Visitor_T <CUTS_BE::NIL, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE::NIL, PICML::Visitor> visitor_type;

  CUTS_BE_Branch_No_Condition_T (CONTEXT & context);

  virtual ~CUTS_BE_Branch_No_Condition_T (void);

  void generate (void);
};

/**
 * @class CUTS_BE_Branches_End_T
 */
template <typename CONTEXT>
class CUTS_BE_Branches_End_T :
  public CUTS_BE_Visitor_T <CUTS_BE::NIL, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE::NIL, PICML::Visitor> visitor_type;

  CUTS_BE_Branches_End_T (CONTEXT & context);

  virtual ~CUTS_BE_Branches_End_T (void);

  void generate (void);
};

/**
 * @class CUTS_BE_Do_While_Begin_T
 */
template <typename CONTEXT>
class CUTS_BE_Do_While_Begin_T :
  public CUTS_BE_Visitor_T <CUTS_BE::NIL, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE::NIL, PICML::Visitor> visitor_type;

  CUTS_BE_Do_While_Begin_T (CONTEXT & context);

  virtual ~CUTS_BE_Do_While_Begin_T (void);

  void generate (void);
};

/**
 * @class CUTS_BE_Do_While_End_T
 */
template <typename CONTEXT>
class CUTS_BE_Do_While_End_T :
  public CUTS_BE_Visitor_T <CUTS_BE::NIL, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE::NIL, PICML::Visitor> visitor_type;

  CUTS_BE_Do_While_End_T (CONTEXT & context);

  virtual ~CUTS_BE_Do_While_End_T (void);

  void generate (void);
};

/**
 * @class CUTS_BE_Do_While_Condition_Begin_T
 */
template <typename CONTEXT>
class CUTS_BE_Do_While_Condition_Begin_T :
  public CUTS_BE_Visitor_T <CUTS_BE::NIL, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE::NIL, PICML::Visitor> visitor_type;

  CUTS_BE_Do_While_Condition_Begin_T (CONTEXT & context);

  virtual ~CUTS_BE_Do_While_Condition_Begin_T (void);

  void generate (void);
};

/**
 * @class CUTS_BE_Do_While_Condition_End_T
 */
template <typename CONTEXT>
class CUTS_BE_Do_While_Condition_End_T :
  public CUTS_BE_Visitor_T <CUTS_BE::NIL, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE::NIL, PICML::Visitor> visitor_type;

  CUTS_BE_Do_While_Condition_End_T (CONTEXT & context);

  virtual ~CUTS_BE_Do_While_Condition_End_T (void);

  void generate (void);
};

/**
 * @class CUTS_BE_While_Condition_Begin_T
 */
template <typename CONTEXT>
class CUTS_BE_While_Condition_Begin_T :
  public CUTS_BE_Visitor_T <CUTS_BE::NIL, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE::NIL, PICML::Visitor> visitor_type;

  CUTS_BE_While_Condition_Begin_T (CONTEXT & context);

  virtual ~CUTS_BE_While_Condition_Begin_T (void);

  void generate (void);
};

/**
 *
 */
template <typename CONTEXT>
class CUTS_BE_While_Condition_End_T :
  public CUTS_BE_Visitor_T <CUTS_BE::NIL, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE::NIL, PICML::Visitor> visitor_type;

  CUTS_BE_While_Condition_End_T (CONTEXT & context);

  virtual ~CUTS_BE_While_Condition_End_T (void);

  void generate (void);
};

/**
 * @class CUTS_BE_While_Begin_T
 */
template <typename CONTEXT>
class CUTS_BE_While_Begin_T :
  public CUTS_BE_Visitor_T <CUTS_BE::NIL, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE::NIL, PICML::Visitor> visitor_type;

  CUTS_BE_While_Begin_T (CONTEXT & context);

  virtual ~CUTS_BE_While_Begin_T (void);

  void generate (void);
};

/**
 * @class CUTS_BE_While_End_T
 */
template <typename CONTEXT>
class CUTS_BE_While_End_T :
  public CUTS_BE_Visitor_T <CUTS_BE::NIL, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE::NIL, PICML::Visitor> visitor_type;

  CUTS_BE_While_End_T (CONTEXT & context);

  virtual ~CUTS_BE_While_End_T (void);

  void generate (void);
};

/**
 * @class CUTS_BE_For_Condition_Begin_T
 */
template <typename CONTEXT>
class CUTS_BE_For_Condition_Begin_T :
  public CUTS_BE_Visitor_T <CUTS_BE::NIL, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE::NIL, PICML::Visitor> visitor_type;

  CUTS_BE_For_Condition_Begin_T (CONTEXT & context);

  virtual ~CUTS_BE_For_Condition_Begin_T (void);

  void generate (void);
};

/**
 * @class CUTS_BE_For_Condition_Delimiter_T
 */
template <typename CONTEXT>
class CUTS_BE_For_Condition_Delimiter_T :
  public CUTS_BE_Visitor_T <CUTS_BE::NIL, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE::NIL, PICML::Visitor> visitor_type;

  CUTS_BE_For_Condition_Delimiter_T (CONTEXT & context);

  virtual ~CUTS_BE_For_Condition_Delimiter_T (void);

  void generate (void);
};

/**
 * @class CUTS_BE_For_Condition_End_T
 */
template <typename CONTEXT>
class CUTS_BE_For_Condition_End_T :
  public CUTS_BE_Visitor_T <CUTS_BE::NIL, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE::NIL, PICML::Visitor> visitor_type;

  CUTS_BE_For_Condition_End_T (CONTEXT & context);

  virtual ~CUTS_BE_For_Condition_End_T (void);

  void generate (void);
};

/**
 * @class CUTS_BE_For_Begin_T
 */
template <typename CONTEXT>
class CUTS_BE_For_Begin_T :
  public CUTS_BE_Visitor_T <CUTS_BE::NIL, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE::NIL, PICML::Visitor> visitor_type;

  CUTS_BE_For_Begin_T (CONTEXT & context);

  virtual ~CUTS_BE_For_Begin_T (void);

  void generate (void);
};

/**
 * @class CUTS_BE_For_End_T
 */
template <typename CONTEXT>
class CUTS_BE_For_End_T :
  public CUTS_BE_Visitor_T <CUTS_BE::NIL, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE::NIL, PICML::Visitor> visitor_type;

  CUTS_BE_For_End_T (CONTEXT & context);

  virtual ~CUTS_BE_For_End_T (void);

  void generate (void);
};

/**
 * @class CUTS_BE_Action_Properties_Begin_T
 */
template <typename CONTEXT>
class CUTS_BE_Action_Properties_Begin_T :
  public CUTS_BE_Visitor_T <CUTS_BE::NIL, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE::NIL, PICML::Visitor> visitor_type;

  CUTS_BE_Action_Properties_Begin_T (CONTEXT & context);

  virtual ~CUTS_BE_Action_Properties_Begin_T (void);

  void generate (size_t count);
};

/**
 * @class CUTS_BE_Action_Property_T
 */
template <typename CONTEXT>
class CUTS_BE_Action_Property_T :
  public CUTS_BE_Visitor_T <CUTS_BE::NIL, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE::NIL, PICML::Visitor> visitor_type;

  CUTS_BE_Action_Property_T (CONTEXT & context);

  virtual ~CUTS_BE_Action_Property_T (void);

  void generate (const PICML::Property_in prop);
};

/**
 * @class CUTS_BE_Action_Properties_End_T
 */
template <typename CONTEXT>
class CUTS_BE_Action_Properties_End_T :
  public CUTS_BE_Visitor_T <CUTS_BE::NIL, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE::NIL, PICML::Visitor> visitor_type;

  CUTS_BE_Action_Properties_End_T (CONTEXT & context);

  virtual ~CUTS_BE_Action_Properties_End_T (void);

  void generate (void);
};

/**
 * @class CUTS_BE_WorkerAction_Begin_T
 */
template <typename CONTEXT>
class CUTS_BE_WorkerAction_Begin_T :
  public CUTS_BE_Visitor_T <CUTS_BE::NIL, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE::NIL, PICML::Visitor> visitor_type;

  CUTS_BE_WorkerAction_Begin_T (CONTEXT & context);

  virtual ~CUTS_BE_WorkerAction_Begin_T (void);

  void generate (const PICML::Action_in action);
};

/**
 * @class CUTS_BE_OutputAction_Begin_T
 */
template <typename CONTEXT>
class CUTS_BE_OutputAction_Begin_T :
  public CUTS_BE_Visitor_T <CUTS_BE::NIL, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE::NIL, PICML::Visitor> visitor_type;

  CUTS_BE_OutputAction_Begin_T (CONTEXT & context);

  virtual ~CUTS_BE_OutputAction_Begin_T (void);

  void generate (const PICML::OutputAction_in action);
};

/**
 * @class CUTS_BE_OutputAction_Property_T
 */
template <typename CONTEXT>
class CUTS_BE_OutputAction_Property_T :
  public CUTS_BE_Visitor_T <CUTS_BE::NIL, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE::NIL, PICML::Visitor> visitor_type;

  CUTS_BE_OutputAction_Property_T (CONTEXT & context);

  virtual ~CUTS_BE_OutputAction_Property_T (void);

  void generate (const PICML::OutputAction_in action,
                 const PICML::Property_in prop);
};

/**
 * @class CUTS_BE_OutputAction_End_T
 */
template <typename CONTEXT>
class CUTS_BE_OutputAction_End_T :
  public CUTS_BE_Visitor_T <CUTS_BE::NIL, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE::NIL, PICML::Visitor> visitor_type;

  CUTS_BE_OutputAction_End_T (CONTEXT & context);

  virtual ~CUTS_BE_OutputAction_End_T (void);

  void generate (const PICML::OutputAction_in action);
};

/**
 * @class CUTS_BE_CallAction_Begin_T
 */
template <typename CONTEXT>
class CUTS_BE_CallAction_Begin_T :
  public CUTS_BE_Visitor_T <CUTS_BE::NIL, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE::NIL, PICML::Visitor> visitor_type;

  CUTS_BE_CallAction_Begin_T (CONTEXT & context);

  virtual ~CUTS_BE_CallAction_Begin_T (void);

  void generate (const PICML::CallAction & action);
};

/**
 * @class CUTS_BE_CallAction_Property_T
 */
template <typename CONTEXT>
class CUTS_BE_CallAction_Property_T :
  public CUTS_BE_Visitor_T <CUTS_BE::NIL, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE::NIL, PICML::Visitor> visitor_type;

  CUTS_BE_CallAction_Property_T (CONTEXT & context);

  virtual ~CUTS_BE_CallAction_Property_T (void);

  void generate (const PICML::CallAction & action,
                 const PICML::Property & prop);
};

/**
 * @class CUTS_BE_CallAction_End_T
 */
template <typename CONTEXT>
class CUTS_BE_CallAction_End_T :
  public CUTS_BE_Visitor_T <CUTS_BE::NIL, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE::NIL, PICML::Visitor> visitor_type;

  CUTS_BE_CallAction_End_T (CONTEXT & context);

  virtual ~CUTS_BE_CallAction_End_T (void);

  void generate (const PICML::CallAction & action);
};

/**
 * @class CUTS_BE_Action_End_T
 */
template <typename CONTEXT>
class CUTS_BE_Action_End_T :
  public CUTS_BE_Visitor_T <CUTS_BE::NIL, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE::NIL, PICML::Visitor> visitor_type;

  CUTS_BE_Action_End_T (CONTEXT & context);

  virtual ~CUTS_BE_Action_End_T (void);

  void generate (void);
};

/**
 * @class CUTS_BE_State_T
 */
template <typename CONTEXT>
class CUTS_BE_State_T :
  public CUTS_BE_Visitor_T <CUTS_BE::NIL, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE::NIL, PICML::Visitor> visitor_type;

  CUTS_BE_State_T (CONTEXT & context);

  virtual ~CUTS_BE_State_T (void);

  void generate (const PICML::State_in state);
};

///////////////////////////////////////////////////////////////////////////////
// deployment generators

//=============================================================================
/**
 *
 */
//=============================================================================

template <typename CONTEXT>
struct CUTS_BE_ComponentAssembly_Begin_T
{
  static bool generate (const PICML::ComponentAssembly_in assembly)
    { return false; }
};

//=============================================================================
/**
 *
 */
//=============================================================================

template <typename CONTEXT>
struct CUTS_BE_ComponentAssembly_End_T
{
  static bool generate (const PICML::ComponentAssembly_in assembly)
    { return false; }
};

//=============================================================================
/**
 *
 */
//=============================================================================

template <typename CONTEXT>
struct CUTS_BE_Component_Instance_T
{
  static bool generate (const PICML::Component_in component)
    { return false; }
};

//=============================================================================
/**
 *
 */
//=============================================================================

template <typename CONTEXT>
struct CUTS_BE_ComponentAssembly_Connections_Begin_T
{
  static bool generate (const PICML::ComponentAssembly_in assembly)
    { return false; }
};


//=============================================================================
/**
 *
 */
//=============================================================================

template <typename CONTEXT>
struct CUTS_BE_ComponentAssembly_Connections_End_T
{
  static bool generate (const PICML::ComponentAssembly_in assembly)
    { return false; }
};

//=============================================================================
/**
 *
 */
//=============================================================================

template <typename CONTEXT>
struct CUTS_BE_DeploymentPlan_Begin_T
{
  static bool generate (const PICML::DeploymentPlan_in)
    { return false; }
};

//=============================================================================
/**
 *
 */
//=============================================================================

template <typename CONTEXT>
struct CUTS_BE_DeploymentPlan_End_T
{
  static bool generate (const PICML::DeploymentPlan_in)
    { return false; }
};

//=============================================================================
/**
 *
 */
//=============================================================================

template <typename CONTEXT>
struct CUTS_BE_Deployment_Node_T
{
  static bool generate (const PICML::Node_in node)
    { return false; }
};

//=============================================================================
/**
 *
 */
//=============================================================================

template <typename CONTEXT>
struct CUTS_BE_Deployment_Location_T
{
  static bool generate (const PICML::Component_in component,
                        const PICML::Node_in node)
  {
    return false;
  }
};

#if defined (__CUTS_INLINE__)
#include "BE_Generators_T.inl"
#endif

#include "BE_Generators_T.cpp"

#endif  // !defined _CUTS_BE_GENERATORS_T_H_
