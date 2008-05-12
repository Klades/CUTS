// -*- C++ -*-

//=============================================================================
/**
 * @file      BE_Project_Generators_T.h
 *
 * $Id$
 *
 * Collection of generators for generating project files
 *
 * @author    James H. Hill
 */
//=============================================================================

#ifndef _CUTS_BE_PROJECT_GENERATORS_T_H_
#define _CUTS_BE_PROJECT_GENERATORS_T_H_

/**
 *
 */
template <typename BE_TYPE, typename NODE_TYPE>
struct CUTS_BE_Project_File_Open_T
{
  static bool generate (const NODE_TYPE & node)
    { return false; }
};

/**
 *
 */
template <typename BE_TYPE, typename NODE_TYPE>
struct CUTS_BE_Project_File_Begin_T
{
  static bool generate (const NODE_TYPE & node)
    { return false; }
};

/**
 *
 */
template <typename BE_TYPE, typename NODE_TYPE>
struct CUTS_BE_Project_Write_T
{
  static bool generate (const NODE_TYPE & node)
    { return false; }
};

/**
 *
 */
template <typename BE_TYPE, typename NODE_TYPE>
struct CUTS_BE_Project_File_End_T
{
  static bool generate (const NODE_TYPE & node)
    { return false; }
};

/**
 *
 */
template <typename BE_TYPE, typename NODE_TYPE>
struct CUTS_BE_Project_File_Close_T
{
  static void generate (void)
    { }
};

#endif  // !defined _CUTS_BE_PROJECT_GENERATORS_T_H_
