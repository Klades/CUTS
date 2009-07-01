// -*- C++ -*-

//=============================================================================
/**
 * @file        CAPI_Project_Generators.h
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _CUTS_BE_CAPI_PROJECT_GENERATORS_H_
#define _CUTS_BE_CAPI_PROJECT_GENERATORS_H_

#include "../../BE_Project_Generators_T.h"
#include "CAPI_Ctx.h"

// Forward decl.
struct CUTS_BE_Impl_Node;

/**
 * @class CUTS_BE_Project_File_Open_T
 */
template < >
class CUTS_BE_Project_File_Open_T <CUTS_BE_Capi::Context, CUTS_BE_Impl_Node> :
  public CUTS_BE_Visitor_T <CUTS_BE_Capi::Context, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE_Capi::Context, PICML::Visitor> visitor_type;

  CUTS_BE_Project_File_Open_T (CUTS_BE_Capi::Context & context);

  virtual ~CUTS_BE_Project_File_Open_T (void);

  void generate (const CUTS_BE_Impl_Node & node);
};

/**
 * @class CUTS_BE_Project_File_Begin_T
 */
template < >
class CUTS_BE_Project_File_Begin_T <CUTS_BE_Capi::Context, CUTS_BE_Impl_Node> :
  public CUTS_BE_Visitor_T <CUTS_BE_Capi::Context, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE_Capi::Context, PICML::Visitor> visitor_type;

  CUTS_BE_Project_File_Begin_T (CUTS_BE_Capi::Context & context);

  virtual ~CUTS_BE_Project_File_Begin_T (void);

  void generate (const CUTS_BE_Impl_Node & node);
};

/**
 * @class CUTS_BE_Project_Write_T
 */
template < >
class CUTS_BE_Project_Write_T <CUTS_BE_Capi::Context, CUTS_BE_Impl_Node> :
  public CUTS_BE_Visitor_T <CUTS_BE_Capi::Context, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE_Capi::Context, PICML::Visitor> visitor_type;

  CUTS_BE_Project_Write_T (CUTS_BE_Capi::Context & context);

  virtual ~CUTS_BE_Project_Write_T (void);

  void generate (const CUTS_BE_Impl_Node & node);

private:
  void generate_i (const PICML::MonolithicImplementation & );
  void generate_event_include_jar (const std::string & string);
  void generate_target_events_build (void);
  void generate_target_events_srcgen (void);
};

/**
 * @class CUTS_BE_Project_File_End_T
 */
template < >
class CUTS_BE_Project_File_End_T <CUTS_BE_Capi::Context, CUTS_BE_Impl_Node> :
  public CUTS_BE_Visitor_T <CUTS_BE_Capi::Context, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE_Capi::Context, PICML::Visitor> visitor_type;

  CUTS_BE_Project_File_End_T (CUTS_BE_Capi::Context & context);

  virtual ~CUTS_BE_Project_File_End_T (void);

  void generate (const CUTS_BE_Impl_Node & node);
};

/**
 * @class CUTS_BE_Project_File_Close_T
 */
template < >
class CUTS_BE_Project_File_Close_T <CUTS_BE_Capi::Context, CUTS_BE_Impl_Node> :
  public CUTS_BE_Visitor_T <CUTS_BE_Capi::Context, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE_Capi::Context, PICML::Visitor> visitor_type;

  CUTS_BE_Project_File_Close_T (CUTS_BE_Capi::Context & context);

  virtual ~CUTS_BE_Project_File_Close_T (void);

  void generate (void);
};

#if defined (__CUTS_INLINE__)
#include "CAPI_Project_Generators.inl"
#endif

#endif  // _CUTS_BE_CAPI_PROJECT_GENERATORS_H_
