// -*- C++ -*-

//=============================================================================
/**
 * @file          Port_Agent_Set.h
 *
 * $Id$
 *
 * @author        James H. Hill
 */
//=============================================================================

#ifndef _CUTS_PORT_AGENT_SET_H_
#define _CUTS_PORT_AGENT_SET_H_

#include "ace/Hash_Map_Manager_T.h"
#include "ace/Null_Mutex.h"

// Forward decl.
class CUTS_Port_Agent;

/// Type definition for a collection of CUTS_Port_Agent objects.
typedef
  ACE_Hash_Map_Manager_Ex <CUTS_Port_Agent *,
                           size_t,
                           ACE_Pointer_Hash <CUTS_Port_Agent *>,
                           ACE_Equal_To <CUTS_Port_Agent *>,
                           ACE_Null_Mutex>
                           CUTS_Port_Agent_Set;

#endif
