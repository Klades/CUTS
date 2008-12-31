// $Id$

#include "Barrier_i.h"

#if !defined (__CUTS_INLINE__)
#include "Barrier_i.inl"
#endif

#include "ace/Guard_T.h"

//
// wait
//
void CUTS_Barrier_i::register_client (CUTS::BarrierCallback_ptr node)
{
  ACE_GUARD_THROW_EX (ACE_Thread_Mutex,
                      guard,
                      this->mutex_,
                      CUTS::WaitFailed ());

  // Insert the callback into the listing.
  CUTS::BarrierCallback_var callback =
    CUTS::BarrierCallback::_duplicate (node);

  if (this->nodes_.insert (callback) == -1)
    throw CUTS::WaitFailed ();

  // Decrement the count.
  -- this->count_;
}

//
// close
//
void CUTS_Barrier_i::broadcast (void)
{
  // Signal each of the nodes.
  set_type::ITERATOR iter (this->nodes_);

  for ( ; !iter.done (); ++ iter)
    (*iter)->signal ();

  // Delete all the nodes in the listing.
  this->nodes_.reset ();
}

//
// close
//
int CUTS_Barrier_i::close (void)
{
  try
  {
    set_type::ITERATOR iter (this->nodes_);

    for ( ; !iter.done (); ++ iter)
      (*iter)->abort ();

    this->nodes_.reset ();
    return 0;
  }
  catch (const CORBA::Exception & ex)
  {
    ACE_ERROR ((LM_ERROR,
                "%T (%t) - %M - %s\n",
                ex._info ().c_str ()));
  }

  return -1;
}
