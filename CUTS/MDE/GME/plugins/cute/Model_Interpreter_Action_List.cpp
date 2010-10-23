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
