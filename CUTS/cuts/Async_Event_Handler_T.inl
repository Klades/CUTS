// $Id$

//
// thread_count
//
template <typename COMPONENT, typename EVENTTYPE>
CUTS_INLINE
size_t CUTS_Async_Event_Handler_T <COMPONENT, EVENTTYPE>::
thread_count (void) const
{
  return this->thread_map_.current_size ();
}

//
// priority
//
template <typename COMPONENT, typename EVENTTYPE>
CUTS_INLINE
int CUTS_Async_Event_Handler_T <COMPONENT, EVENTTYPE>::
priority (void) const
{
  return this->priority_;
}
