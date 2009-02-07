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

#include "Component.h"

// Forward decl.
class CUTS_Input_Event_Port_Instance;

// Forward decl.
class CUTS_Antispam_Visitor;

/**
 * @class CUTS_Component_Instance
 */
class CUTS_ANTISPAM_Export CUTS_Component_Instance
{
public:
  typedef ACE_Hash_Map_Manager <ACE_CString,
                                CUTS_Input_Event_Port_Instance *,
                                ACE_Null_Mutex> input_event_port_type;

  typedef ACE_Unbounded_Set <CUTS_Input_Event_Port_Instance *> start_type;

  /// Constructor.
  CUTS_Component_Instance (const ACE_CString & name,
                           const CUTS_Component & type);

  /// Destructor.
  ~CUTS_Component_Instance (void);

  /**
   * Get the component's type.
   *
   * @return      Reference to the component's type.
   */
  const CUTS_Component & type (void) const;

  const ACE_CString & name (void) const;

  /**
   * Get the component's input events.
   *
   * @return      Reference to the input events.
   */
  const input_event_port_type & input_events (void) const;

  const start_type & start (void) const;

  void accept (CUTS_Antispam_Visitor & visitor);

private:
  /// Initialize the instance based on its type.
  void init (void);

  void new_input_event (const CUTS_Component::input_event_map_type::ENTRY & entry);

  void make_start (const CUTS_Input_Event_Port * port);

  /// Name of the component instance.
  ACE_CString name_;

  /// The type of the component.
  const CUTS_Component & type_;

  input_event_port_type input_events_;

  start_type start_;
};

#if defined (__CUTS_INLINE__)
#include "Component_Instance.inl"
#endif

#endif  // !defined _CUTS_COMPONENT_INSTANCE_H_
