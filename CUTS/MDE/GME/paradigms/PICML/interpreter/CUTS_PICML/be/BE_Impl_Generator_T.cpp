// $Id$

#if !defined (__CUTS_INLINE__)
#include "BE_Impl_Generator_T.inl"
#endif

#include "BE_algorithm.h"
#include "BE_Preprocessor_T.h"
#include "BE_Env_Visitor_T.h"
#include "BE_Execution_Visitor_T.h"
#include "BE_Assembly_Generator_T.h"
#include "BE_Deployment_Generator_T.h"
#include "UDM_Utility_T.h"

#include "boost/bind.hpp"
#include "boost/iterator/filter_iterator.hpp"

//
// Visit_RootFolder
//
template <typename CONTEXT>
void CUTS_BE_Impl_Generator_T <CONTEXT>::
Visit_RootFolder (const PICML::RootFolder & root)
{
  typedef std::vector <PICML::ComponentImplementations> Folder_Set;
  Folder_Set folders = root.ComponentImplementations_children ();

  CUTS_BE::visit <CONTEXT> (folders,
    boost::bind (&Folder_Set::value_type::Accept, _1, boost::ref (*this)));

  typedef std::vector <PICML::DeploymentPlans> DeploymentPlans_Set;
  DeploymentPlans_Set plans = root.DeploymentPlans_children ();

  CUTS_BE::visit <CONTEXT> (plans,
    boost::bind (&DeploymentPlans_Set::value_type::Accept, _1, boost::ref (*this)));
}

//
// Visit_ComponentImplementations
//
template <typename CONTEXT>
void CUTS_BE_Impl_Generator_T <CONTEXT>::
Visit_ComponentImplementations (
const PICML::ComponentImplementations & impls)
{
  std::vector <
    PICML::ComponentImplementationContainer> containers =
    impls.ComponentImplementationContainer_children ();

  std::for_each (containers.begin (),
                 containers.end (),
                 boost::bind (&PICML::ComponentImplementationContainer::Accept,
                              _1,
                              boost::ref (*this)));
}

//
// Visit_ComponentImplementationContainer
//
template <typename CONTEXT>
void CUTS_BE_Impl_Generator_T <CONTEXT>::
Visit_ComponentImplementationContainer (
const PICML::ComponentImplementationContainer & container)
{
  // Get this component implementation. This can either be an
  // assembly, or a monolithic implementation.
  std::vector <PICML::ComponentImplementation> impls =
    container.ComponentImplementation_children ();

  // Preprocess the container and extract as much information
  // as we can about the current component's implementation.
  CUTS_BE_PREPROCESSOR (CONTEXT)->preprocess (container);

  std::for_each (impls.begin (),
                 impls.end (),
                 boost::bind (&CUTS_BE_Impl_Generator_T::Visit_ComponentImplementation,
                              this,
                              _1));
}

//
// Visit_MonolithicImplementation
//
template <typename CONTEXT>
void CUTS_BE_Impl_Generator_T <CONTEXT>::
Visit_ComponentImplementation (const PICML::ComponentImplementation & impl)
{
  if (impl.type () == PICML::MonolithicImplementation::meta)
  {
    PICML::MonolithicImplementation monoimpl =
      PICML::MonolithicImplementation::Cast (impl);

    CUTS_BE::visit <CONTEXT> (monoimpl,
      boost::bind (&PICML::MonolithicImplementation::Accept, _1, boost::ref (*this)));
  }
  else if (impl.type () == PICML::ComponentAssembly::meta)
  {
    PICML::ComponentAssembly assembly = PICML::ComponentAssembly::Cast (impl);

    CUTS_BE::visit <CONTEXT> (assembly,
      boost::bind (&PICML::ComponentAssembly::Accept, _1, boost::ref (*this)));
  }
  else
  {
    // Um, why do we not know about this type!?!?
  }
}

//
// Visit_MonolithicImplementation
//
template <typename CONTEXT>
void CUTS_BE_Impl_Generator_T <CONTEXT>::
Visit_MonolithicImplementation (const PICML::MonolithicImplementation & monoimpl)
{
  // Get the parent of the monolithic implementation.
  PICML::ComponentImplementationContainer container =
    monoimpl.ComponentImplementationContainer_parent ();

  // Get the implementation node and write all the includes.
  const CUTS_BE_Impl_Node * impl = 0;
  CUTS_BE_PREPROCESSOR (CONTEXT)->impls ().find (monoimpl.name (), impl);

  if (0 == impl)
    return;

  CUTS_BE_File_Open_T <arch_type> file_open_gen (this->context_);
  file_open_gen.generate (container, monoimpl);

  // Write the prologue for the file.
  CUTS_BE_Prologue_T <arch_type> prologue_gen (this->context_);
  prologue_gen.generate (container, monoimpl);

  // Write the include files for this implementation.
  CUTS_BE::visit <CONTEXT> (impl->include_,
    boost::bind (&CUTS_BE_Impl_Generator_T::Visit_Include,
    boost::ref (this), _1));

  // Figure out what type of component we are implementing. Right
  // now there is a one-to-one implementation to component type
  // mapping. Therefore, the component has the known behavior
  // for this respective implementation.
  PICML::Implements implements = monoimpl.dstImplements ();

  if (implements != Udm::null)
  {
    // Extract the component type being implemented.
    PICML::ComponentRef ref = implements.dstImplements_end ();
    PICML::Component component = ref.ref ();

    // Write the beginning of the component's implementation.
    CUTS_BE_Component_Impl_Begin_T <arch_type> comp_impl_begin (this->context_);
    comp_impl_begin.generate (monoimpl, component);

    // Visit the component.
    component.Accept (*this);

    // Write the end of the component's implementation.
    CUTS_BE_Component_Impl_End_T <arch_type> comp_impl_end (this->context_);
    comp_impl_end.generate (monoimpl, component);

    // Get all the facets in the component so that we can
    // generate their implementation.
    typedef std::vector <PICML::ProvidedRequestPort> Facet_Set;
    Facet_Set facets = component.ProvidedRequestPort_kind_children ();

    CUTS_BE::visit <CONTEXT> (facets,
      boost::bind (&CUTS_BE_Impl_Generator_T::Visit_ProvidedRequestPort_impl,
      boost::ref (this), _1));

    // Find the component implementation artifact so we can generate
    // the entrypoint for this component's implementation.
    this->monoimpl_ = monoimpl;
    std::set <PICML::MonolithprimaryArtifact> artifacts = monoimpl.dstMonolithprimaryArtifact ();

    std::for_each (artifacts.begin (),
                   artifacts.end (),
                   boost::bind (&PICML::MonolithprimaryArtifact::Accept,
                                _1,
                                boost::ref (*this)));

    //PICML::ComponentFactory factory;

    //if (this->get_component_factory (component, factory))
    //{
    //  // Write the beginning of the factory's implementation.
    //  CUTS_BE_Factory_Impl_Begin_T <CONTEXT>::
    //    generate (factory, monoimpl, component);

    //  CUTS_BE::visit <CONTEXT> (factory,
    //    boost::bind (&PICML::ComponentFactory::Accept,
    //    _1, boost::ref (*this)));

    //  // Write the end of the factory's implementation.
    //  CUTS_BE_Factory_Impl_End_T <CONTEXT>::generate (factory, monoimpl, component);
    //}
  }

  // Write the epilogue for the file, then close it.
  CUTS_BE_Epilogue_T <arch_type> epilogue_gen (this->context_);
  epilogue_gen.generate (container, monoimpl);

  CUTS_BE_File_Close_T <arch_type> file_close_gen (this->context_);
  file_close_gen.generate (container, monoimpl);
}

//
// Visit_MonolithicImplementation
//
template <typename CONTEXT>
void CUTS_BE_Impl_Generator_T <CONTEXT>::
Visit_ComponentAssembly (const PICML::ComponentAssembly & assembly)
{
  // Get the parent of the monolithic implementation.
  PICML::ComponentImplementationContainer container =
    assembly.ComponentImplementationContainer_parent ();

  if (CUTS_BE_ComponentAssembly_File_Open_T <CONTEXT>::generate (container, assembly))
  {
    // Write the prologue for the file.
    CUTS_BE_ComponentAssembly_Prologue_T <CONTEXT>::generate (container, assembly);

    CUTS_BE_Assembly_Generator_T <CONTEXT> generator;
    PICML::ComponentAssembly (assembly).Accept (generator);

    // Write the epilogue for the file, then close it.
    CUTS_BE_ComponentAssembly_Epilogue_T <CONTEXT>::generate (container, assembly);

    CUTS_BE_ComponentAssembly_File_Close_T <CONTEXT>::generate (container, assembly);
  }
}

//
// Visit_Component
//
template <typename CONTEXT>
void CUTS_BE_Impl_Generator_T <CONTEXT>::
Visit_Component (const PICML::Component & component)
{
  // Determine if we are ready to write the variables.
  if (!CUTS_BE_Write_Variables_Last_T <CONTEXT>::result_type)
    this->write_variables_i (component);

  // Visit all the supported interfaces.
  typedef std::vector <PICML::Supports> Supports_Set;
  Supports_Set supports = component.Supports_kind_children ();

  CUTS_BE::visit <CONTEXT> (supports,
    boost::bind (&Supports_Set::value_type::Accept,
    _1, boost::ref (*this)));

  // Visit all the InEventPort elements of the <component>.
  typedef std::vector <PICML::InEventPort> InEventPort_Set;
  InEventPort_Set sinks = component.InEventPort_kind_children ();

  CUTS_BE::visit <CONTEXT> (sinks,
    boost::bind (&InEventPort_Set::value_type::Accept,
    _1, boost::ref (*this)));

  // Visit all the ProvidedRequestPort elements of the <component>.
  typedef std::vector <PICML::ProvidedRequestPort> Facet_Set;
  Facet_Set facets = component.ProvidedRequestPort_kind_children ();

  CUTS_BE::visit <CONTEXT> (facets,
    boost::bind (&Facet_Set::value_type::Accept, _1, boost::ref (*this)));

  // Visit all the PeriodicEvent elements of the <component>.
  typedef std::vector <PICML::PeriodicEvent> PeriodicEvent_Set;
  PeriodicEvent_Set periodics = component.PeriodicEvent_kind_children ();

  CUTS_BE::visit <CONTEXT> (periodics,
    boost::bind (&PeriodicEvent_Set::value_type::Accept, _1, boost::ref (*this)));

  // Visit all the Attribute elements of the <component>.
  typedef std::vector <PICML::Attribute> Attribute_Set;
  Attribute_Set attrs = component.Attribute_kind_children ();

  CUTS_BE::visit <CONTEXT> (attrs,
    boost::bind (&Attribute_Set::value_type::Accept, _1, boost::ref (*this)));

  // Visit all the ReadonlyAttribute elements of the <component>.
  typedef std::vector <PICML::ReadonlyAttribute> ReadonlyAttribute_Set;
  ReadonlyAttribute_Set ro_attrs = component.ReadonlyAttribute_kind_children ();

  typedef is_type <PICML::ReadonlyAttribute> ReadonlyAttribute_Type;

  std::for_each (boost::make_filter_iterator <ReadonlyAttribute_Type> (
                    ro_attrs.begin (), ro_attrs.end ()),
                 boost::make_filter_iterator <ReadonlyAttribute_Type> (
                    ro_attrs.end (), ro_attrs.end ()),
                 boost::bind (&ReadonlyAttribute_Set::value_type::Accept,
                    _1, boost::ref (*this)));

  // Get the environment for the component.
  PICML::Environment env = component.Environment_child ();

  if (env != Udm::null)
  {
    // Begin generating environment related metadata.
    CUTS_BE_Environment_Begin_T <arch_type> env_begin_gen (this->context_);
    env_begin_gen.generate (component);

    CUTS_BE_Env_Visitor_T <arch_type> env_visitor (this->context_);
    env.Accept (env_visitor);

    // End generating environment related metadata.
    CUTS_BE_Environment_End_T <arch_type> env_end_gen (this->context_);
    env_end_gen.generate (component);
  }

  // Determine if we are writing the variables
  if (CUTS_BE_Write_Variables_Last_T <CONTEXT>::result_type)
    this->write_variables_i (component);
}

//
// Visit_MonolithprimaryArtifact
//
template <typename CONTEXT>
void CUTS_BE_Impl_Generator_T <CONTEXT>::
Visit_MonolithprimaryArtifact (const PICML::MonolithprimaryArtifact & primary)
{
  PICML::ImplementationArtifactReference artifact = primary.dstMonolithprimaryArtifact_end ();
  artifact.Accept (*this);
}

//
// Visit_ImplementationArtifactReference
//
template <typename CONTEXT>
void CUTS_BE_Impl_Generator_T <CONTEXT>::
Visit_ImplementationArtifactReference (const PICML::ImplementationArtifactReference & artref)
{
  if (PICML::ComponentImplementationArtifact::meta == artref.type ())
  {
    PICML::ComponentImplementationArtifact artifact =
      PICML::ComponentImplementationArtifact::Cast (artref);

    CUTS_BE_Component_Impl_Entrypoint_T <arch_type> entrypoint_gen (this->context_);
    entrypoint_gen.generate (this->monoimpl_, artifact);
  }
}

//
// Visit_InEventPort
//
template <typename CONTEXT>
void CUTS_BE_Impl_Generator_T <CONTEXT>::
Visit_InEventPort (const PICML::InEventPort & sink)
{
  // Get the connections from the port.
  PICML::Input input = sink.dstInput ();
  PICML::QueryInput query_input = sink.dstQueryInput ();

  std::vector <PICML::Property> properties;

  if (input != Udm::null)
  {
    // Get the properties associate with the input port.
    PICML::InputAction action = input.dstInput_end ();
    properties = action.Property_children ();
  }

  // We are generating a regular event port.
  CUTS_BE_InEventPort_Begin_T <arch_type> port_begin_gen (this->context_);
  port_begin_gen.generate (sink, properties);

  CUTS_BE_Execution_Visitor_T <behavior_type> exec_visitor (this->context_);
  exec_visitor.generate (sink);

  CUTS_BE_InEventPort_End_T <arch_type> port_end_gen (this->context_);
  port_end_gen.generate (sink, properties);
}

//
// Visit_ProvidedRequestPort
//
template <typename CONTEXT>
void CUTS_BE_Impl_Generator_T <CONTEXT>::
Visit_ProvidedRequestPort (const PICML::ProvidedRequestPort & facet)
{
  // Begin the generation of the provided request port.
  CUTS_BE_ProvidedRequestPort_Begin_T <arch_type> port_begin_gen (this->context_);
  port_begin_gen.generate (facet);

  CUTS_BE_Execution_Visitor_T <behavior_type> exec_visitor (this->context_);
  exec_visitor.generate (facet);

  // End the generation of the provided request port.
  CUTS_BE_ProvidedRequestPort_End_T <arch_type> port_end_gen (this->context_);
  port_end_gen.generate (facet);
}

//
// Visit_ProvidedRequestPort
//
template <typename CONTEXT>
void CUTS_BE_Impl_Generator_T <CONTEXT>::
Visit_ProvidedRequestPort_impl (const PICML::ProvidedRequestPort & facet)
{
  // Get the parent component and the facet's interface/object.
  //PICML::Component component = PICML::Component::Cast (facet.parent ());
  //PICML::Object object = PICML::Object::Cast (facet.ref ());

  //if (object != Udm::null)
  //{
  //  // Write the beginning of the facet's implementation.
  //  CUTS_BE_Object_Impl_Begin_T <CONTEXT>::generate (component, facet);

  //  CUTS_BE::visit <CONTEXT> (object,
  //    boost::bind (&PICML::Object::Accept, _1, boost::ref (*this)));

  //  // Write the end of the facet's implementation.
  //  CUTS_BE_Object_Impl_End_T <CONTEXT>::generate (component, facet);
  //}
}

//
// Visit_Include
//
template <typename CONTEXT>
void CUTS_BE_Impl_Generator_T <CONTEXT>::
Visit_Include (const std::string & include)
{
  CUTS_BE_Include_File_T <CONTEXT> include_gen (this->context_);
  include_gen.generate (include);
}

//
// Visit_PeriodicEvent_Variable
//
template <typename CONTEXT>
void CUTS_BE_Impl_Generator_T <CONTEXT>::
Visit_PeriodicEvent_Variable (const PICML::PeriodicEvent & periodic)
{
  CUTS_BE_PeriodicEvent_Variable_T <behavior_type> var_gen (this->context_);
  var_gen.generate (periodic);
}

//
// Visit_Include
//
template <typename CONTEXT>
void CUTS_BE_Impl_Generator_T <CONTEXT>::
Visit_ReadonlyAttribute_Variable (const PICML::ReadonlyAttribute & attr)
{
  CUTS_BE_Attribute_Variable_T <behavior_type> var_gen (this->context_);
  var_gen.generate (attr);
}

//
// Visit_Variable
//
template <typename CONTEXT>
void CUTS_BE_Impl_Generator_T <CONTEXT>::
Visit_Variable (const PICML::Variable & variable)
{
  CUTS_BE_Variable_T <behavior_type> var_gen (this->context_);
  var_gen.generate (variable);
}

//
// Visit_ProvidedRequestPort
//
template <typename CONTEXT>
void CUTS_BE_Impl_Generator_T <CONTEXT>::
Visit_PeriodicEvent (const PICML::PeriodicEvent & periodic)
{
  // Begin the generation of the periodic event.
  CUTS_BE_PeriodicEvent_Begin_T <arch_type> periodic_begin_gen (this->context_);
  periodic_begin_gen.generate (periodic);

  CUTS_BE_Execution_Visitor_T <behavior_type> exec_visitor (this->context_);
  exec_visitor.generate (periodic);

  // End the generation of the periodic event.
  CUTS_BE_PeriodicEvent_End_T <arch_type> periodic_end_gen (this->context_);
  periodic_end_gen.generate (periodic);
}

//
// Visit_InEventPort
//
template <typename CONTEXT>
void CUTS_BE_Impl_Generator_T <CONTEXT>::
Visit_Attribute (const PICML::Attribute & attr)
{
  CUTS_BE_Attribute_Begin_T <arch_type> attr_begin_gen (this->context_);
  attr_begin_gen.generate (attr);

  CUTS_BE_Attribute_End_T <arch_type> attr_end_gen (this->context_);
  attr_end_gen.generate (attr);
}

//
// Visit_ProvidedRequestPort
//
template <typename CONTEXT>
void CUTS_BE_Impl_Generator_T <CONTEXT>::
Visit_ReadonlyAttribute (const PICML::ReadonlyAttribute & attr)
{
  CUTS_BE_ReadonlyAttribute_Begin_T <arch_type> attr_begin_gen (this->context_);
  attr_begin_gen.generate (attr);

  CUTS_BE_ReadonlyAttribute_End_T <arch_type> attr_end_gen (this->context_);
  attr_end_gen.generate (attr);
}

//
// get_component_factory
//
template <typename CONTEXT>
bool CUTS_BE_Impl_Generator_T <CONTEXT>::
get_component_factory (const PICML::Component & component,
                       PICML::ComponentFactory & factory)
{
  // Try and locate the real factory for the component.
  typedef std::set <PICML::ManagesComponent> Manages_Set;
  Manages_Set manages = component.srcManagesComponent ();

  if (manages.size () > 0)
  {
    PICML::ManagesComponent manage = (*manages.begin ());
    factory = manage.srcManagesComponent_end ();
    return true;
  }

  typedef std::set <PICML::ComponentRef> ComponentRef_Set;
  ComponentRef_Set refs = component.referedbyComponentRef ();

  PICML::MgaObject parent;
  std::string parent_type;

  for (ComponentRef_Set::iterator iter = refs.begin ();
       iter != refs.end ();
       iter ++)
  {
    parent = iter->parent ();
    Uml::Class type = parent.type ();

    if (type == PICML::File::meta ||  type == PICML::Package::meta)
      return this->get_component_factory (iter->ref (), factory);
  }

  return false;
}

//
// Visit_WorkerType
//
template <typename CONTEXT>
void CUTS_BE_Impl_Generator_T <CONTEXT>::
Visit_WorkerType (const PICML::WorkerType & type)
{
  PICML::Worker worker = type.ref ();

  if (Udm::null == worker)
    return;

  CUTS_BE_Worker_Variable_T <behavior_type> var_gen (this->context_);
  var_gen.generate (type, worker);
}

//
// Visit_TwowayOperation
//
template <typename CONTEXT>
void CUTS_BE_Impl_Generator_T <CONTEXT>::
Visit_TwowayOperation (const PICML::TwowayOperation & twoway)
{
  //CUTS_BE_TwowayOperation_Begin_T <CONTEXT>::generate (twoway);

  //CUTS_BE_TwowayOperation_End_T <CONTEXT>::generate (twoway);
}

//
// Visit_OnewayOperation
//
template <typename CONTEXT>
void CUTS_BE_Impl_Generator_T <CONTEXT>::
Visit_OnewayOperation (const PICML::OnewayOperation & oneway)
{
  //CUTS_BE_OnewayOperation_Begin_T <CONTEXT>::generate (oneway);

  //CUTS_BE_OnewayOperation_End_T <CONTEXT>::generate (oneway);
}

//
// Visit_ComponentFactory
//
template <typename CONTEXT>
void CUTS_BE_Impl_Generator_T <CONTEXT>::
Visit_ComponentFactory (const PICML::ComponentFactory & factory)
{
  // Visit all the component's factory operations.
  typedef std::vector <PICML::FactoryOperation> FactoryOperation_Set;
  FactoryOperation_Set operations = factory.FactoryOperation_children ();

  CUTS_BE::visit <CONTEXT> (operations,
    boost::bind (&FactoryOperation_Set::value_type::Accept,
    _1, boost::ref (*this)));

  // Visit all the base factories, so we can generate to
  // correct methods for this component's factory.
  typedef std::vector <PICML::Inherits> Inherits_Set;
  Inherits_Set inherits = factory.Inherits_kind_children ();

  CUTS_BE::visit <CONTEXT> (inherits,
    boost::bind (&CUTS_BE_Impl_Generator_T::Visit_ComponentFactory_inherits,
    this, _1));
}

//
// Visit_ComponentFactory
//
template <typename CONTEXT>
void CUTS_BE_Impl_Generator_T <CONTEXT>::
Visit_ComponentFactory_inherits (const PICML::Inherits & inherits)
{
  //PICML::ComponentFactory factory =
  //  PICML::ComponentFactory::Cast (inherits.ref ());

  //CUTS_BE::visit <CONTEXT> (factory,
  //  boost::bind (&PICML::ComponentFactory::Accept, _1, boost::ref (*this)));
}

//
// Visit_FactoryOperation
//
template <typename CONTEXT>
void CUTS_BE_Impl_Generator_T <CONTEXT>::
Visit_FactoryOperation (const PICML::FactoryOperation & fop)
{
  //CUTS_BE_FactoryOperation_Begin_T <CONTEXT>::generate (fop);

  //CUTS_BE_FactoryOperation_End_T <CONTEXT>::generate (fop);
}

//
// Visit_Supports
//
template <typename CONTEXT>
void CUTS_BE_Impl_Generator_T <CONTEXT>::
Visit_Supports (const PICML::Supports & supports)
{
  PICML::Object object = supports.ref ();

  if (object != Udm::null)
  {
    CUTS_BE::visit <CONTEXT> (object,
      boost::bind (&PICML::Object::Accept, _1, boost::ref (*this)));
  }
}

//
// Visit_Component_supports
//
template <typename CONTEXT>
void CUTS_BE_Impl_Generator_T <CONTEXT>::
Visit_Object (const PICML::Object & object)
{
  //// Write all the methods of the facet.
  //typedef std::vector <PICML::OnewayOperation> OnewayOperation_Set;
  //OnewayOperation_Set oneways = object.OnewayOperation_kind_children ();

  //CUTS_BE::visit <CONTEXT> (oneways,
  //  boost::bind (&OnewayOperation_Set::value_type::Accept,
  //  _1, boost::ref (*this)));

  //typedef std::vector <PICML::TwowayOperation> TwowayOperation_Set;
  //TwowayOperation_Set twoways = object.TwowayOperation_kind_children ();

  //CUTS_BE::visit <CONTEXT> (twoways,
  //  boost::bind (&TwowayOperation_Set::value_type::Accept,
  //  _1, boost::ref (*this)));
}

//
// write_variables_i
//
template <typename CONTEXT>
void CUTS_BE_Impl_Generator_T <CONTEXT>::
write_variables_i (const PICML::Component & component)
{
  CUTS_BE_Variables_Begin_T <behavior_type> var_begin_gen (this->context_);
  var_begin_gen.generate (component);

  // Write all the basic variables.
  typedef std::vector <PICML::Variable> Variable_Set;
  Variable_Set vars = component.Variable_kind_children ();

  std::for_each (vars.begin (),
                 vars.end (),
                 boost::bind (&PICML::Variable::Accept,
                              _1,
                              boost::ref (*this)));

  // Write all the worker related variables.
  typedef std::vector <PICML::WorkerType> WorkerType_Set;
  WorkerType_Set workers = component.WorkerType_kind_children ();

  std::for_each (workers.begin (),
                 workers.end (),
                 boost::bind (&PICML::WorkerType::Accept,
                              _1,
                              boost::ref (*this)));

  // Write the attribute variables.
  typedef std::vector <PICML::ReadonlyAttribute> ReadonlyAttribute_Set;
  ReadonlyAttribute_Set ro_attrs = component.ReadonlyAttribute_kind_children ();

  std::for_each (ro_attrs.begin (),
                 ro_attrs.end (),
                 boost::bind (&CUTS_BE_Impl_Generator_T::Visit_ReadonlyAttribute_Variable,
                              this,
                              _1));

  // Write the periodic event variables.
  typedef std::vector <PICML::PeriodicEvent> PeriodicEvent_Set;
  PeriodicEvent_Set periodics = component.PeriodicEvent_kind_children ();

  std::for_each (periodics.begin (),
                 periodics.end (),
                 boost::bind (&CUTS_BE_Impl_Generator_T::Visit_PeriodicEvent_Variable,
                              this,
                              _1));

  // End the generation of the variables.
  CUTS_BE_Variables_End_T <behavior_type> var_end_gen (this->context_);
  var_end_gen.generate (component);
}

//
// Visit_DeploymentPlans
//
template <typename CONTEXT>
void CUTS_BE_Impl_Generator_T <CONTEXT>::
Visit_DeploymentPlans (const PICML::DeploymentPlans & plans)
{
  typedef std::vector <PICML::DeploymentPlan> DeploymentPlan_Set;
  DeploymentPlan_Set dps = plans.DeploymentPlan_children ();

  CUTS_BE::visit <CONTEXT> (dps,
    boost::bind (&DeploymentPlan_Set::value_type::Accept, _1, boost::ref (*this)));
}

//
// Visit_DeploymentPlan
//
template <typename CONTEXT>
void CUTS_BE_Impl_Generator_T <CONTEXT>::
Visit_DeploymentPlan (const PICML::DeploymentPlan & plan)
{
  CUTS_BE_Deployment_Generator_T <CONTEXT> generator;
  PICML::DeploymentPlan (plan).Accept (generator);
}
