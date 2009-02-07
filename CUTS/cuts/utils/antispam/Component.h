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

#include "ace/Hash_Map_Manager_T.h"
#include "ace/Null_Mutex.h"
#include "Port.h"

/**
 * @class CUTS_Component
 */
class CUTS_ANTISPAM_Export CUTS_Component
{
public:
  /// Type definition of the port map.
  typedef ACE_Hash_Map_Manager <ACE_CString,
                                CUTS_Input_Event_Port *,
                                ACE_Null_Mutex> input_event_map_type;

  typedef ACE_Unbounded_Set <CUTS_Input_Event_Port *> start_type;

  /// Constructor.
  CUTS_Component (void);

  /// Destructor.
  ~CUTS_Component (void);

  CUTS_Input_Event_Port * new_input_event (const ACE_CString & name,
                                           bool start = false);

  const input_event_map_type & input_events (void) const;

  const start_type & start (void) const;

private:
  /// Collection of input ports.
  input_event_map_type input_events_;

  /// Collection of input event ports that
  start_type start_;
};

#if defined (__CUTS_INLINE__)
#include "Component.inl"
#endif

#endif  // !defined _CUTS_ANTISPAM_COMPONENT_H_
