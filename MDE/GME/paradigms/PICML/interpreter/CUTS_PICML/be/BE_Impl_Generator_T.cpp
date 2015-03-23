// $Id$

#if !defined (__CUTS_INLINE__)
#include "BE_Impl_Generator_T.inl"
#endif

#include "BE_algorithm.h"
#include "BE_Preprocessor_T.h"
#include "BE_Env_Visitor_T.h"
#include "BE_Execution_Visitor_T.h"
#include "game/mga/utils/modelgen.h"

#include "boost/bind.hpp"
#include "boost/iterator/filter_iterator.hpp"


//
// visit_RootFolder
//
template <typename CONTEXT>
void CUTS_BE_Impl_Generator_T <CONTEXT>::
visit_RootFolder (PICML::RootFolder_in root)
{
  CUTS_BE::visit <CONTEXT> (root->get_ComponentImplementations (),
    [this] (PICML::ComponentImplementation & i) {i->accept (this);});

  CUTS_BE::visit <CONTEXT> (root->get_DeploymentPlans (),
    [this] (PICML::DeploymentPlans & i) {i->accept (this);});
}

//
// visit_ComponentImplementations
//
template <typename CONTEXT>
void CUTS_BE_Impl_Generator_T <CONTEXT>::
visit_ComponentImplementations (PICML::ComponentImplementations_in impls)
{
  GAME::visit_all () (impls->get_ComponentImplementationContainers (), this);
}

//
// visit_ComponentImplementationContainer
//
template <typename CONTEXT>
void CUTS_BE_Impl_Generator_T <CONTEXT>::
visit_ComponentImplementationContainer (PICML::ComponentImplementationContainer_in container)
{
  // Preprocess the container and extract as much information
  // as we can about the current component's implementation.
  this->pp_.preprocess (container);

  // visit the monolithic implementations
  CUTS_BE::visit <CONTEXT> (container->children <PICML::ComponentImplementation> (),
    [this] (PICML::MonolithicImplementation & i) {i->accept (this);});
}

//
// visit_MonolithicImplementation
//
template <typename CONTEXT>
void CUTS_BE_Impl_Generator_T <CONTEXT>::
visit_MonolithicImplementation (PICML::MonolithicImplementation_in monoimpl)
{
  // Get the parent of the monolithic implementation.
  PICML::ComponentImplementationContainer container =
    monoimpl->parent ();

  // Get the implementation node and write all the includes.
  const CUTS_BE_Impl_Node * impl = 0;
  this->pp_.impls ().find (monoimpl->name (), impl);

  if (0 == impl)
    return;

  CUTS_BE_File_Open_T <architecture_type> file_open_gen (this->context_);
  file_open_gen.generate (container, monoimpl);

  // Write the prologue for the file.
  CUTS_BE_Prologue_T <architecture_type> prologue_gen (this->context_);
  prologue_gen.generate (container, monoimpl);

  // Write the include files for this implementation.
  CUTS_BE::visit <CONTEXT> (impl->include_,
    [this] (const std::string & s) {return this->visit_Include (s);});

  // Figure out what type of component we are implementing. Right
  // now there is a one-to-one implementation to component type
  // mapping. Therefore, the component has the known behavior
  // for this respective implementation.
  if (monoimpl->has_src_of_Implements ())
  {
    PICML::Implements implements = monoimpl->src_of_Implements ();

    // Extract the component type being implemented.
    PICML::ComponentRef ref = implements->dst_ComponentRef ();
    PICML::Component component = ref->refers_to_Component ();

    // Write the beginning of the component's implementation.
    CUTS_BE_Component_Impl_Begin_T <architecture_type> comp_impl_begin (this->context_);
    comp_impl_begin.generate (monoimpl, component);

    // Visit the component.
    component->accept (this);

    // Write the end of the component's implementation.
    CUTS_BE_Component_Impl_End_T <architecture_type> comp_impl_end (this->context_);
    comp_impl_end.generate (monoimpl, component);

    // Get all the facets in the component so that we can
    // generate their implementation.
    CUTS_BE::visit <CONTEXT> (component->get_ProvidedRequestPorts (),
      [this] (const PICML::ProvidedRequestPort & p) {return this->visit_ProvidedRequestPort_impl (p);});

    // Find the component implementation artifact so we can generate
    // the entrypoint for this component's implementation.
    this->monoimpl_ = monoimpl;
    GAME::visit_all () (monoimpl->src_of_MonolithprimaryArtifact (), this);

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
  CUTS_BE_Epilogue_T <architecture_type> epilogue_gen (this->context_);
  epilogue_gen.generate (container, monoimpl);

  CUTS_BE_File_Close_T <architecture_type> file_close_gen (this->context_);
  file_close_gen.generate (container, monoimpl);
}

//
// visit_Component
//
template <typename CONTEXT>
void CUTS_BE_Impl_Generator_T <CONTEXT>::
visit_Component (PICML::Component_in component)
{
  // Determine if we are ready to write the variables.
  if (!CUTS_BE_Write_Variables_Last_T <CONTEXT>::result_type)
    this->write_variables_i (component);

  // Visit all the supported interfaces.
  CUTS_BE::visit <CONTEXT> (component->get_Supportss (),
    [this] (const PICML::Supports & i) {return i->accept (this);});

  // Visit all the InEventPort elements of the <component>.
  CUTS_BE::visit <CONTEXT> (component->get_InEventPorts (),
    [this] (const PICML::InEventPort & i) {return i->accept (this);});

  // Visit all the ProvidedRequestPort elements of the <component>.
  CUTS_BE::visit <CONTEXT> (component->get_ProvidedRequestPorts (),
    [this] (const PICML::ProvidedRequestPort & i) {return i->accept (this);});

  // Visit all the PeriodicEvent elements of the <component>.
  CUTS_BE::visit <CONTEXT> (component->get_PeriodicEvents (),
    [this] (const PICML::PeriodicEvent & i) {return i->accept (this);});

  // Visit all the Attribute elements of the <component>.
  CUTS_BE::visit <CONTEXT> (component->get_Attributes (),
    [this] (const PICML::Attribute & i) {return i->accept (this);});

  // Visit all the ReadonlyAttribute elements of the <component>.
  for (auto ro : component->get_ReadonlyAttributes ())
    ro->accept (this);

  // Get the environment for the component.
  if (component->has_Environment ())
  {
    PICML::Environment env = component->get_Environment ();

    // Begin generating environment related metadata.
    CUTS_BE_Environment_Begin_T <architecture_type> env_begin_gen (this->context_);
    env_begin_gen.generate (component);

    CUTS_BE_Env_Visitor_T <CONTEXT> env_visitor (this->context_);
    env->accept (&env_visitor);

    // End generating environment related metadata.
    CUTS_BE_Environment_End_T <architecture_type> env_end_gen (this->context_);
    env_end_gen.generate (component);
  }

  // Determine if we are writing the variables
  if (CUTS_BE_Write_Variables_Last_T <CONTEXT>::result_type)
    this->write_variables_i (component);
}

//
// visit_MonolithprimaryArtifact
//
template <typename CONTEXT>
void CUTS_BE_Impl_Generator_T <CONTEXT>::
visit_MonolithprimaryArtifact (PICML::MonolithprimaryArtifact_in primary)
{
  this->visit_ImplementationArtifactReference (primary->dst_ImplementationArtifactReference ());
}

//
// visit_ImplementationArtifactReference
//
template <typename CONTEXT>
void CUTS_BE_Impl_Generator_T <CONTEXT>::
visit_ImplementationArtifactReference (PICML::ImplementationArtifactReference_in artref)
{
  if (artref->meta ()->name () == PICML::ComponentImplementationArtifact::impl_type::metaname)
  {
    CUTS_BE_Component_Impl_Entrypoint_T <architecture_type> entrypoint_gen (this->context_);
    entrypoint_gen.generate (this->monoimpl_, PICML::ComponentImplementationArtifact::_narrow (artref));
  }
}

//
// visit_InEventPort
//
template <typename CONTEXT>
void CUTS_BE_Impl_Generator_T <CONTEXT>::
visit_InEventPort (PICML::InEventPort_in sink)
{
  std::vector <PICML::Property> properties;

  if (sink->has_src_of_Input ())
  {
    PICML::Input input = sink->src_of_Input ();

    // Get the properties associate with the input port.
    PICML::InputAction action = input->dst_InputAction ();
    GAME::Mga::iter_to_collection (action->children <PICML::Property> (), properties);
  }

  // We are generating a regular event port.
  CUTS_BE_InEventPort_Begin_T <architecture_type> port_begin_gen (this->context_);
  port_begin_gen.generate (sink, properties);

  CUTS_BE_Execution_Visitor_T <behavior_type> exec_visitor (this->context_);
  exec_visitor.generate (sink);

  CUTS_BE_InEventPort_End_T <architecture_type> port_end_gen (this->context_);
  port_end_gen.generate (sink, properties);
}

//
// visit_ProvidedRequestPort
//
template <typename CONTEXT>
void CUTS_BE_Impl_Generator_T <CONTEXT>::
visit_ProvidedRequestPort (PICML::ProvidedRequestPort_in facet)
{
  //// Begin the generation of the provided request port.
  //CUTS_BE_ProvidedRequestPort_Begin_T <architecture_type> port_begin_gen (this->context_);
  //port_begin_gen.generate (facet);

  //CUTS_BE_Execution_Visitor_T <behavior_type> exec_visitor (this->context_);
  //exec_visitor.generate (facet);

  //// End the generation of the provided request port.
  //CUTS_BE_ProvidedRequestPort_End_T <architecture_type> port_end_gen (this->context_);
  //port_end_gen.generate (facet);
}

//
// visit_ProvidedRequestPort
//
template <typename CONTEXT>
void CUTS_BE_Impl_Generator_T <CONTEXT>::
visit_ProvidedRequestPort_impl (PICML::ProvidedRequestPort_in facet)
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
// visit_Include
//
template <typename CONTEXT>
void CUTS_BE_Impl_Generator_T <CONTEXT>::
visit_Include (const std::string & include)
{
  CUTS_BE_Include_File_T <CONTEXT> include_gen (this->context_);
  include_gen.generate (include);
}

//
// visit_PeriodicEvent_Variable
//
template <typename CONTEXT>
void CUTS_BE_Impl_Generator_T <CONTEXT>::
visit_PeriodicEvent_Variable (PICML::PeriodicEvent_in periodic)
{
  CUTS_BE_PeriodicEvent_Variable_T <behavior_type> var_gen (this->context_);
  var_gen.generate (periodic);
}

//
// visit_Include
//
template <typename CONTEXT>
void CUTS_BE_Impl_Generator_T <CONTEXT>::
visit_ReadonlyAttribute_Variable (PICML::ReadonlyAttribute_in attr)
{
  CUTS_BE_Attribute_Variable_T <behavior_type> var_gen (this->context_);
  var_gen.generate (attr);
}

//
// visit_Variable
//
template <typename CONTEXT>
void CUTS_BE_Impl_Generator_T <CONTEXT>::
visit_Variable (PICML::Variable_in variable)
{
  CUTS_BE_Variable_T <behavior_type> var_gen (this->context_);
  var_gen.generate (variable);
}

//
// visit_ProvidedRequestPort
//
template <typename CONTEXT>
void CUTS_BE_Impl_Generator_T <CONTEXT>::
visit_PeriodicEvent (PICML::PeriodicEvent_in periodic)
{
  // Begin the generation of the periodic event.
  CUTS_BE_PeriodicEvent_Begin_T <architecture_type> periodic_begin_gen (this->context_);
  periodic_begin_gen.generate (periodic);

  CUTS_BE_Execution_Visitor_T <behavior_type> exec_visitor (this->context_);
  exec_visitor.generate (periodic);

  // End the generation of the periodic event.
  CUTS_BE_PeriodicEvent_End_T <architecture_type> periodic_end_gen (this->context_);
  periodic_end_gen.generate (periodic);
}

//
// visit_InEventPort
//
template <typename CONTEXT>
void CUTS_BE_Impl_Generator_T <CONTEXT>::
visit_Attribute (PICML::Attribute_in attr)
{
  CUTS_BE_Attribute_Begin_T <architecture_type> attr_begin_gen (this->context_);
  attr_begin_gen.generate (attr);

  CUTS_BE_Attribute_End_T <architecture_type> attr_end_gen (this->context_);
  attr_end_gen.generate (attr);
}

//
// visit_ProvidedRequestPort
//
template <typename CONTEXT>
void CUTS_BE_Impl_Generator_T <CONTEXT>::
visit_ReadonlyAttribute (PICML::ReadonlyAttribute_in attr)
{
  CUTS_BE_ReadonlyAttribute_Begin_T <architecture_type> attr_begin_gen (this->context_);
  attr_begin_gen.generate (attr);

  CUTS_BE_ReadonlyAttribute_End_T <architecture_type> attr_end_gen (this->context_);
  attr_end_gen.generate (attr);
}

//
// get_component_factory
//
template <typename CONTEXT>
bool CUTS_BE_Impl_Generator_T <CONTEXT>::
get_component_factory (const PICML::Component_in component,
                       PICML::ComponentFactory_in factory)
{
  // Try and locate the real factory for the component.
  GAME::Mga::Collection_T <PICML::ManagesComponent> manages =
    component->dst_of_ManagesComponent ();

  if (manages.count () > 0)
  {
    PICML::ManagesComponent manage = manages.first ();
    factory = manage->src_ComponentFactory ();
    return true;
  }

  typedef std::set <PICML::ComponentRef> ComponentRef_Set;
  ComponentRef_Set refs = component.referedbyComponentRef ();

  GAME::Mga::Object parent;
  std::string parent_type;

  for (auto ref : component->referenced_by ())
  {
    if (ref->meta ()->name () != PICML::ComponentRef::impl_type::metaname)
      continue;

    parent = ref->parent ();
    parent_type = parent->meta ()->name ();

    if (parent_type == PICML::File::impl_type::metaname
        || parent_type == PICML::Package::impl_type::metaname)
      return this->get_component_factory (component, factory);
  }

  return false;
}

//
// visit_WorkerType
//
template <typename CONTEXT>
void CUTS_BE_Impl_Generator_T <CONTEXT>::
visit_WorkerType (PICML::WorkerType_in type)
{
  PICML::Worker worker = type->refers_to_Worker ();

  CUTS_BE_Worker_Variable_T <behavior_type> var_gen (this->context_);
  var_gen.generate (type, worker);
}

//
// visit_TwowayOperation
//
template <typename CONTEXT>
void CUTS_BE_Impl_Generator_T <CONTEXT>::
visit_TwowayOperation (PICML::TwowayOperation_in twoway)
{
  //CUTS_BE_TwowayOperation_Begin_T <CONTEXT>::generate (twoway);

  //CUTS_BE_TwowayOperation_End_T <CONTEXT>::generate (twoway);
}

//
// visit_OnewayOperation
//
template <typename CONTEXT>
void CUTS_BE_Impl_Generator_T <CONTEXT>::
visit_OnewayOperation (PICML::OnewayOperation_in oneway)
{
  //CUTS_BE_OnewayOperation_Begin_T <CONTEXT>::generate (oneway);

  //CUTS_BE_OnewayOperation_End_T <CONTEXT>::generate (oneway);
}

//
// visit_ComponentFactory
//
template <typename CONTEXT>
void CUTS_BE_Impl_Generator_T <CONTEXT>::
visit_ComponentFactory (PICML::ComponentFactory_in factory)
{
  // Visit all the component's factory operations.
  CUTS_BE::visit <CONTEXT> (factory->get_FactoryOperations (),
    [this] (PICML::FactoryOperation & i) {i->accept (this);});

  // Visit all the base factories, so we can generate to
  // correct methods for this component's factory.
  CUTS_BE::visit <CONTEXT> (factory->get_Inheritss (),
    [this] (PICML::Inherits & i) {i->accept (this);});
}

//
// visit_ComponentFactory
//
template <typename CONTEXT>
void CUTS_BE_Impl_Generator_T <CONTEXT>::
visit_ComponentFactory_inherits (PICML::Inherits_in inherits)
{
  //PICML::ComponentFactory factory =
  //  PICML::ComponentFactory::Cast (inherits.ref ());

  //CUTS_BE::visit <CONTEXT> (factory,
  //  boost::bind (&PICML::ComponentFactory::Accept, _1, boost::ref (*this)));
}

//
// visit_FactoryOperation
//
template <typename CONTEXT>
void CUTS_BE_Impl_Generator_T <CONTEXT>::
visit_FactoryOperation (PICML::FactoryOperation_in fop)
{
  //CUTS_BE_FactoryOperation_Begin_T <CONTEXT>::generate (fop);

  //CUTS_BE_FactoryOperation_End_T <CONTEXT>::generate (fop);
}

//
// visit_Supports
//
template <typename CONTEXT>
void CUTS_BE_Impl_Generator_T <CONTEXT>::
visit_Supports (PICML::Supports_in supports)
{
  if (supports->Object_is_nil ())
    return;

  PICML::Object object = supports->refers_to_Object ();

  CUTS_BE::visit <CONTEXT> (supports->refers_to_Object (),
    [this] (PICML::Object & i) {i->accept (this);});
}

//
// visit_Component_supports
//
template <typename CONTEXT>
void CUTS_BE_Impl_Generator_T <CONTEXT>::
visit_Object (PICML::Object_in object)
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
write_variables_i (const PICML::Component_in component)
{
  CUTS_BE_Variables_Begin_T <behavior_type> var_begin_gen (this->context_);
  var_begin_gen.generate (component);

  // Write all the basic variables.
  GAME::visit_all () (component->get_Variables (), this);

  // Write all the worker related variables.
  GAME::visit_all () (component->get_WorkerTypes (), this);

  // Write the attribute variables.
  GAME::visit_all () (component->get_ReadonlyAttributes (), this);

  // Write the periodic event variables.
  GAME::visit_all () (component->get_PeriodicEvents (), this);

  // End the generation of the variables.
  CUTS_BE_Variables_End_T <behavior_type> var_end_gen (this->context_);
  var_end_gen.generate (component);
}
