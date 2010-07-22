// -*- C++ -*-

//=============================================================================
/**
 * @file          Pojo_Codegen_Generators.h
 *
 * $Id$
 *
 * @author        James H. Hill
 */
//=============================================================================

#ifndef _QUOTAS_POJO_CODEGEN_GENERATORS_H_
#define _QUOTAS_POJO_CODEGEN_GENERATORS_H_

#include "be/lang/java/Java_Behavior_Generator.h"
#include "Pojo_Codegen_Ctx.h"

/**
 * @class CUTS_BE_Parse_Precondition_T
 *
 * Parse the conditional expressions.
 */
template < >
class CUTS_BE_Parse_Precondition_T <Quotas::Pojo::Codegen::Context>
{
private:
  static const bool result_type = false;
};

/**
 *
 */
template < >
class CUTS_BE_Finalize_T <Quotas::Pojo::Codegen::Context> :
  public CUTS_BE_Visitor_T <Quotas::Pojo::Codegen::Context, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <Quotas::Pojo::Codegen::Context, PICML::Visitor> visitor_type;

  CUTS_BE_Finalize_T (Quotas::Pojo::Codegen::Context & context);

  virtual ~CUTS_BE_Finalize_T (void);

  void generate (const PICML::RootFolder &);
};

/**
 *
 */
template < >
class CUTS_BE_File_Open_T <Quotas::Pojo::Codegen::Context> :
  public CUTS_BE_Visitor_T <Quotas::Pojo::Codegen::Context, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <Quotas::Pojo::Codegen::Context, PICML::Visitor> visitor_type;

  CUTS_BE_File_Open_T (Quotas::Pojo::Codegen::Context & context);

  virtual ~CUTS_BE_File_Open_T (void);

  void generate (const PICML::ComponentImplementationContainer &,
                 const PICML::MonolithicImplementation &);
};

/**
 *
 */
template < >
class CUTS_BE_File_Close_T <Quotas::Pojo::Codegen::Context> :
  public CUTS_BE_Visitor_T <Quotas::Pojo::Codegen::Context, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <Quotas::Pojo::Codegen::Context, PICML::Visitor> visitor_type;

  CUTS_BE_File_Close_T (Quotas::Pojo::Codegen::Context & context);

  virtual ~CUTS_BE_File_Close_T (void);

  void generate (const PICML::ComponentImplementationContainer &,
                 const PICML::MonolithicImplementation &);
};

/**
 *
 */
template < >
class CUTS_BE_Prologue_T <Quotas::Pojo::Codegen::Context> :
  public CUTS_BE_Visitor_T <Quotas::Pojo::Codegen::Context, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <Quotas::Pojo::Codegen::Context, PICML::Visitor> visitor_type;

  CUTS_BE_Prologue_T (Quotas::Pojo::Codegen::Context & context);

  virtual ~CUTS_BE_Prologue_T (void);

  void generate (const PICML::ComponentImplementationContainer &,
                 const PICML::MonolithicImplementation & );
};

/**
 *
 */
template < >
class CUTS_BE_Component_Impl_Begin_T <Quotas::Pojo::Codegen::Context> :
  public CUTS_BE_Visitor_T <Quotas::Pojo::Codegen::Context, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <Quotas::Pojo::Codegen::Context, PICML::Visitor> visitor_type;

  CUTS_BE_Component_Impl_Begin_T (Quotas::Pojo::Codegen::Context & context);

  virtual ~CUTS_BE_Component_Impl_Begin_T (void);

  void generate (const PICML::MonolithicImplementation & mono,
                 const PICML::Component & component);

private:
  void generate_worker_import (const PICML::Worker & );
};

/**
 *
 */
template < >
class CUTS_BE_Component_Impl_End_T <Quotas::Pojo::Codegen::Context> :
  public CUTS_BE_Visitor_T <Quotas::Pojo::Codegen::Context, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <Quotas::Pojo::Codegen::Context, PICML::Visitor> visitor_type;

  CUTS_BE_Component_Impl_End_T (Quotas::Pojo::Codegen::Context & context);

  virtual ~CUTS_BE_Component_Impl_End_T (void);

  void generate (const PICML::MonolithicImplementation & mono,
                 const PICML::Component & component);
};

/**
 *
 */
template < >
class CUTS_BE_Environment_Method_Begin_T <Quotas::Pojo::Codegen::Context> :
  public CUTS_BE_Visitor_T <Quotas::Pojo::Codegen::Context, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <Quotas::Pojo::Codegen::Context, PICML::Visitor> visitor_type;

  CUTS_BE_Environment_Method_Begin_T (Quotas::Pojo::Codegen::Context & context);

  virtual ~CUTS_BE_Environment_Method_Begin_T (void);

  void generate (const PICML::MultiInputAction & action);
};

/**
 *
 */
template < >
class CUTS_BE_Environment_Method_End_T <Quotas::Pojo::Codegen::Context> :
  public CUTS_BE_Visitor_T <Quotas::Pojo::Codegen::Context, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <Quotas::Pojo::Codegen::Context, PICML::Visitor> visitor_type;

  CUTS_BE_Environment_Method_End_T (Quotas::Pojo::Codegen::Context & context);

  virtual ~CUTS_BE_Environment_Method_End_T (void);

  void generate (const PICML::MultiInputAction & action);
};

/**
 *
 */
template < >
class CUTS_BE_Environment_End_T <Quotas::Pojo::Codegen::Context> :
  public CUTS_BE_Visitor_T <Quotas::Pojo::Codegen::Context, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <Quotas::Pojo::Codegen::Context, PICML::Visitor> visitor_type;

  CUTS_BE_Environment_End_T (Quotas::Pojo::Codegen::Context & context);

  virtual ~CUTS_BE_Environment_End_T (void);

  void generate (const PICML::Component & component);
};

/**
 *
 */
template < >
class CUTS_BE_PeriodicEvent_Begin_T <Quotas::Pojo::Codegen::Context> :
  public CUTS_BE_Visitor_T <Quotas::Pojo::Codegen::Context, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <Quotas::Pojo::Codegen::Context, PICML::Visitor> visitor_type;

  CUTS_BE_PeriodicEvent_Begin_T (Quotas::Pojo::Codegen::Context & context);

  virtual ~CUTS_BE_PeriodicEvent_Begin_T (void);

  void generate (const PICML::PeriodicEvent & periodic);
};

/**
 *
 */
template < >
class CUTS_BE_PeriodicEvent_End_T <Quotas::Pojo::Codegen::Context> :
  public CUTS_BE_Visitor_T <Quotas::Pojo::Codegen::Context, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <Quotas::Pojo::Codegen::Context, PICML::Visitor> visitor_type;

  CUTS_BE_PeriodicEvent_End_T (Quotas::Pojo::Codegen::Context & context);

  virtual ~CUTS_BE_PeriodicEvent_End_T (void);

  void generate (const PICML::PeriodicEvent & periodic);
};

/**
 *
 */
template < >
class CUTS_BE_ReadonlyAttribute_Begin_T <Quotas::Pojo::Codegen::Context> :
  public CUTS_BE_Visitor_T <Quotas::Pojo::Codegen::Context, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <Quotas::Pojo::Codegen::Context, PICML::Visitor> visitor_type;

  CUTS_BE_ReadonlyAttribute_Begin_T (Quotas::Pojo::Codegen::Context & context);

  virtual ~CUTS_BE_ReadonlyAttribute_Begin_T (void);

  void generate (const PICML::ReadonlyAttribute & readonly);
};

/**
 *
 */
template < >
class CUTS_BE_ReadonlyAttribute_End_T <Quotas::Pojo::Codegen::Context> :
  public CUTS_BE_Visitor_T <Quotas::Pojo::Codegen::Context, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <Quotas::Pojo::Codegen::Context, PICML::Visitor> visitor_type;

  CUTS_BE_ReadonlyAttribute_End_T (Quotas::Pojo::Codegen::Context & context);

  virtual ~CUTS_BE_ReadonlyAttribute_End_T (void);

  void generate (const PICML::ReadonlyAttribute & readonly);
};

/**
 *
 */
template < >
class CUTS_BE_Attribute_Begin_T <Quotas::Pojo::Codegen::Context> :
  public CUTS_BE_Visitor_T <Quotas::Pojo::Codegen::Context, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <Quotas::Pojo::Codegen::Context, PICML::Visitor> visitor_type;

  CUTS_BE_Attribute_Begin_T (Quotas::Pojo::Codegen::Context & context);

  virtual ~CUTS_BE_Attribute_Begin_T (void);

  void generate (const PICML::Attribute & attr);
};

/**
 *
 */
template < >
class CUTS_BE_Attribute_End_T <Quotas::Pojo::Codegen::Context> :
  public CUTS_BE_Visitor_T <Quotas::Pojo::Codegen::Context, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <Quotas::Pojo::Codegen::Context, PICML::Visitor> visitor_type;

  CUTS_BE_Attribute_End_T (Quotas::Pojo::Codegen::Context & context);

  virtual ~CUTS_BE_Attribute_End_T (void);

  void generate (const PICML::Attribute & attr);
};

/**
 * @class CUTS_BE_Postcondition_T
 */
template < >
class CUTS_BE_Postcondition_T <Quotas::Pojo::Codegen::Context> :
  public CUTS_BE_Visitor_T <Quotas::Pojo::Codegen::Context, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <Quotas::Pojo::Codegen::Context, PICML::Visitor> visitor_type;

  CUTS_BE_Postcondition_T (Quotas::Pojo::Codegen::Context & context);

  virtual ~CUTS_BE_Postcondition_T (void);

  void generate (const std::string & postcondition);
};

#if defined (__CUTS_INLINE__)
#include "Pojo_Codegen_Generators.inl"
#endif

#endif  // !defined _CUTS_BE_CAPI_GENERATORS_H_
