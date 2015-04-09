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

#include "../../lang/java/Java_Behavior_Generator.h"
#include "CAPI_Preprocessor_Handlers.h"
#include "CAPI_Project_Generators.h"
#include "CAPI_Workspace_Generators.h"

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
                 GAME::Mga::Collection_T <PICML::Property> &);

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
                 GAME::Mga::Collection_T <PICML::Property> &);
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

/**
 * @class CUTS_BE_Postcondition_T
 */
template < >
class CUTS_BE_Postcondition_T <CUTS_BE_Capi::Context> :
  public CUTS_BE_Visitor_T <CUTS_BE_Capi::Context, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE_Capi::Context, PICML::Visitor> visitor_type;

  CUTS_BE_Postcondition_T (CUTS_BE_Capi::Context & context);

  virtual ~CUTS_BE_Postcondition_T (void);

  void generate (const std::string & postcondition);
};

#if defined (__CUTS_INLINE__)
#include "CAPI_Generators.inl"
#endif

#endif  // !defined _CUTS_BE_CAPI_GENERATORS_H_
