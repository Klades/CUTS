// -*- C++ -*-

//=============================================================================
/**
 * @file      BE_Impl_Generator_T.h
 *
 * $Id$
 *
 * @author    James H. Hill
 */
//=============================================================================

#ifndef _CUTS_BE_IMPL_GENERATOR_T_H_
#define _CUTS_BE_IMPL_GENERATOR_T_H_

#include "../../paradigms/CHAOS.h"

/**
 * @class CUTS_BE_Impl_Generator_T
 *
 * Implementation generator for CUTS. This class is parameterized
 * by a backend trait that determines what is generated. This class
 * only contains the parsing logic for generating the inplementation.
 * The backend traits that are used when generating the implemenation
 * can be found in CUTS_BE_Traits.
 */
template <typename CONTEXT>
class CUTS_BE_Impl_Generator_T : public CHAOS::Visitor
{
public:
  /// Type definition of the architecture for the code generator
  typedef typename CONTEXT::architecture_type architecture_type;

  /// Type definition of the behavior.
  typedef typename CONTEXT::behavior_type behavior_type;

  /// Default constructor.
  CUTS_BE_Impl_Generator_T (CONTEXT & context);

  /// Destructor.
  virtual ~CUTS_BE_Impl_Generator_T (void);

  void generate (const CHAOS::RootFolder & root);

  /// Visit a RootFolder element.
  void Visit_RootFolder (
    const CHAOS::RootFolder & root);

  /// Visit a ComponentImplementations folder.
  void Visit_ComponentImplementations (
    const CHAOS::ComponentImplementations & impls);

  /// Visit a DeploymentPlans folder.
  void Visit_DeploymentPlans (
    const CHAOS::DeploymentPlans & plans);

  /// Visit a DeploymentPlan element.
  void Visit_DeploymentPlan (
    const CHAOS::DeploymentPlan & plan);

  /// Visit a ComponentImplementationContainer element.
  void Visit_ComponentImplementationContainer (
    const CHAOS::ComponentImplementationContainer & container);

  /// Visit a MonolithicImplementation element.
  void Visit_MonolithicImplementation (
    const CHAOS::MonolithicImplementation & monoimpl);

  /// Visit a MonolithicImplementation element.
  void Visit_ComponentAssembly (
    const CHAOS::ComponentAssembly & assembly);

  /// Visit a Component element.
  void Visit_Component (
    const CHAOS::Component & component);

  void Visit_Supports (
    const CHAOS::Supports & supports);

  /// Visit a Component element.
  void Visit_Object (
    const CHAOS::Object & object);

  /// Visit a InEventPort element.
  void Visit_InEventPort (
    const CHAOS::InEventPort & sink);

  /// Visit a ProvidedRequestPort element.
  void Visit_ProvidedRequestPort (
    const CHAOS::ProvidedRequestPort & facet);

  /// Visit a ProvidedRequestPort element.
  void Visit_ProvidedRequestPort_impl (
    const CHAOS::ProvidedRequestPort & facet);

  /// Visit a ProvidedRequestPort element.
  void Visit_PeriodicEvent (
    const CHAOS::PeriodicEvent & periodic);

  /// Visit a ReadonlyAttribute element.
  void Visit_ReadonlyAttribute (
    const CHAOS::ReadonlyAttribute  & ro_attr);

  /// Visit an Attribute element.
  void Visit_Attribute (
    const CHAOS::Attribute & attr);

  /// Visit a Variable element.
  void Visit_Variable (
    const CHAOS::Variable & variable);

  /// Visit a WorkerType element.
  void Visit_WorkerType (
    const CHAOS::WorkerType & type);

  void Visit_OnewayOperation (
    const CHAOS::OnewayOperation & oneway);

  void Visit_TwowayOperation (
    const CHAOS::TwowayOperation & twoway);

  void Visit_ComponentFactory (
    const CHAOS::ComponentFactory & factory);

  void Visit_ComponentFactory_inherits (
    const CHAOS::Inherits & inherits);

  void Visit_FactoryOperation (
    const CHAOS::FactoryOperation & factory_op);

  void Visit_MonolithprimaryArtifact (
    const CHAOS::MonolithprimaryArtifact & primary);

  void Visit_ImplementationArtifactReference (
    const CHAOS::ImplementationArtifactReference & artref);

protected:
  void Visit_Include (
    const std::string & include);

  void Visit_ReadonlyAttribute_Variable (
    const CHAOS::ReadonlyAttribute & attr);

  void Visit_PeriodicEvent_Variable (
    const CHAOS::PeriodicEvent & periodic);

  void Visit_ComponentImplementation (
    const CHAOS::ComponentImplementation &);

private:
  /// Target context for the generator.
  CONTEXT & context_;

  /// Current monolithic implementation.
  CHAOS::MonolithicImplementation monoimpl_;

  /// Helper method to write the variables for the component.
  void write_variables_i (const CHAOS::Component & component);

  bool get_component_factory (const CHAOS::Component & component,
                              CHAOS::ComponentFactory & factory);

  // prevent the following operations
  CUTS_BE_Impl_Generator_T (const CUTS_BE_Impl_Generator_T &);
  const CUTS_BE_Impl_Generator_T & operator = (const CUTS_BE_Impl_Generator_T &);
};

#if defined (__CUTS_INLINE__)
#include "BE_Impl_Generator_T.inl"
#endif

#include "BE_Impl_Generator_T.cpp"

#endif  // !defined _CUTS_BE_IMPL_GENERATOR_T_H_
