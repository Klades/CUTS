// -*- C++ -*-

//=============================================================================
/**
 * @file      BE_Type_Map.h
 *
 * $Id$
 *
 * @author    James H. Hill
 */
//=============================================================================

#ifndef _CUTS_BE_TYPE_MAP_H_
#define _CUTS_BE_TYPE_MAP_H_

#include "BE_export.h"
#include "PICML/PICML.h"
#include <string>
#include <map>

//=============================================================================
/**
 * @class CUTS_BE_Type_Map
 */
//=============================================================================

class CUTS_BE_Export CUTS_BE_Type_Map
{
public:
  /// Destructor.
  virtual ~CUTS_BE_Type_Map (void);

  virtual std::string value (const PICML::MemberType_in type);

  virtual std::string value (const PICML::PredefinedType_in type);

  virtual std::string value (const PICML::NamedType_in type);

protected:
  /// Type definition for mapping predefined types.
  typedef std::map <std::string, std::string> Type_Map;

  /// Mapping of predefined types to concrete syntax.
  Type_Map predefined_type_map_;

  /// Default constructor.
  CUTS_BE_Type_Map (void);
};

#if defined (__CUTS_INLINE__)
#include "BE_Type_Map.inl"
#endif

#endif  // !defined _CUTS_BE_TYPE_MAP_H_
