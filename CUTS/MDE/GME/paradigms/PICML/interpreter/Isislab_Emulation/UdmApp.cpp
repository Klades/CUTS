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
std::string CUdmApp::output_path_;

bool CUdmApp::interactive_ = true;

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

  if (CUdmApp::interactive_)
  {
    std::string message = "Please specify output directory for ISISLab scripts";

    // If there is no output path specified
    if (!Utils::getPath (message, CUdmApp::output_path_, CUdmApp::output_path_))
      return;
  }

  // Get the root object and visit it.
  Udm::Object root_obj = p_backend->GetRootObject();
  PICML::RootFolder root = PICML::RootFolder::Cast (root_obj);

  CUTS_Isislab_Emulation visitor (CUdmApp::output_path_);
  root.Accept (visitor);

  if (CUdmApp::interactive_)
  {
    ::AfxMessageBox ("Successfully generated ISISLab scripts",
                     MB_OK | MB_ICONINFORMATION);
  }
}

//
// SetParameter
//
void CUdmApp::
SetParameter (const std::string & name, const std::string & value)
{
  if (name == "output")
  {
    CUdmApp::output_path_ = value;
  }
  else if (name == "non-interactive")
  {
    CUdmApp::interactive_ = false;
  }
}
