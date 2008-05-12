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

#include "CAPI_Generators.h"
#include "be/BE_Project_Generators_T.h"

// Forward decl.
struct CUTS_BE_Impl_Node;

/**
 *
 */
template < >
struct CUTS_BE_Project_File_Open_T <CUTS_BE_Capi, CUTS_BE_Impl_Node>
{
  static bool generate (const CUTS_BE_Impl_Node & node);
};

/**
 *
 */
template < >
struct CUTS_BE_Project_File_Begin_T <CUTS_BE_Capi, CUTS_BE_Impl_Node>
{
  static bool generate (const CUTS_BE_Impl_Node & node);
};

/**
 *
 */
template < >
struct CUTS_BE_Project_Write_T <CUTS_BE_Capi, CUTS_BE_Impl_Node>
{
  static bool generate (const CUTS_BE_Impl_Node & node);

private:
  static void generate_i (const PICML::MonolithicImplementation & );
};

/**
 *
 */
template < >
struct CUTS_BE_Project_File_End_T <CUTS_BE_Capi, CUTS_BE_Impl_Node>
{
  static bool generate (const CUTS_BE_Impl_Node & node);
};

/**
 *
 */
template < >
struct CUTS_BE_Project_File_Close_T <CUTS_BE_Capi, CUTS_BE_Impl_Node>
{
  static void generate (void);
};

#endif  // _CUTS_BE_CAPI_PROJECT_GENERATORS_H_
