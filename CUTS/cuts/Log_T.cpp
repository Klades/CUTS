// $Id$

#if !defined (__CUTS_INLINE__)
#include "Log_T.inl"
#endif

#include "ace/Auto_Ptr.h"
#include "ace/CORBA_macros.h"
#include <algorithm>
#include <typeinfo>

//
// CUTS_Log_T
//
template <typename T, typename LOCK>
CUTS_INLINE
CUTS_Log_T <T, LOCK>::CUTS_Log_T (size_t chunk_size, bool auto_grow)
: chunk_size_ (chunk_size),
  curr_size_ (chunk_size),
  used_size_ (0),
  auto_grow_ (auto_grow),
  records_ (1)
{
  CUTS_TRACE ("CUTS_Log_T (typename CUTS_Log_T <T, LOCK>::size_type)");

  chunk_type * chunk = 0;

  ACE_NEW_THROW_EX (chunk,
                    chunk_type (chunk_size),
                    ACE_bad_alloc ());

  this->records_[0] = chunk;
}

//
// CUTS_Log_T
//
template <typename T, typename LOCK>
CUTS_Log_T <T, LOCK>::CUTS_Log_T (const CUTS_Log_T & log)
: chunk_size_ (log.chunk_size_),
  curr_size_ (0),
  used_size_ (0),
  auto_grow_ (log.auto_grow_)
{
  CUTS_TRACE ("CUTS_Log_T <T, LOCK>::CUTS_Log_T (const CUTS_Log_T &)");

  // Set the size of this log.
  if (this->size_i (log.used_size_) == -1)
    return;

  this->copy_i (log);
}

//
// ~CUTS_Log_T
//
template <typename T, typename LOCK>
CUTS_Log_T <T, LOCK>::~CUTS_Log_T (void)
{
  CUTS_TRACE ("CUTS_Log_T <T, LOCK>::~CUTS_Log_T");

  // Delete each chuck of the record log.
  typename record_log::iterator
    iter = this->records_.begin (), iter_end = this->records_.end ();

  for ( ; iter != iter_end; ++ iter)
    delete (*iter);
}

//
// operator =
//
template <typename T, typename LOCK>
const CUTS_Log_T <T, LOCK> &
CUTS_Log_T <T, LOCK>::operator = (const CUTS_Log_T & log)
{
  CUTS_TRACE ("CUTS_Log_T <T, LOCK>::operator = (const CUTS_Log_T &)");

  if (this == &log)
    return *this;

  ACE_WRITE_GUARD_RETURN (LOCK, guard, this->lock_, *this);

  // Do a fast reset of this object.
  this->reset_no_lock ();

  // Copy the content of the log.
  this->copy_i (log);

  return *this;
}

//
// copy_i
//
template <typename T, typename LOCK>
void CUTS_Log_T <T, LOCK>::copy_i (const CUTS_Log_T & log)
{
  CUTS_TRACE ("CUTS_Log_T <T, LOCK>::copy_i (const CUTS_Log_T &)");

  const_iterator iter (log);

  for ( ; !iter.done (); iter.advance ())
    *this->next_free_record_no_lock () = *iter;
}

//
// next_free_record_no_lock
//
template <typename T, typename LOCK>
T * CUTS_Log_T <T, LOCK>::next_free_record_no_lock (void)
{
  CUTS_TRACE ("CUTS_Log_T <T, LOCK>::next_free_record_no_lock");

  if (this->used_size_ < this->curr_size_)
  {
    // Calculate the index and offset into the log.
    size_t index = this->used_size_ / this->chunk_size_;
    size_t offset = this->used_size_ % this->chunk_size_;

    // Increment the used count.
    ++ this->used_size_;

    return &((*this->records_[index])[offset]);
  }
  else if (this->auto_grow_)
  {
    // Increment the size of the record log.
    size_t index = this->records_.size ();

    if (this->size_i (this->curr_size_ + this->chunk_size_) == -1)
      return 0;

    // Increment the used count.
    ++ this->used_size_;

    // Return the next record to the caller.
    return &((*this->records_[index])[0]);
  }
  else
    return 0;
}

//
// next_free_record
//
template <typename T, typename LOCK>
size_t CUTS_Log_T <T, LOCK>::next_free_record (T * & record)
{
  CUTS_TRACE ("CUTS_Log_T <T, LOCK>::next_free_record");
  ACE_WRITE_GUARD_RETURN (LOCK, guard, this->lock_, 0);

  record = this->next_free_record_no_lock ();
  return this->used_size_;
}

//
// size_i
//
template <typename T, typename LOCK>
int CUTS_Log_T <T, LOCK>::size_i (size_t new_size)
{
  CUTS_TRACE ("CUTS_Log_T <T, LOCK>::size_i");

  if (new_size < this->curr_size_)
  {
    // For now, let's ingore request to make the log smaller. We need to
    // revisit this later though.
    return 0;
  }
  else
  {
    // Determine how many chunks we need to allocate.
    size_t chunks = (new_size / this->chunk_size_) - this->records_.size ();

    // Initialize a temporary array of chunks.
    ACE_Auto_Ptr <chunk_type> * temp_chunks = 0;
    ACE_NEW_RETURN (temp_chunks,
                    ACE_Auto_Ptr <chunk_type> [chunks],
                    -1);

    ACE_Auto_Array_Ptr <ACE_Auto_Ptr <chunk_type> > temp (temp_chunks);

    for (size_t i = 0; i < chunks; ++ i)
    {
      // Allocate a new chuck for the record log.
      chunk_type * chunk = 0;
      ACE_NEW_RETURN (chunk, chunk_type (this->chunk_size_), -1);

      // Insert the chunk into the temp data store.
      temp[i].reset (chunk);
    }

    // Increase the number of real chunks.
    size_t size = this->records_.size ();

    if (this->records_.size (size + chunks) == -1)
      return -1;

    // Insert the newly allocated chunks into the record log.
    for (size_t i = 0; i < chunks; ++ i)
      this->records_[size ++] = temp[i].release ();

    // Set the size of the record log.
    this->curr_size_ = this->chunk_size_ * this->records_.size ();
  }

  return 0;
}

///////////////////////////////////////////////////////////////////////////////
// @class CUTS_Log_Iterator_T

//
// advance
//
template <typename T, typename LOCK>
int CUTS_Log_Iterator_T <T, LOCK>::advance (void)
{
  CUTS_TRACE ("CUTS_Log_Iterator_T <T, LOCK>::advance");

  // Get the size of the chunks.
  size_t chunk_size = this->log_.chunk_size_;

  // Move to the next item. If we go pass the size end of the
  // current chunk, we need to move to the next one.
  if (++ this->offset_ >= chunk_size)
  {
    ++ this->index_;
    this->offset_ = 0;
  }

  // Increment the location.
  ++ this->location_;

  // Determine if there are more item left.
  return this->location_ < this->used_size_ ? 1 : 0;
}


///////////////////////////////////////////////////////////////////////////////
// @class CUTS_Log_Const_Iterator_T

//
// advance
//
template <typename T, typename LOCK>
int CUTS_Log_Const_Iterator_T <T, LOCK>::advance (void)
{
  CUTS_TRACE ("CUTS_Log_Const_Iterator_T <T, LOCK>::advance");

  // Get the size of the chunks.
  size_t chunk_size = this->log_.chunk_size_;

  // Move to the next item. If we go pass the size end of the
  // current chunk, we need to move to the next one.
  if (++ this->offset_ >= chunk_size)
  {
    ++ this->index_;
    this->offset_ = 0;
  }

  // Increment the location.
  ++ this->location_;

  // Determine if there are more item left.
  return this->location_ < this->used_size_ ? 1 : 0;
}

