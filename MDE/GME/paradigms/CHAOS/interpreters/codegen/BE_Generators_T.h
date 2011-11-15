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

#include "../../paradigms/CHAOS.h"
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
  public CUTS_BE_Visitor_T <CUTS_BE::NIL, CHAOS::Visitor>
{
public:
  /// Type definition of the visitor type.
  typedef CUTS_BE_Visitor_T <CUTS_BE::NIL, CHAOS::Visitor> visitor_type;

  /**
   * Initializing conclassor.
   *
   * @param[in]       context         Context for the generator.
   */
  CUTS_BE_Initialize_T (CONTEXT & context);

  /// Destructor.
  virtual ~CUTS_BE_Initialize_T (void);

  void generate (const CHAOS::RootFolder & folder);
};

/**
 * @class CUTS_BE_Finalize_T
 *
 * Finalize the backend.
 */
template <typename CONTEXT>
class CUTS_BE_Finalize_T :
  public CUTS_BE_Visitor_T <CUTS_BE::NIL, CHAOS::Visitor>
{
public:
  /// Type definition of the visitor type.
  typedef CUTS_BE_Visitor_T <CUTS_BE::NIL, CHAOS::Visitor> visitor_type;

  /**
   * Initializing conclassor.
   *
   * @param[in]       context         Context for the generator.
   */
  CUTS_BE_Finalize_T (CONTEXT & context);

  /// Destructor.
  virtual ~CUTS_BE_Finalize_T (void);

  void generate (const CHAOS::RootFolder & folder);
};

/**
 * @class CUTS_BE_File_Open_T
 *
 * Open the file for the monolithic implemenation.
 */
template <typename CONTEXT>
class CUTS_BE_File_Open_T :
  public CUTS_BE_Visitor_T <CUTS_BE::NIL, CHAOS::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE::NIL, CHAOS::Visitor> visitor_type;

  CUTS_BE_File_Open_T (CONTEXT & context);

  virtual ~CUTS_BE_File_Open_T (void);

  void generate (const CHAOS::ComponentImplementationContainer &,
                 const CHAOS::MonolithicImplementation &);
};

/**
 * @class CUTS_BE_File_Close_T
 *
 * Close the file for the monolithic implementation.
 */
template <typename CONTEXT>
class CUTS_BE_File_Close_T :
  public CUTS_BE_Visitor_T <CUTS_BE::NIL, CHAOS::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE::NIL, CHAOS::Visitor> visitor_type;

  CUTS_BE_File_Close_T (CONTEXT & context);

  virtual ~CUTS_BE_File_Close_T (void);

  void generate (const CHAOS::ComponentImplementationContainer &,
                 const CHAOS::MonolithicImplementation &);
};

/**
 *
 */
template <typename CONTEXT>
struct CUTS_BE_ComponentAssembly_File_Open_T
{
  static bool generate (const CHAOS::ComponentImplementationContainer &,
                        const CHAOS::ComponentAssembly &)
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
  static bool generate (const CHAOS::ComponentImplementationContainer &,
                        const CHAOS::ComponentAssembly &)
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
  public CUTS_BE_Visitor_T <CUTS_BE::NIL, CHAOS::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE::NIL, CHAOS::Visitor> visitor_type;

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
  public CUTS_BE_Visitor_T <CUTS_BE::NIL, CHAOS::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE::NIL, CHAOS::Visitor> visitor_type;

  CUTS_BE_Prologue_T (CONTEXT & context);

  virtual ~CUTS_BE_Prologue_T (void);

  void generate (const CHAOS::ComponentImplementationContainer &,
                 const CHAOS::MonolithicImplementation &);
};

/**
 * @class CUTS_BE_Prologue_T
 *
 * Generates the epilogue for an implementation's file.
 */
template <typename CONTEXT>
class CUTS_BE_Epilogue_T :
  public CUTS_BE_Visitor_T <CUTS_BE::NIL, CHAOS::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE::NIL, CHAOS::Visitor> visitor_type;

  CUTS_BE_Epilogue_T (CONTEXT & context);

  virtual ~CUTS_BE_Epilogue_T (void);

  void generate (const CHAOS::ComponentImplementationContainer &,
                 const CHAOS::MonolithicImplementation &);
};

/**
 *
 */
template <typename CONTEXT>
struct CUTS_BE_ComponentAssembly_Prologue_T
{
  static bool generate (const CHAOS::ComponentImplementationContainer &,
                        const CHAOS::ComponentAssembly &)
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
  static bool generate (const CHAOS::ComponentImplementationContainer &,
                        const CHAOS::ComponentAssembly &)
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
  public CUTS_BE_Visitor_T <CUTS_BE::NIL, CHAOS::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE::NIL, CHAOS::Visitor> visitor_type;

  CUTS_BE_Component_Impl_Begin_T (CONTEXT & context);

  virtual ~CUTS_BE_Component_Impl_Begin_T (void);

  void generate (const CHAOS::MonolithicImplementation & monoimpl,
                 const CHAOS::Component & component);
};

/**
 * @class CUTS_BE_Component_Impl_End_T
 *
 * End generation of the component's implementation.
 */
template <typename CONTEXT>
class CUTS_BE_Component_Impl_End_T :
  public CUTS_BE_Visitor_T <CUTS_BE::NIL, CHAOS::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE::NIL, CHAOS::Visitor> visitor_type;

  CUTS_BE_Component_Impl_End_T (CONTEXT & context);

  virtual ~CUTS_BE_Component_Impl_End_T (void);

  void generate (const CHAOS::MonolithicImplementation & monoimpl,
                 const CHAOS::Component & component);
};

/**
 * @class CUTS_BE_Environment_Begin_T
 *
 * Begin generation of an environment action.
 */
template <typename CONTEXT>
class CUTS_BE_Environment_Begin_T :
  public CUTS_BE_Visitor_T <CUTS_BE::NIL, CHAOS::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE::NIL, CHAOS::Visitor> visitor_type;

  CUTS_BE_Environment_Begin_T (CONTEXT & context);

  virtual ~CUTS_BE_Environment_Begin_T (void);

  void generate (const CHAOS::Component & component);
};

/**
 * @class CUTS_BE_Environment_Method_Begin_T
 *
 * Begin the generation of an environment method.
 */
template <typename CONTEXT>
class CUTS_BE_Environment_Method_Begin_T :
  public CUTS_BE_Visitor_T <CUTS_BE::NIL, CHAOS::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE::NIL, CHAOS::Visitor> visitor_type;

  CUTS_BE_Environment_Method_Begin_T (CONTEXT & context);

  virtual ~CUTS_BE_Environment_Method_Begin_T (void);

  void generate (const CHAOS::MultiInputAction & action);
};

/**
 * @class CUTS_BE_Environment_Method_End_T
 *
 * End the generation of an environment method.
 */
template <typename CONTEXT>
class CUTS_BE_Environment_Method_End_T :
  public CUTS_BE_Visitor_T <CUTS_BE::NIL, CHAOS::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE::NIL, CHAOS::Visitor> visitor_type;

  CUTS_BE_Environment_Method_End_T (CONTEXT & context);

  virtual ~CUTS_BE_Environment_Method_End_T (void);

  void generate (const CHAOS::MultiInputAction & action);
};

/**
 * @class CUTS_BE_Environment_End_T
 *
 * End of the environment for a component implementation.
 */
template <typename CONTEXT>
class CUTS_BE_Environment_End_T :
  public CUTS_BE_Visitor_T <CUTS_BE::NIL, CHAOS::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE::NIL, CHAOS::Visitor> visitor_type;

  CUTS_BE_Environment_End_T (CONTEXT & context);

  virtual ~CUTS_BE_Environment_End_T (void);

  void generate (const CHAOS::Component & component);
};

/**
 * @class CUTS_BE_ReadonlyAttribute_Begin_T
 */
template <typename CONTEXT>
class CUTS_BE_ReadonlyAttribute_Begin_T :
  public CUTS_BE_Visitor_T <CUTS_BE::NIL, CHAOS::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE::NIL, CHAOS::Visitor> visitor_type;

  CUTS_BE_ReadonlyAttribute_Begin_T (CONTEXT & context);

  virtual ~CUTS_BE_ReadonlyAttribute_Begin_T (void);

  void generate (const CHAOS::ReadonlyAttribute & readonly);
};

/**
 * @class CUTS_BE_ReadonlyAttribute_End_T
 */
template <typename CONTEXT>
class CUTS_BE_ReadonlyAttribute_End_T :
  public CUTS_BE_Visitor_T <CUTS_BE::NIL, CHAOS::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE::NIL, CHAOS::Visitor> visitor_type;

  CUTS_BE_ReadonlyAttribute_End_T (CONTEXT & context);

  virtual ~CUTS_BE_ReadonlyAttribute_End_T (void);

  void generate (const CHAOS::ReadonlyAttribute & readonly);
};

/**
 * @class CUTS_BE_Attribute_Begin_T
 */
template <typename CONTEXT>
class CUTS_BE_Attribute_Begin_T :
  public CUTS_BE_Visitor_T <CUTS_BE::NIL, CHAOS::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE::NIL, CHAOS::Visitor> visitor_type;

  CUTS_BE_Attribute_Begin_T (CONTEXT & context);

  virtual ~CUTS_BE_Attribute_Begin_T (void);

  void generate (const CHAOS::Attribute & attr);
};

/**
 * @class CUTS_BE_Attribute_End_T
 */
template <typename CONTEXT>
class CUTS_BE_Attribute_End_T :
  public CUTS_BE_Visitor_T <CUTS_BE::NIL, CHAOS::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE::NIL, CHAOS::Visitor> visitor_type;

  CUTS_BE_Attribute_End_T (CONTEXT & context);

  virtual ~CUTS_BE_Attribute_End_T (void);

  void generate (const CHAOS::Attribute & attr);
};

/**
 * @class CUTS_BE_Component_Impl_Entrypoint_T
 */
template <typename CONTEXT>
class CUTS_BE_Component_Impl_Entrypoint_T :
  public CUTS_BE_Visitor_T <CUTS_BE::NIL, CHAOS::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE::NIL, CHAOS::Visitor> visitor_type;

  CUTS_BE_Component_Impl_Entrypoint_T (CONTEXT & context);

  virtual ~CUTS_BE_Component_Impl_Entrypoint_T (void);

  void generate (const CHAOS::MonolithicImplementation & monoimpl,
                 const CHAOS::ComponentImplementationArtifact & artifact);
};

/**
 *
 */
template <typename CONTEXT>
struct CUTS_BE_Factory_Impl_Begin_T
{
  static bool generate (const CHAOS::ComponentFactory & factory,
                        const CHAOS::MonolithicImplementation & monoimpl,
                        const CHAOS::Component & component)
    { return false; }
};

/**
 *
 */
template <typename CONTEXT>
struct CUTS_BE_Factory_Impl_End_T
{
  static bool generate (const CHAOS::ComponentFactory & factory,
                        const CHAOS::MonolithicImplementation & monoimpl,
                        const CHAOS::Component & component)
    { return false; }
};

/**
 *
 */
template <typename CONTEXT>
struct CUTS_BE_Object_Impl_Begin_T
{
  static bool generate (const CHAOS::Component & component,
                        const CHAOS::ProvidedRequestPort & facet)
    { return false; }
};

/**
 *
 */
template <typename CONTEXT>
struct CUTS_BE_Object_Impl_End_T
{
  static bool generate (const CHAOS::Component & component,
                        const CHAOS::ProvidedRequestPort & facet)
    { return false; }
};

/**
 * @class CUTS_BE_Variables_Begin_T
 */
template <typename CONTEXT>
class CUTS_BE_Variables_Begin_T :
  public CUTS_BE_Visitor_T <CUTS_BE::NIL, CHAOS::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE::NIL, CHAOS::Visitor> visitor_type;

  CUTS_BE_Variables_Begin_T (CONTEXT & context);

  virtual ~CUTS_BE_Variables_Begin_T (void);

  void generate (const CHAOS::Component & component);
};

/**
 * @class CUTS_BE_Attribute_Variable_T
 */
template <typename CONTEXT>
class CUTS_BE_Attribute_Variable_T :
  public CUTS_BE_Visitor_T <CUTS_BE::NIL, CHAOS::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE::NIL, CHAOS::Visitor> visitor_type;

  CUTS_BE_Attribute_Variable_T (CONTEXT & context);

  virtual ~CUTS_BE_Attribute_Variable_T (void);

  void generate (const CHAOS::ReadonlyAttribute & attr);
};

/**
 * @class CUTS_BE_Variable_T
 */
template <typename CONTEXT>
class CUTS_BE_Variable_T :
  public CUTS_BE_Visitor_T <CUTS_BE::NIL, CHAOS::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE::NIL, CHAOS::Visitor> visitor_type;

  CUTS_BE_Variable_T (CONTEXT & context);

  virtual ~CUTS_BE_Variable_T (void);

  void generate (const CHAOS::Variable & variable);
};

/**
 * @class CUTS_BE_Worker_Variable_T
 */
template <typename CONTEXT>
class CUTS_BE_Worker_Variable_T :
  public CUTS_BE_Visitor_T <CUTS_BE::NIL, CHAOS::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE::NIL, CHAOS::Visitor> visitor_type;

  CUTS_BE_Worker_Variable_T (CONTEXT & context);

  virtual ~CUTS_BE_Worker_Variable_T (void);

  void generate (const CHAOS::WorkerType & type, const CHAOS::Worker & worker);
};

/**
 * @class CUTS_BE_PeriodicEvent_Variable_T
 */
template <typename CONTEXT>
class CUTS_BE_PeriodicEvent_Variable_T :
  public CUTS_BE_Visitor_T <CUTS_BE::NIL, CHAOS::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE::NIL, CHAOS::Visitor> visitor_type;

  CUTS_BE_PeriodicEvent_Variable_T (CONTEXT & context);

  virtual ~CUTS_BE_PeriodicEvent_Variable_T (void);

  void generate (const CHAOS::PeriodicEvent & periodic);
};

/**
 * @class CUTS_BE_Variables_End_T
 */
template <typename CONTEXT>
class CUTS_BE_Variables_End_T :
  public CUTS_BE_Visitor_T <CUTS_BE::NIL, CHAOS::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE::NIL, CHAOS::Visitor> visitor_type;

  CUTS_BE_Variables_End_T (CONTEXT & context);

  virtual ~CUTS_BE_Variables_End_T (void);

  void generate (const CHAOS::Component & component);
};

/**
 * @class CUTS_BE_InEventPort_Begin_T
 */
template <typename CONTEXT>
class CUTS_BE_InEventPort_Begin_T :
  public CUTS_BE_Visitor_T <CUTS_BE::NIL, CHAOS::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE::NIL, CHAOS::Visitor> visitor_type;

  CUTS_BE_InEventPort_Begin_T (CONTEXT & context);

  virtual ~CUTS_BE_InEventPort_Begin_T (void);

  void generate (const CHAOS::InEventPort & sink,
                 const std::vector <CHAOS::Property> & properties);
};

/**
 * @class CUTS_BE_InEventPort_End_T
 */
template <typename CONTEXT>
class CUTS_BE_InEventPort_End_T :
  public CUTS_BE_Visitor_T <CUTS_BE::NIL, CHAOS::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE::NIL, CHAOS::Visitor> visitor_type;

  CUTS_BE_InEventPort_End_T (CONTEXT & context);

  virtual ~CUTS_BE_InEventPort_End_T (void);

  void generate (const CHAOS::InEventPort & sink,
                 const std::vector <CHAOS::Property> & properties);
};

/**
 * @class CUTS_BE_ProvidedRequestPort_Begin_T
 */
template <typename CONTEXT>
class CUTS_BE_ProvidedRequestPort_Begin_T :
  public CUTS_BE_Visitor_T <CUTS_BE::NIL, CHAOS::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE::NIL, CHAOS::Visitor> visitor_type;

  CUTS_BE_ProvidedRequestPort_Begin_T (CONTEXT & context);

  virtual ~CUTS_BE_ProvidedRequestPort_Begin_T (void);

  void generate (const CHAOS::ProvidedRequestPort & source);
};

/**
 * @class CUTS_BE_ProvidedRequestPort_End_T
 */
template <typename CONTEXT>
class CUTS_BE_ProvidedRequestPort_End_T :
  public CUTS_BE_Visitor_T <CUTS_BE::NIL, CHAOS::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE::NIL, CHAOS::Visitor> visitor_type;

  CUTS_BE_ProvidedRequestPort_End_T (CONTEXT & context);

  virtual ~CUTS_BE_ProvidedRequestPort_End_T (void);

  void generate (const CHAOS::ProvidedRequestPort & source);
};

/**
 * @class CUTS_BE_PeriodicEvent_Begin_T
 */
template <typename CONTEXT>
class CUTS_BE_PeriodicEvent_Begin_T :
  public CUTS_BE_Visitor_T <CUTS_BE::NIL, CHAOS::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE::NIL, CHAOS::Visitor> visitor_type;

  CUTS_BE_PeriodicEvent_Begin_T (CONTEXT & context);

  virtual ~CUTS_BE_PeriodicEvent_Begin_T (void);

  void generate (const CHAOS::PeriodicEvent & periodic);
};

/**
 * @class CUTS_BE_PeriodicEvent_End_T
 */
template <typename CONTEXT>
class CUTS_BE_PeriodicEvent_End_T :
  public CUTS_BE_Visitor_T <CUTS_BE::NIL, CHAOS::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE::NIL, CHAOS::Visitor> visitor_type;

  CUTS_BE_PeriodicEvent_End_T (CONTEXT & context);

  virtual ~CUTS_BE_PeriodicEvent_End_T (void);

  void generate (const CHAOS::PeriodicEvent & periodic);
};

//=============================================================================
/**
 *
 */
//=============================================================================

template <typename CONTEXT>
struct CUTS_BE_OnewayOperation_Begin_T
{
  static bool generate (const CHAOS::OnewayOperation & oneway)
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
  static bool generate (const CHAOS::OnewayOperation & oneway)
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
  static bool generate (const CHAOS::TwowayOperation & twoway)
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
  static bool generate (const CHAOS::TwowayOperation & twoway)
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
  static bool generate (const CHAOS::FactoryOperation & factory)
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
  static bool generate (const CHAOS::FactoryOperation & factory)
    { return false; }
};

///////////////////////////////////////////////////////////////////////////////
// CBML

/**
 * @class CUTS_BE_Postcondition_T
 */
template <typename CONTEXT>
class CUTS_BE_Postcondition_T :
  public CUTS_BE_Visitor_T <CUTS_BE::NIL, CHAOS::Visitor>
{
public:
  CUTS_BE_Postcondition_T (CONTEXT & context);

  virtual ~CUTS_BE_Postcondition_T (void);

  typedef CUTS_BE_Visitor_T <CUTS_BE::NIL, CHAOS::Visitor> visitor_type;

  void generate (const std::string & postcondition);
};

/**
 * @class CUTS_BE_Precondition_T
 */
template <typename CONTEXT>
class CUTS_BE_Precondition_T :
  public CUTS_BE_Visitor_T <CUTS_BE::NIL, CHAOS::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE::NIL, CHAOS::Visitor> visitor_type;

  CUTS_BE_Precondition_T (CONTEXT & context);

  virtual ~CUTS_BE_Precondition_T (void);

  void generate (const std::string & precondition);
};

/**
 * @class CUTS_BE_Branches_Begin_T
 */
template <typename CONTEXT>
class CUTS_BE_Branches_Begin_T :
  public CUTS_BE_Visitor_T <CUTS_BE::NIL, CHAOS::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE::NIL, CHAOS::Visitor> visitor_type;

  CUTS_BE_Branches_Begin_T (CONTEXT & context);

  virtual ~CUTS_BE_Branches_Begin_T (void);

  void generate (size_t branches);
};

/**
 * @class CUTS_BE_Branch_Begin_T
 */
template <typename CONTEXT>
class CUTS_BE_Branch_Begin_T :
  public CUTS_BE_Visitor_T <CUTS_BE::NIL, CHAOS::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE::NIL, CHAOS::Visitor> visitor_type;

  CUTS_BE_Branch_Begin_T (CONTEXT & context);

  virtual ~CUTS_BE_Branch_Begin_T (void);

  void generate (void);
};

/**
 * @class CUTS_BE_Branch_End_T
 */
template <typename CONTEXT>
class CUTS_BE_Branch_End_T :
  public CUTS_BE_Visitor_T <CUTS_BE::NIL, CHAOS::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE::NIL, CHAOS::Visitor> visitor_type;

  CUTS_BE_Branch_End_T (CONTEXT & context);

  virtual ~CUTS_BE_Branch_End_T (void);

  void generate (void);
};

/**
 * @class CUTS_BE_Branch_Condition_Begin_T
 */
template <typename CONTEXT>
class CUTS_BE_Branch_Condition_Begin_T :
  public CUTS_BE_Visitor_T <CUTS_BE::NIL, CHAOS::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE::NIL, CHAOS::Visitor> visitor_type;

  CUTS_BE_Branch_Condition_Begin_T (CONTEXT & context);

  virtual ~CUTS_BE_Branch_Condition_Begin_T (void);

  void generate (void);
};

/**
 * @class CUTS_BE_Branch_Condition_End_T
 */
template <typename CONTEXT>
class CUTS_BE_Branch_Condition_End_T :
  public CUTS_BE_Visitor_T <CUTS_BE::NIL, CHAOS::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE::NIL, CHAOS::Visitor> visitor_type;

  CUTS_BE_Branch_Condition_End_T (CONTEXT & context);

  virtual ~CUTS_BE_Branch_Condition_End_T (void);

  void generate (void);
};

/**
 * @class CUTS_BE_Branch_No_Condition_T
 */
template <typename CONTEXT>
class CUTS_BE_Branch_No_Condition_T :
  public CUTS_BE_Visitor_T <CUTS_BE::NIL, CHAOS::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE::NIL, CHAOS::Visitor> visitor_type;

  CUTS_BE_Branch_No_Condition_T (CONTEXT & context);

  virtual ~CUTS_BE_Branch_No_Condition_T (void);

  void generate (void);
};

/**
 * @class CUTS_BE_Branches_End_T
 */
template <typename CONTEXT>
class CUTS_BE_Branches_End_T :
  public CUTS_BE_Visitor_T <CUTS_BE::NIL, CHAOS::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE::NIL, CHAOS::Visitor> visitor_type;

  CUTS_BE_Branches_End_T (CONTEXT & context);

  virtual ~CUTS_BE_Branches_End_T (void);

  void generate (void);
};

/**
 * @class CUTS_BE_Do_While_Begin_T
 */
template <typename CONTEXT>
class CUTS_BE_Do_While_Begin_T :
  public CUTS_BE_Visitor_T <CUTS_BE::NIL, CHAOS::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE::NIL, CHAOS::Visitor> visitor_type;

  CUTS_BE_Do_While_Begin_T (CONTEXT & context);

  virtual ~CUTS_BE_Do_While_Begin_T (void);

  void generate (void);
};

/**
 * @class CUTS_BE_Do_While_End_T
 */
template <typename CONTEXT>
class CUTS_BE_Do_While_End_T :
  public CUTS_BE_Visitor_T <CUTS_BE::NIL, CHAOS::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE::NIL, CHAOS::Visitor> visitor_type;

  CUTS_BE_Do_While_End_T (CONTEXT & context);

  virtual ~CUTS_BE_Do_While_End_T (void);

  void generate (void);
};

/**
 * @class CUTS_BE_Do_While_Condition_Begin_T
 */
template <typename CONTEXT>
class CUTS_BE_Do_While_Condition_Begin_T :
  public CUTS_BE_Visitor_T <CUTS_BE::NIL, CHAOS::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE::NIL, CHAOS::Visitor> visitor_type;

  CUTS_BE_Do_While_Condition_Begin_T (CONTEXT & context);

  virtual ~CUTS_BE_Do_While_Condition_Begin_T (void);

  void generate (void);
};

/**
 * @class CUTS_BE_Do_While_Condition_End_T
 */
template <typename CONTEXT>
class CUTS_BE_Do_While_Condition_End_T :
  public CUTS_BE_Visitor_T <CUTS_BE::NIL, CHAOS::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE::NIL, CHAOS::Visitor> visitor_type;

  CUTS_BE_Do_While_Condition_End_T (CONTEXT & context);

  virtual ~CUTS_BE_Do_While_Condition_End_T (void);

  void generate (void);
};

/**
 * @class CUTS_BE_While_Condition_Begin_T
 */
template <typename CONTEXT>
class CUTS_BE_While_Condition_Begin_T :
  public CUTS_BE_Visitor_T <CUTS_BE::NIL, CHAOS::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE::NIL, CHAOS::Visitor> visitor_type;

  CUTS_BE_While_Condition_Begin_T (CONTEXT & context);

  virtual ~CUTS_BE_While_Condition_Begin_T (void);

  void generate (void);
};

/**
 *
 */
template <typename CONTEXT>
class CUTS_BE_While_Condition_End_T :
  public CUTS_BE_Visitor_T <CUTS_BE::NIL, CHAOS::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE::NIL, CHAOS::Visitor> visitor_type;

  CUTS_BE_While_Condition_End_T (CONTEXT & context);

  virtual ~CUTS_BE_While_Condition_End_T (void);

  void generate (void);
};

/**
 * @class CUTS_BE_While_Begin_T
 */
template <typename CONTEXT>
class CUTS_BE_While_Begin_T :
  public CUTS_BE_Visitor_T <CUTS_BE::NIL, CHAOS::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE::NIL, CHAOS::Visitor> visitor_type;

  CUTS_BE_While_Begin_T (CONTEXT & context);

  virtual ~CUTS_BE_While_Begin_T (void);

  void generate (void);
};

/**
 * @class CUTS_BE_While_End_T
 */
template <typename CONTEXT>
class CUTS_BE_While_End_T :
  public CUTS_BE_Visitor_T <CUTS_BE::NIL, CHAOS::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE::NIL, CHAOS::Visitor> visitor_type;

  CUTS_BE_While_End_T (CONTEXT & context);

  virtual ~CUTS_BE_While_End_T (void);

  void generate (void);
};

/**
 * @class CUTS_BE_Action_Properties_Begin_T
 */
template <typename CONTEXT>
class CUTS_BE_Action_Properties_Begin_T :
  public CUTS_BE_Visitor_T <CUTS_BE::NIL, CHAOS::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE::NIL, CHAOS::Visitor> visitor_type;

  CUTS_BE_Action_Properties_Begin_T (CONTEXT & context);

  virtual ~CUTS_BE_Action_Properties_Begin_T (void);

  void generate (size_t count);
};

/**
 * @class CUTS_BE_Action_Property_T
 */
template <typename CONTEXT>
class CUTS_BE_Action_Property_T :
  public CUTS_BE_Visitor_T <CUTS_BE::NIL, CHAOS::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE::NIL, CHAOS::Visitor> visitor_type;

  CUTS_BE_Action_Property_T (CONTEXT & context);

  virtual ~CUTS_BE_Action_Property_T (void);

  void generate (const CHAOS::Property & property);
};

/**
 * @class CUTS_BE_Action_Properties_End_T
 */
template <typename CONTEXT>
class CUTS_BE_Action_Properties_End_T :
  public CUTS_BE_Visitor_T <CUTS_BE::NIL, CHAOS::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE::NIL, CHAOS::Visitor> visitor_type;

  CUTS_BE_Action_Properties_End_T (CONTEXT & context);

  virtual ~CUTS_BE_Action_Properties_End_T (void);

  void generate (void);
};

/**
 * @class CUTS_BE_WorkerAction_Begin_T
 */
template <typename CONTEXT>
class CUTS_BE_WorkerAction_Begin_T :
  public CUTS_BE_Visitor_T <CUTS_BE::NIL, CHAOS::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE::NIL, CHAOS::Visitor> visitor_type;

  CUTS_BE_WorkerAction_Begin_T (CONTEXT & context);

  virtual ~CUTS_BE_WorkerAction_Begin_T (void);

  void generate (const CHAOS::Worker & worker,
                 const CHAOS::Action & action);
};

/**
 * @class CUTS_BE_OutputAction_Begin_T
 */
template <typename CONTEXT>
class CUTS_BE_OutputAction_Begin_T :
  public CUTS_BE_Visitor_T <CUTS_BE::NIL, CHAOS::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE::NIL, CHAOS::Visitor> visitor_type;

  CUTS_BE_OutputAction_Begin_T (CONTEXT & context);

  virtual ~CUTS_BE_OutputAction_Begin_T (void);

  void generate (const CHAOS::OutputAction & action);
};

/**
 * @class CUTS_BE_OutputAction_Property_T
 */
template <typename CONTEXT>
class CUTS_BE_OutputAction_Property_T :
  public CUTS_BE_Visitor_T <CUTS_BE::NIL, CHAOS::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE::NIL, CHAOS::Visitor> visitor_type;

  CUTS_BE_OutputAction_Property_T (CONTEXT & context);

  virtual ~CUTS_BE_OutputAction_Property_T (void);

  void generate (const CHAOS::OutputAction & action,
                 const CHAOS::Property & property);
};

/**
 * @class CUTS_BE_OutputAction_End_T
 */
template <typename CONTEXT>
class CUTS_BE_OutputAction_End_T :
  public CUTS_BE_Visitor_T <CUTS_BE::NIL, CHAOS::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE::NIL, CHAOS::Visitor> visitor_type;

  CUTS_BE_OutputAction_End_T (CONTEXT & context);

  virtual ~CUTS_BE_OutputAction_End_T (void);

  void generate (const CHAOS::OutputAction & action);
};

/**
 * @class CUTS_BE_Action_End_T
 */
template <typename CONTEXT>
class CUTS_BE_Action_End_T :
  public CUTS_BE_Visitor_T <CUTS_BE::NIL, CHAOS::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE::NIL, CHAOS::Visitor> visitor_type;

  CUTS_BE_Action_End_T (CONTEXT & context);

  virtual ~CUTS_BE_Action_End_T (void);

  void generate (void);
};

/**
 * @class CUTS_BE_State_T
 */
template <typename CONTEXT>
class CUTS_BE_State_T :
  public CUTS_BE_Visitor_T <CUTS_BE::NIL, CHAOS::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE::NIL, CHAOS::Visitor> visitor_type;

  CUTS_BE_State_T (CONTEXT & context);

  virtual ~CUTS_BE_State_T (void);

  void generate (const CHAOS::State & state);
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
  static bool generate (const CHAOS::ComponentAssembly & assembly)
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
  static bool generate (const CHAOS::ComponentAssembly & assembly)
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
  static bool generate (const CHAOS::Component & component)
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
  static bool generate (const CHAOS::ComponentAssembly & assembly)
    { return false; }
};

//=============================================================================
/**
 *
 */
//=============================================================================

template <typename CONTEXT>
struct CUTS_BE_emit_T
{
  static bool generate (const CHAOS::emit & emit)
    { return false; }
};

//=============================================================================
/**
 *
 */
//=============================================================================

template <typename CONTEXT>
struct CUTS_BE_PublishConnector_T
{
  static bool generate (const CHAOS::PublishConnector & connector)
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
  static bool generate (const CHAOS::ComponentAssembly & assembly)
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
  static bool generate (const CHAOS::DeploymentPlan &)
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
  static bool generate (const CHAOS::DeploymentPlan &)
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
  static bool generate (const CHAOS::Node & node)
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
  static bool generate (const CHAOS::Component & component,
                        const CHAOS::Node & node)
  {
    return false;
  }
};

#if defined (__CUTS_INLINE__)
#include "BE_Generators_T.inl"
#endif

#include "BE_Generators_T.cpp"

#endif  // !defined _CUTS_BE_GENERATORS_T_H_
