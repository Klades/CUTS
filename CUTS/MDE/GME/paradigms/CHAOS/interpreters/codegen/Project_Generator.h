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

#ifndef _CUTS_BE_CHAOS_PROEJECT_GENERATOR_H_
#define _CUTS_BE_CHAOS_PROEJECT_GENERATOR_H_

#include "BE_Project_Generators_T.h"
#include "String_Set.h"
#include "Context.h"

// Forward decl.
struct CUTS_BE_Impl_Node;

// Forward decl.
struct CUTS_BE_IDL_Node;

/**
 * @class CUTS_BE_Project_File_Open_T
 */
template < >
class CUTS_BE_Project_File_Open_T <CUTS_CHAOS::Context, CUTS_BE_Impl_Node> :
  public CUTS_BE_Visitor_T <CUTS_CHAOS::Context, CHAOS::Visitor>
{
public:
  /// Type definition of the visitor type.
  typedef CUTS_BE_Visitor_T <CUTS_CHAOS::Context, CHAOS::Visitor> visitor_type;

  CUTS_BE_Project_File_Open_T (CUTS_CHAOS::Context & context);

  virtual ~CUTS_BE_Project_File_Open_T (void);

  void generate (const CUTS_BE_Impl_Node & node);
};

/**
 * @class CUTS_BE_Project_File_Begin_T
 */
template < >
class CUTS_BE_Project_File_Begin_T <CUTS_CHAOS::Context, CUTS_BE_Impl_Node> :
  public CUTS_BE_Visitor_T <CUTS_CHAOS::Context, CHAOS::Visitor>
{
public:
  /// Type definition of the visitor type.
  typedef CUTS_BE_Visitor_T <CUTS_CHAOS::Context, CHAOS::Visitor> visitor_type;

  CUTS_BE_Project_File_Begin_T (CUTS_CHAOS::Context & context);

  virtual ~CUTS_BE_Project_File_Begin_T (void);

  void generate (const CUTS_BE_Impl_Node & node);
};

/**
 *
 */
template < >
class CUTS_BE_Project_Write_T <CUTS_CHAOS::Context, CUTS_BE_Impl_Node> :
  public CUTS_BE_Visitor_T <CUTS_CHAOS::Context, CHAOS::Visitor>
{
public:
  /// Type definition of the visitor type.
  typedef CUTS_BE_Visitor_T <CUTS_CHAOS::Context, CHAOS::Visitor> visitor_type;

  CUTS_BE_Project_Write_T (CUTS_CHAOS::Context & context);

  virtual ~CUTS_BE_Project_Write_T (void);

  void generate (const CUTS_BE_Impl_Node & node);

private:
  void generate_impl_project (const CUTS_BE_Impl_Node & node);

  void generate_listing (const CUTS_BE_IDL_Node * node,
                         const char * prefix,
                         const char * postfix);

  void generate_mpc_i (const CUTS_BE_Impl_Node & node);

  void generate_mpc_values (const std::string & heading,
                            const CUTS_String_Set & listing);

  typedef std::set <const CUTS_BE_IDL_Node *> IDL_Node_Set;

  IDL_Node_Set visited_nodes_;
};

/**
 *
 */
template < >
class CUTS_BE_Project_File_End_T <CUTS_CHAOS::Context, CUTS_BE_Impl_Node> :
  public CUTS_BE_Visitor_T <CUTS_CHAOS::Context, CHAOS::Visitor>
{
public:
  /// Type definition of the visitor type.
  typedef CUTS_BE_Visitor_T <CUTS_CHAOS::Context, CHAOS::Visitor> visitor_type;

  CUTS_BE_Project_File_End_T (CUTS_CHAOS::Context & context);

  virtual ~CUTS_BE_Project_File_End_T (void);

  void generate (const CUTS_BE_Impl_Node & node);
};

/**
 *
 */
template <  >
class CUTS_BE_Project_File_Close_T <CUTS_CHAOS::Context, CUTS_BE_Impl_Node> :
  public CUTS_BE_Visitor_T <CUTS_CHAOS::Context, CHAOS::Visitor>
{
public:
  /// Type definition of the visitor type.
  typedef CUTS_BE_Visitor_T <CUTS_CHAOS::Context, CHAOS::Visitor> visitor_type;

  CUTS_BE_Project_File_Close_T (CUTS_CHAOS::Context & context);

  virtual ~CUTS_BE_Project_File_Close_T (void);

  void generate (void);
};

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_IDL_Node

/**
 * @class CUTS_BE_Project_File_Open_T
 */
template < >
class CUTS_BE_Project_File_Open_T <CUTS_CHAOS::Context, CUTS_BE_IDL_Node> :
  public CUTS_BE_Visitor_T <CUTS_CHAOS::Context, CHAOS::Visitor>
{
public:
  /// Type definition of the visitor type.
  typedef CUTS_BE_Visitor_T <CUTS_CHAOS::Context, CHAOS::Visitor> visitor_type;

  CUTS_BE_Project_File_Open_T (CUTS_CHAOS::Context & context);

  virtual ~CUTS_BE_Project_File_Open_T (void);

  void generate (const CUTS_BE_IDL_Node & node);
};

/**
 * @class CUTS_BE_Project_File_Begin_T
 */
template < >
class CUTS_BE_Project_File_Begin_T <CUTS_CHAOS::Context, CUTS_BE_IDL_Node> :
  public CUTS_BE_Visitor_T <CUTS_CHAOS::Context, CHAOS::Visitor>
{
public:
  /// Type definition of the visitor type.
  typedef CUTS_BE_Visitor_T <CUTS_CHAOS::Context, CHAOS::Visitor> visitor_type;

  CUTS_BE_Project_File_Begin_T (CUTS_CHAOS::Context & context);

  virtual ~CUTS_BE_Project_File_Begin_T (void);

  void generate (const CUTS_BE_IDL_Node & node);
};

/**
 *
 */
template < >
class CUTS_BE_Project_Write_T <CUTS_CHAOS::Context, CUTS_BE_IDL_Node> :
  public CUTS_BE_Visitor_T <CUTS_CHAOS::Context, CHAOS::Visitor>
{
public:
  /// Type definition of the visitor type.
  typedef CUTS_BE_Visitor_T <CUTS_CHAOS::Context, CHAOS::Visitor> visitor_type;

  CUTS_BE_Project_Write_T (CUTS_CHAOS::Context & context);

  virtual ~CUTS_BE_Project_Write_T (void);

  void generate (const CUTS_BE_IDL_Node & node);

protected:
  CUTS_String_Set stub_files_;

  std::string stub_after_;

private:
  void generate_idlgen_project (const CUTS_BE_IDL_Node & node);

  void generate_stub_project (const CUTS_BE_IDL_Node & node);

  void generate_skel_project (const CUTS_BE_IDL_Node & node);

  void generate_eidl_project (const CUTS_BE_IDL_Node & node);

  void generate_exec_project (const CUTS_BE_IDL_Node & node);

  void generate_svnt_project (const CUTS_BE_IDL_Node & node);

  void generate_listing (const CUTS_BE_IDL_Node * node, const char * type);

  typedef std::set <const CUTS_BE_IDL_Node *> IDL_Node_Set;

  IDL_Node_Set visited_nodes_;
};

/**
 *
 */
template <  >
class CUTS_BE_Project_File_End_T <CUTS_CHAOS::Context, CUTS_BE_IDL_Node> :
  public CUTS_BE_Visitor_T <CUTS_CHAOS::Context, CHAOS::Visitor>
{
public:
  /// Type definition of the visitor type.
  typedef CUTS_BE_Visitor_T <CUTS_CHAOS::Context, CHAOS::Visitor> visitor_type;

  CUTS_BE_Project_File_End_T (CUTS_CHAOS::Context & context);

  virtual ~CUTS_BE_Project_File_End_T (void);

  bool generate (const CUTS_BE_IDL_Node & node);
};

/**
 *
 */
template <  >
class CUTS_BE_Project_File_Close_T <CUTS_CHAOS::Context, CUTS_BE_IDL_Node> :
  public CUTS_BE_Visitor_T <CUTS_CHAOS::Context, CHAOS::Visitor>
{
public:
  /// Type definition of the visitor type.
  typedef CUTS_BE_Visitor_T <CUTS_CHAOS::Context, CHAOS::Visitor> visitor_type;

  CUTS_BE_Project_File_Close_T (CUTS_CHAOS::Context & context);

  virtual ~CUTS_BE_Project_File_Close_T (void);

  void generate (void);
};

#if defined (__CUTS_INLINE__)
#include "Project_Generator.inl"
#endif

#endif  // !defined _CUTS_BE_OPENSPLICE_PROEJECT_GENERATOR_H_
