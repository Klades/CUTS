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

#include "ace/Null_Mutex.h"
#include "ace/Hash_Map_Manager.h"
#include "ace/SString.h"
#include "Component.h"

// Forward decl.
class CUTS_Component;

// Forward decl.
class CUTS_Component_Instance;

/**
 * @class CUTS_Component_Assembly
 */
class CUTS_ANTISPAM_Export CUTS_Component_Assembly : public CUTS_Component
{
public:
  typedef ACE_Hash_Map_Manager <ACE_CString,
                                CUTS_Component_Instance *,
                                ACE_Null_Mutex> instances_type;

  typedef
    std::vector <CUTS_Behavior_Graph::vertex_descriptor>
    start_type;

  /// Constructor.
  CUTS_Component_Assembly (const ACE_CString & name);

  /// Destructor.
  ~CUTS_Component_Assembly (void);

  instances_type & instances (void);

  const instances_type & instances (void) const;

  /**
   * Create a new instance of the component.
   *
   * @param[in]       name        Name of the instance
   * @param[in]       type        The instance's type info
   */
  int new_instance (const ACE_CString & name,
                    const CUTS_Component & type,
                    CUTS_Component_Instance * & inst);

  const start_type & start (void) const;

  bool set_start_port (const ACE_CString & name);

private:
  bool get_port (const ACE_CString & name,
                  CUTS_Behavior_Graph::vertex_descriptor & vertex);

  instances_type instances_;

  std::vector <CUTS_Behavior_Graph::vertex_descriptor> start_;
};

#if defined (__CUTS_INLINE__)
#include "Component_Assembly.inl"
#endif

#endif  // !defined _CUTS_COMPONENT_ASSEMBLY_H_
