// -*- C++ -*-
// $Id$

//
// CUTS_Log_T
//
template <typename T, typename LOCK>
CUTS_INLINE
CUTS_Log_T <T, LOCK>::CUTS_Log_T (size_t init_size, bool auto_grow)
: ACE_Array_Base <T> (init_size),
  used_size_ (0),
  auto_grow_ (auto_grow)
{
  CUTS_TRACE ("CUTS_Log_T (typename CUTS_Log_T <T, LOCK>::size_type)");
}

//
// ~CUTS_Log_T
//
template <typename T, typename LOCK>
CUTS_INLINE
CUTS_Log_T <T, LOCK>::~CUTS_Log_T (void)
{
  CUTS_TRACE ("CUTS_Log_T <T, LOCK>::~CUTS_Log_T");
}

//
// free_size
//
template <typename T, typename LOCK>
CUTS_INLINE
size_t CUTS_Log_T <T, LOCK>::free_size (void) const
{
  CUTS_TRACE ("CUTS_Log_T <T, LOCK>::free_size");
  ACE_READ_GUARD_RETURN (LOCK,
                         guard,
                         this->lock_,
                         this->cur_size_ - this->used_size_);

  return this->cur_size_ - this->used_size_;
}

//
// used_size
//
template <typename T, typename LOCK>
CUTS_INLINE
size_t CUTS_Log_T <T, LOCK>::used_size (void) const
{
  CUTS_TRACE ("CUTS_Log_T <T, LOCK>::used_size");
  ACE_READ_GUARD_RETURN (LOCK,
                         guard,
                         this->lock_,
                         this->used_size_);

  return this->used_size_;
}

//
// reset
//
template <typename T, typename LOCK>
CUTS_INLINE
void CUTS_Log_T <T, LOCK>::reset (void)
{
  CUTS_TRACE ("CUTS_Log_T <T, LOCK>::reset");
  ACE_WRITE_GUARD (LOCK, guard, this->lock_);

  this->reset_no_lock ();
}

//
// reset_no_lock
//
template <typename T, typename LOCK>
CUTS_INLINE
void CUTS_Log_T <T, LOCK>::reset_no_lock (void)
{
  CUTS_TRACE ("CUTS_Log_T <T, LOCK>::reset_no_lock");
  this->used_size_ = 0;
}

//
// lock
//
template <typename T, typename LOCK>
CUTS_INLINE
LOCK & CUTS_Log_T <T, LOCK>::lock (void)
{
  CUTS_TRACE ("CUTS_Log_T <T, LOCK>::lock");
  return this->lock_;
}

//
// next_free_record
//
template <typename T, typename LOCK>
CUTS_INLINE
T * CUTS_Log_T <T, LOCK>::next_free_record (void)
{
  CUTS_TRACE ("CUTS_Log_T <T, LOCK>::next_free_record");
  ACE_WRITE_GUARD_RETURN (LOCK, guard, this->lock_, 0);

  return this->next_free_record_no_lock ();
}


//
// size
//
template <typename T, typename LOCK>
CUTS_INLINE
size_t CUTS_Log_T <T, LOCK>::size (void) const
{
  CUTS_TRACE ("CUTS_Log_T <T, LOCK>::size (void) const");
  ACE_READ_GUARD_RETURN (LOCK, guard, this->lock_, this->cur_size_);

  return this->cur_size_;
}

//
// size
//
template <typename T, typename LOCK>
CUTS_INLINE
int CUTS_Log_T <T, LOCK>::size (size_t new_size)
{
  CUTS_TRACE ("CUTS_Log_T <T, LOCK>::size (size_t)");
  ACE_WRITE_GUARD_RETURN (LOCK, guard, this->lock_, -1);

  return ACE_Array_Base <T>::size (new_size);
}

//
// is_full
//
template <typename T, typename LOCK>
CUTS_INLINE
bool CUTS_Log_T <T, LOCK>::is_full (void) const
{
  CUTS_TRACE ("CUTS_Log_T <T, LOCK>::is_full (void) const");
  ACE_READ_GUARD_RETURN (LOCK, guard, this->lock_, false);

  return this->used_size_ >= this->cur_size_;
}

//
// get_buffer
//
template <typename T, typename LOCK>
CUTS_INLINE
T * CUTS_Log_T <T, LOCK>::get_buffer (void)
{
  CUTS_TRACE ("CUTS_Log_T <T, LOCK>::get_buffer (void)");
  return this->array_;
}

//
// get_buffer
//
template <typename T, typename LOCK>
CUTS_INLINE
const T * CUTS_Log_T <T, LOCK>::get_buffer (void) const
{
  CUTS_TRACE ("CUTS_Log_T <T, LOCK>::get_buffer (void) const");
  return this->array_;
}

///////////////////////////////////////////////////////////////////////////////
// @class CUTS_Log_Iterator_T

//
// CUTS_Log_Iterator_T
//
template <typename T, typename LOCK>
CUTS_INLINE
CUTS_Log_Iterator_T <T, LOCK>::
CUTS_Log_Iterator_T (CUTS_Log_T <T, LOCK> & log)
: log_ (log),
  index_ (0)
{
  CUTS_TRACE ("CUTS_Log_Iterator_T <T, LOCK>::CUTS_Log_Iterator_T (CUTS_Log_T <T, LOCK> &)");
}

//
// CUTS_Log_Iterator_T
//
template <typename T, typename LOCK>
CUTS_INLINE
CUTS_Log_Iterator_T <T, LOCK>::~CUTS_Log_Iterator_T (void)
{
  CUTS_TRACE ("CUTS_Log_Iterator_T <T, LOCK>::~CUTS_Log_Iterator_T (void)");
}

//
// done
//
template <typename T, typename LOCK>
CUTS_INLINE
int CUTS_Log_Iterator_T <T, LOCK>::done (void) const
{
  CUTS_TRACE ("CUTS_Log_Iterator_T <T, LOCK>::done (void) const");
  return this->index_ >= this->log_.used_size_;
}

//
// operator ->
//
template <typename T, typename LOCK>
CUTS_INLINE
T * CUTS_Log_Iterator_T <T, LOCK>::operator -> (void)
{
  CUTS_TRACE ("CUTS_Log_Iterator_T <T, LOCK>::operator -> (void)");
  return &this->log_.array_[this->index_];
}

//
// operator *
//
template <typename T, typename LOCK>
CUTS_INLINE
T & CUTS_Log_Iterator_T <T, LOCK>::operator * (void)
{
  CUTS_TRACE ("CUTS_Log_Iterator_T <T, LOCK>::operator * (void)");
  return this->log_.array_[this->index_];
}

///////////////////////////////////////////////////////////////////////////////
// @class CUTS_Log_Const_Iterator_T

//
// CUTS_Log_Iterator_T
//
template <typename T, typename LOCK>
CUTS_INLINE
CUTS_Log_Const_Iterator_T <T, LOCK>::
CUTS_Log_Const_Iterator_T (const CUTS_Log_T <T, LOCK> & log)
: log_ (log),
  index_ (0)
{
  CUTS_TRACE ("CUTS_Log_Const_Iterator_T <T, LOCK>::CUTS_Log_Const_Iterator_T (const CUTS_Log_T <T, LOCK> &)");
}

//
// CUTS_Log_Iterator_T
//
template <typename T, typename LOCK>
CUTS_INLINE
CUTS_Log_Const_Iterator_T <T, LOCK>::~CUTS_Log_Const_Iterator_T (void)
{
  CUTS_TRACE ("CUTS_Log_Const_Iterator_T <T, LOCK>::~CUTS_Log_Const_Iterator_T (void)");
}

//
// done
//
template <typename T, typename LOCK>
CUTS_INLINE
int CUTS_Log_Const_Iterator_T <T, LOCK>::done (void) const
{
  CUTS_TRACE ("CUTS_Log_Const_Iterator_T <T, LOCK>::done (void) const");
  return this->index_ >= this->log_.used_size_;
}

//
// operator ->
//
template <typename T, typename LOCK>
CUTS_INLINE
const T * CUTS_Log_Const_Iterator_T <T, LOCK>::operator -> (void) const
{
  CUTS_TRACE ("CUTS_Log_Const_Iterator_T <T, LOCK>::operator -> (void) const");
  return &this->log_.array_[this->index_];
}

//
// operator *
//
template <typename T, typename LOCK>
CUTS_INLINE
const T & CUTS_Log_Const_Iterator_T <T, LOCK>::operator * (void) const
{
  CUTS_TRACE ("CUTS_Log_Const_Iterator_T <T, LOCK>::operator * (void) const");
  return this->log_.array_[this->index_];
}
