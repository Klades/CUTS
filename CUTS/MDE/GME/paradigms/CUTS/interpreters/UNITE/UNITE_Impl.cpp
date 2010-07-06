// $Id$

#include "StdAfx.h"

#include "UNITE.h"
#include "UNITE_i.c"
#include "UNITE_Impl.h"

#include "game/be/Interpreter_T.h"
#include "game/utils/Project_Settings.h"
#include "game/GAME.h"

#include "paradigm/CUTS.h"

#include "UniteVisitor.h"
#include "Utils/Utils.h"

#include "UdmGme.h"

#define INTERPRETER_PARADIGMS     "CUTS"
#define INTERPRETER_NAME          "UNITE Configuration Generator"
#define INTERPRETER_PROGID        "CUTS.Interpreter.UNITE"

GAME_DECLARE_INTERPRETER (CUTS_UNITE_Interpreter, UNITE_Interpreter_Impl);

///////////////////////////////////////////////////////////////////////////////
// class UNITE_Interpreter_Impl

//
// UNITE_Interpreter_Impl
//
UNITE_Interpreter_Impl::UNITE_Interpreter_Impl (void)
: GAME::Interpreter_Impl_Base (INTERPRETER_NAME,
                               INTERPRETER_PARADIGMS,
                               INTERPRETER_PROGID)
{

}

//
// ~UNITE_Interpreter_Impl
//
UNITE_Interpreter_Impl::~UNITE_Interpreter_Impl (void)
{

}

//
// invoke
//
int UNITE_Interpreter_Impl::
invoke_ex (GAME::Project & project,
           GAME::FCO & fco,
           std::vector <GAME::FCO> & selected,
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

      std::vector <GAME::FCO>::iterator
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

      ::AfxMessageBox ("UNITE configuration file has been generated",
                       MB_OK | MB_ICONINFORMATION);

      // Post process the project.
      this->postprocess (GAME::Project (project));

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
void UNITE_Interpreter_Impl::preprocess (GAME::Project & project)
{
  GAME::utils::Project_Settings settings (project);
  this->output_ = settings.default_output_directory ("CUTS/UNITE");
}

//
// postprocess
//
void UNITE_Interpreter_Impl::postprocess (GAME::Project & project)
{
  GAME::utils::Project_Settings settings (project);
  settings.default_output_directory ("CUTS/UNITE", this->output_);
}
