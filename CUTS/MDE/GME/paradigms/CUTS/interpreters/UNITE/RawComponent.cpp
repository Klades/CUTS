// $Id$

#include "StdAfx.h"
#include "RawComponent.h"
#include "game/be/ComponentDLL.h"
#include "game/utils/Project_Settings.h"
#include "UniteVisitor.h"
#include "Utils/Utils.h"
#include "paradigm/CUTS.h"
#include "UdmGme.h"

#define INTERPRETER_NAME          "CUTS File Generator"
#define INTERPRETER_PARADIGMS     "CUTS"
#define INTERPRETER_PROGID        "MGA.Interpreter.CUTS"

///////////////////////////////////////////////////////////////////////////////
// class CIDL_Interpreter_Impl

//
// CIDL_Interpreter_Impl
//
CIDL_Interpreter_Impl::CIDL_Interpreter_Impl (void)
: GME::Interpreter_Impl_Base (INTERPRETER_NAME,
                              INTERPRETER_PARADIGMS,
                              INTERPRETER_PROGID,
                              false)
{

}

//
// ~CIDL_Interpreter_Impl
//
CIDL_Interpreter_Impl::~CIDL_Interpreter_Impl (void)
{

}

//
// invoke
//
int CIDL_Interpreter_Impl::
invoke_ex (GME::Project & project,
           GME::FCO & fco,
           GME::Collection_T <GME::FCO> & selected,
           long flags)
{
  try
  {
    // Initialize the UDM data network.
    UdmGme::GmeDataNetwork backend (CUTS::diagram);

    try
    {
      // Opening backend using current project.
      backend.OpenExisting (project.impl ());

      // Preprocess the project.
      this->preprocess (project);

      // Convert the current object to a UDM object.
      Udm::Object current;

      if (fco)
        current = backend.Gme2Udm (fco.impl ());

      // Convert the object collection to UDM objects.
      set <Udm::Object> objs;

      GME::Collection_T <GME::FCO>::iterator
        iter = selected.begin (), iter_end = selected.end ();

      for ( ; iter != iter_end; ++ iter)
        objs.insert (backend.Gme2Udm (iter->impl ()));

      // Now, we are ready to begin interpreting the model.
      const std::string message ("Please specify the output directory");

      // If there is no output path specified
      if (!Utils::getPath (message, this->output_, this->output_))
        return -1;

      // Get the root object and visit it.
      Udm::Object root_obj = backend.GetRootObject ();
      CUTS::RootFolder root = CUTS::RootFolder::Cast (root_obj);

      CUTS::UniteVisitor visitor (this->output_);
      root.Accept (visitor);

      ::AfxMessageBox ("Successfully generated CIDL files",
                       MB_OK | MB_ICONINFORMATION);

      // Post process the project.
      this->postprocess (GME::Project (project));

      // Closing backend
      backend.CloseWithUpdate ();
      return 0;
    }
    catch (const udm_exception & ex)
    {
      // Close the data network without updates.
      backend.CloseNoUpdate ();

      // Display error message to client.
      ::AfxMessageBox (ex.what (), MB_ICONERROR | MB_OK);
    }
  }
  catch (const udm_exception & ex)
  {
    ::AfxMessageBox (ex.what (), MB_ICONERROR | MB_OK);
  }

  return -1;
}

//
// preprocess
//
void CIDL_Interpreter_Impl::preprocess (GME::Project & project)
{
  GME::Utils::Project_Settings settings (project);
  this->output_ = settings.default_output_directory ("CUTS");
}

//
// postprocess
//
void CIDL_Interpreter_Impl::postprocess (GME::Project & project)
{
  GME::Utils::Project_Settings settings (project);
  settings.default_output_directory ("CUTS", this->output_);
}

///////////////////////////////////////////////////////////////////////////////
//

GME_RAWCOMPONENT_IMPL (CIDL, INTERPRETER_NAME);