// $Id$

#if !defined (__CUTS_INLINE__)
#include "CCM_Event_Handler_T.inl"
#endif

#include "ace/OS_NS_errno.h"

//
// activate
//
template <typename T, typename EVENT>
int CUTS_CCM_Event_Handler_T <T, EVENT>::activate (void)
{
  CUTS_TRACE ("CUTS_CCM_Event_Handler_T <T, EVENT>::activate (int thr_count)");

  // Activate the message queue.
  if (this->msg_queue_->state () == ACE_Message_Queue_Base::DEACTIVATED)
    this->msg_queue_->activate ();

  // Spawn threads to process the message queue.
  long flags = THR_NEW_LWP | THR_JOINABLE | THR_INHERIT_SCHED;
  int retval = ACE_Task_Base::activate (flags, this->thr_count_);

  if (retval == -1)
  {
    ACE_ERROR ((LM_ERROR,
                "%T (%t) - %M - failed to activate event handler\n"));
  }

  return retval;
}

//
// deactivate
//
template <typename T, typename EVENT>
int CUTS_CCM_Event_Handler_T <T, EVENT>::deactivate (void)
{
  CUTS_TRACE ("CUTS_CCM_Event_Handler_T <T, EVENT>::deactivate (void)");

  // Deactivate the message queue.
  if (this->msg_queue_->state () == ACE_Message_Queue_Base::ACTIVATED)
    this->msg_queue_->deactivate ();

  // Wait for all threads to return.
  this->wait ();

  // Decrement reference count for remaining events.
  EVENT * ev = 0;
  typename task_type::MESSAGE_QUEUE_EX::ITERATOR iter (*this->msg_queue_);

  for (; !iter.done (); iter.advance ())
  {
    // Get the next event.
    iter.next (ev);

    // Decrement its reference count.
    ev->_remove_ref ();
  }

  // Flush the contents of the message queue.
  this->msg_queue_->flush ();
  return 0;
}

//
// handle_event
//
template <typename T, typename EVENT>
int CUTS_CCM_Event_Handler_T <T, EVENT>::handle_event (EVENT * ev)
{
  CUTS_TRACE ("CUTS_CCM_Event_Handler_T <T, EVENT>::handle_event (EVENT * ev)");

  // Increment the reference count.
  ev->_add_ref ();

  // Insert the event into the message queue.
  return this->msg_queue_->enqueue_tail (ev);
}

//
// svc
//
template <typename T, typename EVENT>
int CUTS_CCM_Event_Handler_T <T, EVENT>::svc (void)
{
  CUTS_TRACE ("CUTS_CCM_Event_Handler_T <T, EVENT>::svc (void)");

  if (this->affinity_mask_ != 0)
  {
    // Get this thread's handle. We need to set its processor
    // affinity before we process any events.
    ACE_hthread_t thr_handle;
    ACE_OS::thr_self (thr_handle);

#if defined (__USE_GNU)
    cpu_set_t cpu_set;
    CPU_ZERO (&cpu_set);
    CPU_SET (1, &cpu_set);

    if (::sched_setaffinity (0, sizeof (cpu_set), &cpu_set) < 0)
      ACE_ERROR ((LM_ERROR,
                  "%T (%t) - %M - failed to set CPU affinity [%m]\n"));
#endif

    /*
    // First, zero all the bits in the CPU set.
    size_t count = ACE_CPU_SETSIZE / (8 * sizeof (ACE_UINT32));
#else
    size_t count = CPU_SETSIZE / (8 * sizeof (ACE_UINT32));
#endif
    ACE_UINT32 * cpu_iter = reinterpret_cast <ACE_UINT32 *> (&cpu_set);
    ACE_UINT32 * cpu_iter_end = cpu_iter + count;

    for ( ; cpu_iter != cpu_iter_end; ++ cpu_iter)
      *cpu_iter = 0;

    // Next, set the mask in the CPU set.
    cpu_iter = reinterpret_cast <ACE_UINT32 *> (&cpu_set);

    for (ACE_UINT32 mask = this->affinity_mask_, index = 1;
         mask != 0;
         mask >>= 1)
    {
      if ((mask & 1))
        (*cpu_iter) |= index;

      if (index != 128)
      {
        index <<= 1;
      }
      else
      {
        index = 1;
        cpu_iter ++;
      }
    }

    // Finally, use the mask to set the processor affinity.
    if (ACE_OS::thr_set_affinity (thr_handle,
                                  sizeof (cpu_set),
                                  &cpu_set) != 0)
    {
      ACE_ERROR ((LM_ERROR,
                  "%T (%t) - %M - failed to set processor affinity [%d]\n",
                  this->affinity_mask_));
    }
    */
  }

  try
  {
    int retval;
    EVENT * ev = 0;

    while (this->msg_queue_->state () == ACE_Message_Queue_Base::ACTIVATED)
    {
      // Get the next message from the queue.
      retval = this->msg_queue_->dequeue_head (ev);

      if (retval != -1)
      {
        if (ev != 0)
        {
          // Make an upcall to the component.
          (this->component_->*this->method_) (ev);

          // Decrement the event's reference count.
          ev->_remove_ref ();
        }
        else
          ACE_ERROR ((LM_WARNING,
                      "%T (%t) - %M - event is a NIL object; ignoring...\n"));
      }
      else if (errno != ESHUTDOWN)
        ACE_ERROR ((LM_ERROR,
                    "%T (%t) - %M - failed to get event from queue\n"));
    }

    return 0;
  }
  catch (...)
  {
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) [%N:%l]- %M - caught unknown exception\n")));
  }

  return -1;
}
