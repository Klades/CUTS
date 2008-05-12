// $Id$

#include "BE_Options.h"
#include "BE_Preprocessor.h"

#include "boost/bind.hpp"

#include <algorithm>
#include <sstream>
#include <fstream>

#include "BE_Workspace_Generators_T.h"
#include "BE_Project_Generators_T.h"

//
// CUTS_BE_Workspace_Generator_T
//
template <typename BE_TYPE>
CUTS_BE_Workspace_Generator_T <BE_TYPE>::
CUTS_BE_Workspace_Generator_T (void)
{

}

//
// ~CUTS_BE_Workspace_Generator_T
//
template <typename BE_TYPE>
CUTS_BE_Workspace_Generator_T <BE_TYPE>::
~CUTS_BE_Workspace_Generator_T (void)
{

}

//
// generate
//
template <typename BE_TYPE>
bool CUTS_BE_Workspace_Generator_T <BE_TYPE>::generate (void)
{
  // Construct the name of the workspace.
  std::string workspace (CUTS_BE_OPTIONS ()->project_name_);
  workspace.append ("_CUTS");

  // Open the workspace file for writing.
  if (CUTS_BE_Workspace_File_Open_T <BE_TYPE>::generate (workspace))
  {
    // Begin the workspace.
    CUTS_BE_Workspace_Begin_T <BE_TYPE>::generate (workspace);

    // We are writing all the implementation projects.
    std::for_each (
      CUTS_BE_PREPROCESSOR ()->impls ().graph ().begin (),
      CUTS_BE_PREPROCESSOR ()->impls ().graph ().end (),
      boost::bind (&CUTS_BE_Workspace_Generator_T::generate_impl_project,
                   this,
                   boost::bind (&CUTS_BE_Impl_Graph::Node_Map::value_type::second,
                                _1)));

    // We are writing all the stub projects.
    std::for_each (
      this->required_stubs_.begin (),
      this->required_stubs_.end (),
      boost::bind (&CUTS_BE_Workspace_Generator_T <BE_TYPE>::generate_stub_project,
                   this,
                   _1));

    // End the workspace.
    CUTS_BE_Workspace_End_T <BE_TYPE>::generate (workspace);

    // Close the workspace file.
    CUTS_BE_Workspace_File_Close_T <BE_TYPE>::generate ();
  }

  return true;
}

//
// write_impl_project
//
template <typename BE_TYPE>
void CUTS_BE_Workspace_Generator_T <BE_TYPE>::
generate_impl_project (const CUTS_BE_Impl_Node * node)
{
  if (CUTS_BE_Project_File_Open_T <
        BE_TYPE, CUTS_BE_Impl_Node>::generate (*node))
  {
    // Add the project to the workspace.
    CUTS_BE_Workspace_Project_Include_T <
      BE_TYPE, CUTS_BE_Impl_Node>::generate (*node);

    // Begin the project file.
    CUTS_BE_Project_File_Begin_T <
      BE_TYPE, CUTS_BE_Impl_Node>::generate (*node);

    // Write the project file.
    CUTS_BE_Project_Write_T <
      BE_TYPE, CUTS_BE_Impl_Node>::generate (*node);

    // End the project file.
    CUTS_BE_Project_File_End_T <
      BE_TYPE, CUTS_BE_Impl_Node>::generate (*node);

    // Close the project file.
    CUTS_BE_Project_File_Close_T <
      BE_TYPE, CUTS_BE_Impl_Node>::generate ();

    // Now, we need to add all the stubs for this implementation to the
    // collection of <required_stubs_>. We will iterate over this collection
    // once we have finished all the implementation projects.
    std::for_each (node->references_.begin (),
                   node->references_.end (),
                   boost::bind (&IDL_Node_Set::insert,
                                boost::ref (this->required_stubs_),
                                _1));
  }
}

//
// write_stub_project
//
template <typename BE_TYPE>
void CUTS_BE_Workspace_Generator_T <BE_TYPE>::
generate_stub_project (const CUTS_BE_IDL_Node * node)
{
  // Locate the node in the <visited_nodes_> before we continue
  // process. The main idea is to only process nodes that we
  // haven't seen yet.
  if (this->visited_nodes_.find (node) != this->visited_nodes_.end ())
    return;

  // Insert the node into the collection.
  this->visited_nodes_.insert (node);

  if (CUTS_BE_Project_File_Open_T <
      BE_TYPE, CUTS_BE_IDL_Node>::generate (*node))
  {
    // Begin the project file.
    CUTS_BE_Project_File_Begin_T <
      BE_TYPE, CUTS_BE_IDL_Node>::generate (*node);

    // Write the project file.
    CUTS_BE_Project_Write_T <
      BE_TYPE, CUTS_BE_IDL_Node>::generate (*node);

    // End the project file.
    CUTS_BE_Project_File_End_T <
      BE_TYPE, CUTS_BE_IDL_Node>::generate (*node);

    // Close the project file.
    CUTS_BE_Project_File_Close_T <BE_TYPE, CUTS_BE_IDL_Node>::generate ();

    // Include the project in the workspace.
    CUTS_BE_Workspace_Project_Include_T <
      BE_TYPE, CUTS_BE_IDL_Node>::generate (*node);
  }

  // Generate all the project for this stub references.
  std::for_each (
    node->references_.begin (),
    node->references_.end (),
    boost::bind (&CUTS_BE_Workspace_Generator_T::generate_stub_project,
                  this,
                  _1));
}
