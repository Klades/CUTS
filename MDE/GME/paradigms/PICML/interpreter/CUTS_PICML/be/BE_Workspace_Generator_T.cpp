// $Id$

#include "BE_Options.h"
#include "BE_Workspace_Generators_T.h"
#include "BE_Project_Generators_T.h"
#include "boost/bind.hpp"
#include <algorithm>

//
// CUTS_BE_Workspace_Generator_T
//
template <typename CONTEXT>
CUTS_BE_Workspace_Generator_T <CONTEXT>::
CUTS_BE_Workspace_Generator_T (CONTEXT & context)
: context_ (context)
{

}

//
// ~CUTS_BE_Workspace_Generator_T
//
template <typename CONTEXT>
CUTS_BE_Workspace_Generator_T <CONTEXT>::~CUTS_BE_Workspace_Generator_T (void)
{

}

//
// generate
//
template <typename CONTEXT>
void CUTS_BE_Workspace_Generator_T <CONTEXT>::
generate (const CUTS_BE_Impl_Graph & impls)
{
  // Construct the name of the workspace.
  const std::string & workspace = CUTS_BE_OPTIONS ()->project_name_;

  // Open the workspace file for writing.
  CUTS_BE_Workspace_File_Open_T <CONTEXT> workspace_file_open (this->context_);
  workspace_file_open.generate (workspace);

  // Begin the workspace.
  CUTS_BE_Workspace_Begin_T <CONTEXT> workspace_begin (this->context_);
  workspace_begin.generate (workspace);

  // We are writing all the implementation projects.
  std::for_each (impls.graph ().begin (),
                 impls.graph ().end (),
                 boost::bind (&CUTS_BE_Workspace_Generator_T::generate_impl_project,
                              this,
                              boost::bind (&CUTS_BE_Impl_Graph::Node_Map::value_type::second,
                                           _1)));

  // We are writing all the stub projects.
  std::for_each (this->required_stubs_.begin (),
                 this->required_stubs_.end (),
                 boost::bind (&CUTS_BE_Workspace_Generator_T::generate_stub_project,
                              this,
                              _1));

  // End the workspace.
  CUTS_BE_Workspace_End_T <CONTEXT> workspace_end (this->context_);
  workspace_end.generate (workspace);

  // Close the workspace file.
  CUTS_BE_Workspace_File_Close_T <CONTEXT> workspace_close (this->context_);
  workspace_close.generate ();
}

//
// write_impl_project
//
template <typename CONTEXT>
void CUTS_BE_Workspace_Generator_T <CONTEXT>::
generate_impl_project (const CUTS_BE_Impl_Node * node)
{
  CUTS_BE_Project_File_Open_T <CONTEXT,
                               CUTS_BE_Impl_Node>
                               project_file_open (this->context_);

  project_file_open.generate (*node);

  // Add the project to the workspace.
  CUTS_BE_Workspace_Project_Include_T <CONTEXT,
                                       CUTS_BE_Impl_Node>
                                       project_include (this->context_);

  project_include.generate (*node);

  // Begin the project file.
  CUTS_BE_Project_File_Begin_T <CONTEXT,
                                CUTS_BE_Impl_Node>
                                project_file_begin (this->context_);

  project_file_begin.generate (*node);

  // Write the project file.
  CUTS_BE_Project_Write_T <CONTEXT,
                           CUTS_BE_Impl_Node>
                           project_write (this->context_);

  project_write.generate (*node);

  // End the project file.
  CUTS_BE_Project_File_End_T <CONTEXT,
                              CUTS_BE_Impl_Node>
                              project_file_end (this->context_);

  project_file_end.generate (*node);

  // Close the project file.
  CUTS_BE_Project_File_Close_T <CONTEXT,
                                CUTS_BE_Impl_Node>
                                project_file_close (this->context_);

  project_file_close.generate ();

  // Now, we need to add all the stubs for this implementation to the
  // collection of <required_stubs_>. We will iterate over this collection
  // once we have finished all the implementation projects.
  std::for_each (node->references_.begin (),
                 node->references_.end (),
                 boost::bind (&IDL_Node_Set::insert,
                              boost::ref (this->required_stubs_),
                              _1));
}

//
// write_stub_project
//
template <typename CONTEXT>
void CUTS_BE_Workspace_Generator_T <CONTEXT>::
generate_stub_project (const CUTS_BE_IDL_Node * node)
{
  // Locate the node in the <visited_nodes_> before we continue
  // process. The main idea is to only process nodes that we
  // haven't seen yet.
  if (this->visited_nodes_.find (node) != this->visited_nodes_.end ())
    return;

  // Insert the node into the collection.
  this->visited_nodes_.insert (node);

  CUTS_BE_Project_File_Open_T <CONTEXT,
                               CUTS_BE_IDL_Node>
                               project_file_open (this->context_);

  project_file_open.generate (*node);

  // Begin the project file.
  CUTS_BE_Project_File_Begin_T <CONTEXT,
                                CUTS_BE_IDL_Node>
                                project_file_begin (this->context_);

  project_file_begin.generate (*node);

  // Write the project file.
  CUTS_BE_Project_Write_T <CONTEXT,
                           CUTS_BE_IDL_Node>
                           project_write (this->context_);

  project_write.generate (*node);

  // End the project file.
  CUTS_BE_Project_File_End_T <CONTEXT,
                              CUTS_BE_IDL_Node>
                              project_file_end (this->context_);

  project_file_end.generate (*node);

  // Close the project file.
  CUTS_BE_Project_File_Close_T <CONTEXT,
                                CUTS_BE_IDL_Node>
                                project_file_close (this->context_);

  project_file_close.generate ();

  // Include the project in the workspace.
  CUTS_BE_Workspace_Project_Include_T <CONTEXT,
                                       CUTS_BE_IDL_Node>
                                       workspace_include (this->context_);

  workspace_include.generate (*node);

  // Generate all the project for this stub references.
  std::for_each (node->references_.begin (),
                 node->references_.end (),
                 boost::bind (&CUTS_BE_Workspace_Generator_T::generate_stub_project,
                              this,
                              _1));
}