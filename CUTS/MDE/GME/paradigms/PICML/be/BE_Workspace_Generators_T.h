// -*- C++ -*-

//=============================================================================
/**
 * @file        BE_Workspace_Generators_T.h
 *
 * $Id$
 *
 * Collection of generators for generating the workspace.
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _CUTS_BE_WORKSPACE_GENERATORS_T_H_
#define _CUTS_BE_WORKSPACE_GENERATORS_T_H_

#include <string>

/**
 *
 */
template <typename BE_TYPE>
struct CUTS_BE_Workspace_File_Open_T
{
  static bool generate (const std::string & name)
    { return false; }
};

/**
 *
 */
template <typename BE_TYPE>
struct CUTS_BE_Workspace_Begin_T
{
  static bool generate (const std::string & name)
    { return false; }
};

/**
 *
 */
template <typename BE_TYPE, typename NODE_TYPE>
struct CUTS_BE_Workspace_Project_Include_T
{
  static bool generate (const NODE_TYPE & node)
    { return false; }
};

/**
 *
 */
template <typename BE_TYPE>
struct CUTS_BE_Workspace_End_T
{
  static bool generate (const std::string & name)
    { return false; }
};

/**
 *
 */
template <typename BE_TYPE>
struct CUTS_BE_Workspace_File_Close_T
{
  static void generate (void)
    { return false; }
};

#endif  // !defined _CUTS_BE_WORKSPACE_GENERATORS_T_H_
