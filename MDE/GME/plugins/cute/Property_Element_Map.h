// -*- C++ -*-

//=============================================================================
/**
 * @file        Property_Element_Map.h
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _CUTS_CUTE_PROPERTY_ELEMENT_MAP_H_
#define _CUTS_CUTE_PROPERTY_ELEMENT_MAP_H_

#include "ace/Hash_Multi_Map_Manager_T.h"
#include "ace/Null_Mutex.h"
#include "ace/SString.h"
#include "cuts/config.h"

/// Type definition of the map type.
typedef ACE_Hash_Multi_Map_Manager <ACE_CString,
                                    GAME::Mga::Attribute,
                                    ACE_Hash <ACE_CString>,
                                    ACE_Equal_To <ACE_CString>,
                                    ACE_Null_Mutex>
                                    CUTS_CUTE_Property_Element_Map;

#endif  // !defined _CUTS_CUTE_PROPERTY_ELEMENT_MAP_H_
