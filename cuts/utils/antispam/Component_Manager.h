// -*- C++ -*-

//=============================================================================
/**
 * @file        Component_Manager.h
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _CUTS_COMPONENT_MANAGER_H_
#define _CUTS_COMPONENT_MANAGER_H_

#include "Antispam_export.h"
#include "ace/SString.h"
#include "ace/Hash_Map_Manager.h"
#include "ace/Null_Mutex.h"

/// Forward decl.
class CUTS_Component;

/**
 * @class CUTS_Component_Manager
 */
class CUTS_ANTISPAM_Export CUTS_Component_Manager
{
public:
  typedef ACE_Hash_Map_Manager <ACE_CString,
                                CUTS_Component *,
                                ACE_Null_Mutex> map_type;

  /// Default constructor
  CUTS_Component_Manager (void);

  /// Destructor
  ~CUTS_Component_Manager (void);

  int create (const ACE_CString & name, CUTS_Component * & type);

  map_type & items (void);

  const map_type & items (void) const;

private:
  /// Collection of component types.
  map_type map_;
};

#endif  // !defined _CUTS_COMPONENT_MANAGER_H_
