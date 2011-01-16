// -*- C++ -*-

//=============================================================================
/**
 * @file        BE_Impl_Graph_Builder_T.h
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _CUTS_BE_IMPL_GRAPH_BUILDER_T_H_
#define _CUTS_BE_IMPL_GRAPH_BUILDER_T_H_

#include "BE_Impl_Graph.h"
#include "BE_IDL_Graph.h"
#include "PICML/PICML.h"

/**
 * @class CUTS_BE_Impl_Graph_Builder_T
 *
 * Dependency graph generator for the component implementations. This is
 * parameterized by the backend generator type.
 */
template <typename T>
class CUTS_BE_Impl_Graph_Builder_T : public PICML::Visitor
{
public:
  /// Default constructor.
  CUTS_BE_Impl_Graph_Builder_T (CUTS_BE_Impl_Graph & impl_graph,
                                CUTS_BE_IDL_Graph & idl_graph);

  /// Destructor.
  virtual ~CUTS_BE_Impl_Graph_Builder_T (void);

  /// Visit a ComponentImplementationContainer object.
  void Visit_ComponentImplementationContainer (
    const PICML::ComponentImplementationContainer & container);

  /// Visit a MonolithicImplementation object.
  void Visit_MonolithicImplementation (
    const PICML::MonolithicImplementation & monoimpl);

  void Visit_ComponentImplementationArtifact (
    const PICML::ComponentImplementationArtifact & cia);

  void Visit_ComponentServantArtifact (
    const PICML::ComponentServantArtifact & csa);

  /// Visit a MonolithprimaryArtifact object.
  void Visit_MonolithprimaryArtifact (
    const PICML::MonolithprimaryArtifact & primary);

  /// Visit a Component object
  void Visit_Component (
    const PICML::Component & component);

  /// Visit a WorkerType object
  void Visit_WorkerType (
    const PICML::WorkerType & worker_type);

  /// Visit a Worker object.
  void Visit_Worker (
    const PICML::Worker & worker);

  /// Visit a WorkerFile object.
  void Visit_WorkerFile (
    const PICML::WorkerFile & file);

  /// Visit a WorkerLibrary object
  void Visit_WorkerLibrary (
    const PICML::WorkerLibrary & library);

private:
  /// Target implementation dependency graph for the builder.
  CUTS_BE_Impl_Graph & impl_graph_;

  /// Target IDL dependency graph for the builder.
  CUTS_BE_IDL_Graph & idl_graph_;

  /// Implemenation that is currently being preprocessed.
  CUTS_BE_Impl_Node * curr_impl_;
};

#include "BE_Impl_Graph_Builder_T.cpp"

#endif  // !defined _CUTS_BE_IMPL_GRAPH_BUILDER_T_H_
