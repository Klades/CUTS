// -*- C++ -*-

//=============================================================================
/**
 * @file      Resource_List.h
 *
 * $Id$
 *
 * @author    James H. Hill
 */
//=============================================================================

#ifndef _GME_NAOMI_RESOURCE_LIST_H_
#define _GME_NAOMI_RESOURCE_LIST_H_

#include "GNC_Base_export.h"
#include <string>
#include <list>

/**
 * @struct GME_Naomi_Resource
 *
 * Resource for the complex type's attribute.
 */
struct GNC_BASE_Export GME_Naomi_Resource
{
  /// Name of the resource.
  std::string name_;

  /// Uri of the resource.
  std::string uri_;
};

/// Type definition for a list of resources.
typedef std::list <GME_Naomi_Resource> GME_Naomi_Resource_List;

#endif  // !defined _GME_NAOMI_RESOURCE_LIST_H_