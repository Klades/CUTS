// $Id$

#include "PICML/PICML.h"
#include "BE_Workspace_Generator_T.h"
#include "BE_Impl_Generator_T.h"

//
// CUTS_BE_Manager_T
//
template <typename BE_TYPE>
CUTS_BE_Manager_T <BE_TYPE>::CUTS_BE_Manager_T (void)
{

}

//
// ~CUTS_BE_Manager_T
//
template <typename BE_TYPE>
CUTS_BE_Manager_T <BE_TYPE>::~CUTS_BE_Manager_T (void)
{

}

//
// handle
//
template <typename BE_TYPE>
bool CUTS_BE_Manager_T <BE_TYPE>::
handle (const PICML::RootFolder & root)
{
  // Initialize the backend generator.
  CUTS_BE_Initialize_T <BE_TYPE>::generate (root);

  // Generate the executor implementation.
  CUTS_BE_Impl_Generator_T <BE_TYPE> exec_generator;
  PICML::RootFolder (root).Accept (exec_generator);

  // Generate the workspace/project files.
  CUTS_BE_Workspace_Generator_T <BE_TYPE> workspace;
  workspace.generate ();

  // Finalize the backend generator.
  CUTS_BE_Finalize_T <BE_TYPE>::generate (root);
  return true;
}
