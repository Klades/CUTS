///////////////////////////////////////////////////////////////////////////
// RawComponent.cpp, the main RAW COM component implementation file
// This is the file (along with its header RawComponent.h)
// that the component implementor is expected to modify in the first place
//
///////////////////////////////////////////////////////////////////////////
#include "stdafx.h"

#include "ComHelp.h"
#include "GMECOM.h"
#include "ComponentConfig.h"
#include "UdmConfig.h"
#include "RawComponent.h"

// Udm includes
#include "UdmBase.h"
#include "Uml.h"
#include "UmlExt.h"

#ifdef _USE_DOM
  #include "UdmDOM.h"
#endif

#include "UdmGme.h"
#include "UdmStatic.h"
#include "UdmUtil.h"

#include "UdmApp.h"

// Global config object
_config config;

#include "game/mga/Project.h"
#include "be/BE_Options.h"

//
// Initialize
//
STDMETHODIMP RawComponent::Initialize (struct IMgaProject * proj)
{
  return S_OK;
}


//
// Invoke
//
STDMETHODIMP RawComponent::
Invoke (IMgaProject* project, IMgaFCOs *models, long param)
{
#ifdef SUPPORT_OLD_INVOKE
  CComPtr<IMgaFCO> focus;
  CComVariant parval = param;
  return InvokeEx(gme, focus, selected, parvar);
#else
  if (interactive)
    AfxMessageBox ("This component does not support the obsolete invoke mechanism");
  return E_MGA_NOT_SUPPORTED;
#endif
}

#ifdef _DYNAMIC_META
//
// Dummy function for UDM meta initialization
//
void dummy (void)
{

}
#endif

//
// InvokeEx
//
STDMETHODIMP RawComponent::InvokeEx (IMgaProject *project,
                                     IMgaFCO *currentobj,
                                     IMgaFCOs *selectedobjs,
                                     long param)
{
  // Calling the user's initialization function
  if (CUdmApp::Initialize ())
    return S_FALSE;

  CComPtr <IMgaProject> ccpProject (project);

  try
  {
    if (interactive)
    {
      CComBSTR projname;
      CComBSTR focusname = "<nothing>";

      CComPtr <IMgaTerritory> terr;

      COMTHROW (ccpProject->CreateTerritory (NULL, &terr));

      // Loading the project
      using namespace META_NAMESPACE;
      UdmGme::GmeDataNetwork dngBackend (META_NAMESPACE::diagram);

      try
      {
        // Opening backend
        dngBackend.OpenExisting (ccpProject, Udm::CHANGES_LOST_DEFAULT);

        CComPtr <IMgaFCO> ccpFocus(currentobj);
        Udm::Object currentObject;

        if (ccpFocus)
          currentObject = dngBackend.Gme2Udm (ccpFocus);

        set<Udm::Object> selectedObjects;

        CComPtr <IMgaFCOs> ccpSelObject(selectedobjs);

        MGACOLL_ITERATE (IMgaFCO,ccpSelObject)
        {
          Udm::Object currObj;
          if(MGACOLL_ITER)
          {
            currObj=dngBackend.Gme2Udm(MGACOLL_ITER);
          }

          selectedObjects.insert(currObj);
        }
        MGACOLL_ITERATE_END;

        //=====================================================================
        // @@ BEGIN PREPROCESSING METHODS

        this->preprocess (project);

        // @@ END PREPROCESSING METHODS
        //=====================================================================

        // Calling the main entry point
        CUdmApp::UdmMain (&dngBackend,
                          currentObject,
                          selectedObjects,
                          param);

        //=====================================================================
        // @@ BEGIN POSTPROCESSING METHODS

        this->postprocess (project);

        // @@ END POSTPROCESSING METHODS
        //=====================================================================

        // Closing backend
        dngBackend.CloseWithUpdate ();
      }
      catch(udm_exception &exc)
      {
        // Close GME Backend (we may close it twice, but GmeDataNetwork handles it)
        dngBackend.CloseNoUpdate ();

        AfxMessageBox (exc.what (), MB_ICONERROR | MB_OK);
        return S_FALSE;
      }
    }
  }
  catch (udm_exception &exc)
  {
    AfxMessageBox (exc.what());
    return S_FALSE;
  }
  catch (...)
  {
    ccpProject->AbortTransaction ();
    AfxMessageBox ("An unexpected error has occured during the interpretation process.");
    return E_UNEXPECTED;
  }

  return S_OK;
}

//
// ObjectsInvokeEx
//
STDMETHODIMP RawComponent::ObjectsInvokeEx (IMgaProject *project,
                                            IMgaObject *currentobj,
                                            IMgaObjects *selectedobjs,
                                            long param)
{
  if (interactive)
  {
    AfxMessageBox("Tho ObjectsInvoke method is not implemented");
  }
  return E_MGA_NOT_SUPPORTED;
}

//
// get_ComponentParameter
//
STDMETHODIMP RawComponent::get_ComponentParameter (BSTR name,
                                                   VARIANT *pVal)
{
  return S_OK;
}

//
// get_ComponentParameter
//
STDMETHODIMP RawComponent::put_ComponentParameter (BSTR name,
                                                   VARIANT newVal)
{
  return S_OK;
}

//
// preprocess
//
int RawComponent::preprocess (IMgaProject * proj)
{
  // Initialize the project's name.
  GAME::Mga::Project project (proj);
  CUTS_BE_OPTIONS ()->project_name_ = project.name ();

  // Initialize the output directory.
  GAME::Mga::Folder root = project.root_folder ();
  CUTS_BE_OPTIONS ()->output_directory_ = root->registry_value ("__OutputDir__/CUTS_PICML");

  return 0;
}

//
// postprocess
//
int RawComponent::postprocess (IMgaProject * proj)
{
  // Get the root folder for the project.
  GAME::Mga::Project project (proj);
  GAME::Mga::Folder root = project.root_folder ();

  // Cache the output directory for future use.
  root->registry_value ("__OutputDir__/CUTS_PICML", CUTS_BE_OPTIONS ()->output_directory_);

  return 0;
}
