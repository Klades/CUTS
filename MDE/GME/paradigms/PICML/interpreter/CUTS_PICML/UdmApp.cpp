// $Id$

#include "StdAfx.h"
#include "UdmApp.h"
#include "Main_Dialog.h"

#include "be/arch/ccm/ciao/CIAO_Manager.h"
#include "be/arch/ccm/opensplice/Manager.h"
#include "be/arch/ccm/rtidds/Manager.h"
#include "be/arch/ccm/tcpip/TCPIP_Manager.h"

#include "be/BE_Options.h"
#include "cuts/Auto_Functor_T.h"

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
void CUdmApp::UdmMain (Udm::DataNetwork* p_backend,
                       Udm::Object focusObject,
                       set <Udm::Object> selectedObjects,
                       long param)
{
  // Display main dialog and initialize it with current
  // backend options.
  Main_Dialog dialog (::AfxGetMainWnd ());

  dialog.opts_.output_dir_ = CUTS_BE_OPTIONS ()->output_directory_.c_str ();
  dialog.opts_.backends_.push_back ("Component Intergrated ACE ORB (CIAO)");
  dialog.opts_.backends_.push_back ("OpenSplice (in CCM)");
  dialog.opts_.backends_.push_back ("RTI-DDS (in CCM)");
  dialog.opts_.backends_.push_back ("TCP/IP (in CCM)");

  if (dialog.DoModal () == IDCANCEL)
    return;

  // Get the root folder for the project.
  PICML::RootFolder root = PICML::RootFolder::Cast (p_backend->GetRootObject());

  std::string message;

  typedef CUTS_BE_Manager * (* FACTORY_METHOD) (void);
  FACTORY_METHOD backend_factory = 0;

  // Initialize the backend options. Eventually, the user will
  // be able to set these via a dialog.
  switch (dialog.opts_.selected_backend_)
  {
  case 0:
    backend_factory = &CUTS_BE_CIAO::Manager::_create;
    break;

  case 1:
    backend_factory = &CUTS_BE_OpenSplice::Manager::_create;
    break;

  case 2:
    backend_factory = &CUTS_BE_RTIDDS::Manager::_create;
    break;

  case 3:
    backend_factory = &CUTS_BE_TCPIP::Manager::_create;
    break;
  }

  if (0 != backend_factory)
  {
    CUTS_BE_OPTIONS ()->output_directory_ = dialog.opts_.output_dir_.GetBuffer ();
    CUTS_BE_OPTIONS ()->exec_suffix_  = "_exec";

    // Create the manager from the factory.
    CUTS_Auto_Functor_T <CUTS_BE_Manager>
      manager (backend_factory (), &CUTS_BE_Manager::close);

    // Let the manager handle the root folder.
    if (manager->handle (root))
      message = "Successfully generated implementation files";
    else
      message = "Failed to generate implementation files.";

    // Display a status message to the user.
    if (!message.empty ())
      ::AfxMessageBox (message.c_str (), MB_ICONINFORMATION | MB_OK);
  }
  else
  {
    ::AfxMessageBox ("Unknown backend", MB_ICONINFORMATION | MB_OK);
  }
}
