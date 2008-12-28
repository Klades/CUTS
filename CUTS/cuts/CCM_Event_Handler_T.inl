// -*- C++ -*-
// $Id$

//
// CUTS_CCM_Event_Handler_T
//
template <typename T, typename EVENT>
CUTS_INLINE
CUTS_CCM_Event_Handler_T <T, EVENT>::CUTS_CCM_Event_Handler_T (void)
: component_ (0),
  method_ (0),
  thr_count_ (1)
{

}

//
// CUTS_CCM_Event_Handler_T
//
template <typename T, typename EVENT>
CUTS_INLINE
CUTS_CCM_Event_Handler_T <T, EVENT>::
CUTS_CCM_Event_Handler_T (T * component, callback_type method)
: component_ (component),
  method_ (method),
  thr_count_ (1)
{

}

//
// ~CUTS_CCM_Event_Handler_T
//
template <typename T, typename EVENT>
CUTS_INLINE
CUTS_CCM_Event_Handler_T <T, EVENT>::~CUTS_CCM_Event_Handler_T (void)
{

}

//
// init
//
template <typename T, typename EVENT>
CUTS_INLINE
int CUTS_CCM_Event_Handler_T <T, EVENT>::
init (T * component, callback_type method)
{
  this->component_ = component;
  this->method_ = method;
  return 0;
}
