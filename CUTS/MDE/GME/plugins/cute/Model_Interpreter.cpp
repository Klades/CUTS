// $Id$

#include "stdafx.h"
#include "Model_Interpreter.h"

#if !defined (__CUTS_INLINE__)
#include "Model_Interpreter.inl"
#endif

#include "game/ComponentEx.h"

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
      GME::ComponentEx interpreter (this->interpreter_.c_str ());

      // Execute the interpreter.
      interpreter.invoke (this->project_,
                          this->target_,
                          this->selected_.items (),
                          this->flags_);
    }
    catch (...)
    {

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
