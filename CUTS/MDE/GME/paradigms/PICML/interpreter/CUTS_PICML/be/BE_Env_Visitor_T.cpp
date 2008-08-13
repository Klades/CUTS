// $Id$

#include "BE_Execution_Visitor_T.h"

//
// CUTS_BE_Env_Visitor_T
//
template <typename IMPL_STRATEGY>
CUTS_BE_Env_Visitor_T <IMPL_STRATEGY>::CUTS_BE_Env_Visitor_T (void)
{

}

//
// ~CUTS_BE_Env_Visitor_T
//
template <typename IMPL_STRATEGY>
CUTS_BE_Env_Visitor_T <IMPL_STRATEGY>::~CUTS_BE_Env_Visitor_T (void)
{

}

//
// Visit_Environment
//
template <typename IMPL_STRATEGY>
void CUTS_BE_Env_Visitor_T <IMPL_STRATEGY>::
Visit_Environment (const PICML::Environment & env)
{
  typedef std::set <PICML::MultiInput> MultiInput_Set;
  MultiInput_Set inputs = env.dstMultiInput ();

  CUTS_BE::visit <IMPL_STRATEGY> (inputs,
    boost::bind (&MultiInput_Set::value_type::Accept,
    _1, boost::ref (*this)));
}

//
// Visit_MulitInput
//
template <typename IMPL_STRATEGY>
void CUTS_BE_Env_Visitor_T <IMPL_STRATEGY>::
Visit_MultiInput (const PICML::MultiInput & input)
{
  PICML::MultiInputAction action = input.dstMultiInput_end ();

  CUTS_BE::visit <IMPL_STRATEGY> (action,
    boost::bind (&PICML::MultiInputAction::Accept, _1, boost::ref (*this)));
}

//
// Visit_InputAction
//
template <typename IMPL_STRATEGY>
void CUTS_BE_Env_Visitor_T <IMPL_STRATEGY>::
Visit_MultiInputAction (const PICML::MultiInputAction & action)
{
  CUTS_BE_Environment_Method_Begin_T <IMPL_STRATEGY>::generate (action);

  CUTS_BE_Execution_Visitor_T <IMPL_STRATEGY> exec_visitor;
  PICML::MultiInputAction mia (action);

  CUTS_BE::visit <IMPL_STRATEGY> (mia,
    boost::bind (&PICML::MultiInputAction::Accept, _1, boost::ref (exec_visitor)));

  CUTS_BE_Environment_Method_End_T <IMPL_STRATEGY>::generate (action);
}
