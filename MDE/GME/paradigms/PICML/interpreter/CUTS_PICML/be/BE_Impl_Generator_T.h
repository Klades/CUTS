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

#include "PICML/PICML.h"
#include "PICML/Visitor.h"
#include "BE_Preprocessor_T.h"

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
class CUTS_BE_Impl_Generator_T : public PICML::Visitor
{
public:
  /// Type definition of the architecture for the code generator
  typedef typename CONTEXT::architecture_type architecture_type;

  /// Type definition of the behavior.
  typedef typename CONTEXT::behavior_type behavior_type;

  /// Default constructor.
  CUTS_BE_Impl_Generator_T (CONTEXT & context, CUTS_BE_Preprocessor_T <CONTEXT> & pp);

  /// Destructor.
  virtual ~CUTS_BE_Impl_Generator_T (void);

  void generate (const PICML::RootFolder_in root);

  /// Visit a RootFolder element.
  void visit_RootFolder (
    PICML::RootFolder_in root);

  /// Visit a ComponentImplementations folder.
  void visit_ComponentImplementations (
    PICML::ComponentImplementations_in impls);

  /// Visit a ComponentImplementationContainer element.
  void visit_ComponentImplementationContainer (
    PICML::ComponentImplementationContainer_in container);

  /// Visit a MonolithicImplementation element.
  void visit_MonolithicImplementation (
    PICML::MonolithicImplementation_in monoimpl);

  /// Visit a Component element.
  void visit_Component (
    PICML::Component_in component);

  void visit_Supports (
    PICML::Supports_in supports);

  /// Visit a Component element.
  void visit_Object (
    PICML::Object_in object);

  /// Visit a InEventPort element.
  void visit_InEventPort (
    PICML::InEventPort_in sink);

  /// Visit a ProvidedRequestPort element.
  void visit_ProvidedRequestPort (
    PICML::ProvidedRequestPort_in facet);

  /// Visit a ProvidedRequestPort element.
  void visit_ProvidedRequestPort_impl (
    PICML::ProvidedRequestPort_in facet);

  /// Visit a ProvidedRequestPort element.
  void visit_PeriodicEvent (
    PICML::PeriodicEvent_in periodic);

  /// Visit a ReadonlyAttribute element.
  void visit_ReadonlyAttribute (
    PICML::ReadonlyAttribute_in ro_attr);

  /// Visit an Attribute element.
  void visit_Attribute (
    PICML::Attribute_in attr);

  /// Visit a Variable element.
  void visit_Variable (
    PICML::Variable_in variable);

  /// Visit a WorkerType element.
  void visit_WorkerType (
    PICML::WorkerType_in type);

  void visit_OnewayOperation (
    PICML::OnewayOperation_in oneway);

  void visit_TwowayOperation (
    PICML::TwowayOperation_in twoway);

  void visit_ComponentFactory (
    PICML::ComponentFactory_in factory);

  void visit_ComponentFactory_inherits (
    PICML::Inherits_in inherits);

  void visit_FactoryOperation (
    PICML::FactoryOperation_in factory_op);

  void visit_MonolithprimaryArtifact (
    PICML::MonolithprimaryArtifact_in primary);

  void visit_ImplementationArtifactReference (
    PICML::ImplementationArtifactReference_in artref);

protected:
  void visit_Include (
    const std::string & include);

  void visit_ReadonlyAttribute_Variable (
    PICML::ReadonlyAttribute_in attr);

  void visit_PeriodicEvent_Variable (
    PICML::PeriodicEvent_in periodic);

private:
  /// Target context for the generator.
  CONTEXT & context_;

  CUTS_BE_Preprocessor_T <CONTEXT> & pp_;

  /// Current monolithic implementation.
  PICML::MonolithicImplementation monoimpl_;

  /// Helper method to write the variables for the component.
  void write_variables_i (const PICML::Component_in component);

  bool get_component_factory (const PICML::Component_in component,
                              PICML::ComponentFactory_in factory);

  // prevent the following operations
  CUTS_BE_Impl_Generator_T (const CUTS_BE_Impl_Generator_T &);
  const CUTS_BE_Impl_Generator_T & operator = (const CUTS_BE_Impl_Generator_T &);
};

#if defined (__CUTS_INLINE__)
#include "BE_Impl_Generator_T.inl"
#endif

#include "BE_Impl_Generator_T.cpp"

#endif  // !defined _CUTS_BE_IMPL_GENERATOR_T_H_
