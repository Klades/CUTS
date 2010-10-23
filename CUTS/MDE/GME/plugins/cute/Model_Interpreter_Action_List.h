// -*- C++ -*-

//=============================================================================
/**
 * @file        Model_Interpreter_Action_List.h
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _CUTS_CUTE_MODEL_INTERPRETER_ACTION_LIST_H_
#define _CUTS_CUTE_MODEL_INTERPRETER_ACTION_LIST_H_

#include "ace/Hash_Multi_Map_Manager_T.h"
#include "ace/Null_Mutex.h"
#include "ace/SString.h"
#include "cuts/config.h"

// Forward decl.
class CUTS_CUTE_Model_Interpreter_Action;

// Forward decl.
class CUTS_Property_Map;

/**
 * @file CUTS_CUTE_Model_Interpreter_Action_List
 */
class CUTS_CUTE_Model_Interpreter_Action_List :
  public ACE_Unbounded_Set <CUTS_CUTE_Model_Interpreter_Action *>
{
public:
  typedef ACE_Unbounded_Set <CUTS_CUTE_Model_Interpreter_Action *> base_type;

  typedef base_type::ITERATOR ITERATOR;

  typedef base_type::CONST_ITERATOR CONST_ITERATOR;

  /// Default constructor.
  CUTS_CUTE_Model_Interpreter_Action_List (void);

  /// Destructor.
  ~CUTS_CUTE_Model_Interpreter_Action_List (void);

  /// Invoke the CUTS_CUTE_Model_Interpreter_Action::replace () method.
  void handle_replace (const CUTS_Property_Map & map) const;

  /// Invoke the CUTS_CUTE_Model_Interpreter_Action::reset () method.
  void handle_reset (void) const;

  /// Reset the configuration list.
  void reset (void);
};


#if defined (__CUTS_INLINE__)
#include "Model_Interpreter_Action_List.inl"
#endif

#endif  // !defined _CUTS_CUTE_PROPERTY_ELEMENT_MAP_H_
