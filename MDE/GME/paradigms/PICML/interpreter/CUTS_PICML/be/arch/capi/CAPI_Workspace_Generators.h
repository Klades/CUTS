// -*- C++ -*-

//=============================================================================
/**
 * @file          CAPI_Workspace_Generators.h
 *
 * $Id$
 *
 * @author        James H. Hill
 */
//=============================================================================

#ifndef _CUTS_BE_CAPI_WORKSPACE_GENERATORS_H_
#define _CUTS_BE_CAPI_WORKSPACE_GENERATORS_H_

#include "../../BE_Workspace_Generators_T.h"
#include "CAPI_Generators.h"

// Forward decl.
struct CUTS_BE_Impl_Node;

/**
 * @class CUTS_BE_Workspace_File_Open_T
 */
template < >
class CUTS_BE_Workspace_File_Open_T <CUTS_BE_Capi::Context> :
  public CUTS_BE_Visitor_T <CUTS_BE_Capi::Context, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE_Capi::Context, PICML::Visitor> visitor_type;

  CUTS_BE_Workspace_File_Open_T (CUTS_BE_Capi::Context & context);

  virtual ~CUTS_BE_Workspace_File_Open_T (void);

  void generate (const std::string & name);
};

/**
 * @class CUTS_BE_Workspace_Begin_T
 */
template < >
class CUTS_BE_Workspace_Begin_T <CUTS_BE_Capi::Context> :
  public CUTS_BE_Visitor_T <CUTS_BE_Capi::Context, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE_Capi::Context, PICML::Visitor> visitor_type;

  CUTS_BE_Workspace_Begin_T (CUTS_BE_Capi::Context & context);

  virtual ~CUTS_BE_Workspace_Begin_T (void);

  void generate (const std::string & name);
};

/**
 * @class CUTS_BE_Workspace_Project_Include_T
 */
template < >
class CUTS_BE_Workspace_Project_Include_T <CUTS_BE_Capi::Context, CUTS_BE_Impl_Node> :
  public CUTS_BE_Visitor_T <CUTS_BE_Capi::Context, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE_Capi::Context, PICML::Visitor> visitor_type;

  CUTS_BE_Workspace_Project_Include_T (CUTS_BE_Capi::Context & context);

  virtual ~CUTS_BE_Workspace_Project_Include_T (void);

  void generate (const CUTS_BE_Impl_Node & node);
};

/**
 * @class CUTS_BE_Workspace_End_T
 */
template < >
class CUTS_BE_Workspace_End_T <CUTS_BE_Capi::Context> :
  public CUTS_BE_Visitor_T <CUTS_BE_Capi::Context, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE_Capi::Context, PICML::Visitor> visitor_type;

  CUTS_BE_Workspace_End_T (CUTS_BE_Capi::Context & context);

  virtual ~CUTS_BE_Workspace_End_T (void);

  void generate (const std::string & name);

private:
  void generate_eventtypes_project (void);
  void generate_target_eventtypes_srcgen (std::ofstream & outfile);
  void generate_target_eventtypes_jar_build (std::ofstream & outfile);
  void generate_target_eventtypes_build (std::ofstream & outfile);
};

/**
 * @class CUTS_BE_Workspace_File_Close_T
 */
template < >
class CUTS_BE_Workspace_File_Close_T <CUTS_BE_Capi::Context> :
  public CUTS_BE_Visitor_T <CUTS_BE_Capi::Context, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE_Capi::Context, PICML::Visitor> visitor_type;

  CUTS_BE_Workspace_File_Close_T (CUTS_BE_Capi::Context & context);

  virtual ~CUTS_BE_Workspace_File_Close_T (void);

  void generate (void);
};

#if defined (__CUTS_INLINE__)
#include "CAPI_Workspace_Generators.inl"
#endif

#endif  // !defined _CUTS_BE_CAPI_WORKSPACE_GENERATORS_H_
