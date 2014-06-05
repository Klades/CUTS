// -*- C++ -*-
// $Id$

//
// probability
//
template <typename COMPONENT>
CUTS_INLINE
void CUTS_Application_Task_T <COMPONENT>::
init (Component_Type * component, Method_Pointer method)
{
  this->component_ = component;
  this->method_ = method;
}
