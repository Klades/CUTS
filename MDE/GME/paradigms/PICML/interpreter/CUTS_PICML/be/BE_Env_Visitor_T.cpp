// $Id$

#include "BE_Execution_Visitor_T.h"

//
// CUTS_BE_Env_Visitor_T
//
template <typename CONTEXT>
CUTS_BE_Env_Visitor_T <CONTEXT>::
CUTS_BE_Env_Visitor_T (CONTEXT & context)
: context_ (context)
{

}

//
// ~CUTS_BE_Env_Visitor_T
//
template <typename CONTEXT>
CUTS_BE_Env_Visitor_T <CONTEXT>::~CUTS_BE_Env_Visitor_T (void)
{

}

//
// visit_Environment
//
template <typename CONTEXT>
void CUTS_BE_Env_Visitor_T <CONTEXT>::
visit_Environment (PICML::Environment_in env)
{
  CUTS_BE::visit <CONTEXT> (env->src_of_MultiInput (),
    [&] (PICML::MultiInput item) {item->accept (this);});
}

//
// visit_MulitInput
//
template <typename CONTEXT>
void CUTS_BE_Env_Visitor_T <CONTEXT>::
visit_MultiInput (PICML::MultiInput_in input)
{
  CUTS_BE::visit <CONTEXT> (input->dst_MultiInputAction (),
    [&] (PICML::MultiInputAction action) {action->accept (this);});
}

//
// visit_InputAction
//
template <typename CONTEXT>
void CUTS_BE_Env_Visitor_T <CONTEXT>::
visit_MultiInputAction (PICML::MultiInputAction_in action)
{
  CUTS_BE_Environment_Method_Begin_T <architecture_type> env_method_begin_gen (this->context_);
  env_method_begin_gen.generate (action);

  CUTS_BE_Execution_Visitor_T <behavior_type> exec_visitor (this->context_);
  action->accept (&exec_visitor);

  CUTS_BE_Environment_Method_End_T <architecture_type> env_method_end_gen (this->context_);
  env_method_end_gen.generate (action);
}
