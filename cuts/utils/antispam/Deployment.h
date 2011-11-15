// -*- C++ -*-

//=============================================================================
/**
 * @file        Deployment.h
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _CUTS_DEPLOYMENT_H_
#define _CUTS_DEPLOYMENT_H_

#include "Antispam_export.h"
#include "ace/SString.h"
#include "ace/Hash_Map_Manager.h"
#include "ace/Null_Mutex.h"

/// Forward decl.
class CUTS_Host;

/**
 * @class CUTS_Component_Manager
 */
class CUTS_ANTISPAM_Export CUTS_Deployment
{
public:
  typedef ACE_Hash_Map_Manager <ACE_CString,
                                CUTS_Host *,
                                ACE_Null_Mutex> map_type;

  /// Default constructor
  CUTS_Deployment (void);

  /// Destructor
  ~CUTS_Deployment (void);

  int create (const ACE_CString & name, CUTS_Host * & host);

  map_type & items (void);

  const map_type & items (void) const;

private:
  /// Collection of component types.
  map_type map_;
};

#endif  // !defined _CUTS_DEPLOYMENT_H_
