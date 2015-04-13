// -*- C++ -*-

//=============================================================================
/**
 * @file        Behavior_Generator.h
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _CUTS_BE_CPP_BEHAVIOR_GENERATOR_H_
#define _CUTS_BE_CPP_BEHAVIOR_GENERATOR_H_

#include "../../BE_Generators_T.h"
#include "Cpp.h"

/**
 * @class CUTS_BE_Variables_Begin_T
 */
template < >
class CUTS_BE_CPP_Export CUTS_BE_Variables_Begin_T <CUTS_BE_CPP::Context> :
  public CUTS_BE_Visitor_T <CUTS_BE_CPP::Context, PICML::Visitor>
{
public:
  typedef public CUTS_BE_Visitor_T <CUTS_BE_CPP::Context, PICML::Visitor> visitor_type;

  CUTS_BE_Variables_Begin_T (CUTS_BE_CPP::Context & context);

  virtual ~CUTS_BE_Variables_Begin_T (void);

  void generate (const PICML::Component_in component);
};

/**
 * @class CUTS_BE_Attribute_Variable_T
 */
template < >
class CUTS_BE_CPP_Export CUTS_BE_Attribute_Variable_T <CUTS_BE_CPP::Context> :
  public CUTS_BE_Visitor_T <CUTS_BE_CPP::Context, PICML::Visitor>
{
public:
  typedef public CUTS_BE_Visitor_T <CUTS_BE_CPP::Context, PICML::Visitor> visitor_type;

  CUTS_BE_Attribute_Variable_T (CUTS_BE_CPP::Context & context);

  virtual ~CUTS_BE_Attribute_Variable_T (void);

  void generate (const PICML::ReadonlyAttribute_in attr);
};

/**
 * @class CUTS_BE_Variable_T
 */
template < >
class CUTS_BE_CPP_Export CUTS_BE_Variable_T <CUTS_BE_CPP::Context> :
  public CUTS_BE_Visitor_T <CUTS_BE_CPP::Context, PICML::Visitor>
{
public:
  typedef public CUTS_BE_Visitor_T <CUTS_BE_CPP::Context, PICML::Visitor> visitor_type;

  CUTS_BE_Variable_T (CUTS_BE_CPP::Context & context);

  virtual ~CUTS_BE_Variable_T (void);

  void generate (const PICML::Variable_in variable);
};

/**
 * @class CUTS_BE_Worker_Variable_T
 */
template < >
class CUTS_BE_CPP_Export CUTS_BE_Worker_Variable_T <CUTS_BE_CPP::Context> :
  public CUTS_BE_Visitor_T <CUTS_BE_CPP::Context, PICML::Visitor>
{
public:
  typedef public CUTS_BE_Visitor_T <CUTS_BE_CPP::Context, PICML::Visitor> visitor_type;

  CUTS_BE_Worker_Variable_T (CUTS_BE_CPP::Context & context);

  virtual ~CUTS_BE_Worker_Variable_T (void);

  void generate (const PICML::WorkerType_in type, const PICML::Worker_in worker);
};

/**
 * @class CUTS_BE_PeriodicEvent_Variable_T
 */
template < >
class CUTS_BE_CPP_Export CUTS_BE_PeriodicEvent_Variable_T <CUTS_BE_CPP::Context> :
  public CUTS_BE_Visitor_T <CUTS_BE_CPP::Context, PICML::Visitor>
{
public:
  typedef public CUTS_BE_Visitor_T <CUTS_BE_CPP::Context, PICML::Visitor> visitor_type;

  CUTS_BE_PeriodicEvent_Variable_T (CUTS_BE_CPP::Context & context);

  virtual ~CUTS_BE_PeriodicEvent_Variable_T (void);

  void generate (const PICML::PeriodicEvent_in periodic);
};

/**
 * @class CUTS_BE_Precondition_T
 */
template < >
class CUTS_BE_CPP_Export CUTS_BE_Precondition_T <CUTS_BE_CPP::Context> :
  public CUTS_BE_Visitor_T <CUTS_BE_CPP::Context, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE_CPP::Context, PICML::Visitor> visitor_type;

  CUTS_BE_Precondition_T (CUTS_BE_CPP::Context & context);

  virtual ~CUTS_BE_Precondition_T (void);

  void generate (const std::string & precondition);
};

/**
 * @class CUTS_BE_Postcondition_T
 */
template < >
class CUTS_BE_CPP_Export CUTS_BE_Postcondition_T <CUTS_BE_CPP::Context> :
  public CUTS_BE_Visitor_T <CUTS_BE_CPP::Context, PICML::Visitor>
{
public:
  CUTS_BE_Postcondition_T (CUTS_BE_CPP::Context & context);

  virtual ~CUTS_BE_Postcondition_T (void);

  typedef public CUTS_BE_Visitor_T <CUTS_BE_CPP::Context, PICML::Visitor> visitor_type;

  void generate (const std::string & postcondition);
};

/**
 * @class CUTS_BE_Branches_Begin_T
 */
template < >
class CUTS_BE_CPP_Export CUTS_BE_Branches_Begin_T <CUTS_BE_CPP::Context> :
  public CUTS_BE_Visitor_T <CUTS_BE_CPP::Context, PICML::Visitor>
{
public:
  typedef public CUTS_BE_Visitor_T <CUTS_BE_CPP::Context, PICML::Visitor> visitor_type;

  CUTS_BE_Branches_Begin_T (CUTS_BE_CPP::Context & context);

  virtual ~CUTS_BE_Branches_Begin_T (void);

  void generate (size_t branches);
};

/**
 * @class CUTS_BE_Branch_Begin_T
 */
template < >
class CUTS_BE_CPP_Export CUTS_BE_Branch_Begin_T <CUTS_BE_CPP::Context> :
  public CUTS_BE_Visitor_T <CUTS_BE_CPP::Context, PICML::Visitor>
{
public:
  typedef public CUTS_BE_Visitor_T <CUTS_BE_CPP::Context, PICML::Visitor> visitor_type;

  CUTS_BE_Branch_Begin_T (CUTS_BE_CPP::Context & context);

  virtual ~CUTS_BE_Branch_Begin_T (void);

  void generate (void);
};

/**
 * @class CUTS_BE_CPP_Export CUTS_BE_Branch_End_T
 */
template < >
class CUTS_BE_CPP_Export CUTS_BE_Branch_End_T <CUTS_BE_CPP::Context> :
  public CUTS_BE_Visitor_T <CUTS_BE_CPP::Context, PICML::Visitor>
{
public:
  typedef public CUTS_BE_Visitor_T <CUTS_BE_CPP::Context, PICML::Visitor> visitor_type;

  CUTS_BE_Branch_End_T (CUTS_BE_CPP::Context & context);

  virtual ~CUTS_BE_Branch_End_T (void);

  void generate (void);
};

/**
 * @class CUTS_BE_Branch_Condition_Begin_T
 */
template < >
class CUTS_BE_CPP_Export CUTS_BE_Branch_Condition_Begin_T <CUTS_BE_CPP::Context> :
  public CUTS_BE_Visitor_T <CUTS_BE_CPP::Context, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE_CPP::Context, PICML::Visitor> visitor_type;

  CUTS_BE_Branch_Condition_Begin_T (CUTS_BE_CPP::Context & context);

  virtual ~CUTS_BE_Branch_Condition_Begin_T (void);

  void generate (void);
};

/**
 * @class CUTS_BE_Branch_Condition_End_T
 */
template < >
class CUTS_BE_CPP_Export CUTS_BE_Branch_Condition_End_T <CUTS_BE_CPP::Context> :
  public CUTS_BE_Visitor_T <CUTS_BE_CPP::Context, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE_CPP::Context, PICML::Visitor> visitor_type;

  CUTS_BE_Branch_Condition_End_T (CUTS_BE_CPP::Context & context);

  virtual ~CUTS_BE_Branch_Condition_End_T (void);

  void generate (void);
};

/**
 * @class CUTS_BE_Branch_No_Condition_T
 */
template < >
class CUTS_BE_CPP_Export CUTS_BE_Branch_No_Condition_T <CUTS_BE_CPP::Context> :
  public CUTS_BE_Visitor_T <CUTS_BE_CPP::Context, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE_CPP::Context, PICML::Visitor> visitor_type;

  CUTS_BE_Branch_No_Condition_T (CUTS_BE_CPP::Context & context);

  virtual ~CUTS_BE_Branch_No_Condition_T (void);

  void generate (void);
};

/**
 * @class CUTS_BE_Branches_End_T
 */
template < >
class CUTS_BE_CPP_Export CUTS_BE_Branches_End_T <CUTS_BE_CPP::Context> :
  public CUTS_BE_Visitor_T <CUTS_BE_CPP::Context, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE_CPP::Context, PICML::Visitor> visitor_type;

  CUTS_BE_Branches_End_T (CUTS_BE_CPP::Context & context);

  virtual ~CUTS_BE_Branches_End_T (void);

  void generate (void);
};

/**
 * @class CUTS_BE_Action_Property_T
 */
template < >
class CUTS_BE_CPP_Export CUTS_BE_Action_Property_T <CUTS_BE_CPP::Context> :
  public CUTS_BE_Visitor_T <CUTS_BE_CPP::Context, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE_CPP::Context, PICML::Visitor> visitor_type;

  CUTS_BE_Action_Property_T (CUTS_BE_CPP::Context & context);

  virtual ~CUTS_BE_Action_Property_T (void);

  void generate (const PICML::Property_in property);
};

/**
 * @class CUTS_BE_WorkerAction_Begin_T
 */
template < >
class CUTS_BE_CPP_Export CUTS_BE_WorkerAction_Begin_T <CUTS_BE_CPP::Context> :
  public CUTS_BE_Visitor_T <CUTS_BE_CPP::Context, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE_CPP::Context, PICML::Visitor> visitor_type;

  CUTS_BE_WorkerAction_Begin_T (CUTS_BE_CPP::Context & context);

  virtual ~CUTS_BE_WorkerAction_Begin_T (void);

  void generate (const PICML::Action_in action);
};

/**
 * @class CUTS_BE_OutputAction_Begin_T
 */
template < >
class CUTS_BE_CPP_Export CUTS_BE_OutputAction_Begin_T <CUTS_BE_CPP::Context> :
  public CUTS_BE_Visitor_T <CUTS_BE_CPP::Context, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE_CPP::Context, PICML::Visitor> visitor_type;

  CUTS_BE_OutputAction_Begin_T (CUTS_BE_CPP::Context & context);

  virtual ~CUTS_BE_OutputAction_Begin_T (void);

  void generate (const PICML::OutputAction_in action);
};

/**
 * @class CUTS_BE_OutputAction_Property_T
 */
template < >
class CUTS_BE_CPP_Export CUTS_BE_OutputAction_Property_T <CUTS_BE_CPP::Context> :
  public CUTS_BE_Visitor_T <CUTS_BE_CPP::Context, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE_CPP::Context, PICML::Visitor> visitor_type;

  CUTS_BE_OutputAction_Property_T (CUTS_BE_CPP::Context & context);

  virtual ~CUTS_BE_OutputAction_Property_T (void);

  void generate (const PICML::OutputAction_in action,
                 const PICML::Property_in property);
};

/**
 * @class CUTS_BE_OutputAction_End_T
 */
template < >
class CUTS_BE_CPP_Export CUTS_BE_OutputAction_End_T <CUTS_BE_CPP::Context> :
  public CUTS_BE_Visitor_T <CUTS_BE_CPP::Context, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE_CPP::Context, PICML::Visitor> visitor_type;

  CUTS_BE_OutputAction_End_T (CUTS_BE_CPP::Context & context);

  virtual ~CUTS_BE_OutputAction_End_T (void);

  void generate (const PICML::OutputAction_in action);
};

/**
 * @class CUTS_BE_Action_End_T
 */
template < >
class CUTS_BE_CPP_Export CUTS_BE_Action_End_T <CUTS_BE_CPP::Context> :
  public CUTS_BE_Visitor_T <CUTS_BE_CPP::Context, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE_CPP::Context, PICML::Visitor> visitor_type;

  CUTS_BE_Action_End_T (CUTS_BE_CPP::Context & context);

  virtual ~CUTS_BE_Action_End_T (void);

  void generate (void);
};

/**
 * @class CUTS_BE_Action_Properties_Begin_T
 */
template < >
class CUTS_BE_CPP_Export CUTS_BE_Action_Properties_Begin_T <CUTS_BE_CPP::Context> :
  public CUTS_BE_Visitor_T <CUTS_BE_CPP::Context, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE_CPP::Context, PICML::Visitor> visitor_type;

  CUTS_BE_Action_Properties_Begin_T (CUTS_BE_CPP::Context & context);

  virtual ~CUTS_BE_Action_Properties_Begin_T (void);

  void generate (size_t count);
};

/**
 * @class CUTS_BE_Do_While_Begin_T
 */
template < >
class CUTS_BE_CPP_Export CUTS_BE_Do_While_Begin_T <CUTS_BE_CPP::Context> :
  public CUTS_BE_Visitor_T <CUTS_BE_CPP::Context, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE_CPP::Context, PICML::Visitor> visitor_type;

  CUTS_BE_Do_While_Begin_T (CUTS_BE_CPP::Context & context);

  virtual ~CUTS_BE_Do_While_Begin_T (void);

  void generate (void);
};

/**
 * @class CUTS_BE_Do_While_Condition_Begin_T
 */
template < >
class CUTS_BE_CPP_Export CUTS_BE_Do_While_Condition_Begin_T <CUTS_BE_CPP::Context> :
  public CUTS_BE_Visitor_T <CUTS_BE_CPP::Context, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE_CPP::Context, PICML::Visitor> visitor_type;

  CUTS_BE_Do_While_Condition_Begin_T (CUTS_BE_CPP::Context & context);

  virtual ~CUTS_BE_Do_While_Condition_Begin_T (void);

  void generate (void);
};

/**
 * @class CUTS_BE_Do_While_Condition_End_T
 */
template < >
class CUTS_BE_CPP_Export CUTS_BE_Do_While_Condition_End_T <CUTS_BE_CPP::Context> :
  public CUTS_BE_Visitor_T <CUTS_BE_CPP::Context, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE_CPP::Context, PICML::Visitor> visitor_type;

  CUTS_BE_Do_While_Condition_End_T (CUTS_BE_CPP::Context & context);

  virtual ~CUTS_BE_Do_While_Condition_End_T (void);

  void generate (void);
};

/**
 * @class CUTS_BE_Do_While_End_T
 */
template < >
class CUTS_BE_CPP_Export CUTS_BE_Do_While_End_T <CUTS_BE_CPP::Context> :
  public CUTS_BE_Visitor_T <CUTS_BE_CPP::Context, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE_CPP::Context, PICML::Visitor> visitor_type;

  CUTS_BE_Do_While_End_T (CUTS_BE_CPP::Context & context);

  virtual ~CUTS_BE_Do_While_End_T (void);

  void generate (void);
};

/**
 * @class CUTS_BE_While_Begin_T
 */
template < >
class CUTS_BE_CPP_Export CUTS_BE_While_Begin_T <CUTS_BE_CPP::Context> :
  public CUTS_BE_Visitor_T <CUTS_BE_CPP::Context, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE_CPP::Context, PICML::Visitor> visitor_type;

  CUTS_BE_While_Begin_T (CUTS_BE_CPP::Context & context);

  virtual ~CUTS_BE_While_Begin_T (void);

  void generate (void);
};

/**
 * @class CUTS_BE_While_Condition_Begin_T
 */
template < >
class CUTS_BE_CPP_Export CUTS_BE_While_Condition_Begin_T <CUTS_BE_CPP::Context> :
  public CUTS_BE_Visitor_T <CUTS_BE_CPP::Context, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE_CPP::Context, PICML::Visitor> visitor_type;

  CUTS_BE_While_Condition_Begin_T (CUTS_BE_CPP::Context & context);

  virtual ~CUTS_BE_While_Condition_Begin_T (void);

  void generate (void);
};

/**
 * @class CUTS_BE_While_Condition_End_T
 */
template < >
class CUTS_BE_CPP_Export CUTS_BE_While_Condition_End_T <CUTS_BE_CPP::Context> :
  public CUTS_BE_Visitor_T <CUTS_BE_CPP::Context, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE_CPP::Context, PICML::Visitor> visitor_type;

  CUTS_BE_While_Condition_End_T (CUTS_BE_CPP::Context & context);

  virtual ~CUTS_BE_While_Condition_End_T (void);

  void generate (void);
};

/**
 * @class CUTS_BE_While_End_T
 */
template < >
class CUTS_BE_CPP_Export CUTS_BE_While_End_T <CUTS_BE_CPP::Context> :
  public CUTS_BE_Visitor_T <CUTS_BE_CPP::Context, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE_CPP::Context, PICML::Visitor> visitor_type;

  CUTS_BE_While_End_T (CUTS_BE_CPP::Context & context);

  virtual ~CUTS_BE_While_End_T (void);

  void generate (void);
};

/**
 * @class CUTS_BE_For_Begin_T
 */
template < >
class CUTS_BE_CPP_Export CUTS_BE_For_Begin_T <CUTS_BE_CPP::Context> :
  public CUTS_BE_Visitor_T <CUTS_BE_CPP::Context, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE_CPP::Context, PICML::Visitor> visitor_type;

  CUTS_BE_For_Begin_T (CUTS_BE_CPP::Context & context);

  virtual ~CUTS_BE_For_Begin_T (void);

  void generate (void);
};

/**
 * @class CUTS_BE_For_Condition_Begin_T
 */
template < >
class CUTS_BE_CPP_Export CUTS_BE_For_Condition_Begin_T <CUTS_BE_CPP::Context> :
  public CUTS_BE_Visitor_T <CUTS_BE_CPP::Context, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE_CPP::Context, PICML::Visitor> visitor_type;

  CUTS_BE_For_Condition_Begin_T (CUTS_BE_CPP::Context & context);

  virtual ~CUTS_BE_For_Condition_Begin_T (void);

  void generate (void);
};

/**
 * @class CUTS_BE_For_Condition_Delimiter_T
 */
template < >
class CUTS_BE_CPP_Export CUTS_BE_For_Condition_Delimiter_T <CUTS_BE_CPP::Context> :
  public CUTS_BE_Visitor_T <CUTS_BE_CPP::Context, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE_CPP::Context, PICML::Visitor> visitor_type;

  CUTS_BE_For_Condition_Delimiter_T (CUTS_BE_CPP::Context & context);

  virtual ~CUTS_BE_For_Condition_Delimiter_T (void);

  void generate (void);
};

/**
 * @class CUTS_BE_For_Condition_End_T
 */
template < >
class CUTS_BE_CPP_Export CUTS_BE_For_Condition_End_T <CUTS_BE_CPP::Context> :
  public CUTS_BE_Visitor_T <CUTS_BE_CPP::Context, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE_CPP::Context, PICML::Visitor> visitor_type;

  CUTS_BE_For_Condition_End_T (CUTS_BE_CPP::Context & context);

  virtual ~CUTS_BE_For_Condition_End_T (void);

  void generate (void);
};

/**
 * @class CUTS_BE_For_End_T
 */
template < >
class CUTS_BE_CPP_Export CUTS_BE_For_End_T <CUTS_BE_CPP::Context> :
  public CUTS_BE_Visitor_T <CUTS_BE_CPP::Context, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE_CPP::Context, PICML::Visitor> visitor_type;

  CUTS_BE_For_End_T (CUTS_BE_CPP::Context & context);

  virtual ~CUTS_BE_For_End_T (void);

  void generate (void);
};


#if defined (__CUTS_INLINE__)
#include "Behavior_Generator.inl"
#endif

#endif  // !defined _CUTS_BE_CPP_BEHAVIOR_GENERATOR_H_
