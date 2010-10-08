// $Id$

#include "StdAfx.h"
#include "UdmApp.h"
#include "Main_Dialog.h"
#include "Utils/Utils.h"

#include "be/CoWorkEr_Cache.h"
#include "be/BE_CUTS_Project.h"
#include "be/BE_Manager.h"
#include "be/BE_Manager_Factory.h"
#include "be/BE_Options.h"

#include "cuts/Auto_Functor_T.h"

//
// dummy function for UDM meta initialization
//
extern void dummy(void);

//
// repo_
//
CUTS_BE_Manager_Factory_Repo CUdmApp::repo_;

//
// Initialize
//
int CUdmApp::Initialize (void)
{
  return 0;
}

//
// UdmMain
//
void CUdmApp::UdmMain (Udm::DataNetwork* p_backend,
                       Udm::Object focusObject,
                       set <Udm::Object> selectedObjects,
                       long param)
{
  // Display main dialog and initialize it with current
  // backend options.
  CUTS_BE_Options * options = CUTS_BE_OPTIONS ();

  Main_Dialog dialog (options, ::AfxGetMainWnd ());

  if (dialog.DoModal () == IDCANCEL)
    return;

  // Get the root folder for the project.
  PICML::RootFolder root =
    PICML::RootFolder::Cast (p_backend->GetRootObject());

  std::string message;

  switch (options->option_)
  {
  case CUTS_BE_Options::OPT_GENERATE_SOURCE:
    {
      // Initialize the backend options. Eventually, the user will
      // be able to set these via a dialog.
      options->exec_suffix_  = "_exec";

      CUTS_BE_Manager_Factory * factory = dialog.factory ();

      if (factory)
      {
        // Create the manager from the factory.
        CUTS_Auto_Functor_T <CUTS_BE_Manager>
          manager (factory->create_manager (), &CUTS_BE_Manager::close);

        if (manager.get ())
        {
          // Store the manager in an auto functor that calls the
          // 'close' method once we leave this scope.

          // Let the manager handle the root folder.
          if (manager->handle (root))
            message = "Successfully generated implementation files";
          else
            message = "Failed to generate implementation files.";
        }
        else
        {
          message = "Failed to create manager";
        }
      }
      else
      {
        message = "CUTS_BE_CIAO is not loaded";
      }
    }
    break;
  }

  // Display a status message to the user.
  if (!message.empty ())
  {
    ::AfxMessageBox (message.c_str (),
                     MB_ICONINFORMATION | MB_OK);
  }
}
