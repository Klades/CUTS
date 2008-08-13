// $Id$

#include "BE_Assembly_Generator_Preprocessor.h"
#include "boost/graph/topological_sort.hpp"
#include "boost/bind.hpp"
#include <algorithm>

//
// CUTS_BE_Assembly_Generator_Preprocessor
//
CUTS_BE_Assembly_Generator_Preprocessor::
CUTS_BE_Assembly_Generator_Preprocessor (
  std::vector <PICML::ComponentAssembly> & assembly_list)
: assembly_list_ (assembly_list)
{

}

//
// ~CUTS_BE_Assembly_Generator_Preprocessor
//
CUTS_BE_Assembly_Generator_Preprocessor::
~CUTS_BE_Assembly_Generator_Preprocessor (void)
{

}

//
// Visit_RootFolder
//
void CUTS_BE_Assembly_Generator_Preprocessor::
Visit_RootFolder (const PICML::RootFolder & root)
{
  typedef 
    std::vector <PICML::ComponentImplementations> 
    ComponentImplementations_set;

  ComponentImplementations_set folders = 
    root.ComponentImplementations_children ();

  std::for_each (folders.begin (),
                 folders.end (),
                 boost::bind (&ComponentImplementations_set::value_type::Accept,
                              _1,
                              boost::ref (*this)));

  // Run topological sort on the dependency graph, which is just
  // a specialized case of depth-first search.
  std::vector <vertex_type> results;

  boost::topological_sort (this->graph_, 
                           std::back_inserter (results));

  boost::topological_sort (this->graph_, 
    std::back_inserter (results),
    boost::visitor (boost::make_dfs_visitor (
      boost::write_property (boost::vertex_name, 
      std::back_inserter (this->assembly_list_), 
      boost::on_finish_vertex ()))));

  // Copy the results into the assembly list. Unfortunately, I 
  // can't get the parameter version above working so the results 
  // are entered directly into the list.
  std::vector <vertex_type>::iterator 
    iter = results.begin (), iter_end = results.end ();

  for ( ; iter != iter_end; iter ++)
  {
    this->assembly_list_.push_back (
      boost::get (boost::vertex_name, this->graph_, *iter));
  }
}

//
// Visit_ComponentImplementations
//
void CUTS_BE_Assembly_Generator_Preprocessor::
Visit_ComponentImplementations (const PICML::ComponentImplementations & folder)
{
  typedef 
    std::vector <PICML::ComponentImplementationContainer>
    Container_set;

  Container_set containers =
    folder.ComponentImplementationContainer_children ();

  std::for_each (containers.begin (),
                 containers.end (),
                 boost::bind (&Container_set::value_type::Accept,
                              _1,
                              boost::ref (*this)));
}

//
// Visit_ComponentImplementationContainer
//
void CUTS_BE_Assembly_Generator_Preprocessor::
Visit_ComponentImplementationContainer (
  const PICML::ComponentImplementationContainer & container)
{
  typedef std::vector <PICML::ComponentAssembly> ComponentAssembly_set;

  ComponentAssembly_set assemblies = 
    container.ComponentAssembly_kind_children ();

  std::for_each (assemblies.begin (),
                 assemblies.end (),
                 boost::bind (&ComponentAssembly_set::value_type::Accept,
                              _1,
                              boost::ref (*this)));
}

//
// Visit_ComponentAssembly
//
void CUTS_BE_Assembly_Generator_Preprocessor::
Visit_ComponentAssembly (const PICML::ComponentAssembly & assembly)
{
  vertex_type parent_desc;

  // Add this assembly to the graph as a vertex.
  vertex_map_type::iterator result = this->vertex_map_.find (assembly);
  
  if (result != this->vertex_map_.end ())
  {
    parent_desc = result->second;
  }
  else
  {
    parent_desc = boost::add_vertex (assembly, this->graph_);
    this->vertex_map_.insert (std::make_pair (assembly, parent_desc));
  }

  // Add all the child assemblies as an edge.
  typedef std::vector <PICML::ComponentAssembly> ComponentAssembly_set;
  ComponentAssembly_set assemblies = assembly.ComponentAssembly_children ();

  ComponentAssembly_set::iterator 
    iter = assemblies.begin (), iter_end = assemblies.end ();

  vertex_type child_desc;
  PICML::ComponentAssembly child_assembly;      

  for ( ; iter != iter_end; iter ++)
  {
    // Get the archtype of this assembly.
    child_assembly = iter->Archetype ();

    // Find the child vertex in the map.
    result = this->vertex_map_.find (child_assembly);

    if (result != this->vertex_map_.end ())
    {
      child_desc = result->second;
    }
    else
    {
      child_desc = boost::add_vertex (child_assembly, this->graph_);
      this->vertex_map_.insert (std::make_pair (child_assembly, child_desc));
    }

    // Create a new edge between the child and parent vertex.
    boost::add_edge (parent_desc, child_desc, this->graph_);
  }
}

