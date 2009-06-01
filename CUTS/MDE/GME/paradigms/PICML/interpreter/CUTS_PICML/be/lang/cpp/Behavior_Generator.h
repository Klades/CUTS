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

  void generate (const PICML::Component & component);
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

  void generate (const PICML::ReadonlyAttribute & attr);
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

  void generate (const PICML::Variable & variable);
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

  void generate (const PICML::WorkerType & type, const PICML::Worker & worker);
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

  void generate (const PICML::PeriodicEvent & periodic);
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

  void generate (const PICML::Property & property);
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

  void generate (const PICML::Worker & worker,
                 const PICML::Action & action);
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

  void generate (const PICML::OutputAction & action);
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

  void generate (const PICML::OutputAction & action,
                 const PICML::Property & property);
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

  void generate (const PICML::OutputAction & action);
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

#if defined (__CUTS_INLINE__)
#include "Behavior_Generator.inl"
#endif

#endif  // !defined _CUTS_BE_CPP_BEHAVIOR_GENERATOR_H_
