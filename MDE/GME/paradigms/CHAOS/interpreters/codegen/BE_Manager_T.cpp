// $Id$

#include "../../paradigms/CHAOS.h"
#include "BE_Workspace_Generator_T.h"
#include "BE_Impl_Generator_T.h"

//
// CUTS_BE_Manager_T
//
template <typename CONTEXT>
CUTS_BE_Manager_T <CONTEXT>::CUTS_BE_Manager_T (void)
{

}

//
// ~CUTS_BE_Manager_T
//
template <typename CONTEXT>
CUTS_BE_Manager_T <CONTEXT>::~CUTS_BE_Manager_T (void)
{

}

//
// handle
//
template <typename CONTEXT>
bool CUTS_BE_Manager_T <CONTEXT>::handle (const CHAOS::RootFolder & root)
{
  // Initialize the backend generator.
  CUTS_BE_Initialize_T <CONTEXT> init_gen (this->context_);
  init_gen.generate (root);
  // CUTS_BE::generate (root, init_gen);

  // Generate the executor implementation.
  CUTS_BE_Impl_Generator_T <CONTEXT> impl_gen (this->context_);
  impl_gen.generate (root);

  // Generate the workspace/project files.
  CUTS_BE_Workspace_Generator_T <CONTEXT> workspace (this->context_);
  workspace.generate ();

  // Finalize the backend generator.
  CUTS_BE_Finalize_T <CONTEXT> fini_gen (this->context_);
  fini_gen.generate (root);

  return true;
}
