// $Id$

#if !defined (__CUTS_INLINE__)
#include "cuts/Log_T.inl"
#endif

#include "ace/Guard_T.h"
#include <algorithm>

//
// CUTS_Log_T
//
template <typename T, typename LOCK>
CUTS_Log_T <T, LOCK>::CUTS_Log_T (const CUTS_Log_T & log)
: ACE_Array_Base <T> (log.used_),
  used_ (0),
  auto_grow_ (log.auto_grow_)
{
  CUTS_TRACE ("CUTS_Log_T <T, LOCK>::CUTS_Log_T (const CUTS_Log_T &)");

  this->copy_log_i (log);
}

//
// next_free_record
//
template <typename T, typename LOCK>
T * CUTS_Log_T <T, LOCK>::next_free_record (void)
{
  CUTS_TRACE ("CUTS_Log_T <T, LOCK>::next_free_record");

  if (this->used_ < this->cur_size_)
  {
    // Optimized for the fast path.
    ACE_READ_GUARD_RETURN (LOCK, guard, this->lock_, 0);
    return this->next_free_record_no_lock ();
  }
  else if (this->auto_grow_)
  {
    ACE_WRITE_GUARD_RETURN (LOCK, guard, this->lock_, 0);

    // Double the size of the log and return the next record. We add
    // one to the size just in case the current size is 0.
    this->ACE_Array_Base <T>::size (this->cur_size_ * 2 + 1);
    return this->next_free_record_no_lock ();
  }
  else
  {
    return 0;
  }
}

//
// operator =
//
template <typename T, typename LOCK>
const CUTS_Log_T <T, LOCK> &
CUTS_Log_T <T, LOCK>::operator = (const CUTS_Log_T <T, LOCK> & log)
{
  CUTS_TRACE ("CUTS_Log_T <T, LOCK>::operator = (const CUTS_Log_T <T, LOCK> &)");

  // Save the auto grow state.
  this->auto_grow_ = log.auto_grow_;
  this->copy_log (log);
  return *this;
}

//
// copy_log
//
template <typename T, typename LOCK>
void CUTS_Log_T <T, LOCK>::copy_log (const CUTS_Log_T & log)
{
  CUTS_TRACE ("CUTS_Log_T <T, LOCK>::copy_log (const CUTS_Log_T &)");
  ACE_WRITE_GUARD (LOCK, guard, this->lock_);

  // Set the size of the log and copy it.
  this->ACE_Array_Base <T>::size (log.used_size ());
  this->copy_log_i (log);
}

//
// copy_log_i
//
template <typename T, typename LOCK>
void CUTS_Log_T <T, LOCK>::copy_log_i (const CUTS_Log_T & log)
{
  CUTS_TRACE ("CUTS_Log_T <T, LOCK>::copy_log_i (const CUTS_Log_T &)");
  std::copy (log.begin (), log.used_end (), this->begin ());
  this->used_ = log.used_;
}

//
// size
//
template <typename T, typename LOCK>
CUTS_INLINE
typename CUTS_Log_T <T, LOCK>::size_type
CUTS_Log_T <T, LOCK>::size (void) const
{
  CUTS_TRACE ("CUTS_Log_T <T, LOCK>::size (void) const");
  ACE_READ_GUARD_RETURN (LOCK,
                         guard,
                         this->lock_,
                         this->ACE_Array_Base <T>::size ());

  return this->ACE_Array_Base <T>::size ();
}

//
// size
//
template <typename T, typename LOCK>
CUTS_INLINE
int CUTS_Log_T <T, LOCK>::
size (typename CUTS_Log_T <T, LOCK>::size_type new_size)
{
  CUTS_TRACE ("CUTS_Log_T <T, LOCK>::size (typename CUTS_Log_T <T, LOCK>::size_type)");
  ACE_WRITE_GUARD_RETURN (LOCK, guard, this->lock_, -1);
  return this->ACE_Array_Base <T>::size (new_size);
}
