// $Id$

#include "stdafx.h"
#include "Model_Interpreter.h"

#if !defined (__CUTS_INLINE__)
#include "Model_Interpreter.inl"
#endif

#include "game/ComponentEx.h"
#include "game/Transaction.h"

#include "cuts/utils/Property_Map.h"
#include "boost/bind.hpp"

//
// handle_config
//
void CUTS_CUTE_Model_Interpreter::
handle_config (const CUTS_Property_Map & config)
{
  try
  {
    do
    {
      // Substitute the template parameters.
      GAME::Transaction t (this->project_);
      this->actlist_.handle_replace (config);
      t.commit ();
    } while (false);

    try
    {
      // Load the specified interpreter.
      GAME::ComponentEx interpreter =
        GAME::ComponentEx::impl_type::_load (this->interpreter_.c_str ());

      // Set the parameter(s) for the interpreter. This includes setting
      // all the default parameters for the interpreter.
      interpreter->interactive (false);

      for (CUTS_Property_Map::map_type::CONST_ITERATOR iter (this->params_.map ()); !iter.done (); ++ iter)
        interpreter->parameter (iter->key ().c_str (), iter->item ().c_str ());

      // Execute the interpreter.
      interpreter->initialize (this->project_);
      interpreter->invoke (this->project_,
                           this->target_,
                           this->selected_,
                           this->flags_);
    }
    catch (...)
    {
      UINT type = MB_ICONWARNING | MB_OK;
      ::AfxMessageBox ("caught unknown exception", type);
    }

    do
    {
      // Reset the values of the template.
      GAME::Transaction t (this->project_);
      this->actlist_.handle_reset ();

      t.commit ();
    } while (false);
  }
  catch (...)
  {
    this->project_.abort_transaction ();
  }
}
