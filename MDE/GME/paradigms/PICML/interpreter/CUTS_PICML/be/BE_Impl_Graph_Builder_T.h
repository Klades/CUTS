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
#include "PICML/Visitor.h"

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
    const PICML::ComponentImplementationContainer_in container);

  /// Visit a MonolithicImplementation object.
  void Visit_MonolithicImplementation (
    const PICML::MonolithicImplementation_in monoimpl);

  void Visit_ComponentImplementationArtifact (
    const PICML::ComponentImplementationArtifact_in cia);

  void Visit_ComponentServantArtifact (
    const PICML::ComponentServantArtifact_in csa);

  /// Visit a MonolithprimaryArtifact object.
  void Visit_MonolithprimaryArtifact (
    const PICML::MonolithprimaryArtifact_in primary);

  /// Visit a Component object
  void Visit_Component (
    const PICML::Component_in component);

  /// Visit a WorkerType object
  void Visit_WorkerType (
    const PICML::WorkerType_in worker_type);

  /// Visit a Worker object.
  void Visit_Worker (
    const PICML::Worker_in worker);

  /// Visit a WorkerFile object.
  void Visit_WorkerFile (
    const PICML::WorkerFile_in file);

  /// Visit a WorkerLibrary object
  void Visit_WorkerLibrary (
    const PICML::WorkerLibrary_in library);

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
