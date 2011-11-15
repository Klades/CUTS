// -*- C++ -*-

//=============================================================================
/**
 * @file      BE_Project_Generators_T.h
 *
 * $Id$
 *
 * @author    James H. Hill
 */
//=============================================================================

#ifndef _CUTS_BE_PROJECT_GENERATORS_T_H_
#define _CUTS_BE_PROJECT_GENERATORS_T_H_

#include "PICML/PICML.h"
#include "BE_Visitor_T.h"

/**
 * @class CUTS_BE_Project_File_Open_T
 */
template <typename CONTEXT, typename NODE_TYPE>
class CUTS_BE_Project_File_Open_T :
  public CUTS_BE_Visitor_T <CUTS_BE::NIL, PICML::Visitor>
{
public:
  /// Type definition of the visitor type.
  typedef CUTS_BE_Visitor_T <CUTS_BE::NIL, PICML::Visitor> visitor_type;

  CUTS_BE_Project_File_Open_T (CONTEXT & context);

  virtual ~CUTS_BE_Project_File_Open_T (void);

  void generate (const NODE_TYPE & node);
};

/**
 * @class CUTS_BE_Project_File_Begin_T
 */
template <typename CONTEXT, typename NODE_TYPE>
class CUTS_BE_Project_File_Begin_T :
  public CUTS_BE_Visitor_T <CUTS_BE::NIL, PICML::Visitor>
{
public:
  /// Type definition of the visitor type.
  typedef CUTS_BE_Visitor_T <CUTS_BE::NIL, PICML::Visitor> visitor_type;

  CUTS_BE_Project_File_Begin_T (CONTEXT & context);

  virtual ~CUTS_BE_Project_File_Begin_T (void);

  void generate (const NODE_TYPE & node);
};

/**
 * @class CUTS_BE_Project_Write_T
 */
template <typename CONTEXT, typename NODE_TYPE>
class CUTS_BE_Project_Write_T :
  public CUTS_BE_Visitor_T <CUTS_BE::NIL, PICML::Visitor>
{
public:
  /// Type definition of the visitor type.
  typedef CUTS_BE_Visitor_T <CUTS_BE::NIL, PICML::Visitor> visitor_type;

  CUTS_BE_Project_Write_T (CONTEXT & context);

  virtual ~CUTS_BE_Project_Write_T (void);

  void generate (const NODE_TYPE & node);
};

/**
 * @class CUTS_BE_Project_File_End_T
 */
template <typename CONTEXT, typename NODE_TYPE>
class CUTS_BE_Project_File_End_T :
  public CUTS_BE_Visitor_T <CUTS_BE::NIL, PICML::Visitor>
{
public:
  /// Type definition of the visitor type.
  typedef CUTS_BE_Visitor_T <CUTS_BE::NIL, PICML::Visitor> visitor_type;

  CUTS_BE_Project_File_End_T (CONTEXT & context);

  virtual ~CUTS_BE_Project_File_End_T (void);

  void generate (const NODE_TYPE & node);
};

/**
 * @class CUTS_BE_Project_File_Close_T
 */
template <typename CONTEXT, typename NODE_TYPE>
class CUTS_BE_Project_File_Close_T :
  public CUTS_BE_Visitor_T <CUTS_BE::NIL, PICML::Visitor>
{
public:
  /// Type definition of the visitor type.
  typedef CUTS_BE_Visitor_T <CUTS_BE::NIL, PICML::Visitor> visitor_type;

  CUTS_BE_Project_File_Close_T (CONTEXT & context);

  virtual ~CUTS_BE_Project_File_Close_T (void);

  void generate (void);
};

#if defined (__CUTS_INLINE__)
#include "BE_Project_Generators_T.inl"
#endif

#include "BE_Project_Generators_T.cpp"

#endif  // !defined _CUTS_BE_PROJECT_GENERATORS_T_H_
