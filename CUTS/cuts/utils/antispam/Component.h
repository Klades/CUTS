// -*- C++ -*-

//=============================================================================
/**
 * @file        Component.h
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _CUTS_ANTISPAM_COMPONENT_H_
#define _CUTS_ANTISPAM_COMPONENT_H_

#include "Behavior_Graph.h"

/**
 * @class CUTS_Component
 */
class CUTS_ANTISPAM_Export CUTS_Component
{
public:

  /// Constructor.
  CUTS_Component (const ACE_CString & name);

  /// Destructor.
  ~CUTS_Component (void);

  /**
   * Get the name of the component.
   */
  const ACE_CString & name (void) const;

  /**
   * Associate an input port with an output port.
   *
   * @param[in]       input       Name of the input port
   * @param[in]       output      Name of the output port
   */
  bool associate (const ACE_CString & input,
                  const ACE_CString & output,
                  bool create = true);

  bool get_port_details (const ACE_CString & name,
                         CUTS_Port_Details & details) const;

  bool get_port_details (CUTS_Behavior_Graph::vertex_descriptor,
                         CUTS_Port_Details & details) const;

  bool set_port_details (const ACE_CString & name,
                         const CUTS_Port_Details & details);

  bool set_port_details (CUTS_Behavior_Graph::vertex_descriptor,
                         const CUTS_Port_Details & details);

  /**
   * Count the number of ports.
   */
  size_t port_count (void) const;

  const CUTS_Behavior_Graph & behavior (void) const;

  /**
   * Locate a port in the component.
   *
   * @param[in]       name        Name of the port
   * @param[out]      vertex      The port in question.
   * @retval          true        Port is found (\a vertex is valid)
   * @retval          true        Port is not found (\a vertex is not valid)
   */
  bool find_port (const ACE_CString & name,
                  CUTS_Behavior_Graph::vertex_descriptor & vertex) const;

protected:
  /// Name of the component.
  ACE_CString name_;

  /// Behavior graph for the component.
  CUTS_Behavior_Graph graph_;
};

#if defined (__CUTS_INLINE__)
#include "Component.inl"
#endif

#endif  // !defined _CUTS_ANTISPAM_COMPONENT_H_
