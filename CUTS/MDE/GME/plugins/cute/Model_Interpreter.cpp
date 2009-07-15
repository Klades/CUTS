// $Id$

#include "stdafx.h"
#include "Model_Interpreter.h"

#if !defined (__CUTS_INLINE__)
#include "Model_Interpreter.inl"
#endif

#include "game/ComponentEx.h"
#include "cuts/utils/Property_Map.h"

//
// ~CUTS_CUTE_Model_Interpreter
//
CUTS_CUTE_Model_Interpreter::~CUTS_CUTE_Model_Interpreter (void)
{
  for (property_manager_map::ITERATOR iter (this->config_mgr_);
       !iter.done ();
       ++ iter)
  {
    delete iter->item ();
  }
}

//
// base_config
//
void CUTS_CUTE_Model_Interpreter::
base_config (CUTS_Property_Map & config, const std::string & basename)
{
  CUTS_Property_Map * base_config = 0;

  if (0 == this->config_mgr_.find (basename.c_str (), base_config))
    config.join (*base_config, true);
}

//
// handle_config
//
void CUTS_CUTE_Model_Interpreter::
handle_config (const CUTS_Property_Map & config)
{
  try
  {
    // Store a duplicate of the configuration just in case it
    // is used a base configuration in other configurations.
    CUTS_Property_Map * dup_config = 0;

    ACE_NEW (dup_config,
             CUTS_Property_Map (config));

    if (0 != dup_config)
    {
      ACE_CString config_name;
      config.get ("config.name", config_name);

      this->config_mgr_.bind (config_name, dup_config);
    }

    // Substitute the template parameters.
    this->project_.begin_transaction ();
    this->actlist_.handle_replace (config);
    this->project_.commit_transaction ();

    try
    {
      // Load the specified interpreter.
      GME::ComponentEx interpreter (this->interpreter_.c_str ());

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
                          this->selected_.items (),
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
