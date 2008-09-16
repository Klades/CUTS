// $Id$

//
// spawn_i
//
template <typename COMPONENT, typename EVENTTYPE>
CUTS_INLINE
int CUTS_Async_Event_Handler_T <COMPONENT, EVENTTYPE>::
spawn_i (size_t count)
{
  ACE_DEBUG ((LM_DEBUG,
              "%T (%t) - %M - spawning %d threads\n",
              count));

  ACE_GUARD_RETURN (ACE_Thread_Mutex, 
                    guard, 
                    this->spawn_lock_, 
                    -1);
            
  // We need to spawn <thread_count_> number of threads
  // with specified <priority_>.
  int retval = this->thr_manager_.spawn_n (count,
                                           &THIS::event_loop,
                                           this,
                                           THR_NEW_LWP | THR_JOINABLE |
                                           THR_INHERIT_SCHED,
                                           this->priority_,
                                           GRP_ACTIVE);

  if (retval != -1)
  {
    // Initialize the count value and wait for all the 
    // threads to spawn.
    this->spawn_count_ = count;
    this->spawn_condition_.wait ();
  } 
}

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
