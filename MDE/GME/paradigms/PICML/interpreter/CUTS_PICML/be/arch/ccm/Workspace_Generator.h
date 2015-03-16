// -*- C++ -*-

//=============================================================================
/**
 * @file      Workspace_Generator.h
 *
 * $Id$
 *
 * @author    James H. Hill
 */
//=============================================================================

#ifndef _CUTS_BE_CCM_WORKSPACE_GENERATOR_H_
#define _CUTS_BE_CCM_WORKSPACE_GENERATOR_H_

#include "../../BE_Workspace_Generators_T.h"
#include "PICML/Visitor.h"
#include "CCM.h"

// Forward decl.
struct CUTS_BE_Impl_Node;

// Forward decl.
struct CUTS_BE_IDL_Node;

/**
 * @class CUTS_BE_Workspace_File_Open_T
 */
template < >
class CUTS_BE_CCM_Export CUTS_BE_Workspace_File_Open_T <CUTS_BE_CCM::Cpp::Context> :
  public CUTS_BE_Visitor_T <CUTS_BE_CCM::Cpp::Context, PICML::Visitor>
{
public:
  /// Type definition of the visitor type.
  typedef CUTS_BE_Visitor_T <CUTS_BE_CCM::Cpp::Context, PICML::Visitor> visitor_type;

  /**
   * Initializing constructor
   *
   * @param[in]       context         Target context.
   */
  CUTS_BE_Workspace_File_Open_T (CUTS_BE_CCM::Cpp::Context & context);

  /// Destructor.
  virtual ~CUTS_BE_Workspace_File_Open_T (void);

  void generate (const std::string & name);
};

/**
 * @class CUTS_BE_Workspace_Begin_T
 */
template < >
class CUTS_BE_CCM_Export CUTS_BE_Workspace_Begin_T <CUTS_BE_CCM::Cpp::Context>:
  public CUTS_BE_Visitor_T <CUTS_BE_CCM::Cpp::Context, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE_CCM::Cpp::Context, PICML::Visitor> visitor_type;

  CUTS_BE_Workspace_Begin_T (CUTS_BE_CCM::Cpp::Context & context);

  virtual ~CUTS_BE_Workspace_Begin_T (void);

  void generate (const std::string & name);
};

/**
 * @class CUTS_BE_Workspace_Project_Include_T
 */
template < >
class CUTS_BE_CCM_Export CUTS_BE_Workspace_Project_Include_T <CUTS_BE_CCM::Cpp::Context, CUTS_BE_Impl_Node> :
  public CUTS_BE_Visitor_T <CUTS_BE_CCM::Cpp::Context, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE_CCM::Cpp::Context, PICML::Visitor> visitor_type;

  CUTS_BE_Workspace_Project_Include_T (CUTS_BE_CCM::Cpp::Context & context);

  virtual ~CUTS_BE_Workspace_Project_Include_T (void);

  void generate (const CUTS_BE_Impl_Node & node);
};

/**
 * @class CUTS_BE_Workspace_Project_Include_T
 */
template < >
class CUTS_BE_CCM_Export CUTS_BE_Workspace_Project_Include_T <CUTS_BE_CCM::Cpp::Context, CUTS_BE_IDL_Node> :
  public CUTS_BE_Visitor_T <CUTS_BE_CCM::Cpp::Context, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE_CCM::Cpp::Context, PICML::Visitor> visitor_type;

  CUTS_BE_Workspace_Project_Include_T (CUTS_BE_CCM::Cpp::Context & context);

  virtual ~CUTS_BE_Workspace_Project_Include_T (void);

  void generate (const CUTS_BE_IDL_Node & node);
};

/**
 * @class CUTS_BE_Workspace_End_T
 */
template < >
class CUTS_BE_CCM_Export CUTS_BE_Workspace_End_T <CUTS_BE_CCM::Cpp::Context> :
  public CUTS_BE_Visitor_T <CUTS_BE_CCM::Cpp::Context, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE_CCM::Cpp::Context, PICML::Visitor> visitor_type;

  CUTS_BE_Workspace_End_T (CUTS_BE_CCM::Cpp::Context & context);

  virtual ~CUTS_BE_Workspace_End_T (void);

  void generate (const std::string & name);
};

/**
 * @class CUTS_BE_Workspace_File_Close_T
 */
template < >
class CUTS_BE_CCM_Export CUTS_BE_Workspace_File_Close_T <CUTS_BE_CCM::Cpp::Context> :
  public CUTS_BE_Visitor_T <CUTS_BE_CCM::Cpp::Context, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE_CCM::Cpp::Context, PICML::Visitor> visitor_type;

  CUTS_BE_Workspace_File_Close_T (CUTS_BE_CCM::Cpp::Context & context);

  virtual ~CUTS_BE_Workspace_File_Close_T (void);

  void generate (void);
};

#if defined (__CUTS_INLINE__)
#include "Workspace_Generator.inl"
#endif

#endif  // !defined _CUTS_BE_CIAO_PROJECT_GENERATOR_H_
