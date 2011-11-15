// $Id$

#if !defined (__CUTS_INLINE__)
#include "Log_T.inl"
#endif

#include "ace/Auto_Ptr.h"
#include "ace/CORBA_macros.h"
#include <algorithm>
#include <typeinfo>

//
// next_free_record_no_lock
//
template <typename T, typename LOCK>
T * CUTS_Log_T <T, LOCK>::next_free_record_no_lock (void)
{
  CUTS_TRACE ("CUTS_Log_T <T, LOCK>::next_free_record_no_lock");

  if (this->used_size_ < this->cur_size_)
  {
    return &this->array_[this->used_size_ ++];
  }
  else if (this->auto_grow_)
  {
    ACE_Array_Base <T>::size (this->cur_size_ * 2);
    return &this->array_[this->used_size_ ++];
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

///////////////////////////////////////////////////////////////////////////////
// class CUTS_Log_Iterator_T

//
// advance
//
template <typename T, typename LOCK>
int CUTS_Log_Iterator_T <T, LOCK>::advance (void)
{
  CUTS_TRACE ("CUTS_Log_Iterator_T <T, LOCK>::advance");

  if (this->index_ < this->log_.used_size_)
    ++ this->index_;

  // Determine if there are more item left.
  return this->index_ < this->log_.used_size_ ? 1 : 0;
}


///////////////////////////////////////////////////////////////////////////////
// class CUTS_Log_Const_Iterator_T

//
// advance
//
template <typename T, typename LOCK>
int CUTS_Log_Const_Iterator_T <T, LOCK>::advance (void)
{
  CUTS_TRACE ("CUTS_Log_Const_Iterator_T <T, LOCK>::advance");

  if (this->index_ < this->log_.used_size_)
    ++ this->index_;

  // Determine if there are more item left.
  return this->index_ < this->log_.used_size_ ? 1 : 0;
}

