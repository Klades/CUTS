// -*- C++ -*-

//=============================================================================
/**
 * @file      CUTS_BE_Eisa.h
 *
 * $Id$
 *
 * @author    James H. Hill
 */
//=============================================================================

#ifndef _CUTS_BE_CIAO_TRAITS_H_
#define _CUTS_BE_CIAO_TRAITS_H_

#include "../BE_Generators_T.h"
#include "../BE_Workspace_Generators_T.h"
#include "../BE_Project_Generators_T.h"

#include "Context.h"
#include "Exec_Header_Generator.h"
#include "Exec_Source_Generator.h"

// Forward decl.
struct CUTS_BE_Impl_Node;

// Forward decl.
struct CUTS_BE_IDL_Node;

//=============================================================================
/**
 *
 */
//=============================================================================

template < >
struct CUTS_BE_File_Open_T <CUTS_BE_Eisa>
{
  static bool
  generate (const PICML::ComponentImplementationContainer & container,
            const PICML::MonolithicImplementation & impl)
  {
    return EISA_EXEC_HEADER_GENERATOR ()->open_file (container) |
           EISA_EXEC_SOURCE_GENERATOR ()->open_file (container);
  }
};

//=============================================================================
/**
 *
 */
//=============================================================================

template < >
struct CUTS_BE_File_Close_T <CUTS_BE_Eisa>
{
  static bool
  generate (const PICML::ComponentImplementationContainer & container,
            const PICML::MonolithicImplementation & impl)
  {
    EISA_EXEC_HEADER_GENERATOR ()->close_file (container);
    EISA_EXEC_SOURCE_GENERATOR ()->close_file (container);
    return true;
  }
};

//=============================================================================
/**
 *
 */
//=============================================================================

template < >
struct CUTS_BE_Prologue_T <CUTS_BE_Eisa>
{
  static bool
  generate (const PICML::ComponentImplementationContainer & container,
            const PICML::MonolithicImplementation & impl)
  {
    EISA_EXEC_HEADER_GENERATOR ()->write_prologue (container);
    EISA_EXEC_SOURCE_GENERATOR ()->write_prologue (container);
    return true;
  }
};

//=============================================================================
/**
 *
 */
//=============================================================================

template < >
struct CUTS_BE_Epilogue_T <CUTS_BE_Eisa>
{
  static bool
  generate (const PICML::ComponentImplementationContainer & container,
            const PICML::MonolithicImplementation & impl)
  {
    EISA_EXEC_HEADER_GENERATOR ()->write_epilogue (container);
    EISA_EXEC_SOURCE_GENERATOR ()->write_epilogue (container);
    return true;
  }
};

//=============================================================================
/**
 *
 */
//=============================================================================

template < >
struct CUTS_BE_Component_Impl_Begin_T <CUTS_BE_Eisa>
{
  static bool
  generate (const PICML::MonolithicImplementation & monoimpl,
            const PICML::Component & component)
  {
    EISA_EXEC_HEADER_GENERATOR ()->write_impl_begin (monoimpl, component);
    EISA_EXEC_SOURCE_GENERATOR ()->write_impl_begin (monoimpl, component);
    return true;
  }
};

//=============================================================================
/**
 *
 */
//=============================================================================

template < >
struct CUTS_BE_Component_Impl_End_T <CUTS_BE_Eisa>
{
  static bool
  generate (const PICML::MonolithicImplementation & monoimpl,
            const PICML::Component & component)
  {
    EISA_EXEC_HEADER_GENERATOR ()->write_impl_end (monoimpl, component);
    EISA_EXEC_SOURCE_GENERATOR ()->write_impl_end (monoimpl, component);
    return true;
  }
};

//=============================================================================
/**
 *
 */
//=============================================================================

template < >
struct CUTS_BE_Factory_Impl_Begin_T <CUTS_BE_Eisa>
{
  static bool
  generate (const PICML::ComponentFactory & factory,
            const PICML::MonolithicImplementation & monoimpl,
            const PICML::Component & component)
  {
    EISA_EXEC_HEADER_GENERATOR ()->
      write_factory_impl_begin (factory, monoimpl, component);
    EISA_EXEC_SOURCE_GENERATOR ()->
      write_factory_impl_begin (factory, monoimpl, component);
    return true;
  }
};

//=============================================================================
/**
 *
 */
//=============================================================================

template < >
struct CUTS_BE_Factory_Impl_End_T <CUTS_BE_Eisa>
{
  static bool generate (const PICML::ComponentFactory & factory,
                        const PICML::MonolithicImplementation & monoimpl,
                        const PICML::Component & component)
  {
    EISA_EXEC_HEADER_GENERATOR ()->
      write_factory_impl_end (factory, monoimpl, component);
    EISA_EXEC_SOURCE_GENERATOR ()->
      write_factory_impl_end (factory, monoimpl, component);
    return true;
  }
};

//=============================================================================
/**
 *
 */
//=============================================================================

template < >
struct CUTS_BE_Object_Impl_Begin_T <CUTS_BE_Eisa>
{
  static bool generate (const PICML::Component & component,
                        const PICML::ProvidedRequestPort & facet)
  {
    EISA_EXEC_HEADER_GENERATOR ()->write_object_impl_begin (component, facet);
    EISA_EXEC_SOURCE_GENERATOR ()->write_object_impl_begin (component, facet);
    return true;
  }
};

//=============================================================================
/**
 *
 */
//=============================================================================

template < >
struct CUTS_BE_Object_Impl_End_T <CUTS_BE_Eisa>
{
  static bool generate (const PICML::Component & component,
                        const PICML::ProvidedRequestPort & facet)
  {
    EISA_EXEC_HEADER_GENERATOR ()->write_object_impl_end (component, facet);
    EISA_EXEC_SOURCE_GENERATOR ()->write_object_impl_end (component, facet);
    return true;
  }
};

//=============================================================================
/**
 *
 */
//=============================================================================

template < >
struct CUTS_BE_Include_File_T <CUTS_BE_Eisa>
{
  static bool generate (const std::string & include)
  {
    EISA_EXEC_HEADER_GENERATOR ()->write_include (include);
    return true;
  }
};

//=============================================================================
/**
 *
 */
//=============================================================================

template < >
struct CUTS_BE_Environment_Begin_T <CUTS_BE_Eisa>
{
  static bool
  generate (const PICML::Component & component)
  {
    EISA_EXEC_HEADER_GENERATOR ()->write_environment_begin (component);
    EISA_EXEC_SOURCE_GENERATOR ()->write_environment_begin (component);
    return true;
  }
};

//=============================================================================
/**
 *
 */
//=============================================================================

template < >
struct CUTS_BE_Environment_Method_Begin_T <CUTS_BE_Eisa>
{
  static bool generate (const PICML::MultiInputAction & action)
  {
    EISA_EXEC_HEADER_GENERATOR ()->write_environment_method_begin (action);
    EISA_EXEC_SOURCE_GENERATOR ()->write_environment_method_begin (action);
    return true;
  }
};

//=============================================================================
/**
 *
 */
//=============================================================================

template < >
struct CUTS_BE_Environment_Method_End_T <CUTS_BE_Eisa>
{
  static bool generate (const PICML::MultiInputAction & action)
  {
    EISA_EXEC_HEADER_GENERATOR ()->write_environment_method_end (action);
    EISA_EXEC_SOURCE_GENERATOR ()->write_environment_method_end (action);
    return true;
  }
};

//=============================================================================
/**
 *
 */
//=============================================================================

template < >
struct CUTS_BE_Environment_End_T <CUTS_BE_Eisa>
{
  static bool
  generate (const PICML::Component & component)
  {
    EISA_EXEC_HEADER_GENERATOR ()->write_environment_end (component);
    EISA_EXEC_SOURCE_GENERATOR ()->write_environment_end (component);
    return true;
  }
};

//=============================================================================
/**
 *
 */
//=============================================================================

template < >
struct CUTS_BE_Variables_Begin_T <CUTS_BE_Eisa>
{
  static bool
  generate (const PICML::Component & component)
  {
    EISA_EXEC_HEADER_GENERATOR ()->write_variables_begin (component);
    EISA_EXEC_SOURCE_GENERATOR ()->write_variables_begin (component);
    return true;
  }
};

//=============================================================================
/**
 *
 */
//=============================================================================

template < >
struct CUTS_BE_Worker_Variable_T <CUTS_BE_Eisa>
{
  static bool generate (const PICML::WorkerType & type,
                        const PICML::Worker & worker)
  {
    EISA_EXEC_HEADER_GENERATOR ()->write_worker_variable (type, worker);
    EISA_EXEC_SOURCE_GENERATOR ()->write_worker_variable (type, worker);
    return true;
  }
};

//=============================================================================
/**
 *
 */
//=============================================================================

template < >
struct CUTS_BE_Variables_End_T <CUTS_BE_Eisa>
{
  static bool
  generate (const PICML::Component & component)
  {
    EISA_EXEC_HEADER_GENERATOR ()->write_variables_end ();
    EISA_EXEC_SOURCE_GENERATOR ()->write_variables_end ();
    return true;
  }
};

//=============================================================================
/**
 *
 */
//=============================================================================

template < >
struct CUTS_BE_PeriodicEvent_Variable_T <CUTS_BE_Eisa>
{
  static bool generate (const PICML::PeriodicEvent & periodic)
  {
    EISA_EXEC_HEADER_GENERATOR ()->write_PeriodicEvent_variable (periodic);
    EISA_EXEC_SOURCE_GENERATOR ()->write_PeriodicEvent_variable (periodic);
    return true;
  }
};

//=============================================================================
/**
 *
 */
//=============================================================================

template < >
struct CUTS_BE_Attribute_Variable_T <CUTS_BE_Eisa>
{
  static bool generate (const PICML::ReadonlyAttribute & attr)
  {
    EISA_EXEC_HEADER_GENERATOR ()->write_ReadonlyAttribute_variable (attr);
    EISA_EXEC_SOURCE_GENERATOR ()->write_ReadonlyAttribute_variable (attr);
    return true;
  }
};

//=============================================================================
/**
 *
 */
//=============================================================================

template < >
struct CUTS_BE_Variable_T <CUTS_BE_Eisa>
{
  static bool generate (const PICML::Variable & variable)
  {
    EISA_EXEC_HEADER_GENERATOR ()->write_variable  (variable);
    EISA_EXEC_SOURCE_GENERATOR ()->write_variable  (variable);
    return true;
  }
};

//=============================================================================
/**
 *
 */
//=============================================================================

template < >
struct CUTS_BE_InEventPort_Begin_T <CUTS_BE_Eisa>
{
  static bool generate (const PICML::InEventPort & sink,
                        const std::vector <PICML::Property> &)
  {
    EISA_EXEC_HEADER_GENERATOR ()->write_InEventPort_begin (sink);
    EISA_EXEC_SOURCE_GENERATOR ()->write_InEventPort_begin (sink);
    return true;
  }
};

//=============================================================================
/**
 *
 */
//=============================================================================

template < >
struct CUTS_BE_InEventPort_End_T <CUTS_BE_Eisa>
{
  static bool generate (const PICML::InEventPort & sink,
                        const std::vector <PICML::Property> &)
  {
    EISA_EXEC_HEADER_GENERATOR ()->write_InEventPort_end  (sink);
    EISA_EXEC_SOURCE_GENERATOR ()->write_InEventPort_end  (sink);
    return true;
  }
};

//=============================================================================
/**
 *
 */
//=============================================================================

template < >
struct CUTS_BE_ProvidedRequestPort_Begin_T <CUTS_BE_Eisa>
{
  static bool generate (const PICML::ProvidedRequestPort & source)
  {
    EISA_EXEC_HEADER_GENERATOR ()->write_ProvidedRequestPort_begin (source);
    EISA_EXEC_SOURCE_GENERATOR ()->write_ProvidedRequestPort_begin (source);
    return true;
  }
};

//=============================================================================
/**
 *
 */
//=============================================================================

template < >
struct CUTS_BE_ProvidedRequestPort_End_T <CUTS_BE_Eisa>
{
  static bool generate (const PICML::ProvidedRequestPort & source)
  {
    EISA_EXEC_HEADER_GENERATOR ()->write_ProvidedRequestPort_end  (source);
    EISA_EXEC_SOURCE_GENERATOR ()->write_ProvidedRequestPort_end  (source);
    return true;
  }
};

//=============================================================================
/**
 *
 */
//=============================================================================

template < >
struct CUTS_BE_PeriodicEvent_Begin_T <CUTS_BE_Eisa>
{
  static bool generate (const PICML::PeriodicEvent & periodic)
  {
    EISA_EXEC_HEADER_GENERATOR ()->write_PeriodicEvent_begin (periodic);
    EISA_EXEC_SOURCE_GENERATOR ()->write_PeriodicEvent_begin (periodic);
    return true;
  }
};

//=============================================================================
/**
 *
 */
//=============================================================================

template < >
struct CUTS_BE_PeriodicEvent_End_T <CUTS_BE_Eisa>
{
  static bool generate (const PICML::PeriodicEvent & periodic)
  {
    EISA_EXEC_HEADER_GENERATOR ()->write_PeriodicEvent_end  (periodic);
    EISA_EXEC_SOURCE_GENERATOR ()->write_PeriodicEvent_end  (periodic);
    return true;
  }
};

//=============================================================================
/**
 *
 */
//=============================================================================

template < >
struct CUTS_BE_ReadonlyAttribute_Begin_T <CUTS_BE_Eisa>
{
  static bool generate (const PICML::ReadonlyAttribute & attr)
  {
    EISA_EXEC_HEADER_GENERATOR ()->write_ReadonlyAttribute_begin (attr);
    EISA_EXEC_SOURCE_GENERATOR ()->write_ReadonlyAttribute_begin (attr);
    return true;
  }
};

//=============================================================================
/**
 *
 */
//=============================================================================

template < >
struct CUTS_BE_ReadonlyAttribute_End_T <CUTS_BE_Eisa>
{
  static bool generate (const PICML::ReadonlyAttribute & attr)
  {
    EISA_EXEC_HEADER_GENERATOR ()->write_ReadonlyAttribute_end  (attr);
    EISA_EXEC_SOURCE_GENERATOR ()->write_ReadonlyAttribute_end  (attr);
    return true;
  }
};

//=============================================================================
/**
 *
 */
//=============================================================================

template < >
struct CUTS_BE_Attribute_Begin_T <CUTS_BE_Eisa>
{
  static bool generate (const PICML::Attribute & attr)
  {
    EISA_EXEC_HEADER_GENERATOR ()->write_Attribute_begin (attr);
    EISA_EXEC_SOURCE_GENERATOR ()->write_Attribute_begin (attr);
    return true;
  }
};

//=============================================================================
/**
 *
 */
//=============================================================================

template < >
struct CUTS_BE_Attribute_End_T <CUTS_BE_Eisa>
{
  static bool generate (const PICML::Attribute & attr)
  {
    EISA_EXEC_HEADER_GENERATOR ()->write_Attribute_end  (attr);
    EISA_EXEC_SOURCE_GENERATOR ()->write_Attribute_end  (attr);
    return true;
  }
};

//=============================================================================
/**
 *
 */
//=============================================================================

template < >
struct CUTS_BE_OnewayOperation_Begin_T <CUTS_BE_Eisa>
{
  static bool generate (const PICML::OnewayOperation & oneway)
  {
    EISA_EXEC_HEADER_GENERATOR ()->write_OnewayOperation_begin (oneway);
    EISA_EXEC_SOURCE_GENERATOR ()->write_OnewayOperation_begin (oneway);
    return true;
  }
};

//=============================================================================
/**
 *
 */
//=============================================================================

template < >
struct CUTS_BE_OnewayOperation_End_T <CUTS_BE_Eisa>
{
  static bool generate (const PICML::OnewayOperation & oneway)
  {
    EISA_EXEC_HEADER_GENERATOR ()->write_OnewayOperation_end  (oneway);
    EISA_EXEC_SOURCE_GENERATOR ()->write_OnewayOperation_end  (oneway);
    return true;
  }
};

//=============================================================================
/**
 *
 */
//=============================================================================

template < >
struct CUTS_BE_TwowayOperation_Begin_T <CUTS_BE_Eisa>
{
  static bool generate (const PICML::TwowayOperation & twoway)
  {
    EISA_EXEC_HEADER_GENERATOR ()->write_TwowayOperation_begin (twoway);
    EISA_EXEC_SOURCE_GENERATOR ()->write_TwowayOperation_begin (twoway);
    return true;
  }
};

//=============================================================================
/**
 *
 */
//=============================================================================

template < >
struct CUTS_BE_TwowayOperation_End_T <CUTS_BE_Eisa>
{
  static bool generate (const PICML::TwowayOperation & twoway)
  {
    EISA_EXEC_HEADER_GENERATOR ()->write_TwowayOperation_end  (twoway);
    EISA_EXEC_SOURCE_GENERATOR ()->write_TwowayOperation_end  (twoway);
    return true;
  }
};

//=============================================================================
/**
 *
 */
//=============================================================================

template < >
struct CUTS_BE_FactoryOperation_Begin_T <CUTS_BE_Eisa>
{
  static bool generate (const PICML::FactoryOperation & fop)
  {
    EISA_EXEC_HEADER_GENERATOR ()->write_FactoryOperation_begin (fop);
    EISA_EXEC_SOURCE_GENERATOR ()->write_FactoryOperation_begin (fop);
    return true;
  }
};

//=============================================================================
/**
 *
 */
//=============================================================================

template < >
struct CUTS_BE_FactoryOperation_End_T <CUTS_BE_Eisa>
{
  static bool generate (const PICML::FactoryOperation & fop)
  {
    EISA_EXEC_HEADER_GENERATOR ()->write_FactoryOperation_end (fop);
    EISA_EXEC_SOURCE_GENERATOR ()->write_FactoryOperation_end (fop);
    return true;
  }
};

//=============================================================================
/**
 *
 */
//=============================================================================

template < >
struct CUTS_BE_Postcondition_T <CUTS_BE_Eisa>
{
  static bool generate (const std::string & postcondition)
  {
    EISA_EXEC_SOURCE_GENERATOR ()->write_postcondition (postcondition);
    return true;
  }
};

//=============================================================================
/**
 *
 */
//=============================================================================

template < >
struct CUTS_BE_Branches_Begin_T <CUTS_BE_Eisa>
{
  static bool generate (size_t branches)
  {
    EISA_EXEC_SOURCE_GENERATOR ()->write_branches_begin (branches);
    return true;
  }
};

//=============================================================================
/**
 *
 */
//=============================================================================

template < >
struct CUTS_BE_Branch_Condition_Begin_T <CUTS_BE_Eisa>
{
  static bool generate (void)
  {
    EISA_EXEC_SOURCE_GENERATOR ()->write_branch_condition_begin ();
    return true;
  }
};

//=============================================================================
/**
 *
 */
//=============================================================================

template < >
struct CUTS_BE_Branch_Condition_End_T <CUTS_BE_Eisa>
{
  static bool generate (void)
  {
    EISA_EXEC_SOURCE_GENERATOR ()->write_branch_condition_end ();
    return true;
  }
};

//=============================================================================
/**
 *
 */
//=============================================================================

template < >
struct CUTS_BE_Branch_No_Condition_T <CUTS_BE_Eisa>
{
  static bool generate (void)
  {
    EISA_EXEC_SOURCE_GENERATOR ()->write_branch_else_condition ();
    return true;
  }
};

//=============================================================================
/**
 *
 */
//=============================================================================

template < >
struct CUTS_BE_Branch_Begin_T <CUTS_BE_Eisa>
{
  static inline bool generate ()
  {
    EISA_EXEC_SOURCE_GENERATOR ()->write_branch_begin ();
    return true;
  }
};

//=============================================================================
/**
 *
 */
//=============================================================================

template < >
struct CUTS_BE_Branch_End_T <CUTS_BE_Eisa>
{
  static inline bool generate ()
  {
    EISA_EXEC_SOURCE_GENERATOR ()->write_branch_end ();
    return true;
  }
};

//=============================================================================
/**
 *
 */
//=============================================================================

template < >
struct CUTS_BE_Branches_End_T <CUTS_BE_Eisa>
{
  static inline bool generate (void)
  {
    EISA_EXEC_SOURCE_GENERATOR ()->write_branches_end ();
    return true;
  }
};

//=============================================================================
/**
 *
 */
//=============================================================================

template < >
struct CUTS_BE_Action_Property_T <CUTS_BE_Eisa>
{
  static inline bool generate (const PICML::Property & property)
  {
    EISA_EXEC_SOURCE_GENERATOR ()->write_action_property (property);
    return true;
  }
};

//=============================================================================
/**
 *
 */
//=============================================================================

template < >
struct CUTS_BE_WorkerAction_Begin_T <CUTS_BE_Eisa>
{
  static inline bool
    generate (const PICML::Worker & worker, const PICML::Action & action)
  {
    EISA_EXEC_SOURCE_GENERATOR ()->
      write_WorkerAction_begin (worker, action);
    return true;
  }
};

//=============================================================================
/**
 *
 */
//=============================================================================

template < >
struct CUTS_BE_OutputAction_Begin_T <CUTS_BE_Eisa>
{
  static inline bool generate (const PICML::OutputAction & action)
  {
    EISA_EXEC_SOURCE_GENERATOR ()->write_OutputAction_begin (action);
    return true;
  }
};

//=============================================================================
/**
 *
 */
//=============================================================================

template < >
struct CUTS_BE_OutputAction_Property_T <CUTS_BE_Eisa>
{
  static inline bool generate (const PICML::OutputAction & action,
                               const PICML::Property & property)
  {
    EISA_EXEC_SOURCE_GENERATOR ()->
      write_OuputAction_Property (action, property);
    return true;
  }
};

//=============================================================================
/**
 *
 */
//=============================================================================

template < >
struct CUTS_BE_OutputAction_End_T <CUTS_BE_Eisa>
{
  static inline bool generate (const PICML::OutputAction & action)
  {
    EISA_EXEC_SOURCE_GENERATOR ()->write_OutputAction_end (action);
    return true;
  }
};

//=============================================================================
/**
 *
 */
//=============================================================================

template < >
struct CUTS_BE_Action_End_T <CUTS_BE_Eisa>
{
  static inline bool generate (void)
  {
    EISA_EXEC_SOURCE_GENERATOR ()->write_action_end ();
    return true;
  }
};

//=============================================================================
/**
 *
 */
//=============================================================================

template < >
struct CUTS_BE_Equal_To_T <CUTS_BE_Eisa>
{
  static bool generate (const char * first, const char * last)
  {
    EISA_EXEC_SOURCE_GENERATOR ()->write_equal_to ();
    return true;
  }
};

//=============================================================================
/**
 *
 */
//=============================================================================

template < >
struct CUTS_BE_Not_Equal_To_T <CUTS_BE_Eisa>
{
  static bool generate (const char * first, const char * last)
  {
    EISA_EXEC_SOURCE_GENERATOR ()->write_not_equal_to ();
    return true;
  }
};

//=============================================================================
/**
 *
 */
//=============================================================================

template < >
struct CUTS_BE_Greater_Than_T <CUTS_BE_Eisa>
{
  static bool generate (const char * first, const char * last)
  {
    EISA_EXEC_SOURCE_GENERATOR ()->write_greater_than ();
    return false;
  }
};

//=============================================================================
/**
 *
 */
//=============================================================================

template < >
struct CUTS_BE_Greater_Than_Equal_To_T <CUTS_BE_Eisa>
{
  static bool generate (const char * first, const char * last)
  {
    EISA_EXEC_SOURCE_GENERATOR ()->write_greater_than_equal_to ();
    return false;
  }
};

//=============================================================================
/**
 *
 */
//=============================================================================

template < >
struct CUTS_BE_Less_Than_T <CUTS_BE_Eisa>
{
  static bool generate (const char * first, const char * last)
  {
    EISA_EXEC_SOURCE_GENERATOR ()->write_less_than ();
    return false;
  }
};

//=============================================================================
/**
 *
 */
//=============================================================================

template < >
struct CUTS_BE_Less_Than_Equal_To_T <CUTS_BE_Eisa>
{
  static bool generate (const char * first, const char * last)
  {
    EISA_EXEC_SOURCE_GENERATOR ()->write_less_than_equal_to ();
    return false;
  }
};

//=============================================================================
/**
 *
 */
//=============================================================================

template < >
struct CUTS_BE_Identifier_T <CUTS_BE_Eisa>
{
  static bool generate (const char * begin, const char * end)
  {
    EISA_EXEC_SOURCE_GENERATOR ()->write_identifier (std::string (begin, end));
    return true;
  }
};

//=============================================================================
/**
 *
 */
//=============================================================================

template < >
struct CUTS_BE_Transcribe_Text_T <CUTS_BE_Eisa>
{
  static bool generate (const char * begin, const char * end)
  {
    EISA_EXEC_SOURCE_GENERATOR ()->write_text (std::string (begin, end));
    return true;
  }
};

//=============================================================================
/**
 *
 */
//=============================================================================

template < >
struct CUTS_BE_Transcribe_Char_T <CUTS_BE_Eisa>
{
  static bool generate (char ch)
  {
    EISA_EXEC_SOURCE_GENERATOR ()->write_char (ch);
    return true;
  }
};

//=============================================================================
/**
 *
 */
//=============================================================================

template < >
struct CUTS_BE_And_T <CUTS_BE_Eisa>
{
  static bool generate (const char * begin, const char * end)
  {
    EISA_EXEC_SOURCE_GENERATOR ()->write_and_symbol ();
    return true;
  }
};

//=============================================================================
/**
 *
 */
//=============================================================================

template < >
struct CUTS_BE_Or_T <CUTS_BE_Eisa>
{
  static bool generate (const char * begin, const char * end)
  {
    EISA_EXEC_SOURCE_GENERATOR ()->write_or_symbol ();
    return true;
  }
};

//=============================================================================
/**
 *
 */
//=============================================================================

template < >
struct CUTS_BE_Workspace_File_Open_T <CUTS_BE_Eisa>
{
  static bool generate (const std::string & name);
};

//=============================================================================
/**
 *
 */
//=============================================================================

template < >
struct CUTS_BE_Workspace_Begin_T <CUTS_BE_Eisa>
{
  static bool generate (const std::string & name);
};

//=============================================================================
/**
 *
 */
//=============================================================================

template < >
struct CUTS_BE_Workspace_Project_Include_T <CUTS_BE_Eisa, CUTS_BE_Impl_Node>
{
  static bool generate (const CUTS_BE_Impl_Node & node);
};

//=============================================================================
/**
 *
 */
//=============================================================================

template < >
struct CUTS_BE_Workspace_Project_Include_T <CUTS_BE_Eisa, CUTS_BE_IDL_Node>
{
  static bool generate (const CUTS_BE_IDL_Node & node);
};

//=============================================================================
/**
 *
 */
//=============================================================================

template < >
struct CUTS_BE_Workspace_End_T <CUTS_BE_Eisa>
{
  static bool generate (const std::string & name);
};

//=============================================================================
/**
 *
 */
//=============================================================================

template < >
struct CUTS_BE_Workspace_File_Close_T <CUTS_BE_Eisa>
{
  static void generate (void);
};

///////////////////////////////////////////////////////////////////////////////
// project generators (CUTS_BE_Impl_Node)

/**
 *
 */
template < >
struct CUTS_BE_Project_File_Open_T <CUTS_BE_Eisa, CUTS_BE_Impl_Node>
{
  static bool generate (const CUTS_BE_Impl_Node & node);
};

/**
 *
 */
template < >
struct CUTS_BE_Project_File_Begin_T <CUTS_BE_Eisa, CUTS_BE_Impl_Node>
{
  static bool generate (const CUTS_BE_Impl_Node & node);
};

/**
 *
 */
template < >
struct CUTS_BE_Project_Write_T <CUTS_BE_Eisa, CUTS_BE_Impl_Node>
{
  typedef std::set <const CUTS_BE_IDL_Node *> IDL_Node_Set;

  static bool generate (const CUTS_BE_Impl_Node & node);

private:
  static void generate_exec_project (const CUTS_BE_Impl_Node & node);

  static void generate_svnt_project (const CUTS_BE_Impl_Node & node);

  static void generate_skel_project (const CUTS_BE_Impl_Node & node);

  static void generate_stub_listing (const CUTS_BE_IDL_Node * node);

  static void generate_mpc_i (const CUTS_BE_Impl_Node & node);

  static void generate_mpc_values (const std::string & heading,
                                   const CUTS_String_Set & listing);

  static IDL_Node_Set visited_nodes_;

  static std::string svnt_project_;
};

/**
 *
 */
template < >
struct CUTS_BE_Project_File_End_T <CUTS_BE_Eisa, CUTS_BE_Impl_Node>
{
  static bool generate (const CUTS_BE_Impl_Node & node);
};

/**
 *
 */
template <  >
struct CUTS_BE_Project_File_Close_T <CUTS_BE_Eisa, CUTS_BE_Impl_Node>
{
  static void generate (void);
};

///////////////////////////////////////////////////////////////////////////////
// project generators (CUTS_BE_IDL_Node)

/**
 *
 */
template <  >
struct CUTS_BE_Project_File_Open_T <CUTS_BE_Eisa, CUTS_BE_IDL_Node>
{
  static bool generate (const CUTS_BE_IDL_Node & node);
};

/**
 *
 */
template <  >
struct CUTS_BE_Project_File_Begin_T <CUTS_BE_Eisa, CUTS_BE_IDL_Node>
{
  static bool generate (const CUTS_BE_IDL_Node & node);
};

/**
 *
 */
template < >
struct CUTS_BE_Project_Write_T <CUTS_BE_Eisa, CUTS_BE_IDL_Node>
{
  typedef std::set <const CUTS_BE_IDL_Node *> IDL_Node_Set;

  static bool generate (const CUTS_BE_IDL_Node & node);

private:
  static void generate_stub_listing (const CUTS_BE_IDL_Node * node);

  static IDL_Node_Set visited_nodes_;
};

/**
 *
 */
template <  >
struct CUTS_BE_Project_File_End_T <CUTS_BE_Eisa, CUTS_BE_IDL_Node>
{
  static bool generate (const CUTS_BE_IDL_Node & node);
};

/**
 *
 */
template <  >
struct CUTS_BE_Project_File_Close_T <CUTS_BE_Eisa, CUTS_BE_IDL_Node>
{
  static void generate (void);
};

#endif  // !defined _CUTS_BE_CIAO_TRAITS_H_
