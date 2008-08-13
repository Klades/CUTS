// $Id$

#include "StdAfx.h"
#include "UdmApp.h"
#include "Utils/Utils.h"
#include "PICML/PICML.h"
#include "Isislab_Emulation.h"

//
// dummy function for UDM meta initialization
//
extern void dummy(void);

//
// outdir_
//
std::string CUdmApp::outdir_;

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
  std::string message = "Please specify output directory for ISISLab scripts";

  // If there is no output path specified
  if (!Utils::getPath (message, CUdmApp::outdir_, CUdmApp::outdir_))
    return;

  // Get the root object and visit it.
  Udm::Object root_obj = p_backend->GetRootObject();
  PICML::RootFolder root = PICML::RootFolder::Cast (root_obj);

  CUTS_Isislab_Emulation visitor (CUdmApp::outdir_);
  root.Accept (visitor);

  ::AfxMessageBox ("Successfully generated ISISLab scripts",
                   MB_OK | MB_ICONINFORMATION);
}
