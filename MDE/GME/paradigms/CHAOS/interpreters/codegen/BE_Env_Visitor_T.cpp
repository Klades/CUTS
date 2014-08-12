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
// Visit_Environment
//
template <typename CONTEXT>
void CUTS_BE_Env_Visitor_T <CONTEXT>::
Visit_Environment (const CHAOS::Environment & env)
{
  typedef std::set <CHAOS::MultiInput> MultiInput_Set;
  MultiInput_Set inputs = env.dstMultiInput ();

  CUTS_BE::visit <CONTEXT> (inputs,
    [&] (MultiInput_Set::value_type item) {item.Accept (*this);});
}

//
// Visit_MulitInput
//
template <typename CONTEXT>
void CUTS_BE_Env_Visitor_T <CONTEXT>::
Visit_MultiInput (const CHAOS::MultiInput & input)
{
  CHAOS::MultiInputAction action = input.dstMultiInput_end ();

  CUTS_BE::visit <CONTEXT> (action,
    [&] (CHAOS::MultiInputAction item) {item.Accept (*this);});
}

//
// Visit_InputAction
//
template <typename CONTEXT>
void CUTS_BE_Env_Visitor_T <CONTEXT>::
Visit_MultiInputAction (const CHAOS::MultiInputAction & action)
{
  CUTS_BE_Environment_Method_Begin_T <CONTEXT> env_method_begin_gen (this->context_);
  env_method_begin_gen.generate (action);

  CUTS_BE_Execution_Visitor_T <CONTEXT> exec_visitor (this->context_);
  CHAOS::MultiInputAction mia (action);

  CUTS_BE::visit <CONTEXT> (mia,
    [&] (CHAOS::MultiInputAction item) {item.Accept (exec_visitor);});

  CUTS_BE_Environment_Method_End_T <CONTEXT> env_method_end_gen (this->context_);
  env_method_end_gen.generate (action);
}
