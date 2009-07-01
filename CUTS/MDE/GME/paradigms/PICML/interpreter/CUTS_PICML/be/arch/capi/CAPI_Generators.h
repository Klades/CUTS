// -*- C++ -*-

//=============================================================================
/**
 * @file          CAPI_Generators.h
 *
 * Defines the different generators used by the CAPI backend
 *
 * $Id$
 *
 * @author        James H. Hill
 */
//=============================================================================

#ifndef _CUTS_BE_CAPI_GENERATORS_H_
#define _CUTS_BE_CAPI_GENERATORS_H_

#include "CAPI_Ctx.h"
#include "../../BE_Generators_T.h"
#include "../../BE_algorithm.h"

/**
 * @class CUTS_BE_Parse_Precondition_T
 *
 * Parse the conditional expressions.
 */
template < >
class CUTS_BE_Parse_Precondition_T <CUTS_BE_Capi::Context>
{
private:
  static const bool result_type = false;
};

/**
 *
 */
template < >
class CUTS_BE_Finalize_T <CUTS_BE_Capi::Context> :
  public CUTS_BE_Visitor_T <CUTS_BE_Capi::Context, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE_Capi::Context, PICML::Visitor> visitor_type;

  CUTS_BE_Finalize_T (CUTS_BE_Capi::Context & context);

  virtual ~CUTS_BE_Finalize_T (void);

  void generate (const PICML::RootFolder &);

private:
  void generate_mapping_file (const PICML::Event & , const std::string & outdir);
};

/**
 *
 */
template < >
class CUTS_BE_File_Open_T <CUTS_BE_Capi::Context> :
  public CUTS_BE_Visitor_T <CUTS_BE_Capi::Context, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE_Capi::Context, PICML::Visitor> visitor_type;

  CUTS_BE_File_Open_T (CUTS_BE_Capi::Context & context);

  virtual ~CUTS_BE_File_Open_T (void);

  void generate (const PICML::ComponentImplementationContainer &,
                 const PICML::MonolithicImplementation &);
};

/**
 *
 */
template < >
class CUTS_BE_File_Close_T <CUTS_BE_Capi::Context> :
  public CUTS_BE_Visitor_T <CUTS_BE_Capi::Context, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE_Capi::Context, PICML::Visitor> visitor_type;

  CUTS_BE_File_Close_T (CUTS_BE_Capi::Context & context);

  virtual ~CUTS_BE_File_Close_T (void);

  void generate (const PICML::ComponentImplementationContainer &,
                 const PICML::MonolithicImplementation &);
};

/**
 *
 */
template < >
class CUTS_BE_Prologue_T <CUTS_BE_Capi::Context> :
  public CUTS_BE_Visitor_T <CUTS_BE_Capi::Context, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE_Capi::Context, PICML::Visitor> visitor_type;

  CUTS_BE_Prologue_T (CUTS_BE_Capi::Context & context);

  virtual ~CUTS_BE_Prologue_T (void);

  void generate (const PICML::ComponentImplementationContainer &,
                 const PICML::MonolithicImplementation & );
};

/**
 *
 */
template < >
class CUTS_BE_Component_Impl_Begin_T <CUTS_BE_Capi::Context> :
  public CUTS_BE_Visitor_T <CUTS_BE_Capi::Context, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE_Capi::Context, PICML::Visitor> visitor_type;

  CUTS_BE_Component_Impl_Begin_T (CUTS_BE_Capi::Context & context);

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
class CUTS_BE_Component_Impl_End_T <CUTS_BE_Capi::Context> :
  public CUTS_BE_Visitor_T <CUTS_BE_Capi::Context, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE_Capi::Context, PICML::Visitor> visitor_type;

  CUTS_BE_Component_Impl_End_T (CUTS_BE_Capi::Context & context);

  virtual ~CUTS_BE_Component_Impl_End_T (void);

  void generate (const PICML::MonolithicImplementation & mono,
                 const PICML::Component & component);
};

/**
 *
 */
template < >
class CUTS_BE_InEventPort_Begin_T <CUTS_BE_Capi::Context> :
  public CUTS_BE_Visitor_T <CUTS_BE_Capi::Context, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE_Capi::Context, PICML::Visitor> visitor_type;

  CUTS_BE_InEventPort_Begin_T (CUTS_BE_Capi::Context & context);

  virtual ~CUTS_BE_InEventPort_Begin_T (void);

  void generate (const PICML::InEventPort & sink,
                 const std::vector <PICML::Property> &);

private:
  void configure (const PICML::InEventPort & parent,
                  const PICML::Property & prop);
};

/**
 *
 */
template < >
class CUTS_BE_InEventPort_End_T <CUTS_BE_Capi::Context> :
  public CUTS_BE_Visitor_T <CUTS_BE_Capi::Context, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE_Capi::Context, PICML::Visitor> visitor_type;

  CUTS_BE_InEventPort_End_T (CUTS_BE_Capi::Context & context);

  virtual ~CUTS_BE_InEventPort_End_T (void);

  void generate (const PICML::InEventPort & sink,
                 const std::vector <PICML::Property> &);
};

/**
 *
 */
template < >
class CUTS_BE_Environment_Method_Begin_T <CUTS_BE_Capi::Context> :
  public CUTS_BE_Visitor_T <CUTS_BE_Capi::Context, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE_Capi::Context, PICML::Visitor> visitor_type;

  CUTS_BE_Environment_Method_Begin_T (CUTS_BE_Capi::Context & context);

  virtual ~CUTS_BE_Environment_Method_Begin_T (void);

  void generate (const PICML::MultiInputAction & action);
};

/**
 *
 */
template < >
class CUTS_BE_Environment_Method_End_T <CUTS_BE_Capi::Context> :
  public CUTS_BE_Visitor_T <CUTS_BE_Capi::Context, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE_Capi::Context, PICML::Visitor> visitor_type;

  CUTS_BE_Environment_Method_End_T (CUTS_BE_Capi::Context & context);

  virtual ~CUTS_BE_Environment_Method_End_T (void);

  void generate (const PICML::MultiInputAction & action);
};

/**
 *
 */
template < >
class CUTS_BE_Environment_End_T <CUTS_BE_Capi::Context> :
  public CUTS_BE_Visitor_T <CUTS_BE_Capi::Context, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE_Capi::Context, PICML::Visitor> visitor_type;

  CUTS_BE_Environment_End_T (CUTS_BE_Capi::Context & context);

  virtual ~CUTS_BE_Environment_End_T (void);

  void generate (const PICML::Component & component);
};

/**
 *
 */
template < >
class CUTS_BE_PeriodicEvent_Begin_T <CUTS_BE_Capi::Context> :
  public CUTS_BE_Visitor_T <CUTS_BE_Capi::Context, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE_Capi::Context, PICML::Visitor> visitor_type;

  CUTS_BE_PeriodicEvent_Begin_T (CUTS_BE_Capi::Context & context);

  virtual ~CUTS_BE_PeriodicEvent_Begin_T (void);

  void generate (const PICML::PeriodicEvent & periodic);
};

/**
 *
 */
template < >
class CUTS_BE_PeriodicEvent_End_T <CUTS_BE_Capi::Context> :
  public CUTS_BE_Visitor_T <CUTS_BE_Capi::Context, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE_Capi::Context, PICML::Visitor> visitor_type;

  CUTS_BE_PeriodicEvent_End_T (CUTS_BE_Capi::Context & context);

  virtual ~CUTS_BE_PeriodicEvent_End_T (void);

  void generate (const PICML::PeriodicEvent & periodic);
};

/**
 *
 */
template < >
class CUTS_BE_ReadonlyAttribute_Begin_T <CUTS_BE_Capi::Context> :
  public CUTS_BE_Visitor_T <CUTS_BE_Capi::Context, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE_Capi::Context, PICML::Visitor> visitor_type;

  CUTS_BE_ReadonlyAttribute_Begin_T (CUTS_BE_Capi::Context & context);

  virtual ~CUTS_BE_ReadonlyAttribute_Begin_T (void);

  void generate (const PICML::ReadonlyAttribute & readonly);
};

/**
 *
 */
template < >
class CUTS_BE_ReadonlyAttribute_End_T <CUTS_BE_Capi::Context> :
  public CUTS_BE_Visitor_T <CUTS_BE_Capi::Context, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE_Capi::Context, PICML::Visitor> visitor_type;

  CUTS_BE_ReadonlyAttribute_End_T (CUTS_BE_Capi::Context & context);

  virtual ~CUTS_BE_ReadonlyAttribute_End_T (void);

  void generate (const PICML::ReadonlyAttribute & readonly);
};

/**
 *
 */
template < >
class CUTS_BE_Attribute_Begin_T <CUTS_BE_Capi::Context> :
  public CUTS_BE_Visitor_T <CUTS_BE_Capi::Context, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE_Capi::Context, PICML::Visitor> visitor_type;

  CUTS_BE_Attribute_Begin_T (CUTS_BE_Capi::Context & context);

  virtual ~CUTS_BE_Attribute_Begin_T (void);

  void generate (const PICML::Attribute & attr);
};

/**
 *
 */
template < >
class CUTS_BE_Attribute_End_T <CUTS_BE_Capi::Context> :
  public CUTS_BE_Visitor_T <CUTS_BE_Capi::Context, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE_Capi::Context, PICML::Visitor> visitor_type;

  CUTS_BE_Attribute_End_T (CUTS_BE_Capi::Context & context);

  virtual ~CUTS_BE_Attribute_End_T (void);

  void generate (const PICML::Attribute & attr);
};

#if defined (__CUTS_INLINE__)
#include "CAPI_Generators.inl"
#endif


#endif  // !defined _CUTS_BE_CAPI_GENERATORS_H_
