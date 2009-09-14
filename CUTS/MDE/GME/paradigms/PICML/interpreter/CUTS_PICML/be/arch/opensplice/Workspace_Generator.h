// $Id$

//=============================================================================
/**
 * @file        Workspace_Generator.h
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _CUTS_BE_OPENSPLICE_WORKSPACE_GENERATOR_H_
#define _CUTS_BE_OPENSPLICE_WORKSPACE_GENERATOR_H_

#include "../ciao/Workspace_Generator.h"
#include "Context.h"

/**
 * @class CUTS_BE_Workspace_File_Open_T
 */
template < >
class CUTS_BE_Workspace_File_Open_T <CUTS_BE_OpenSplice::Context> :
  public CUTS_BE_Workspace_File_Open_T <CUTS_BE_CIAO::Context>
{
public:
  typedef CUTS_BE_Workspace_File_Open_T <CUTS_BE_CIAO::Context> base_type;

  CUTS_BE_Workspace_File_Open_T (CUTS_BE_OpenSplice::Context & context);

  virtual ~CUTS_BE_Workspace_File_Open_T (void);
};

/**
 * @class CUTS_BE_Workspace_Begin_T
 */
template < >
class CUTS_BE_Workspace_Begin_T <CUTS_BE_OpenSplice::Context> :
  public CUTS_BE_Workspace_Begin_T <CUTS_BE_CIAO::Context>
{
public:
  typedef CUTS_BE_Workspace_Begin_T <CUTS_BE_CIAO::Context> base_type;

  CUTS_BE_Workspace_Begin_T (CUTS_BE_OpenSplice::Context & context);

  virtual ~CUTS_BE_Workspace_Begin_T (void);
};

/**
 * @class CUTS_BE_Workspace_Project_Include_T
 */
template < >
class CUTS_BE_Workspace_Project_Include_T <CUTS_BE_OpenSplice::Context, CUTS_BE_Impl_Node> :
  public CUTS_BE_Workspace_Project_Include_T <CUTS_BE_CIAO::Context, CUTS_BE_Impl_Node>
{
public:
  typedef CUTS_BE_Workspace_Project_Include_T <CUTS_BE_CIAO::Context, CUTS_BE_Impl_Node> base_type;

  CUTS_BE_Workspace_Project_Include_T (CUTS_BE_OpenSplice::Context & context);

  virtual ~CUTS_BE_Workspace_Project_Include_T (void);
};

/**
 * @class CUTS_BE_Workspace_Project_Include_T
 */
template < >
class CUTS_BE_Workspace_Project_Include_T <CUTS_BE_OpenSplice::Context, CUTS_BE_IDL_Node> :
  public CUTS_BE_Workspace_Project_Include_T <CUTS_BE_CIAO::Context, CUTS_BE_IDL_Node>
{
public:
  typedef CUTS_BE_Workspace_Project_Include_T <CUTS_BE_CIAO::Context, CUTS_BE_IDL_Node> base_type;

  CUTS_BE_Workspace_Project_Include_T (CUTS_BE_OpenSplice::Context & context);

  virtual ~CUTS_BE_Workspace_Project_Include_T (void);
};

/**
 * @class CUTS_BE_Workspace_End_T
 */
template < >
class CUTS_BE_Workspace_End_T <CUTS_BE_OpenSplice::Context> :
  public CUTS_BE_Workspace_End_T <CUTS_BE_CIAO::Context>
{
public:
  typedef CUTS_BE_Workspace_End_T <CUTS_BE_CIAO::Context> base_type;

  CUTS_BE_Workspace_End_T (CUTS_BE_OpenSplice::Context & context);

  virtual ~CUTS_BE_Workspace_End_T (void);
};

/**
 * @class CUTS_BE_Workspace_File_Close_T
 */
template < >
class CUTS_BE_Workspace_File_Close_T <CUTS_BE_OpenSplice::Context> :
  public CUTS_BE_Workspace_File_Close_T <CUTS_BE_CIAO::Context>
{
public:
  typedef CUTS_BE_Workspace_File_Close_T <CUTS_BE_CIAO::Context> base_type;

  CUTS_BE_Workspace_File_Close_T (CUTS_BE_OpenSplice::Context & context);

  virtual ~CUTS_BE_Workspace_File_Close_T (void);
};

#if defined (__CUTS_INLINE__)
#include "Workspace_Generator.inl"
#endif

#endif  // !defined _CUTS_BE_TCPIP_WORKSPACE_GENERATOR_H_
