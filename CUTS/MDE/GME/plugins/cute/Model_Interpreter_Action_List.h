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

#include "Property_Locator_Handler.h"

#include "cuts/config.h"

// Forward decl.
class CUTS_CUTE_Model_Interpreter_Action;

// Forward decl.
class CUTS_Property_Map;

/**
 * @file CUTS_CUTE_Model_Interpreter_Action_List
 */
class CUTS_CUTE_Model_Interpreter_Action_List :
  public ACE_Unbounded_Set <CUTS_CUTE_Model_Interpreter_Action *>,
  public CUTS_CUTE_Property_Locator_Handler
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

  /**
   * The attribute has one or more parameters defined in its text.
   *
   * @param[in]         attr        The target attribute
   * @param[in]         params      The identified parameters
   */
  virtual int handle_attribute (GAME::Mga::Attribute_in attr,
                                const ACE_Unbounded_Set <ACE_CString> & params);

  /**
   * The name on the specified element has one or more parameters
   * defined in its text.
   *
   * @param[in]         folder      The target folder
   * @param[in]         params      The identified parameters
   */
  virtual int handle_name (GAME::Mga::Object_in folder,
                           const ACE_Unbounded_Set <ACE_CString> & params);
};


#if defined (__CUTS_INLINE__)
#include "Model_Interpreter_Action_List.inl"
#endif

#endif  // !defined _CUTS_CUTE_PROPERTY_ELEMENT_MAP_H_
