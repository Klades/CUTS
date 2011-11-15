// -*- C++ -*-

//=============================================================================
/**
 * @file        Component_Instance.h
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _CUTS_COMPONENT_INSTANCE_H_
#define _CUTS_COMPONENT_INSTANCE_H_

#include "Behavior_Graph.h"
#include <vector>

// Forward decl.
class CUTS_Component_Assembly;

/**
 * @class CUTS_Component_Instance
 */
class CUTS_ANTISPAM_Export CUTS_Component_Instance
{
public:
  /// Type definition for the collection of ports.
  typedef
    std::vector <CUTS_Behavior_Graph::vertex_descriptor>
    ports_type;

  /**
   * Initializing constructor
   *
   * @param[in]         type        The component instance's type
   */
  CUTS_Component_Instance (const CUTS_Component_Assembly & assembly,
                           ports_type ports);

  /// Destructor.
  ~CUTS_Component_Instance (void);

  /**
   * Calculate the utilization of the component.
   *
   * @return            Utilization of the component.
   */
  double utilization (void) const;

  const CUTS_Component_Assembly & assembly (void) const;

  const ports_type & ports (void) const;

private:
  /// Parent assembly for the instance.
  const CUTS_Component_Assembly & assembly_;

  /// Ports for the instance in the assembly's behavior graph
  std::vector <CUTS_Behavior_Graph::vertex_descriptor> ports_;
};

#if defined (__CUTS_INLINE__)
#include "Component_Instance.inl"
#endif

#endif  // !defined _CUTS_COMPONENT_INSTANCE_H_
