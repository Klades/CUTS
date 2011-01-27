// $Id$

#include "stdafx.h"
#include "Model_Interpreter_Action_List.h"

#if !defined (__CUTS_INLINE__)
#include "Model_Interpreter_Action_List.inl"
#endif

#include "Model_Interpreter_Action.h"

//
// reset
//
void CUTS_CUTE_Model_Interpreter_Action_List::reset (void)
{
  // Delete all the actions.
  for (ITERATOR iter (*this); !iter.done (); ++ iter)
    delete (*iter);

  // Pass control to the base class.
  base_type::reset ();
}

//
// handle_reset
//
void CUTS_CUTE_Model_Interpreter_Action_List::handle_reset (void) const
{
  for (CONST_ITERATOR iter (*this); !iter.done (); ++ iter)
    (*iter)->reset ();
}

//
// handle_replace
//
void CUTS_CUTE_Model_Interpreter_Action_List::
handle_replace (const CUTS_Property_Map & config) const
{
  for (CONST_ITERATOR iter (*this); !iter.done (); ++ iter)
    (*iter)->replace (config);
}

//
// handle_attribute
//
int CUTS_CUTE_Model_Interpreter_Action_List::
handle_attribute (GAME::Attribute_in attr,
                  const ACE_Unbounded_Set <ACE_CString> & params)
{
  // We have found an attribute with one or more template parameters.
  CUTS_CUTE_Model_Interpreter_Action * action = 0;

  ACE_NEW_THROW_EX (action,
                    CUTS_CUTE_Replace_Model_Attribute_Action (attr),
                    ACE_bad_alloc ());

  this->insert (action);
  return 0;
}

//
// handle_name
//
int CUTS_CUTE_Model_Interpreter_Action_List::
handle_name (GAME::Object_in obj,
             const ACE_Unbounded_Set <ACE_CString> & params)
{
  CUTS_CUTE_Model_Interpreter_Action * action = 0;

  ACE_NEW_THROW_EX (action,
                    CUTS_CUTE_Replace_Model_Name_Action (obj),
                    ACE_bad_alloc ());

  this->insert (action);
  return 0;
}
