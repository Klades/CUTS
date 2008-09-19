// $Id$

#if !defined (__CUTS_INLINE__)
#include "cuts/Async_Event_Handler_T.inl"
#endif

/**
 * Default thread count for the event handler.
 *
 * @note Should this be placed in config.h??
 */
#define CUTS_DEFAULT_THREAD_COUNT 1

//
// CUTS_Event_Handler_T
//
template <typename COMPONENT, typename EVENTTYPE>
CUTS_Async_Event_Handler_T <COMPONENT, EVENTTYPE>::
CUTS_Async_Event_Handler_T (Config_Type & config)
: Event_Handler_Base (config),
  priority_ (ACE_DEFAULT_THREAD_PRIORITY),
  spawn_condition_ (spawn_lock_)
{
  this->activate ();
}

//
// ~CUTS_Event_Handler_T
//
template <typename COMPONENT, typename EVENTTYPE>
CUTS_Async_Event_Handler_T <COMPONENT, EVENTTYPE>::
~CUTS_Async_Event_Handler_T (void)
{
  this->deactivate ();
}

//
// event_loop
//
template <typename COMPONENT, typename EVENTTYPE>
ACE_THR_FUNC_RETURN
CUTS_Async_Event_Handler_T <COMPONENT, EVENTTYPE>::event_loop (void * param)
{
  CUTS_TRACE ("CUTS_Async_Event_Handler_T <COMPONENT, EVENTTYPE>::event_loop (void *)");

  bool active = true;
  THIS * _this = reinterpret_cast <THIS *> (param);

  // Register the thread with the event handler.
  if (_this->register_thread (&active) == -1)
  {
    ACE_ERROR_RETURN ((LM_ERROR,
                       "%M -%T - failed to register event thread\n"),
                       0);
  }

  while (active)
  {
    // Get the next event from the queue.
    EVENTTYPE * event = 0;
    ACE_Time_Value toc;

    if (_this->event_queue_.dequeue (event, &toc) != -1)
    {
      // Calculate how long the event was in the queue.
      ACE_Time_Value queue_time = ACE_OS::gettimeofday ();
      queue_time -= toc;

      if (event != 0)
      {
        // Pass control to the shared implementation.
        _this->handle_event_i (event, queue_time);

        // Release the event.
        CORBA::remove_ref (event);
      }
    }
  }

  // Unregister the thread before we let it exit.
  _this->unregister_thread ();
  return 0;
}

//
// activate
//
template <typename COMPONENT, typename EVENTTYPE>
void CUTS_Async_Event_Handler_T <COMPONENT, EVENTTYPE>::activate (void)
{
  // Make sure we have at least default number of threads spawned.
  if (this->thread_count () == 0)
    this->spawn_i (CUTS_DEFAULT_THREAD_COUNT);
}

//
// deactivate
//
template <typename COMPONENT, typename EVENTTYPE>
void CUTS_Async_Event_Handler_T <COMPONENT, EVENTTYPE>::deactivate (void)
{
  // Gracefully empty the <event_queue_> and releasing all the
  // references to the CORBA events.
  if (!this->event_queue_.is_empty ())
  {
    EVENTTYPE * ev = 0;

    while (this->event_queue_.dequeue (ev) > 0)
      CORBA::remove_ref (ev);
  }

  // Deactivate the <event_queue_> and wait all threads owned
  // by the manager to exit.
  this->thread_count (0);
}

//
// handle_event
//
template <typename COMPONENT, typename EVENTTYPE>
void CUTS_Async_Event_Handler_T <COMPONENT, EVENTTYPE>::
handle_event (EVENTTYPE * ev)
{
  CUTS_TRACE ("CUTS_Async_Event_Handler_T <COMPONENT, EVENTTYPE>::handle_event (EVENTTYPE *)");

  CORBA::add_ref (ev);
  this->event_queue_.enqueue (ev);
}

//
// thread_count
//
template <typename COMPONENT, typename EVENTTYPE>
void CUTS_Async_Event_Handler_T <COMPONENT, EVENTTYPE>::thread_count (size_t count)
{
  // We only allow one thread to change the thread count
  // at any given time.
  static ACE_Thread_Mutex lock;
  ACE_GUARD (ACE_Thread_Mutex, guard, lock);

  // Save the <thread_count_> so that we dont access the
  // lock more times than needed.
  size_t thr_count = this->thread_map_.current_size ();

  if (count > thr_count)
  {
    // Spawn additional threads.
    size_t spawn_count = count - thr_count;
    this->spawn_i (spawn_count);
  }
  else if (thr_count > count)
  {
    size_t kill_count = thr_count - count;
    typename Thread_Map::iterator iter (this->thread_map_);
    typename Thread_Map::ENTRY * entry = 0;

    // Set the <grp_id_> of <kill_count> threads to <GRP_KILL>.
    while (iter.done () != 1)
    {
      iter.next (entry);

      // Change the group id of the thread, change it's active
      // state and resume it if it's not active.
      (*entry->int_id_.active_) = false;
      this->thr_manager_.set_grp (entry->ext_id_, GRP_KILL);

      if (-- kill_count == 0)
        break;

      iter.advance ();
    }

    // Let's wait until we know that all threads in <GRP_KILL>
    // have exited.
    this->thr_manager_.resume_grp (GRP_KILL);
    this->thr_manager_.wait_grp (GRP_KILL);
  }
}

//
// priority
//
template <typename COMPONENT, typename EVENTTYPE>
void CUTS_Async_Event_Handler_T <COMPONENT, EVENTTYPE>::
priority (int prio)
{
  if (this->priority_ != prio)
  {
    typename Thread_Map::iterator iter (this->thread_map_);
    typename Thread_Map::ENTRY * entry = 0;

    // Set the priority of every thread owned by the event
    // handler to <prio>.
    while (iter.done () != 1)
    {
      iter.next (entry);

      if (entry != 0)
        ACE_Thread::setprio (entry->int_id_.handle_, prio);

      iter.advance ();
    }

    this->priority_ = prio;
  }
}

//
// register_thread
//
template <typename COMPONENT, typename EVENTTYPE>
int CUTS_Async_Event_Handler_T <COMPONENT, EVENTTYPE>::
register_thread (bool * active)
{
  ACE_GUARD_RETURN (ACE_Thread_Mutex,
                    guard,
                    this->spawn_lock_,
                    -1);

  // Get the id and handle to the calling thread.
  ACE_thread_t thr_id = this->thr_manager_.thr_self ();

  // Initialize a <cuts_thread_t>.
  cuts_thread_t cuts_thr;
  cuts_thr.active_ = active;
  int retval = this->thr_manager_.thr_self (cuts_thr.handle_);

  if (retval == -1)
    return -1;

  retval = this->thread_map_.bind (thr_id, cuts_thr);

  if (retval != -1)
    {
      // Decrement the spawn count.
      -- this->spawn_count_;

      // Signal the thread that we have activate all the
      // threads in the event handler.
      if (this->spawn_count_ == 0)
        this->spawn_condition_.signal ();
    }

  return retval;
}

//
// register_thread
//
template <typename COMPONENT, typename EVENTTYPE>
int CUTS_Async_Event_Handler_T <COMPONENT, EVENTTYPE>::
unregister_thread (void)
{
  ACE_thread_t thr_id = this->thr_manager_.thr_self ();
  return this->thread_map_.unbind (thr_id);
}

//
// spawn_i
//
template <typename COMPONENT, typename EVENTTYPE>
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

  return retval;
}


