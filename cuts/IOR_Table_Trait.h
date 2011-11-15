// -*- C++ -*-

//=============================================================================
/**
 * @file        IOR_File_Trait.h
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _CUTS_IOR_TABLE_TRAIT_H_
#define _CUTS_IOR_TABLE_TRAIT_H_

#include "tao/corba.h"
#include "IOR_Table_Trait_export.h"

/**
 * @struct CUTS_IOR_Table_Trait
 */
struct CUTS_IORTABLE_TRAIT_Export CUTS_IOR_Table_Trait
{
public:
  /// Pre-assigned id for the trait.
  static const int ID = 1;

  /**
   * Notification for activating an object.
   *
   * @param[in]       obj         Object undergoing activation
   * @param[in]       value       Value of the trait
   */
  static int handle_activate (::CORBA::Object_ptr obj, const ACE_CString & value);

  /**
   * Notification for deactivating an object.
   *
   * @param[in]       obj         Object undergoing deactivation
   * @param[in]       value       Value of the trait
   */
  static int handle_deactivate (::CORBA::Object_ptr obj, const ACE_CString & value);
};

#endif  // !defined _CUTS_IOR_TABLE_TRAIT_H_
