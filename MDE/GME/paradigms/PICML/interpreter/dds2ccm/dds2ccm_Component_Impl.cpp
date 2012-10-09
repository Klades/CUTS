// $Id$

#include "StdAfx.h"
#include "dds2ccm_Component.h"
#include "dds2ccm_Component_Impl.h"
#include "game/mga/utils/Project_Settings.h"

#include "game/mga/Transaction.h"
#include "game/mga/Utils.h"
#include "game/mga/component/Interpreter_T.h"

#include "game/mga/Project.h"
#include "game/mga/Errors.h"
#include "Event_Creator.h"

GAME_DECLARE_INTERPRETER (dds2ccm_Component, dds2ccm_Component_Impl);

//
//dds2ccm_Component_Impl
//
dds2ccm_Component_Impl::dds2ccm_Component_Impl (void)
: GAME::Mga::Interpreter_Impl_Base ("dds2ccm Generator",
                                    "PICML",
                                    "PICML.Interpreter.dds2ccm")
{

}

//
//~dds2ccm_Component_Impl
//
dds2ccm_Component_Impl::~dds2ccm_Component_Impl (void)
{

}

//
//invoke ex
//
int dds2ccm_Component_Impl::
invoke_ex (GAME::Mga::Project project,
           GAME::Mga::FCO_in focus,
           std::vector <GAME::Mga::FCO> & selected,
           long flags)
{
  using GAME::Mga::RootFolder;

  GAME::Mga::Transaction t (project);

  try
  {
    // Visit the RootFolder. We are going to create the dds2ccm events
    // in the supplied target folder. We use a seperate IDL folder so it
    // can be easily removed from the model.

    RootFolder root_folder = project.root_folder ();

    dds2ccm::Event_Creator creator;
    root_folder->accept (&creator);

    // Commit our changes to the model.
    t.commit ();

    return 0;
  }
  catch (GAME::Mga::Failed_Result & ex)
  {
    std::string msg;
    GAME::Mga::ERRORS::instance ()->lookup (ex.value (), msg);

    ::AfxMessageBox (msg.c_str (), MB_ICONERROR);
  }
  catch (GAME::Mga::Exception & ex)
  {
    // Abort the current transaction.
    t.abort ();

    // Display message box to the user.
    ::AfxMessageBox (ex.message ().c_str ());
  }

  return -1;
}

