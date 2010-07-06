// $Id$

#include "stdafx.h"
#include "Model_Interpreter.h"

#if !defined (__CUTS_INLINE__)
#include "Model_Interpreter.inl"
#endif

#include "game/ComponentEx.h"
#include "cuts/utils/Property_Map.h"

//
// handle_config
//
void CUTS_CUTE_Model_Interpreter::
handle_config (const CUTS_Property_Map & config)
{
  try
  {
    // Substitute the template parameters.
    this->project_.begin_transaction ();
    this->actlist_.handle_replace (config);
    this->project_.commit_transaction ();

    try
    {
      // Load the specified interpreter.
      GAME::ComponentEx interpreter = GAME::ComponentEx::_load (this->interpreter_.c_str ());

      // Set the parameter(s) for the interpreter. This includes setting
      // all the default parameters for the interpreter.
      interpreter.parameter ("-non-interactive", "");

      for (CUTS_Property_Map::const_iterator iter (this->params_.map ());
           !iter.done ();
           ++ iter)
      {
        interpreter.parameter (iter->key ().c_str (), iter->item ().c_str ());
      }

      // Execute the interpreter.
      interpreter.invoke (this->project_,
                          this->target_,
                          this->selected_,
                          this->flags_);
    }
    catch (...)
    {
      UINT type = MB_ICONWARNING | MB_OK;
      ::AfxMessageBox ("caught unknown exception", type);
    }

    // Reset the values of the template.
    this->project_.begin_transaction ();
    this->actlist_.handle_reset ();
    this->project_.commit_transaction ();
  }
  catch (...)
  {
    this->project_.abort_transaction ();
  }
}
