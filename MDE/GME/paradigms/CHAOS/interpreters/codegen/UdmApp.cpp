// $Id$

#include "StdAfx.h"
#include "UdmApp.h"
#include "BE_Options.h"
#include "Utils/Utils.h"
#include "Manager.h"

//
// dummy function for UDM meta initialization
//
extern void dummy(void);

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
void CUdmApp::UdmMain (Udm::DataNetwork* backend,
                       Udm::Object focusObject,
                       set <Udm::Object> selectedObjects,
                       long param)
{
  bool retval =
    Utils::getPath ("Select output directory for source files:",
                    CUTS_BE_OPTIONS ()->output_directory_,
                    CUTS_BE_OPTIONS ()->output_directory_);

  if (!retval)
    return;

  CHAOS::RootFolder root = CHAOS::RootFolder::Cast (backend->GetRootObject());

  CUTS_CHAOS_Codegen_Manager codegen;
  std::string message;

  if (codegen.handle (root))
    message = "Successfully generated implementation files";
  else
    message = "Failed to generate implementation files.";

  ::AfxMessageBox (message.c_str (), MB_ICONINFORMATION | MB_OK);
}
