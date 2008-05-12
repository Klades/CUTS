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

#include "be/BE_Workspace_Generators_T.h"
#include "CAPI_Generators.h"

// Forward decl.
struct CUTS_BE_Impl_Node;

/**
 *
 */
template < >
struct CUTS_BE_Workspace_File_Open_T <CUTS_BE_Capi>
{
  static bool generate (const std::string & name);
};

/**
 *
 */
template < >
struct CUTS_BE_Workspace_Begin_T <CUTS_BE_Capi>
{
  static bool generate (const std::string & name);
};

/**
 *
 */
template < >
struct CUTS_BE_Workspace_Project_Include_T <CUTS_BE_Capi, CUTS_BE_Impl_Node>
{
  static bool generate (const CUTS_BE_Impl_Node & node);
};

/**
 *
 */
template < >
struct CUTS_BE_Workspace_End_T <CUTS_BE_Capi>
{
  static bool generate (const std::string & name);
};

/**
 *
 */
template < >
struct CUTS_BE_Workspace_File_Close_T <CUTS_BE_Capi>
{
  static void generate (void);
};

#endif  // !defined _CUTS_BE_CAPI_WORKSPACE_GENERATORS_H_
