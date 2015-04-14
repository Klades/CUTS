// -*- C++ -*-
// $Id$

//
// CUTS_BE_Traits
//
CUTS_INLINE
CUTS_BE_Traits::CUTS_BE_Traits (void)
{

}

//
// ~CUTS_BE_Traits
//
CUTS_INLINE
CUTS_BE_Traits::~CUTS_BE_Traits (void)
{

}

CUTS_INLINE
bool CUTS_BE_Traits::
open_file (const PICML::ComponentImplementationContainer_in container)
{
  return false;
}

CUTS_INLINE
void CUTS_BE_Traits::
close_file (const PICML::ComponentImplementationContainer_in container)
{

}

CUTS_INLINE
void CUTS_BE_Traits::
write_prologue (const PICML::ComponentImplementationContainer_in container)
{

}

CUTS_INLINE
void CUTS_BE_Traits::
write_epilogue (const PICML::ComponentImplementationContainer_in container)
{

}

CUTS_INLINE
void CUTS_BE_Traits::
write_includes (const CUTS_String_Set & includes)
{

}

CUTS_INLINE
void CUTS_BE_Traits::
write_impl_begin (const PICML::MonolithicImplementation_in monoimpl,
                  const PICML::Component_in type)
{

}

CUTS_INLINE
void CUTS_BE_Traits::
write_impl_end (const PICML::MonolithicImplementation_in,
                const PICML::Component_in type)
{

}

CUTS_INLINE
void CUTS_BE_Traits::
write_object_impl_begin (const PICML::Component_in component,
                         const PICML::ProvidedRequestPort_in facet)
{

}

CUTS_INLINE
void CUTS_BE_Traits::
write_object_impl_end (const PICML::Component_in component,
                       const PICML::ProvidedRequestPort_in facet)
{

}

CUTS_INLINE
void CUTS_BE_Traits::
write_factory_impl_begin (const PICML::ComponentFactory_in factory,
                          const PICML::MonolithicImplementation_in impl,
                          const PICML::Component_in type)
{

}

CUTS_INLINE
void CUTS_BE_Traits::
write_factory_impl_end (const PICML::ComponentFactory_in factory,
                        const PICML::MonolithicImplementation_in impl,
                        const PICML::Component_in type)
{

}

CUTS_INLINE
void CUTS_BE_Traits::
write_ProvidedRequestPort_begin (const PICML::ProvidedRequestPort_in facet)
{

}

CUTS_INLINE
void CUTS_BE_Traits::
write_ProvidedRequestPort_end (const PICML::ProvidedRequestPort_in facet)
{

}

CUTS_INLINE
void CUTS_BE_Traits::
write_InEventPort_begin (const PICML::InEventPort_in sink)
{

}

CUTS_INLINE
void CUTS_BE_Traits::
write_InEventPort_end (const PICML::InEventPort_in sink)
{

}

CUTS_INLINE
void CUTS_BE_Traits::
write_Attribute_begin (const PICML::Attribute_in attr)
{

}

CUTS_INLINE
void CUTS_BE_Traits::
write_Attribute_end (const PICML::Attribute_in attr)
{

}

CUTS_INLINE
void CUTS_BE_Traits::
write_ReadonlyAttribute_begin (const PICML::ReadonlyAttribute_in ro_attr)
{

}

CUTS_INLINE
void CUTS_BE_Traits::
write_ReadonlyAttribute_end (const PICML::ReadonlyAttribute_in ro_attr)
{

}

CUTS_INLINE
void CUTS_BE_Traits::
write_PeriodicEvent_begin (const PICML::PeriodicEvent_in periodic)
{

}

CUTS_INLINE
void CUTS_BE_Traits::
write_PeriodicEvent_end (const PICML::PeriodicEvent_in periodic)
{

}

CUTS_INLINE
void CUTS_BE_Traits::
write_ApplicationTask_begin (const PICML::ApplicationTask_in apptask)
{

}

CUTS_INLINE
void CUTS_BE_Traits::
write_ApplicationTask_end (const PICML::ApplicationTask_in apptask)
{

}

CUTS_INLINE
void CUTS_BE_Traits::
write_OnewayOperation_begin (const PICML::OnewayOperation_in oneway)
{

}

CUTS_INLINE
void CUTS_BE_Traits::
write_OnewayOperation_end (const PICML::OnewayOperation_in oneway)
{

}

CUTS_INLINE
void CUTS_BE_Traits::
write_TwowayOperation_begin (const PICML::TwowayOperation_in twoway)
{

}

CUTS_INLINE
void CUTS_BE_Traits::
write_TwowayOperation_end (const PICML::TwowayOperation_in twoway)
{

}

CUTS_INLINE
void CUTS_BE_Traits::
write_environment_begin (const PICML::Component_in component)
{

}

CUTS_INLINE
void CUTS_BE_Traits::
write_environment_end (const PICML::Component_in component)
{

}

CUTS_INLINE
void CUTS_BE_Traits::
write_environment_method_begin (const PICML::MultiInputAction_in action)
{

}

CUTS_INLINE
void CUTS_BE_Traits::
write_environment_method_end (const PICML::MultiInputAction_in)
{

}

CUTS_INLINE
void CUTS_BE_Traits::
write_variables_begin (const PICML::Component_in component)
{

}

CUTS_INLINE
void CUTS_BE_Traits::
write_variable (const PICML::Variable_in variable)
{

}

CUTS_INLINE
void CUTS_BE_Traits::
write_worker_variable (const PICML::WorkerType_in type,
                       const PICML::Worker_in worker)
{

}

CUTS_INLINE
void CUTS_BE_Traits::
write_ReadonlyAttribute_variable (const PICML::ReadonlyAttribute_in type)
{

}

CUTS_INLINE
void CUTS_BE_Traits::
write_PeriodicEvent_variable (const PICML::PeriodicEvent_in periodic)
{

}

CUTS_INLINE
void CUTS_BE_Traits::
write_ApplicationTask_variable (const PICML::ApplicationTask & apptask)
{

}

CUTS_INLINE
void CUTS_BE_Traits::write_variables_end (void)
{

}

CUTS_INLINE
void CUTS_BE_Traits::
write_precondition (const std::string & precondition)
{

}

CUTS_INLINE
void CUTS_BE_Traits::
write_postcondition (const std::string & postcondition)
{

}

CUTS_INLINE
void CUTS_BE_Traits::
write_action_property (const PICML::Property_in property)
{

}

CUTS_INLINE
void CUTS_BE_Traits::
write_WorkerAction_begin (const PICML::Worker_in worker,
                          const PICML::Action_in action)
{

}

CUTS_INLINE
void CUTS_BE_Traits::
write_OutputAction_begin (const PICML::OutputAction_in action)
{

}

CUTS_INLINE
void CUTS_BE_Traits::write_action_end (void)
{

}

CUTS_INLINE
void CUTS_BE_Traits::
write_FactoryOperation_begin (const PICML::FactoryOperation_in factory)
{

}

CUTS_INLINE
void CUTS_BE_Traits::
write_FactoryOperation_end (const PICML::FactoryOperation_in factory)
{

}
