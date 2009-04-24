// $Id$

#include "stdafx.h"
#include "CUTE_Dialog.h"
#include "RawComponent.h"
#include "ComponentConfig.h"
#include "Property_Locator.h"
#include "Windows_Registry.h"
#include "game/be/ComponentDLL.h"
#include <sstream>

GME_RAWCOMPONENT_IMPL (CUTE, COMPONENT_NAME);

//
// CUTS_CUTE
//
CUTS_CUTE::CUTS_CUTE (void)
: GME::Plugin_Impl ("CUTS Template Engine", COCLASS_PROGID)
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
int CUTS_CUTE::invoke_ex (GME::Project & project,
                          GME::FCO & fco,
                          GME::Collection_T <GME::FCO> & selected,
                          long flags)
{
  try
  {
    // Load the interpreters for this paradigm.
    ACE_Unbounded_Set <ACE_CString> interpreters;
    this->get_interpreters (project.paradigm_name ().c_str (),
                            interpreters);

    // Let the user select the configuration and interpreter.
    CUTS_CUTE_Dialog dialog (::AfxGetMainWnd ());
    dialog.interpreter_list (&interpreters);

    if (IDOK == dialog.DoModal ())
    {
      // First, locate all objects with a template parameter. We are
      // going to cache the elements.
      CUTS_CUTE_Property_Locator locator;
      project.root_folder ().accept (locator);
    }

    return 0;
  }
  catch (const GME::Failed_Result & ex)
  {
    std::ostringstream ostr;
    ostr << "failed result: [0x" << std::hex
         << ex.value () << "]" << std::endl;

    ::AfxMessageBox (ostr.str ().c_str ());
  }
  catch (const GME::Exception & )
  {
  }

  return -1;
}

//
// get_interpreters
//
void CUTS_CUTE::
get_interpreters (const char * paradigm_name,
                  ACE_Unbounded_Set <ACE_CString> & list)
{
  // Open the GME component section in the registry.
  CUTS_Windows_Registry_Key components;

  if (0 != components.open (HKEY_CURRENT_USER, "Software\\GME\\Components"))
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
      list.insert (description);
    }
  }
}
