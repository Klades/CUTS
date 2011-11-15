// $Id$

#include "stdafx.h"
#include "Pojo_Codegen_Impl.h"

#include "game/be/Interpreter_T.h"
#include "Utils/Utils.h"

#include "UdmGme.h"
#include "Pojo_Codegen_Manager.h"

GAME_DECLARE_INTERPRETER (Quotas_Pojo_Codegen, Quotas_Pojo_Codegen_Impl);

//
// Quotas_Spring_Deployment
//
Quotas_Pojo_Codegen_Impl::Quotas_Pojo_Codegen_Impl (void)
: GAME::Interpreter_Impl_Base ("Quotas Pojo Code Generator", "Quotas.Interpreter.PojoCodeGen", "PICML")
{

}

//
// ~Quotas_Spring_Deployment
//
Quotas_Pojo_Codegen_Impl::~Quotas_Pojo_Codegen_Impl (void)
{

}

//
// invoke_ex
//
int Quotas_Pojo_Codegen_Impl::
invoke_ex (GAME::Project & project,
           GAME::FCO & fco,
           std::vector <GAME::FCO> & selected,
           long flags)
{
  // Get the output directory for the code generation.
  std::string & outpath = CUTS_BE_OPTIONS ()->output_directory_;
  if (!::Utils::getPath ("Selecting output directory", outpath))
    return 0;

  try
  {
    // Initilize the backend in UDM.
    UdmGme::GmeDataNetwork dngBackend (PICML::diagram);

    try
    {
      // Opening the project in UDM.
      dngBackend.OpenExisting (project.impl ());
      CUTS_BE_OPTIONS ()->project_name_ = project.name ();

      // Generate the code for the project. The generation starts
      // at the project's root folder.
      PICML::RootFolder root_folder =
        PICML::RootFolder::Cast (dngBackend.GetRootObject ());

      Quotas_Pojo_Codegen_Manager manager;
      manager.handle (root_folder);

      if (this->is_interactive_)
        ::AfxMessageBox ("Successfully generated source code");

      // Closing backend with an update.
      dngBackend.CloseWithUpdate ();
      return 0;
    }
    catch (udm_exception & exc)
    {
      if (this->is_interactive_)
        ::AfxMessageBox (exc.what ());
    }

    // Close the backend with no update.
    dngBackend.CloseNoUpdate ();
  }
  catch (udm_exception & exc)
  {
    if (this->is_interactive_)
      ::AfxMessageBox (exc.what ());
  }

  return 0;
}
