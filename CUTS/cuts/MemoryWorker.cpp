// $Id$

#include "cuts/MemoryWorker.h"
#include "ace/Guard_T.h"

#define CUTS_MEMORY_ALLOC_SIZE 1024

#if !defined (__CUTS_INLINE__)
#include "cuts/MemoryWorker.inl"
#endif

//
// CUTS_Memory_Worker
//
CUTS_Memory_Worker::CUTS_Memory_Worker (void)
{

}

//
// ~CUTS_Memory_Worker
//
CUTS_Memory_Worker::~CUTS_Memory_Worker (void)
{
  try
    {
      // delete all the remaining memory in the container
      Memory_Allocations::iterator iter;
      
      for ( iter = this->memory_.begin ();
	    iter != this->memory_.end ();
	    iter ++)
	{
	  delete [] (*iter);
	}
    }
  catch (...)
    {

    }
}

//
// allocate
//
void CUTS_Memory_Worker::allocate (size_t kilobytes)
{
  try
    {
      ACE_GUARD (ACE_Thread_Mutex, guard, this->lock_);
      
      while (kilobytes -- > 0)
	{
	  char * allocation = 0;
	  ACE_NEW (allocation, char [CUTS_MEMORY_ALLOC_SIZE]);
	  
	  if (allocation != 0)
	    this->memory_.push_back (allocation);
	}
    }
  catch (...)
    {

    }
}

//
// deallocate
//
void CUTS_Memory_Worker::deallocate (size_t kilobytes)
{
  try
    {
      ACE_GUARD (ACE_Thread_Mutex, guard, this->lock_);
      
      // Make sure we are not trying to deallocate more memory
      // that what is currently allocated.
      if (kilobytes > this->memory_.size ())
	kilobytes = this->memory_.size ();
      
      char * memory = 0;
      
      while (kilobytes -- > 0)
	{
	  // get the next allocation on the <memory_> stack
	  memory = this->memory_.front ();
	  this->memory_.pop_front ();
	  
	  // delete the piece of
	  delete [] memory;
	}
    }
  catch (...)
    {

    }
}
