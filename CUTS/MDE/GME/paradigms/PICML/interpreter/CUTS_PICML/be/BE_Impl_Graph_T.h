// -*- C++ -*-

//=============================================================================
/** 
 * @file        BE_Impl_Graph_T.h
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _CUTS_BE_IMPL_GRAPH_T_H_
#define _CUTS_BE_IMPL_GRAPH_T_H_

#include "BE_Depend_Graph_T.h"
#include "BE_Impl_Node.h"
#include "PICML/PICML.h"

/**
 * @class CUTS_BE_Impl_Graph_T
 *
 * Dependency graph generator for the component implementations. This is
 * parameterized by the backend generator type.
 */
template <typename T>
class CUTS_BE_Impl_Graph_T :
  public PICML::Visitor,
  public CUTS_BE_Depend_Graph_T <CUTS_BE_Impl_Node>
{
public:
  /// Default constructor.
  CUTS_BE_Impl_Graph_T (void);

  /// Destructor.
  virtual ~CUTS_BE_Impl_Graph_T (void);

protected:
  /// Visit a ComponentImplementationContainer object.
  void Visit_ComponentImplementationContainer (
    const PICML::ComponentImplementationContainer & container);

  /// Visit a MonolithicImplementation object.
  void Visit_MonolithicImplementation (
    const PICML::MonolithicImplementation & monoimpl);

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
  /// Implemenation that is currently being preprocessed.
  CUTS_BE_Impl_Node * current_impl_;
};

#include "BE_Impl_Graph_T.cpp"

#endif  // !defined _CUTS_BE_IMPL_GRAPH_T_H_
