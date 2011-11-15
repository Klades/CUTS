// -*- C++ -*-

//=============================================================================
/**
 * @file          XML_Generators.h
 *
 * $Id$
 *
 * @author        James H. Hill
 */
//=============================================================================

#ifndef _CUTS_BE_XML_GENERATORS_H_
#define _CUTS_BE_XML_GENERATORS_H_

#include <fstream>
#include "../BE_Generators_T.h"
#include "../BE_algorithm.h"
#include "../String_Set.h"
#include "CCF/CodeGenerationKit/IndentationXML.hpp"
#include "CCF/CodeGenerationKit/IndentationImplanter.hpp"

/**
 * @struct CUTS_BE_Xml
 */
struct CUTS_BE_Xml
{
  /// Target TIOA output file.
  std::ofstream outfile_;

  /// Indentation implanter.
  typedef Indentation::Implanter <
    Indentation::XML, char> _formatter_type;

  /// Pointer to the formatter.
  std::auto_ptr <_formatter_type> formatter_;
};

////
//// disable the following points of generation
////
//namespace CUTS_BE
//{
//  CUTS_BE_NOT_VISIT (CUTS_BE_Xml, PICML::ProvidedRequestPort);
//  CUTS_BE_NOT_VISIT (CUTS_BE_Xml, PICML::Attribute);
//  CUTS_BE_NOT_VISIT (CUTS_BE_Xml, PICML::ReadonlyAttribute);
//  CUTS_BE_NOT_VISIT (CUTS_BE_Xml, PICML::ComponentFactory);
//  CUTS_BE_NOT_VISIT (CUTS_BE_Xml, PICML::Object);
//  CUTS_BE_NOT_VISIT (CUTS_BE_Xml, PICML::OnewayOperation);
//  CUTS_BE_NOT_VISIT (CUTS_BE_Xml, PICML::TwowayOperation);
//}

template < >
struct CUTS_BE_Parse_Precondition_T <CUTS_BE_Xml>
{
  static const bool result_type = false;
};

/**
 * @class CUTS_BE_File_Open_T
 */
template < >
class CUTS_BE_File_Open_T <CUTS_BE_Xml> :
  public CUTS_BE_Visitor_T <CUTS_BE_Xml, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE_Xml, PICML::Visitor> visitor_type;

  CUTS_BE_File_Open_T (CUTS_BE_Xml & context);

  virtual ~CUTS_BE_File_Open_T (void);

  void generate (const PICML::ComponentImplementationContainer &,
                 const PICML::MonolithicImplementation &);
};

/**
 * @class CUTS_BE_File_Close_T
 */
template < >
class CUTS_BE_File_Close_T <CUTS_BE_Xml> :
  public CUTS_BE_Visitor_T <CUTS_BE_Xml, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE_Xml, PICML::Visitor> visitor_type;

  CUTS_BE_File_Close_T (CUTS_BE_Xml & context);

  virtual ~CUTS_BE_File_Close_T (void);

  void generate (const PICML::ComponentImplementationContainer &,
                 const PICML::MonolithicImplementation &);
};

/**
 * @class CUTS_BE_Prologue_T
 */
template < >
class CUTS_BE_Prologue_T <CUTS_BE_Xml> :
  public CUTS_BE_Visitor_T <CUTS_BE_Xml, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE_Xml, PICML::Visitor> visitor_type;

  CUTS_BE_Prologue_T (CUTS_BE_Xml & context);

  virtual ~CUTS_BE_Prologue_T (void);

  void generate (const PICML::ComponentImplementationContainer &,
                 const PICML::MonolithicImplementation & );
};

/**
 *
 */
template < >
class CUTS_BE_Component_Impl_Begin_T <CUTS_BE_Xml> :
  public CUTS_BE_Visitor_T <CUTS_BE_Xml, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE_Xml, PICML::Visitor> visitor_type;

  CUTS_BE_Component_Impl_Begin_T (CUTS_BE_Xml & context);

  virtual ~CUTS_BE_Component_Impl_Begin_T (void);

  void generate (const PICML::MonolithicImplementation & mono,
                 const PICML::Component & component);
};

/**
 * @class CUTS_BE_Component_Impl_End_T
 */
template < >
class CUTS_BE_Component_Impl_End_T <CUTS_BE_Xml> :
  public CUTS_BE_Visitor_T <CUTS_BE_Xml, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE_Xml, PICML::Visitor> visitor_type;

  CUTS_BE_Component_Impl_End_T (CUTS_BE_Xml & context);

  virtual ~CUTS_BE_Component_Impl_End_T (void);

  void generate (const PICML::MonolithicImplementation & mono,
                 const PICML::Component & component);
};

/**
 * @class CUTS_BE_Variables_Begin_T
 */
template < >
class CUTS_BE_Variables_Begin_T <CUTS_BE_Xml> :
  public CUTS_BE_Visitor_T <CUTS_BE_Xml, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE_Xml, PICML::Visitor> visitor_type;

  CUTS_BE_Variables_Begin_T (CUTS_BE_Xml & context);

  virtual ~CUTS_BE_Variables_Begin_T (void);

  void generate (const PICML::Component & component);
};

/**
 * @class CUTS_BE_Variable_T
 */
template < >
class CUTS_BE_Variable_T <CUTS_BE_Xml> :
  public CUTS_BE_Visitor_T <CUTS_BE_Xml, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE_Xml, PICML::Visitor> visitor_type;

  CUTS_BE_Variable_T (CUTS_BE_Xml & context);

  virtual ~CUTS_BE_Variable_T (void);

  void generate (const PICML::Variable & variable);
};

/**
 * @class CUTS_BE_Worker_Variable_T
 */
template < >
class CUTS_BE_Worker_Variable_T <CUTS_BE_Xml> :
  public CUTS_BE_Visitor_T <CUTS_BE_Xml, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE_Xml, PICML::Visitor> visitor_type;

  CUTS_BE_Worker_Variable_T (CUTS_BE_Xml & context);

  virtual ~CUTS_BE_Worker_Variable_T (void);

  void generate (const PICML::WorkerType & type,
                 const PICML::Worker & worker);
};

/**
 * @class CUTS_BE_Variables_End_T
 */
template < >
class CUTS_BE_Variables_End_T <CUTS_BE_Xml> :
  public CUTS_BE_Visitor_T <CUTS_BE_Xml, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE_Xml, PICML::Visitor> visitor_type;

  CUTS_BE_Variables_End_T (CUTS_BE_Xml & context);

  virtual ~CUTS_BE_Variables_End_T (void);

  void generate (const PICML::Component & component);
};

/**
 * @class CUTS_BE_WorkerAction_Begin_T
 */
template < >
class CUTS_BE_WorkerAction_Begin_T <CUTS_BE_Xml> :
  public CUTS_BE_Visitor_T <CUTS_BE_Xml, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE_Xml, PICML::Visitor> visitor_type;

  CUTS_BE_WorkerAction_Begin_T (CUTS_BE_Xml & context);

  virtual ~CUTS_BE_WorkerAction_Begin_T (void);

  void generate (const PICML::Worker & worker,
                 const PICML::Action & action);
};

/**
 * @class CUTS_BE_Precondition_T
 */
template < >
class CUTS_BE_Precondition_T <CUTS_BE_Xml> :
  public CUTS_BE_Visitor_T <CUTS_BE_Xml, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE_Xml, PICML::Visitor> visitor_type;

  CUTS_BE_Precondition_T (CUTS_BE_Xml & context);

  virtual ~CUTS_BE_Precondition_T (void);

  void generate (const std::string & precondition);
};

/**
 * @class CUTS_BE_Action_Property_T
 */
template < >
class CUTS_BE_Action_Property_T <CUTS_BE_Xml> :
  public CUTS_BE_Visitor_T <CUTS_BE_Xml, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE_Xml, PICML::Visitor> visitor_type;

  CUTS_BE_Action_Property_T (CUTS_BE_Xml & context);

  virtual ~CUTS_BE_Action_Property_T (void);

  void generate (const PICML::Property & property);
};

/**
 * @class CUTS_BE_OutputAction_Begin_T
 */
template < >
class CUTS_BE_OutputAction_Begin_T <CUTS_BE_Xml> :
  public CUTS_BE_Visitor_T <CUTS_BE_Xml, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE_Xml, PICML::Visitor> visitor_type;

  CUTS_BE_OutputAction_Begin_T (CUTS_BE_Xml & context);

  virtual ~CUTS_BE_OutputAction_Begin_T (void);

  void generate (const PICML::OutputAction & action);
};

/**
 * @class CUTS_BE_OutputAction_Property_T
 */
template < >
class CUTS_BE_OutputAction_Property_T <CUTS_BE_Xml> :
  public CUTS_BE_Visitor_T <CUTS_BE_Xml, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE_Xml, PICML::Visitor> visitor_type;

  CUTS_BE_OutputAction_Property_T (CUTS_BE_Xml & context);

  virtual ~CUTS_BE_OutputAction_Property_T (void);

  void generate (const PICML::OutputAction & action,
                 const PICML::Property & property);
};

/**
 * @class CUTS_BE_OutputAction_End_T
 */
template < >
class CUTS_BE_OutputAction_End_T <CUTS_BE_Xml> :
  public CUTS_BE_Visitor_T <CUTS_BE_Xml, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE_Xml, PICML::Visitor> visitor_type;

  CUTS_BE_OutputAction_End_T (CUTS_BE_Xml & context);

  virtual ~CUTS_BE_OutputAction_End_T (void);

  void generate (const PICML::OutputAction & action);
};

/**
 * @class CUTS_BE_Action_End_T
 */
template < >
class CUTS_BE_Action_End_T <CUTS_BE_Xml> :
  public CUTS_BE_Visitor_T <CUTS_BE_Xml, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE_Xml, PICML::Visitor> visitor_type;

  CUTS_BE_Action_End_T (CUTS_BE_Xml & context);

  virtual ~CUTS_BE_Action_End_T (void);

  void generate (void);
};

/**
 * @class CUTS_BE_InEventPort_Begin_T
 */
template < >
class CUTS_BE_InEventPort_Begin_T <CUTS_BE_Xml> :
  public CUTS_BE_Visitor_T <CUTS_BE_Xml, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE_Xml, PICML::Visitor> visitor_type;

  CUTS_BE_InEventPort_Begin_T (CUTS_BE_Xml & context);

  virtual ~CUTS_BE_InEventPort_Begin_T (void);

  void generate (const PICML::InEventPort & sink,
                 const std::vector <PICML::Property> &);
};

/**
 * @class CUTS_BE_InEventPort_End_T
 */
template < >
class CUTS_BE_InEventPort_End_T <CUTS_BE_Xml> :
  public CUTS_BE_Visitor_T <CUTS_BE_Xml, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE_Xml, PICML::Visitor> visitor_type;

  CUTS_BE_InEventPort_End_T (CUTS_BE_Xml & context);

  virtual ~CUTS_BE_InEventPort_End_T (void);

  void generate (const PICML::InEventPort & sink,
                 const std::vector <PICML::Property> &);
};

/**
 * @class CUTS_BE_Environment_Begin_T
 */
template < >
class CUTS_BE_Environment_Begin_T <CUTS_BE_Xml> :
  public CUTS_BE_Visitor_T <CUTS_BE_Xml, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE_Xml, PICML::Visitor> visitor_type;

  CUTS_BE_Environment_Begin_T (CUTS_BE_Xml & context);

  virtual ~CUTS_BE_Environment_Begin_T (void);

  void generate (const PICML::Component & component);
};

/**
 * @class CUTS_BE_Environment_Method_Begin_T
 */
template < >
class CUTS_BE_Environment_Method_Begin_T <CUTS_BE_Xml> :
  public CUTS_BE_Visitor_T <CUTS_BE_Xml, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE_Xml, PICML::Visitor> visitor_type;

  CUTS_BE_Environment_Method_Begin_T (CUTS_BE_Xml & context);

  virtual ~CUTS_BE_Environment_Method_Begin_T (void);

  void generate (const PICML::MultiInputAction & action);
};

/**
 * @class CUTS_BE_Environment_Method_End_T
 */
template < >
class CUTS_BE_Environment_Method_End_T <CUTS_BE_Xml> :
  public CUTS_BE_Visitor_T <CUTS_BE_Xml, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE_Xml, PICML::Visitor> visitor_type;

  CUTS_BE_Environment_Method_End_T (CUTS_BE_Xml & context);

  virtual ~CUTS_BE_Environment_Method_End_T (void);

  void generate (const PICML::MultiInputAction & action);
};

/**
 * @class CUTS_BE_Environment_End_T
 */
template < >
class CUTS_BE_Environment_End_T <CUTS_BE_Xml> :
  public CUTS_BE_Visitor_T <CUTS_BE_Xml, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE_Xml, PICML::Visitor> visitor_type;

  CUTS_BE_Environment_End_T (CUTS_BE_Xml & context);

  virtual ~CUTS_BE_Environment_End_T (void);

  void generate (const PICML::Component & component);
};

/**
 * @class CUTS_BE_PeriodicEvent_Begin_T
 */
template < >
class CUTS_BE_PeriodicEvent_Begin_T <CUTS_BE_Xml> :
  public CUTS_BE_Visitor_T <CUTS_BE_Xml, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE_Xml, PICML::Visitor> visitor_type;

  CUTS_BE_PeriodicEvent_Begin_T (CUTS_BE_Xml & context);

  virtual ~CUTS_BE_PeriodicEvent_Begin_T (void);

  void generate (const PICML::PeriodicEvent & periodic);
};

/**
 * @class CUTS_BE_PeriodicEvent_End_T
 */
template < >
class CUTS_BE_PeriodicEvent_End_T <CUTS_BE_Xml> :
  public CUTS_BE_Visitor_T <CUTS_BE_Xml, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE_Xml, PICML::Visitor> visitor_type;

  CUTS_BE_PeriodicEvent_End_T (CUTS_BE_Xml & context);

  virtual ~CUTS_BE_PeriodicEvent_End_T (void);

  void generate (const PICML::PeriodicEvent & periodic);
};

/**
 * @class CUTS_BE_Branches_Begin_T
 */
template < >
class CUTS_BE_Branches_Begin_T <CUTS_BE_Xml> :
  public CUTS_BE_Visitor_T <CUTS_BE_Xml, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE_Xml, PICML::Visitor> visitor_type;

  CUTS_BE_Branches_Begin_T (CUTS_BE_Xml & context);

  virtual ~CUTS_BE_Branches_Begin_T (void);

  void generate (size_t branches);
};

/**
 * @class CUTS_BE_Branch_Condition_Begin_T
 */
template < >
class CUTS_BE_Branch_Condition_Begin_T <CUTS_BE_Xml> :
  public CUTS_BE_Visitor_T <CUTS_BE_Xml, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE_Xml, PICML::Visitor> visitor_type;

  CUTS_BE_Branch_Condition_Begin_T (CUTS_BE_Xml & context);

  virtual ~CUTS_BE_Branch_Condition_Begin_T (void);

  void generate (void);
};

/**
 * @class CUTS_BE_Branch_End_T
 */
template < >
class CUTS_BE_Branch_End_T <CUTS_BE_Xml> :
  public CUTS_BE_Visitor_T <CUTS_BE_Xml, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE_Xml, PICML::Visitor> visitor_type;

  CUTS_BE_Branch_End_T (CUTS_BE_Xml & context);

  virtual ~CUTS_BE_Branch_End_T (void);

  void generate (void);
};

/**
 * @class CUTS_BE_Branches_End_T
 */
template < >
class CUTS_BE_Branches_End_T <CUTS_BE_Xml> :
  public CUTS_BE_Visitor_T <CUTS_BE_Xml, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE_Xml, PICML::Visitor> visitor_type;

  CUTS_BE_Branches_End_T (CUTS_BE_Xml & context);

  virtual ~CUTS_BE_Branches_End_T (void);

  void generate (void);
};

#if defined (__CUTS_INLINE__)
#include "XML_Generators.inl"
#endif

#endif  // !defined _CUTS_BE_XML_GENERATORS_H_
