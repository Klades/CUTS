// -*- C++ -*-

//=============================================================================
/**
 * @file          XML_Generators.h
 *
 * Defines the different generators used by the CAPI backend
 *
 * $Id$
 *
 * @author        James H. Hill
 */
//=============================================================================

#ifndef _CUTS_BE_XML_GENERATORS_H_
#define _CUTS_BE_XML_GENERATORS_H_

#include "be/BE_Generators_T.h"
#include "be/BE_algorithm.h"
#include "be/String_Set.h"
#include "ace/Singleton.h"
#include "ace/Null_Mutex.h"
#include <fstream>
#include <stack>

// code generation headers
#include "CCF/CodeGenerationKit/IndentationJava.hpp"
#include "CCF/CodeGenerationKit/IndentationXML.hpp"
#include "CCF/CodeGenerationKit/IndentationImplanter.hpp"

//=============================================================================
/**
 * @struct CUTS_BE_Capi
 *
 * Context for the CAPI backend. This is used to store persistant data
 * needed by the CAPI backend generator when writing the implemenation
 * files.
 */
//=============================================================================

class CUTS_BE_Capi
{
public:
  static std::string setter_method (const std::string & name);

  static std::string getter_method (const std::string & name);

  static std::string fq_name (const PICML::NamedType & type,
                              char separator = '.');

  static std::string scope (const PICML::NamedType & type,
                            char separator = '.');

  typedef std::map <Uml::Class, std::string> PredefinedType_Map;

  static PredefinedType_Map predefined_type_map_;

  /// Default constructor.
  CUTS_BE_Capi (void);

  /// Target source file.
  std::ofstream outfile_;

  /// Indentation implanter.
  typedef Indentation::Implanter <
    Indentation::Java, char> _formatter_type;

  /// Pointer to the formatter.
  std::auto_ptr <_formatter_type> formatter_;

  /// Indentation implanter.
  typedef Indentation::Implanter <
    Indentation::XML, char> _project_formatter_type;

  /// Target project file.
  std::ofstream project_file_;

  std::ofstream workspace_file_;

  std::auto_ptr <_project_formatter_type> project_formatter_;

  std::auto_ptr <_project_formatter_type> workspace_formatter_;

  void reset (void);

  void generate_accessor_methods (std::string type, string varname);

  void generate_required_method_impl (const std::string & method);

  void generate_throws_signature (const std::string & method);

  typedef std::map <std::string, std::string> Periodic_Map;

  // <port name, <event type, event version> >
  typedef std::map <
    std::string,
    std::pair <std::string, std::string> >
    Event_Port_Map;

  Event_Port_Map sinks_;

  Event_Port_Map sources_;

  Periodic_Map periodics_;

  typedef std::map <std::string, bool> Env_Seen_Map;

  Env_Seen_Map env_seen_;

  /// The classname of the current implementation.
  std::string impl_classname_;

  /// Keeps track of the current branch depth.
  std::stack <size_t> branches_;
};

// Singleton declaration for the backend generator.
#define CUTS_BE_CAPI() \
  ACE_Singleton <CUTS_BE_Capi, ACE_Null_Mutex>::instance ()

//
// disable the following points of generation
//
namespace CUTS_BE
{
  CUTS_BE_NOT_VISIT (CUTS_BE_Capi, PICML::ProvidedRequestPort);
  CUTS_BE_NOT_VISIT (CUTS_BE_Capi, PICML::ComponentFactory);
  CUTS_BE_NOT_VISIT (CUTS_BE_Capi, PICML::Object);
  CUTS_BE_NOT_VISIT (CUTS_BE_Capi, PICML::OnewayOperation);
  CUTS_BE_NOT_VISIT (CUTS_BE_Capi, PICML::TwowayOperation);
}

/**
 *
 */
template < >
struct CUTS_BE_File_Open_T <CUTS_BE_Capi>
{
  static bool generate (const PICML::ComponentImplementationContainer &,
            const PICML::MonolithicImplementation &);
};

/**
 *
 */
template < >
struct CUTS_BE_File_Close_T <CUTS_BE_Capi>
{
  static bool generate (const PICML::ComponentImplementationContainer &,
                        const PICML::MonolithicImplementation &);
};

/**
 *
 */
template < >
struct CUTS_BE_Prologue_T <CUTS_BE_Capi>
{
  static bool generate (const PICML::ComponentImplementationContainer &,
                        const PICML::MonolithicImplementation & );
};

////=============================================================================
///**
// *
// */
////=============================================================================
//
//template < >
//struct CUTS_BE_Include_File_T <CUTS_BE_Capi>
//{
//  static bool generate (const std::string & include);
//};

/**
 *
 */
template < >
struct CUTS_BE_Component_Impl_Begin_T <CUTS_BE_Capi>
{
  static bool generate (const PICML::MonolithicImplementation & mono,
                        const PICML::Component & component);

private:
  static void generate_worker_import (const PICML::Worker & );
};

/**
 *
 */
template < >
struct CUTS_BE_Component_Impl_End_T <CUTS_BE_Capi>
{
  static bool generate (const PICML::MonolithicImplementation & mono,
                        const PICML::Component & component);
};

/**
 *
 */
template < >
struct CUTS_BE_Variables_Begin_T <CUTS_BE_Capi>
{
  static bool generate (const PICML::Component & component);
};

/**
 *
 */
template < >
struct CUTS_BE_Variable_T <CUTS_BE_Capi>
{
  static bool generate (const PICML::Variable & variable);
};

/**
 *
 */
template < >
struct CUTS_BE_Worker_Variable_T <CUTS_BE_Capi>
{
  static bool generate (const PICML::WorkerType & type,
                        const PICML::Worker & worker);
};

/**
 *
 */
template < >
struct CUTS_BE_Variables_End_T <CUTS_BE_Capi>
{
  static bool generate (const PICML::Component & component);
};

/**
 *
 */
template < >
struct CUTS_BE_WorkerAction_Begin_T <CUTS_BE_Capi>
{
  static bool generate (const PICML::Worker & worker,
                        const PICML::Action & action);
};

/**
 *
 */
template < >
struct CUTS_BE_Action_Property_T <CUTS_BE_Capi>
{
  static bool generate (const PICML::Property & property);
};

/**
 *
 */
template < >
struct CUTS_BE_OutputAction_Begin_T <CUTS_BE_Capi>
{
  static bool generate (const PICML::OutputAction & action);
};

/**
 *
 */
template < >
struct CUTS_BE_OutputAction_Property_T <CUTS_BE_Capi>
{
  static bool generate (const PICML::OutputAction & action,
                        const PICML::Property & property);
};

/**
 *
 */
template < >
struct CUTS_BE_OutputAction_End_T <CUTS_BE_Capi>
{
  static bool generate (const PICML::OutputAction & action);
};

/**
 *
 */
template < >
struct CUTS_BE_Action_End_T <CUTS_BE_Capi>
{
  static bool generate (void);
};

/**
 *
 */
template < >
struct CUTS_BE_InEventPort_Begin_T <CUTS_BE_Capi>
{
  static bool generate (const PICML::InEventPort & sink,
                        const std::vector <PICML::Property> &);

private:
  static void configure (const PICML::InEventPort & parent,
                         const PICML::Property & property);
};

/**
 *
 */
template < >
struct CUTS_BE_InEventPort_End_T <CUTS_BE_Capi>
{
  static bool generate (const PICML::InEventPort & sink,
                        const std::vector <PICML::Property> &);
};

/**
 *
 */
template < >
struct CUTS_BE_Environment_Begin_T <CUTS_BE_Capi>
{
  static bool generate (const PICML::Component & component);
};

/**
 *
 */
template < >
struct CUTS_BE_Environment_Method_Begin_T <CUTS_BE_Capi>
{
  static bool generate (const PICML::MultiInputAction & action);
};

/**
 *
 */
template < >
struct CUTS_BE_Environment_Method_End_T <CUTS_BE_Capi>
{
  static bool generate (const PICML::MultiInputAction & action);
};

/**
 *
 */
template < >
struct CUTS_BE_Environment_End_T <CUTS_BE_Capi>
{
  static bool generate (const PICML::Component & component);
};

/**
 *
 */
template < >
struct CUTS_BE_PeriodicEvent_Begin_T <CUTS_BE_Capi>
{
  static bool generate (const PICML::PeriodicEvent & periodic);
};

/**
 *
 */
template < >
struct CUTS_BE_Postcondition_T <CUTS_BE_Capi>
{
  static bool generate (const std::string & postcondition);
};

/**
 *
 */
template < >
struct CUTS_BE_PeriodicEvent_End_T <CUTS_BE_Capi>
{
  static bool generate (const PICML::PeriodicEvent & periodic);
};

/**
 *
 */
template < >
struct CUTS_BE_Branches_Begin_T <CUTS_BE_Capi>
{
  static bool generate (size_t branches);
};

/**
 *
 */
template < >
struct CUTS_BE_Branch_Condition_Begin_T <CUTS_BE_Capi>
{
  static bool generate (void);
};

/**
 *
 */
template < >
struct CUTS_BE_Branch_Condition_End_T <CUTS_BE_Capi>
{
  static bool generate (void);
};

/**
 *
 */
template < >
struct CUTS_BE_Branch_No_Condition_T <CUTS_BE_Capi>
{
  static bool generate (void);
};

/**
 *
 */
template < >
struct CUTS_BE_Branch_Begin_T <CUTS_BE_Capi>
{
  static bool generate (void);
};

/**
 *
 */
template < >
struct CUTS_BE_Branch_End_T <CUTS_BE_Capi>
{
  static bool generate (void);
};

/**
 *
 */
template < >
struct CUTS_BE_Branches_End_T <CUTS_BE_Capi>
{
  static bool generate (void);
};

/**
 *
 */
template < >
struct CUTS_BE_Do_While_Begin_T <CUTS_BE_Capi>
{
  static bool generate (void);
};

/**
 *
 */
template < >
struct CUTS_BE_Do_While_End_T <CUTS_BE_Capi>
{
  static bool generate (void);
};

/**
 *
 */
template < >
struct CUTS_BE_Do_While_Condition_Begin_T <CUTS_BE_Capi>
{
  static bool generate (void);
};

/**
 *
 */
template < >
struct CUTS_BE_Do_While_Condition_End_T <CUTS_BE_Capi>
{
  static bool generate (void);
};

/**
 *
 */
template < >
struct CUTS_BE_While_Condition_Begin_T <CUTS_BE_Capi>
{
  static bool generate (void);
};

/**
 *
 */
template < >
struct CUTS_BE_While_Condition_End_T <CUTS_BE_Capi>
{
  static bool generate (void);
};

/**
 *
 */
template < >
struct CUTS_BE_While_Begin_T <CUTS_BE_Capi>
{
  static bool generate (void);
};

/**
 *
 */
template < >
struct CUTS_BE_While_End_T <CUTS_BE_Capi>
{
  static bool generate (void);
};

/**
 *
 */
template < >
struct CUTS_BE_Equal_To_T <CUTS_BE_Capi>
{
  static bool generate (const char * first, const char * last);
};

/**
 *
 */
template < >
struct CUTS_BE_Not_Equal_To_T <CUTS_BE_Capi>
{
  static bool generate (const char * first, const char * last);
};

/**
 *
 */
template < >
struct CUTS_BE_Greater_Than_T <CUTS_BE_Capi>
{
  static bool generate (const char * first, const char * last);
};

/**
 *
 */
template < >
struct CUTS_BE_Greater_Than_Equal_To_T <CUTS_BE_Capi>
{
  static bool generate (const char * first, const char * last);
};

/**
 *
 */
template < >
struct CUTS_BE_Less_Than_T <CUTS_BE_Capi>
{
  static bool generate (const char * first, const char * last);
};

/**
 *
 */
template < >
struct CUTS_BE_Less_Than_Equal_To_T <CUTS_BE_Capi>
{
  static bool generate (const char * first, const char * last);
};

/**
 *
 */
template < >
struct CUTS_BE_Identifier_T <CUTS_BE_Capi>
{
  static bool generate (const char * begin, const char * end);
};

/**
 *
 */
template < >
struct CUTS_BE_Transcribe_Text_T <CUTS_BE_Capi>
{
  static bool generate (const char * begin, const char * end);
};

/**
 *
 */
template < >
struct CUTS_BE_Transcribe_Char_T <CUTS_BE_Capi>
{
  static bool generate (char ch);
};

/**
 *
 */
template < >
struct CUTS_BE_Attribute_Variable_T <CUTS_BE_Capi>
{
  static bool generate (const PICML::ReadonlyAttribute & attr);
};

/**
 *
 */
template < >
struct CUTS_BE_ReadonlyAttribute_Begin_T <CUTS_BE_Capi>
{
  static bool generate (const PICML::ReadonlyAttribute & readonly);
};

/**
 *
 */
template < >
struct CUTS_BE_ReadonlyAttribute_End_T <CUTS_BE_Capi>
{
  static bool generate (const PICML::ReadonlyAttribute & readonly);
};

/**
 *
 */
template < >
struct CUTS_BE_Attribute_Begin_T <CUTS_BE_Capi>
{
  static bool generate (const PICML::Attribute & attr);
};

/**
 *
 */
template < >
struct CUTS_BE_Attribute_End_T <CUTS_BE_Capi>
{
  static bool generate (const PICML::Attribute & attr);
};

#endif  // !defined _CUTS_BE_XML_GENERATORS_H_
