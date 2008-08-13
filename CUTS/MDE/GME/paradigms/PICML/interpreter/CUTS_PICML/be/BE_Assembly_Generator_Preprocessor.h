// -*- C++ -*-

//=============================================================================
/**
 * @file        BE_Assembly_Generator_Preprocessor.h
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _CUTS_BE_ASSEMBLY_GENERATOR_PREPROCESSOR_H_
#define _CUTS_BE_ASSEMBLY_GENERATOR_PREPROCESSOR_H_

#include "PICML/PICML.h"
#include "boost/graph/graph_traits.hpp"
#include "boost/graph/adjacency_list.hpp"

//=============================================================================
/**
 * @class CUTS_BE_Assembly_Generator_Preprocessor 
 *
 * Preprocessor the assembly generator. Given a PICML project, it will
 * determine the order for generating (building) the assemblies for 
 * CUTS since assemblies can contain instances of other assemblies.
 */
//=============================================================================

class CUTS_BE_Assembly_Generator_Preprocessor :
  public PICML::Visitor
{
public:
  /**
   * @param[out]    assembly_list       Order for generating assemblies.
   */
  CUTS_BE_Assembly_Generator_Preprocessor (
    std::vector <PICML::ComponentAssembly> & assembly_list);

  /// Destructor.
  virtual ~CUTS_BE_Assembly_Generator_Preprocessor (void);

  virtual void Visit_RootFolder (
    const PICML::RootFolder & root);

  virtual void Visit_ComponentImplementations (
    const PICML::ComponentImplementations & folder);

  virtual void Visit_ComponentImplementationContainer (
    const PICML::ComponentImplementationContainer & container);

  virtual void Visit_ComponentAssembly (
    const PICML::ComponentAssembly & assembly);

private:
  typedef std::vector <PICML::ComponentAssembly> container_type;

  /// The target assembly list.
  container_type & assembly_list_;

  /// The boost adjacency list for the dependency graph.
  typedef 
    boost::adjacency_list <boost::setS, 
                           boost::vecS, 
                           boost::directedS,
                           boost::property <boost::vertex_name_t, 
                                            PICML::ComponentAssembly> >
                           graph_type;

  /// Type definition of the vertex type.
  typedef
    boost::graph_traits <graph_type>::vertex_descriptor vertex_type;

  /// Type definition of the edge type.
  typedef 
    std::pair <vertex_type, vertex_type> edge_type;

  typedef 
    std::map <PICML::ComponentAssembly, vertex_type> vertex_map_type;

  /// The dependency graph for the assemblies.
  graph_type graph_;

  /// Mapping of the current vertices.
  vertex_map_type vertex_map_;

  // prevent the following operations
  CUTS_BE_Assembly_Generator_Preprocessor (const CUTS_BE_Assembly_Generator_Preprocessor &);
  const CUTS_BE_Assembly_Generator_Preprocessor & operator = (const CUTS_BE_Assembly_Generator_Preprocessor &);
};

#endif  // !defined _CUTS_BE_ASSEMBLY_GENERATOR_PREPROCESSOR_H_
