// $Id$

#include "stdafx.h"
#include "Spring_Deployment.h"
#include "Spring_Deployment_Impl.h"
#include "Spring_Deployment_Visitor.h"

#include "game/be/Interpreter_T.h"
#include "Utils/Utils.h"

#include "UdmGme.h"
#include "PICML/PICML.h"

GAME_DECLARE_INTERPRETER (Quotas_Spring_Deployment, Quotas_Spring_Deployment_Impl);

//
// Quotas_Spring_Deployment
//
Quotas_Spring_Deployment_Impl::Quotas_Spring_Deployment_Impl (void)
: GAME::Interpreter_Impl_Base ("Quotas Spring Deployment", "Quotas.Interpreter.SpringDeployment", "PICML")
{

}

//
// ~Quotas_Spring_Deployment
//
Quotas_Spring_Deployment_Impl::~Quotas_Spring_Deployment_Impl (void)
{
}

//
// invoke_ex
//
int Quotas_Spring_Deployment_Impl::
invoke_ex (GAME::Project & project,
           GAME::FCO & fco,
           std::vector <GAME::FCO> & selected,
           long flags)
{
  AFX_MANAGE_STATE (::AfxGetStaticModuleState ());

  std::string path;

  if (!Utils::getPath ("Select output directory for deployment plan(s)", path))
    return 0;

  try
  {
    UdmGme::GmeDataNetwork dngBackend (PICML::diagram);

    try
    {
      // Opening the project in UDM.
      dngBackend.OpenExisting (project.impl ());

      // Visit the root folder of the project.
      PICML::RootFolder root = PICML::RootFolder::Cast (dngBackend.GetRootObject ());
      Quotas_Spring_Deployment_Visitor visitor (path);
      root.Accept (visitor);

      if (this->is_interactive_)
        ::AfxMessageBox ("Successfully generated descriptors");

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
