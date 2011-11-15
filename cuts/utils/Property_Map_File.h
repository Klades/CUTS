// -*- C++ -*-

//=============================================================================
/**
 * @file        Property_Map_File.h
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _CUTS_PROPERTY_MAP_FILE_H_
#define _CUTS_PROPERTY_MAP_FILE_H_

#include "Utils_export.h"

// Forward decl.
class CUTS_Property_Map;

/**
 * @class CUTS_Property_Map_File
 */
class CUTS_UTILS_Export CUTS_Property_Map_File
{
public:
  /**
   * Initializing constructor. This will set the target property
   * map associated with the file.
   *
   * @param[in]         prop_map        Target property map
   */
  CUTS_Property_Map_File (CUTS_Property_Map & prop_map);

  /// Destructor.
  ~CUTS_Property_Map_File (void);

  /**
   * Read properties from the specified file.
   *
   * @param[in]       filename          Name of the file.
   */
  bool read (const char * filename);

  /**
   * Write the associated property map to the specified file.
   *
   * @param[in]       filename          Name of the file.
   */
  bool write (const char * filename) const;

private:
  /// Target property map for the file.
  CUTS_Property_Map & prop_map_;
};

#endif  // !defined _CUTS_PROPERTY_MAP_FILE_H_
