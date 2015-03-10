// -*- C++ -*-

//=============================================================================
/**
 * @file      BE_Trait.h
 *
 * $Id$
 *
 * @author    James H. Hill
 */
//=============================================================================

#ifndef _CUTS_BE_TRAITS_H_
#define _CUTS_BE_TRAITS_H_

#include "BE_export.h"
#include "String_Set.h"
#include "PICML/PICML.h"

//=============================================================================
/**
 * @class CUTS_BE_Traits
 *
 * Base class for all backend generators. This class defines the traits
 * that must be defined by all generators. If the generator opts not
 * to define a trait, then a default trait will be assigned.
 */
//=============================================================================

class CUTS_BE_Export CUTS_BE_Traits
{
public:
  /// Default constructor.
  CUTS_BE_Traits (void);

  /// Destructor.
  virtual ~CUTS_BE_Traits (void);

  virtual bool open_file (
    const PICML::ComponentImplementationContainer_in container);

  virtual void close_file (
    const PICML::ComponentImplementationContainer_in container);

  virtual void write_prologue (
    const PICML::ComponentImplementationContainer_in container);

  virtual void write_epilogue (
    const PICML::ComponentImplementationContainer_in container);

  virtual void write_includes (
    const CUTS_String_Set & includes);

  // @@ begin component implementation

  virtual void write_impl_begin (
    const PICML::MonolithicImplementation_in monoimpl,
    const PICML::Component_in type);

  virtual void write_InEventPort_begin (
    const PICML::InEventPort_in sink);

  virtual void write_InEventPort_end (
    const PICML::InEventPort_in sink);

  virtual void write_ProvidedRequestPort_begin (
    const PICML::ProvidedRequestPort_in facet);

  virtual void write_ProvidedRequestPort_end (
    const PICML::ProvidedRequestPort_in facet);

  virtual void write_Attribute_begin (
    const PICML::Attribute_in attr);

  virtual void write_Attribute_end (
    const PICML::Attribute_in attr);

  virtual void write_ReadonlyAttribute_begin (
    const PICML::ReadonlyAttribute_in ro_attr);

  virtual void write_ReadonlyAttribute_end (
    const PICML::ReadonlyAttribute_in ro_attr);

  virtual void write_PeriodicEvent_begin (
    const PICML::PeriodicEvent_in periodic);

  virtual void write_PeriodicEvent_end (
    const PICML::PeriodicEvent_in periodic);

  virtual void write_environment_begin (
    const PICML::Component_in component);

  virtual void write_environment_method_begin (
    const PICML::MultiInputAction_in);

  virtual void write_environment_method_end (
    const PICML::MultiInputAction_in);

  virtual void write_environment_end (
    const PICML::Component_in component);

  virtual void write_impl_end (
    const PICML::MonolithicImplementation_in,
    const PICML::Component_in type);

  // @@ end component implementation

  // @@ begin facet implementation

  virtual void write_object_impl_begin (
    const PICML::Component_in component,
    const PICML::ProvidedRequestPort_in facet);

  virtual void write_OnewayOperation_begin (
    const PICML::OnewayOperation_in oneway);

  virtual void write_OnewayOperation_end (
    const PICML::OnewayOperation_in oneway);

  virtual void write_TwowayOperation_begin (
    const PICML::TwowayOperation_in twoway);

  virtual void write_TwowayOperation_end (
    const PICML::TwowayOperation_in twoway);

  virtual void write_object_impl_end (
    const PICML::Component_in component,
    const PICML::ProvidedRequestPort_in facet);

  // @@ end facet implementation

  // @@ begin home implementation

  virtual void write_factory_impl_begin (
    const PICML::ComponentFactory_in factory,
    const PICML::MonolithicImplementation_in impl,
    const PICML::Component_in type);

  virtual void write_FactoryOperation_begin (
    const PICML::FactoryOperation_in factory);

  virtual void write_FactoryOperation_end (
    const PICML::FactoryOperation_in factory);

  virtual void write_factory_impl_end (
    const PICML::ComponentFactory_in factory,
    const PICML::MonolithicImplementation_in impl,
    const PICML::Component_in type);

  // @@ end home implementation

  virtual void write_variables_begin (
    const PICML::Component_in component);

  virtual void write_variable (
    const PICML::Variable_in variable);

  virtual void write_worker_variable (
    const PICML::WorkerType_in type,
    const PICML::Worker_in worker);

  virtual void write_ReadonlyAttribute_variable (
    const PICML::ReadonlyAttribute_in readonly);

  virtual void write_PeriodicEvent_variable (
    const PICML::PeriodicEvent_in periodic);

  virtual void write_variables_end (void);

  virtual void write_precondition (
    const std::string & precondition);

  virtual void write_postcondition (
    const std::string & precondition);

  virtual void write_WorkerAction_begin (
    const PICML::Worker_in worker,
    const PICML::Action_in action);

  virtual void write_OutputAction_begin (
    const PICML::OutputAction_in action);

  virtual void write_action_property (
    const PICML::Property_in property);

  virtual void write_action_end (void);

private:
  // prevent the following operations
  CUTS_BE_Traits (const CUTS_BE_Traits &);
  const CUTS_BE_Traits & operator = (const CUTS_BE_Traits &);
};

#if defined (__CUTS_INLINE__)
#include "BE_Traits.inl"
#endif

#endif  // !defined _CUTS_BE_TRAITS_H_
