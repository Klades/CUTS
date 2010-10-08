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
#include "Java.h"

/**
 * @class CUTS_BE_Attribute_Variable_T
 */
template < >
class CUTS_BE_JAVA_Export CUTS_BE_Attribute_Variable_T <CUTS_BE_Java::Context> :
  public CUTS_BE_Visitor_T <CUTS_BE_Java::Context, PICML::Visitor>
{
public:
  typedef public CUTS_BE_Visitor_T <CUTS_BE_Java::Context, PICML::Visitor> visitor_type;

  CUTS_BE_Attribute_Variable_T (CUTS_BE_Java::Context & context);

  virtual ~CUTS_BE_Attribute_Variable_T (void);

  void generate (const PICML::ReadonlyAttribute & attr);
};

/**
 * @class CUTS_BE_Variable_T
 */
template < >
class CUTS_BE_JAVA_Export CUTS_BE_Variable_T <CUTS_BE_Java::Context> :
  public CUTS_BE_Visitor_T <CUTS_BE_Java::Context, PICML::Visitor>
{
public:
  typedef public CUTS_BE_Visitor_T <CUTS_BE_Java::Context, PICML::Visitor> visitor_type;

  CUTS_BE_Variable_T (CUTS_BE_Java::Context & context);

  virtual ~CUTS_BE_Variable_T (void);

  void generate (const PICML::Variable & variable);
};

/**
 * @class CUTS_BE_Worker_Variable_T
 */
template < >
class CUTS_BE_JAVA_Export CUTS_BE_Worker_Variable_T <CUTS_BE_Java::Context> :
  public CUTS_BE_Visitor_T <CUTS_BE_Java::Context, PICML::Visitor>
{
public:
  typedef public CUTS_BE_Visitor_T <CUTS_BE_Java::Context, PICML::Visitor> visitor_type;

  CUTS_BE_Worker_Variable_T (CUTS_BE_Java::Context & context);

  virtual ~CUTS_BE_Worker_Variable_T (void);

  void generate (const PICML::WorkerType & type, const PICML::Worker & worker);
};

/**
 * @class CUTS_BE_Precondition_T
 */
template < >
class CUTS_BE_JAVA_Export CUTS_BE_Precondition_T <CUTS_BE_Java::Context> :
  public CUTS_BE_Visitor_T <CUTS_BE_Java::Context, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE_Java::Context, PICML::Visitor> visitor_type;

  CUTS_BE_Precondition_T (CUTS_BE_Java::Context & context);

  virtual ~CUTS_BE_Precondition_T (void);

  void generate (const std::string & precondition);
};

/**
 * @class CUTS_BE_Postcondition_T
 */
template < >
class CUTS_BE_JAVA_Export CUTS_BE_Postcondition_T <CUTS_BE_Java::Context> :
  public CUTS_BE_Visitor_T <CUTS_BE_Java::Context, PICML::Visitor>
{
public:
  typedef public CUTS_BE_Visitor_T <CUTS_BE_Java::Context, PICML::Visitor> visitor_type;

  CUTS_BE_Postcondition_T (CUTS_BE_Java::Context & context);

  virtual ~CUTS_BE_Postcondition_T (void);

  void generate (const std::string & postcondition);
};

/**
 * @class CUTS_BE_Branches_Begin_T
 */
template < >
class CUTS_BE_JAVA_Export CUTS_BE_Branches_Begin_T <CUTS_BE_Java::Context> :
  public CUTS_BE_Visitor_T <CUTS_BE_Java::Context, PICML::Visitor>
{
public:
  typedef public CUTS_BE_Visitor_T <CUTS_BE_Java::Context, PICML::Visitor> visitor_type;

  CUTS_BE_Branches_Begin_T (CUTS_BE_Java::Context & context);

  virtual ~CUTS_BE_Branches_Begin_T (void);

  void generate (size_t branches);
};

/**
 * @class CUTS_BE_Branch_Begin_T
 */
template < >
class CUTS_BE_JAVA_Export CUTS_BE_Branch_Begin_T <CUTS_BE_Java::Context> :
  public CUTS_BE_Visitor_T <CUTS_BE_Java::Context, PICML::Visitor>
{
public:
  typedef public CUTS_BE_Visitor_T <CUTS_BE_Java::Context, PICML::Visitor> visitor_type;

  CUTS_BE_Branch_Begin_T (CUTS_BE_Java::Context & context);

  virtual ~CUTS_BE_Branch_Begin_T (void);

  void generate (void);
};

/**
 * @class CUTS_BE_JAVA_Export CUTS_BE_Branch_End_T
 */
template < >
class CUTS_BE_JAVA_Export CUTS_BE_Branch_End_T <CUTS_BE_Java::Context> :
  public CUTS_BE_Visitor_T <CUTS_BE_Java::Context, PICML::Visitor>
{
public:
  typedef public CUTS_BE_Visitor_T <CUTS_BE_Java::Context, PICML::Visitor> visitor_type;

  CUTS_BE_Branch_End_T (CUTS_BE_Java::Context & context);

  virtual ~CUTS_BE_Branch_End_T (void);

  void generate (void);
};

/**
 * @class CUTS_BE_Branch_Condition_Begin_T
 */
template < >
class CUTS_BE_JAVA_Export CUTS_BE_Branch_Condition_Begin_T <CUTS_BE_Java::Context> :
  public CUTS_BE_Visitor_T <CUTS_BE_Java::Context, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE_Java::Context, PICML::Visitor> visitor_type;

  CUTS_BE_Branch_Condition_Begin_T (CUTS_BE_Java::Context & context);

  virtual ~CUTS_BE_Branch_Condition_Begin_T (void);

  void generate (void);
};

/**
 * @class CUTS_BE_Branch_Condition_End_T
 */
template < >
class CUTS_BE_JAVA_Export CUTS_BE_Branch_Condition_End_T <CUTS_BE_Java::Context> :
  public CUTS_BE_Visitor_T <CUTS_BE_Java::Context, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE_Java::Context, PICML::Visitor> visitor_type;

  CUTS_BE_Branch_Condition_End_T (CUTS_BE_Java::Context & context);

  virtual ~CUTS_BE_Branch_Condition_End_T (void);

  void generate (void);
};

/**
 * @class CUTS_BE_Branch_No_Condition_T
 */
template < >
class CUTS_BE_JAVA_Export CUTS_BE_Branch_No_Condition_T <CUTS_BE_Java::Context> :
  public CUTS_BE_Visitor_T <CUTS_BE_Java::Context, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE_Java::Context, PICML::Visitor> visitor_type;

  CUTS_BE_Branch_No_Condition_T (CUTS_BE_Java::Context & context);

  virtual ~CUTS_BE_Branch_No_Condition_T (void);

  void generate (void);
};

/**
 * @class CUTS_BE_Branches_End_T
 */
template < >
class CUTS_BE_JAVA_Export CUTS_BE_Branches_End_T <CUTS_BE_Java::Context> :
  public CUTS_BE_Visitor_T <CUTS_BE_Java::Context, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE_Java::Context, PICML::Visitor> visitor_type;

  CUTS_BE_Branches_End_T (CUTS_BE_Java::Context & context);

  virtual ~CUTS_BE_Branches_End_T (void);

  void generate (void);
};

/**
 * @class CUTS_BE_Action_Property_T
 */
template < >
class CUTS_BE_JAVA_Export CUTS_BE_Action_Property_T <CUTS_BE_Java::Context> :
  public CUTS_BE_Visitor_T <CUTS_BE_Java::Context, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE_Java::Context, PICML::Visitor> visitor_type;

  CUTS_BE_Action_Property_T (CUTS_BE_Java::Context & context);

  virtual ~CUTS_BE_Action_Property_T (void);

  void generate (const PICML::Property & property);
};

/**
 * @class CUTS_BE_WorkerAction_Begin_T
 */
template < >
class CUTS_BE_JAVA_Export CUTS_BE_WorkerAction_Begin_T <CUTS_BE_Java::Context> :
  public CUTS_BE_Visitor_T <CUTS_BE_Java::Context, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE_Java::Context, PICML::Visitor> visitor_type;

  CUTS_BE_WorkerAction_Begin_T (CUTS_BE_Java::Context & context);

  virtual ~CUTS_BE_WorkerAction_Begin_T (void);

  void generate (const PICML::Action & action);
};

/**
 * @class CUTS_BE_RequestAction_Begin_T
 */
template < >
class CUTS_BE_JAVA_Export CUTS_BE_RequestAction_Begin_T <CUTS_BE_Java::Context> :
  public CUTS_BE_Visitor_T <CUTS_BE_Java::Context, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE_Java::Context, PICML::Visitor> visitor_type;

  CUTS_BE_RequestAction_Begin_T (CUTS_BE_Java::Context & context);

  void generate (const PICML::RequestAction & action);
};

/**
 * @class CUTS_BE_RequestAction_End_T
 */
template < >
class CUTS_BE_JAVA_Export CUTS_BE_RequestAction_End_T <CUTS_BE_Java::Context> :
  public CUTS_BE_Visitor_T <CUTS_BE_Java::Context, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE_Java::Context, PICML::Visitor> visitor_type;

  CUTS_BE_RequestAction_End_T (CUTS_BE_Java::Context & context);

  void generate (const PICML::RequestAction & action);
};

/**
 * @class CUTS_BE_OutputAction_Begin_T
 */
template < >
class CUTS_BE_JAVA_Export CUTS_BE_OutputAction_Begin_T <CUTS_BE_Java::Context> :
  public CUTS_BE_Visitor_T <CUTS_BE_Java::Context, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE_Java::Context, PICML::Visitor> visitor_type;

  CUTS_BE_OutputAction_Begin_T (CUTS_BE_Java::Context & context);

  virtual ~CUTS_BE_OutputAction_Begin_T (void);

  void generate (const PICML::OutputAction & action);
};

/**
 * @class CUTS_BE_OutputAction_Property_T
 */
template < >
class CUTS_BE_JAVA_Export CUTS_BE_OutputAction_Property_T <CUTS_BE_Java::Context> :
  public CUTS_BE_Visitor_T <CUTS_BE_Java::Context, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE_Java::Context, PICML::Visitor> visitor_type;

  CUTS_BE_OutputAction_Property_T (CUTS_BE_Java::Context & context);

  virtual ~CUTS_BE_OutputAction_Property_T (void);

  void generate (const PICML::OutputAction & action,
                 const PICML::Property & property);
};

/**
 * @class CUTS_BE_OutputAction_End_T
 */
template < >
class CUTS_BE_JAVA_Export CUTS_BE_OutputAction_End_T <CUTS_BE_Java::Context> :
  public CUTS_BE_Visitor_T <CUTS_BE_Java::Context, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE_Java::Context, PICML::Visitor> visitor_type;

  CUTS_BE_OutputAction_End_T (CUTS_BE_Java::Context & context);

  virtual ~CUTS_BE_OutputAction_End_T (void);

  void generate (const PICML::OutputAction & action);
};

/**
 *
 */
template < >
class CUTS_BE_JAVA_Export CUTS_BE_Action_Properties_Begin_T <CUTS_BE_Java::Context> :
  public CUTS_BE_Visitor_T <CUTS_BE_Java::Context, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE_Java::Context, PICML::Visitor> visitor_type;

  CUTS_BE_Action_Properties_Begin_T (CUTS_BE_Java::Context & context);

  virtual ~CUTS_BE_Action_Properties_Begin_T (void);

  void generate (size_t count);
};


/**
 * @class CUTS_BE_Action_End_T
 */
template < >
class CUTS_BE_JAVA_Export CUTS_BE_Action_End_T <CUTS_BE_Java::Context> :
  public CUTS_BE_Visitor_T <CUTS_BE_Java::Context, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE_Java::Context, PICML::Visitor> visitor_type;

  CUTS_BE_Action_End_T (CUTS_BE_Java::Context & context);

  virtual ~CUTS_BE_Action_End_T (void);

  void generate (void);
};

/**
 * @class CUTS_BE_Do_While_Begin_T
 */
template < >
class CUTS_BE_JAVA_Export CUTS_BE_Do_While_Begin_T <CUTS_BE_Java::Context> :
  public CUTS_BE_Visitor_T <CUTS_BE_Java::Context, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE_Java::Context, PICML::Visitor> visitor_type;

  CUTS_BE_Do_While_Begin_T (CUTS_BE_Java::Context & context);

  virtual ~CUTS_BE_Do_While_Begin_T (void);

  void generate (void);
};

/**
 * @class CUTS_BE_Do_While_Condition_Begin_T
 */
template < >
class CUTS_BE_JAVA_Export CUTS_BE_Do_While_Condition_Begin_T <CUTS_BE_Java::Context> :
  public CUTS_BE_Visitor_T <CUTS_BE_Java::Context, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE_Java::Context, PICML::Visitor> visitor_type;

  CUTS_BE_Do_While_Condition_Begin_T (CUTS_BE_Java::Context & context);

  virtual ~CUTS_BE_Do_While_Condition_Begin_T (void);

  void generate (void);
};

/**
 * @class CUTS_BE_Do_While_Condition_End_T
 */
template < >
class CUTS_BE_JAVA_Export CUTS_BE_Do_While_Condition_End_T <CUTS_BE_Java::Context> :
  public CUTS_BE_Visitor_T <CUTS_BE_Java::Context, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE_Java::Context, PICML::Visitor> visitor_type;

  CUTS_BE_Do_While_Condition_End_T (CUTS_BE_Java::Context & context);

  virtual ~CUTS_BE_Do_While_Condition_End_T (void);

  void generate (void);
};

/**
 * @class CUTS_BE_Do_While_End_T
 */
template < >
class CUTS_BE_JAVA_Export CUTS_BE_Do_While_End_T <CUTS_BE_Java::Context> :
  public CUTS_BE_Visitor_T <CUTS_BE_Java::Context, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE_Java::Context, PICML::Visitor> visitor_type;

  CUTS_BE_Do_While_End_T (CUTS_BE_Java::Context & context);

  virtual ~CUTS_BE_Do_While_End_T (void);

  void generate (void);
};

/**
 * @class CUTS_BE_While_Begin_T
 */
template < >
class CUTS_BE_JAVA_Export CUTS_BE_While_Begin_T <CUTS_BE_Java::Context> :
  public CUTS_BE_Visitor_T <CUTS_BE_Java::Context, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE_Java::Context, PICML::Visitor> visitor_type;

  CUTS_BE_While_Begin_T (CUTS_BE_Java::Context & context);

  virtual ~CUTS_BE_While_Begin_T (void);

  void generate (void);
};

/**
 * @class CUTS_BE_While_Condition_Begin_T
 */
template < >
class CUTS_BE_JAVA_Export CUTS_BE_While_Condition_Begin_T <CUTS_BE_Java::Context> :
  public CUTS_BE_Visitor_T <CUTS_BE_Java::Context, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE_Java::Context, PICML::Visitor> visitor_type;

  CUTS_BE_While_Condition_Begin_T (CUTS_BE_Java::Context & context);

  virtual ~CUTS_BE_While_Condition_Begin_T (void);

  void generate (void);
};

/**
 * @class CUTS_BE_While_Condition_End_T
 */
template < >
class CUTS_BE_JAVA_Export CUTS_BE_While_Condition_End_T <CUTS_BE_Java::Context> :
  public CUTS_BE_Visitor_T <CUTS_BE_Java::Context, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE_Java::Context, PICML::Visitor> visitor_type;

  CUTS_BE_While_Condition_End_T (CUTS_BE_Java::Context & context);

  virtual ~CUTS_BE_While_Condition_End_T (void);

  void generate (void);
};

/**
 * @class CUTS_BE_While_End_T
 */
template < >
class CUTS_BE_JAVA_Export CUTS_BE_While_End_T <CUTS_BE_Java::Context> :
  public CUTS_BE_Visitor_T <CUTS_BE_Java::Context, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE_Java::Context, PICML::Visitor> visitor_type;

  CUTS_BE_While_End_T (CUTS_BE_Java::Context & context);

  virtual ~CUTS_BE_While_End_T (void);

  void generate (void);
};

#if defined (__CUTS_INLINE__)
#include "Java_Behavior_Generator.inl"
#endif

#endif  // !defined _CUTS_BE_CPP_BEHAVIOR_GENERATOR_H_
