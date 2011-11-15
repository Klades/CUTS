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

#ifndef _CUTS_IOR_FILE_TRAIT_H_
#define _CUTS_IOR_FILE_TRAIT_H_

#include "tao/corba.h"
#include "CUTS_export.h"

/**
 * @struct CUTS_IOR_File_Trait
 */
struct CUTS_Export CUTS_IOR_File_Trait
{
public:
  /// Pre-assigned id for the trait.
  static const int ID = 0;

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

#endif  // !defined _CUTS_IOR_FILE_TRAIT_H_
