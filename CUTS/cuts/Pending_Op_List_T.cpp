// $Id$

#if !defined (__CUTS_INLINE__)
#include "cuts/Pending_Op_List_T.inl"
#endif

#include "cuts/Pending_Op_T.h"

//
// reset
//
template <typename T>
void CUTS_Pending_Op_List_T <T>::reset (void)
{
  CUTS_Pending_Op_T <T> ** op = 0;
  typename Pending_Op_Queue::ITERATOR iter (this->queue_);

  while (iter.next (op) != 0)
  {
    // Release the memory for this operation then advance
    // to the next operation.
    if (op != 0)
      delete *op;

    iter.advance ();
  }

  // Now, reset the queue.
  this->queue_.reset ();
}

//
// process
//
template <typename T>
int CUTS_Pending_Op_List_T <T>::process (T * object)
{
  CUTS_Pending_Op_T <T> ** op = 0;
  typename Pending_Op_Queue::ITERATOR iter (this->queue_);

  while (iter.next (op) != 0)
  {
    // Execute the operation, then advance to the next one.
    if (op != 0)
      (*op)->execute (object);
    else
      {
        ACE_ERROR ((LM_ERROR,
                    "%T - %M - NIL pending operation object\n"));
      }

    iter.advance ();
  }

  // Release all the resourcs.
  this->reset ();

  // Right now, we always return 0.
  return 0;
}
