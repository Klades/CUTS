// $Id$

#include "StdAfx.h"
#include "Code_Generation.h"
#include "Code_Generation_Impl.h"
#include "Main_Dialog.h"

#include "game/mga/component/Interpreter_T.h"
#include "game/mga/utils/Project_Settings.h"

#include "Main_Dialog.h"
#include "be/arch/ccm/ciao/CIAO_Manager.h"
#include "be/arch/ccm/coredx/Manager.h"
#include "be/arch/ccm/opensplice/Manager.h"
#include "be/arch/ccm/rtidds/Manager.h"
#include "be/arch/ccm/tcpip/TCPIP_Manager.h"
#include "be/BE_Options.h"
#include "cuts/Auto_Functor_T.h"

GAME_DECLARE_INTERPRETER (CodeGeneration, Code_Generation_Impl);

//
// Quotas_Integrator_Impl
//
Code_Generation_Impl::Code_Generation_Impl (void)
: GAME::Mga::Interpreter_Impl_Base ("CUTS Code Generation", "CUTS.Interpreter.PICML", "PICML"),
  selected_backend_ (-1)
{
  /// Note, this must match the order of the elements in GME or the wrong manager will be used.
  this->backends_.push_back (backend_t ("ciao", "Component Intergrated ACE ORB (CIAO)", &CUTS_BE_CIAO::Manager::_create));
  this->backends_.push_back (backend_t ("coredx", "CoreDX", &CUTS_BE_CoreDX::Manager::_create));
  this->backends_.push_back (backend_t ("opensplice", "OpenSplice", &CUTS_BE_OpenSplice::Manager::_create));
  this->backends_.push_back (backend_t ("rtidds", "RTI-DDS", &CUTS_BE_RTIDDS::Manager::_create));
  this->backends_.push_back (backend_t ("tcpip", "TCP/IP", &CUTS_BE_TCPIP::Manager::_create));
}

//
// ~Code_Generation_Impl
//
Code_Generation_Impl::~Code_Generation_Impl (void)
{
  ACE_Singleton <CUTS_BE_Options, ACE_Null_Mutex>::close ();
}

//
// initialize
//
int Code_Generation_Impl::initialize (GAME::Mga::Project project)
{
  GAME::Mga::Readonly_Transaction t (project);
//  GAME::Mga::Transaction t (project);

  // Store the name of the project.
  CUTS_BE_OPTIONS ()->project_name_ = project.name ();

  // Load the previous project settings.
  GAME::Mga::Project_Settings settings (project, "CUTS/CodeGeneration");
  settings.get_value ("OutputPath", this->output_);
  settings.get_value ("Backend", this->selected_backend_);

  return 0;
}

//
// invoke_ex
//
int Code_Generation_Impl::
invoke_ex (GAME::Mga::Project project,
           GAME::Mga::FCO focus,
           GAME::Mga::Collection_T <GAME::Mga::FCO> & selected,
           long flags)
{
  try
  {
    // Start our transaction
    //GAME::Mga::Readonly_Transaction transaction (project);
    GAME::Mga::Transaction transaction (project);

    if (this->is_interactive_)
    {
      Main_Dialog dialog (::AfxGetMainWnd ());

      // Initialize the dialog before showing it.
      dialog.opts_.output_dir_ = this->output_.c_str ();
      dialog.opts_.selected_backend_ = this->selected_backend_;

      for (size_t i = 0; i < this->backends_.size (); ++ i)
        dialog.opts_.backends_.push_back (this->backends_[i].name_.c_str ());

      // Show the dialog.
      if (dialog.DoModal () == IDCANCEL)
        return 0;

      // Store the selected values.
      this->selected_backend_ = dialog.opts_.selected_backend_;
      this->output_ = dialog.opts_.output_dir_.GetBuffer ();
    }

    std::string message;

    // Get the root folder for the project.
    PICML::RootFolder root = project.root_folder ();
    backend_t::FACTORY_METHOD factory = this->backends_[this->selected_backend_].factory_;

    if (0 != factory)
    {
      CUTS_BE_OPTIONS ()->output_directory_ = this->output_;
      CUTS_BE_OPTIONS ()->exec_suffix_  = "_exec";

      // Create the manager from the factory.
      CUTS_Auto_Functor_T <CUTS_BE_Manager> manager (factory (), &CUTS_BE_Manager::close);

      // Let the manager handle the root folder.
      if (manager->handle (root))
        message = "Successfully generated implementation files";
      else
        message = "Failed to generate implementation files.";

      // Display a status message to the user.
      if (this->is_interactive_ && !message.empty ())
        ::AfxMessageBox (message.c_str (), MB_ICONINFORMATION | MB_OK);
    }
    else
    {
      if (this->is_interactive_)
        ::AfxMessageBox ("Unknown backend", MB_ICONINFORMATION | MB_OK);
    }

    // Save the current selections for next time.
    GAME::Mga::Project_Settings settings (project, "CUTS/CodeGeneration");
    settings.set_value ("OutputPath", this->output_);
    settings.set_value ("Backend", this->selected_backend_);

    return 0;
  }
  catch (::GAME::Mga::Exception & ex)
  {
    ::AfxMessageBox (ex.message ().c_str ());
  }
}

//
// set_parameter
//
int Code_Generation_Impl::
set_parameter (const std::string & name, const std::string & value)
{
  if (name == "OutputPath")
  {
    this->output_ = value;
  }
  else if (name == "Backend")
  {
    for (size_t i = 0; i < this->backends_.size (); ++ i)
    {
      if (this->backends_[i].type_ == value)
      {
        this->selected_backend_ = i;
        break;
      }
    }
  }

  return 0;
}
