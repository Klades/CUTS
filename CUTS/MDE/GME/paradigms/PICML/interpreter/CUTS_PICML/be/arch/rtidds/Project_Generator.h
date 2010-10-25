// -*- C++ -*-

//=============================================================================
/**
 * @file      Component_Impl_Generator.h
 *
 * $Id$
 *
 * @author    James H. Hill
 */
//=============================================================================

#ifndef _CUTS_BE_RTIDDS_PROEJECT_GENERATOR_H_
#define _CUTS_BE_RTIDDS_PROEJECT_GENERATOR_H_

#include "../../BE_Project_Generators_T.h"
#include "../ciao/CIAO_Project_Generator.h"
#include "Context.h"

/**
 * @class CUTS_BE_Project_File_Open_T
 */
template < >
class CUTS_BE_Project_File_Open_T <CUTS_BE_RTIDDS::Context, CUTS_BE_Impl_Node> :
  public CUTS_BE_Project_File_Open_T <CUTS_BE_CIAO::Context, CUTS_BE_Impl_Node>
{
public:
  /// Type definition of the visitor type.
  typedef CUTS_BE_Project_File_Open_T <CUTS_BE_CIAO::Context, CUTS_BE_Impl_Node> base_type;

  CUTS_BE_Project_File_Open_T (CUTS_BE_RTIDDS::Context & context);

  virtual ~CUTS_BE_Project_File_Open_T (void);
};

/**
 * @class CUTS_BE_Project_File_Begin_T
 */
template < >
class CUTS_BE_Project_File_Begin_T <CUTS_BE_RTIDDS::Context, CUTS_BE_Impl_Node> :
  public CUTS_BE_Project_File_Begin_T <CUTS_BE_CIAO::Context, CUTS_BE_Impl_Node>
{
public:
  /// Type definition of the visitor type.
  typedef CUTS_BE_Project_File_Begin_T <CUTS_BE_CIAO::Context, CUTS_BE_Impl_Node> base_type;

  CUTS_BE_Project_File_Begin_T (CUTS_BE_RTIDDS::Context & context);

  virtual ~CUTS_BE_Project_File_Begin_T (void);
};

/**
 *
 */
template < >
class CUTS_BE_Project_Write_T <CUTS_BE_RTIDDS::Context, CUTS_BE_Impl_Node> :
  public CUTS_BE_Project_Write_T <CUTS_BE_CIAO::Context, CUTS_BE_Impl_Node>
{
public:
  /// Type definition of the visitor type.
  typedef CUTS_BE_Project_Write_T <CUTS_BE_CIAO::Context, CUTS_BE_Impl_Node> base_type;

  CUTS_BE_Project_Write_T (CUTS_BE_RTIDDS::Context & context);

  virtual ~CUTS_BE_Project_Write_T (void);
};

/**
 *
 */
template < >
class CUTS_BE_Project_File_End_T <CUTS_BE_RTIDDS::Context, CUTS_BE_Impl_Node> :
  public CUTS_BE_Project_File_End_T <CUTS_BE_CIAO::Context, CUTS_BE_Impl_Node>
{
public:
  /// Type definition of the visitor type.
  typedef CUTS_BE_Project_File_End_T <CUTS_BE_CIAO::Context, CUTS_BE_Impl_Node> base_type;

  CUTS_BE_Project_File_End_T (CUTS_BE_RTIDDS::Context & context);

  virtual ~CUTS_BE_Project_File_End_T (void);
};

/**
 *
 */
template <  >
class CUTS_BE_Project_File_Close_T <CUTS_BE_RTIDDS::Context, CUTS_BE_Impl_Node> :
  public CUTS_BE_Project_File_Close_T <CUTS_BE_CIAO::Context, CUTS_BE_Impl_Node>
{
public:
  /// Type definition of the visitor type.
  typedef CUTS_BE_Project_File_Close_T <CUTS_BE_CIAO::Context, CUTS_BE_Impl_Node> base_type;

  CUTS_BE_Project_File_Close_T (CUTS_BE_RTIDDS::Context & context);

  virtual ~CUTS_BE_Project_File_Close_T (void);
};

/**
 * @class CUTS_BE_Project_File_Open_T
 */
template < >
class CUTS_BE_Project_File_Open_T <CUTS_BE_RTIDDS::Context, CUTS_BE_IDL_Node> :
  public CUTS_BE_Project_File_Open_T <CUTS_BE_CIAO::Context, CUTS_BE_IDL_Node>
{
public:
  /// Type definition of the visitor type.
  typedef CUTS_BE_Project_File_Open_T <CUTS_BE_CIAO::Context, CUTS_BE_IDL_Node> base_type;

  CUTS_BE_Project_File_Open_T (CUTS_BE_RTIDDS::Context & context);

  virtual ~CUTS_BE_Project_File_Open_T (void);
};

/**
 * @class CUTS_BE_Project_File_Begin_T
 */
template < >
class CUTS_BE_Project_File_Begin_T <CUTS_BE_RTIDDS::Context, CUTS_BE_IDL_Node> :
  public CUTS_BE_Project_File_Begin_T <CUTS_BE_CIAO::Context, CUTS_BE_IDL_Node>
{
public:
  /// Type definition of the visitor type.
  typedef CUTS_BE_Project_File_Begin_T <CUTS_BE_CIAO::Context, CUTS_BE_IDL_Node> base_type;

  CUTS_BE_Project_File_Begin_T (CUTS_BE_RTIDDS::Context & context);

  virtual ~CUTS_BE_Project_File_Begin_T (void);
};

/**
 *
 */
template < >
class CUTS_BE_Project_Write_T <CUTS_BE_RTIDDS::Context, CUTS_BE_IDL_Node> :
  public CUTS_BE_Project_Write_T <CUTS_BE_CIAO::Context, CUTS_BE_IDL_Node>
{
public:
  /// Type definition of the visitor type.
  typedef CUTS_BE_Project_Write_T <CUTS_BE_CIAO::Context, CUTS_BE_IDL_Node> base_type;

  CUTS_BE_Project_Write_T (CUTS_BE_RTIDDS::Context & context);

  virtual ~CUTS_BE_Project_Write_T (void);

  void generate (const CUTS_BE_IDL_Node & node);
};

/**
 *
 */
template <  >
class CUTS_BE_Project_File_End_T <CUTS_BE_RTIDDS::Context, CUTS_BE_IDL_Node> :
  public CUTS_BE_Project_File_End_T <CUTS_BE_CIAO::Context, CUTS_BE_IDL_Node>
{
public:
  /// Type definition of the visitor type.
  typedef CUTS_BE_Project_File_End_T <CUTS_BE_CIAO::Context, CUTS_BE_IDL_Node> base_type;

  CUTS_BE_Project_File_End_T (CUTS_BE_RTIDDS::Context & context);

  virtual ~CUTS_BE_Project_File_End_T (void);
};

/**
 *
 */
template <  >
class CUTS_BE_Project_File_Close_T <CUTS_BE_RTIDDS::Context, CUTS_BE_IDL_Node> :
  public CUTS_BE_Project_File_Close_T <CUTS_BE_CIAO::Context, CUTS_BE_IDL_Node>
{
public:
  /// Type definition of the visitor type.
  typedef CUTS_BE_Project_File_Close_T <CUTS_BE_CIAO::Context, CUTS_BE_IDL_Node> base_type;

  CUTS_BE_Project_File_Close_T (CUTS_BE_RTIDDS::Context & context);

  virtual ~CUTS_BE_Project_File_Close_T (void);
};

#if defined (__CUTS_INLINE__)
#include "Project_Generator.inl"
#endif

#endif  // !defined _CUTS_BE_RTIDDS_PROEJECT_GENERATOR_H_
