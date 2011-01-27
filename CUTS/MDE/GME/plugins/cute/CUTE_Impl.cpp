// $Id$

#include "stdafx.h"
#include "CUTE_Impl.h"

#include "CUTE.h"
#include "CUTE_i.c"

#include "CUTE_Dialog.h"

#include "Model_Interpreter.h"
#include "Model_Interpreter_Action_List.h"
#include "Property_Locator.h"
#include "Unique_Property_Bag.h"
#include "Windows_Registry.h"

#include "game/be/Plugin_T.h"
#include "game/Project.h"
#include "game/Transaction.h"

#include "cuts/utils/Config_List_Parser_T.h"

#include "ace/Arg_Shifter.h"
#include "ace/ARGV.h"

#include <sstream>
#include <fstream>

GAME_DECLARE_PLUGIN (CUTE_Plugin, CUTS_CUTE);

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
: GAME::Plugin_Impl ("CUTS Template Engine", "CUTS.Plugin.CUTE")
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
int CUTS_CUTE::invoke_ex (GAME::Project project,
                          GAME::FCO_in focus,
                          std::vector <GAME::FCO> & selected,
                          long flags)
{
  try
  {
    // Get a list of the interpreters for this project.
    CUTS_CUTE_Interpreter_List interpreters;
    this->get_interpreters (project, interpreters);

    // Let the user select the configuration and interpreter.
    CUTS_CUTE_Dialog dialog (::AfxGetMainWnd ());
    dialog.interpreter_list (&interpreters);

    if (IDCANCEL == dialog.DoModal ())
      return 0;

    switch (dialog.option ())
    {
    case 0:
      // Handle the generation of the configuration file.
      this->handle_generate (project,
                             focus,
                             selected,
                             flags,
                             dialog.configuration_filename ().GetString ());
      break;

    case 1:
      {
        // Locate the selected interpreter.
        ACE_CString prog_id;
        interpreters.find (dialog.selected_interpreter ().GetString (), prog_id);

        // Handle the intepretation of the model.
        this->handle_interpret (project,
                                focus,
                                selected,
                                flags,
                                dialog.configuration_filename ().GetString (),
                                prog_id.c_str (),
                                dialog.parameters ().GetString ());
        break;
      }
    }

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
get_interpreters (GAME::Project proj, CUTS_CUTE_Interpreter_List & list)
{
  GAME::Transaction t (proj, TRANSACTION_READ_ONLY);

  // Open the GAME component section in the registry.
  CUTS_Windows_Registry_Key components;

  if (0 != components.open (HKEY_CURRENT_USER, "Software\\GME\\Components"))
    return;

  char description[255];

  // Iterate over all the components.
  CUTS_Windows_Registry_Key component, associated, paradigm;
  CUTS_Windows_Registry_Key_Iterator key_iter (components);
  const std::string paradigm_name = proj.paradigm_name ();

  for ( ; !key_iter.done (); key_iter.advance ())
  {
    // Open the component and its associated paradigms.
    if (0 != component.open (components, key_iter.name ()))
      continue;
    else if (0 != associated.open (component, "Associated"))
      continue;
    else if (0 != associated.get_value (paradigm_name.c_str ()))
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

//
// handle_interpret
//
int CUTS_CUTE::
handle_interpret (GAME::Project project,
                  GAME::FCO_in focus,
                  std::vector <GAME::FCO> & selected,
                  long flags,
                  const char * config_file,
                  const char * prog_id,
                  const char * parameters)
{
  // First, let's convert the parameters into a property map. This
  // way it will be a LOT easier to pass the configuration to the
  // selected model interpreter.
  CUTS_Property_Map params;
  params <<= parameters;

  CUTS_CUTE_Model_Interpreter_Action_List actlist;

  do
  {
    // Next, locate all attributes with a template parameter. We are
    // going to cache the elements for later.
    GAME::Transaction t (project, TRANSACTION_READ_ONLY);

    CUTS_CUTE_Property_Locator locator (actlist);
    project.root_folder ()->accept (&locator);
  } while (0);

  // Then, parse the configuration file specified by the end-user
  // in the dialog. After parsing each configuration, we will
  // interpret the model using the configuration.
  CUTS_CUTE_Model_Interpreter interpreter (actlist,
                                           params,
                                           project,
                                           focus,
                                           selected,
                                           flags);

  // Get the program id for the selected interpreter.
  interpreter.interpreter (prog_id);

  CUTS_Config_List_Parser_T <CUTS_CUTE_Model_Interpreter> parser (interpreter);
  parser.parse (config_file);

  ::AfxMessageBox ("Successfully applied template configurations");
  return 0;
}

//
// handle_generate
//
int CUTS_CUTE::
handle_generate (GAME::Project project,
                 GAME::FCO_in fco,
                 std::vector <GAME::FCO> & selected,
                 long flags,
                 const char * config_file)
{
  CUTS_CUTE_Unique_Property_Bag bag;

  do
  {
    GAME::Transaction t (project, TRANSACTION_READ_ONLY);

    // Locate all unique parameters in the model.
    CUTS_CUTE_Property_Locator locator (bag);
    project.root_folder ()->accept (&locator);
  } while (0);

  // Open the configuration for writing. Right now, let's just overwrite
  // the file's contents.
  std::ofstream outfile;
  outfile.open (config_file);

  if (!outfile.is_open ())
    return -1;

  outfile << "config ([INSERT NAME]) {" << std::endl;

  CUTS_CUTE_Unique_Property_Bag::CONST_ITERATOR iter (bag.items ());

  for ( ; !iter.done (); ++ iter)
    outfile << "  " << *iter << "=" << std::endl;

  outfile << "}" << std::endl;

  outfile.close ();
  return 0;
}
