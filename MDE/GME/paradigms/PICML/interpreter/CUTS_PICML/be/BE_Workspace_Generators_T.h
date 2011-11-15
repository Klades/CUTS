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

#include "PICML/PICML.h"
#include "BE_Visitor_T.h"

/**
 * @class CUTS_BE_Workspace_File_Open_T
 */
template <typename CONTEXT>
class CUTS_BE_Workspace_File_Open_T :
  public CUTS_BE_Visitor_T <CUTS_BE::NIL, PICML::Visitor>
{
public:
  /// Type definition of the visitor type.
  typedef CUTS_BE_Visitor_T <CUTS_BE::NIL, PICML::Visitor> visitor_type;

  CUTS_BE_Workspace_File_Open_T (CONTEXT & context);

  virtual ~CUTS_BE_Workspace_File_Open_T (void);

  void generate (const std::string & name);
};

/**
 * @class CUTS_BE_Workspace_Begin_T
 */
template <typename CONTEXT>
class CUTS_BE_Workspace_Begin_T :
  public CUTS_BE_Visitor_T <CUTS_BE::NIL, PICML::Visitor>
{
public:
  /// Type definition of the visitor type.
  typedef CUTS_BE_Visitor_T <CUTS_BE::NIL, PICML::Visitor> visitor_type;

  CUTS_BE_Workspace_Begin_T (CONTEXT & context);

  virtual ~CUTS_BE_Workspace_Begin_T (void);

  void generate (const std::string & name);
};

/**
 * @class CUTS_BE_Workspace_Project_Include_T
 */
template <typename CONTEXT, typename NODE_TYPE>
class CUTS_BE_Workspace_Project_Include_T :
  public CUTS_BE_Visitor_T <CUTS_BE::NIL, PICML::Visitor>
{
public:
  /// Type definition of the visitor type.
  typedef CUTS_BE_Visitor_T <CUTS_BE::NIL, PICML::Visitor> visitor_type;

  CUTS_BE_Workspace_Project_Include_T (CONTEXT & context);

  virtual ~CUTS_BE_Workspace_Project_Include_T (void);

  void generate (const NODE_TYPE & node);
};

/**
 * @class CUTS_BE_Workspace_End_T
 */
template <typename CONTEXT>
class CUTS_BE_Workspace_End_T :
  public CUTS_BE_Visitor_T <CUTS_BE::NIL, PICML::Visitor>
{
public:
  /// Type definition of the visitor type.
  typedef CUTS_BE_Visitor_T <CUTS_BE::NIL, PICML::Visitor> visitor_type;

  CUTS_BE_Workspace_End_T (CONTEXT & context);

  virtual ~CUTS_BE_Workspace_End_T (void);

  void generate (const std::string & name);
};

/**
 * @class CUTS_BE_Workspace_File_Close_T
 */
template <typename CONTEXT>
class CUTS_BE_Workspace_File_Close_T :
  public CUTS_BE_Visitor_T <CUTS_BE::NIL, PICML::Visitor>
{
public:
  /// Type definition of the visitor type.
  typedef CUTS_BE_Visitor_T <CUTS_BE::NIL, PICML::Visitor> visitor_type;

  CUTS_BE_Workspace_File_Close_T (CONTEXT & context);

  virtual ~CUTS_BE_Workspace_File_Close_T (void);

  void generate (void);
};

#if defined (__CUTS_INLINE__)
#include "BE_Workspace_Generators_T.inl"
#endif

#endif  // !defined _CUTS_BE_WORKSPACE_GENERATORS_T_H_
