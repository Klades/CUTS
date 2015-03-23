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
  void visit_ComponentImplementationContainer (
    PICML::ComponentImplementationContainer_in container);

  /// Visit a MonolithicImplementation object.
  void visit_MonolithicImplementation (
    PICML::MonolithicImplementation_in monoimpl);

  void visit_ComponentImplementationArtifact (
    PICML::ComponentImplementationArtifact_in cia);

  void visit_ComponentServantArtifact (
    PICML::ComponentServantArtifact_in csa);

  /// Visit a MonolithprimaryArtifact object.
  void visit_MonolithprimaryArtifact (
    PICML::MonolithprimaryArtifact_in primary);

  /// Visit a Component object
  void visit_Component (
    PICML::Component_in component);

  /// Visit a WorkerType object
  void visit_WorkerType (
    PICML::WorkerType_in worker_type);

  /// Visit a Worker object.
  void visit_Worker (
    PICML::Worker_in worker);

  /// Visit a WorkerFile object.
  void visit_WorkerFile (
    PICML::WorkerFile_in file);

  /// Visit a WorkerLibrary object
  void visit_WorkerLibrary (
    PICML::WorkerLibrary_in library);

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
