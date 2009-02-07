// -*- C++ -*-

//=============================================================================
/**
 * @file        Component_Assembly.h
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _CUTS_COMPONENT_ASSEMBLY_H_
#define _CUTS_COMPONENT_ASSEMBLY_H_

#include "Antispam_export.h"
#include "ace/Null_Mutex.h"
#include "ace/Hash_Map_Manager.h"
#include "ace/SString.h"
#include "ace/Unbounded_Set.h"

// Forward decl.
class CUTS_Component_Instance;

// Forward decl.
class CUTS_Component;

// Forward decl.
class CUTS_Input_Event_Port_Instance;

/**
 * @class CUTS_Component_Assembly
 */
class CUTS_ANTISPAM_Export CUTS_Component_Assembly
{
public:
  typedef ACE_Hash_Map_Manager <ACE_CString,
                                CUTS_Component_Instance *,
                                ACE_Null_Mutex> instances_type;

  typedef ACE_Unbounded_Set <CUTS_Input_Event_Port_Instance *> start_type;

  /// Constructor.
  CUTS_Component_Assembly (void);

  /// Destructor.
  ~CUTS_Component_Assembly (void);

  const instances_type & instances (void) const;

  CUTS_Component_Instance * new_instance (const ACE_CString & name,
                                          const CUTS_Component & type);

  const start_type & start (void) const;

private:
  instances_type instances_;

  start_type start_;
};

#if defined (__CUTS_INLINE__)
#include "Component_Assembly.inl"
#endif

#endif  // !defined _CUTS_COMPONENT_ASSEMBLY_H_
