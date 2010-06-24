// $Id$

#include "stdafx.h"
#include "CUTE_Impl.h"

#include "CUTE.h"
#include "CUTE_i.c"
#include "game/be/Plugin_T.h"

#include "CUTE_Dialog.h"
#include "Model_Interpreter.h"
#include "Model_Interpreter_Action_List.h"
#include "Property_Locator.h"
#include "Windows_Registry.h"

#include "cuts/utils/Config_List_Parser_T.h"

#include "ace/Arg_Shifter.h"
#include "ace/ARGV.h"

#include <sstream>

DECLARE_GAME_PLUGIN (CUTE_Plugin, CUTS_CUTE);

//
// operator <<= (CUTS_Property_Map & , const CString & )
//
bool operator <<= (CUTS_Property_Map & map, const CString & params)
{
  // Convert the string into an argv list.
  ACE_ARGV_T <char> argv (params.GetString (), true);

  // Initialize the shifter with the argv list.
  int argc = argv.argc ();
  ACE_Arg_Shifter_T <char> shifter (argc, argv.argv ());

  // Parse the command-line arguments using the shifter.
  const char * option, * value;

  while (shifter.is_anything_left ())
  {
    // Get the next option in the argument vector.
    while (shifter.is_anything_left () && !shifter.is_option_next ())
      shifter.consume_arg ();

    if (shifter.is_anything_left ())
    {
      // Get the current option and its value.
      option = shifter.get_current ();
      value = shifter.get_the_parameter (option);

      // Insert the values into map.
      map[option] = 0 != value ? value : "";
    }
  }

  return true;
}

//
// CUTS_CUTE
//
CUTS_CUTE::CUTS_CUTE (void)
: GAME::Plugin_Impl ("CUTS Template Engine", "CUTS.Plugin.CUTE", false)
{

}

//
// ~CUTS_CUTE
//
CUTS_CUTE::~CUTS_CUTE (void)
{

}

//
// invoke_ex
//
int CUTS_CUTE::invoke_ex (GAME::Project & project,
                          GAME::FCO & target,
                          std::vector <GAME::FCO> & selected,
                          long flags)
{
  try
  {
    // Load the interpreters for this paradigm.
    CUTS_CUTE_Interpreter_List interpreters;

    project.begin_transaction ();
    this->get_interpreters (project.paradigm_name ().c_str (), interpreters);
    project.commit_transaction ();

    // Let the user select the configuration and interpreter.
    CUTS_CUTE_Dialog dialog (::AfxGetMainWnd ());
    dialog.interpreter_list (&interpreters);

    if (IDOK == dialog.DoModal ())
    {
      // First, let's convert the parameters into a property map. This
      // way it will be a LOT easier to pass the configuration to the
      // selected model interpreter.
      CUTS_Property_Map params;
      params <<= dialog.parameters ();

      // Next, locate all attributes with a template parameter. We are
      // going to cache the elements for later.
      project.begin_transaction ();
      CUTS_CUTE_Model_Interpreter_Action_List actlist;
      CUTS_CUTE_Property_Locator locator (actlist);
      project.root_folder ().accept (locator);
      project.commit_transaction ();

      // Then, parse the configuration file specified by the end-user
      // in the dialog. After parsing each configuration, we will
      // interpret the model using the configuration.

      CUTS_CUTE_Model_Interpreter interpreter (actlist,
                                               params,
                                               project,
                                               target,
                                               selected,
                                               flags);

      // Get the program id for the selected interpreter.
      ACE_CString prog_id;
      interpreters.find (dialog.selected_interpreter ().GetString (), prog_id);
      interpreter.interpreter (prog_id);

      CUTS_Config_List_Parser_T <CUTS_CUTE_Model_Interpreter> parser (interpreter);
      parser.parse (dialog.configuration_filename ().GetString ());
    }

    ::AfxMessageBox ("Successfully applied template configurations");
    return 0;
  }
  catch (const GAME::Failed_Result & ex)
  {
    std::ostringstream ostr;
    ostr << "failed result: [0x" << std::hex
         << ex.value () << "]" << std::endl;

    ::AfxMessageBox (ostr.str ().c_str ());
  }
  catch (const GAME::Exception & )
  {
  }

  return -1;
}

//
// get_interpreters
//
void CUTS_CUTE::
get_interpreters (const char * paradigm_name, CUTS_CUTE_Interpreter_List & list)
{
  // Open the GAME component section in the registry.
  CUTS_Windows_Registry_Key components;

  if (0 != components.open (HKEY_CURRENT_USER, "Software\\GAME\\Components"))
    return;

  char description[255];

  // Iterate over all the components.
  CUTS_Windows_Registry_Key component, associated, paradigm;
  CUTS_Windows_Registry_Key_Iterator key_iter (components);

  for ( ; !key_iter.done (); key_iter.advance ())
  {
    // Open the component and its associated paradigms.
    if (0 != component.open (components, key_iter.name ()))
      continue;
    else if (0 != associated.open (component, "Associated"))
      continue;
    else if (0 != associated.get_value (paradigm_name))
      continue;
    else if (0 != component.get_value ("Description",
                                       description,
                                       sizeof (description)))
    {
      continue;
    }
    else
    {
      list.bind (description, key_iter.name ());
    }
  }
}
