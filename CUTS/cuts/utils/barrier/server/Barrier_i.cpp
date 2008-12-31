// $Id$

#include "Barrier_i.h"

#if !defined (__CUTS_INLINE__)
#include "Barrier_i.inl"
#endif

#include "ace/Guard_T.h"

//
// wait
//
void CUTS_Barrier_i::
register_client (const char * name, CUTS::BarrierCallback_ptr bc)
{
  ACE_GUARD_THROW_EX (ACE_Thread_Mutex,
                      guard,
                      this->mutex_,
                      CUTS::WaitFailed ());

  ACE_DEBUG ((LM_DEBUG,
              "%T (%t) - %M - registering %s with barrier\n",
              name));

  // Insert the callback into the listing.
  CUTS::BarrierCallback_var node = CUTS::BarrierCallback::_duplicate (bc);
  int retval = this->nodes_.bind (name, node);

  if (retval == 0)
    node._retn ();
  else if (retval == -1)
    throw CUTS::WaitFailed ();
  else if (retval == 1)
    throw CUTS::DuplicateName ();

  // Decrement the count.
  -- this->count_;
}

//
// broadcast
//
void CUTS_Barrier_i::broadcast (void)
{
  map_type::ITERATOR iter (this->nodes_);

  // Signal each of the nodes.
  for ( ; !iter.done (); ++ iter)
  {
    ACE_DEBUG ((LM_DEBUG,
                "%T (%t) - %M - signaling %s to continue...\n",
                iter->key ().c_str ()));

    iter->item ()->signal ();
  }

  // Delete all the nodes in the listing.
  this->nodes_.unbind_all ();
}

//
// close
//
int CUTS_Barrier_i::close (void)
{
  try
  {
    map_type::ITERATOR iter (this->nodes_);

    // Signal each node to abort.
    for ( ; !iter.done (); ++ iter)
    {
      ACE_DEBUG ((LM_DEBUG,
                  "%T (%t) - %M - signaling %s to abort...\n",
                  iter->key ().c_str ()));

      iter->item ()->abort ();
    }

    // Delete all the nodes in the map.
    this->nodes_.unbind_all ();
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
