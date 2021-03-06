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
  thr_count_ (1),
  affinity_mask_ (0)
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

//
// thread_count
//
template <typename T, typename EVENT>
CUTS_INLINE
void CUTS_CCM_Event_Handler_T <T, EVENT>::thread_count (size_t count)
{
  this->thr_count_ = count;
}

//
// init
//
template <typename T, typename EVENT>
CUTS_INLINE
void CUTS_CCM_Event_Handler_T <T, EVENT>::affinity_mask (ACE_UINT32 mask)
{
  this->affinity_mask_ = mask;
}
