// -*- C++ -*-
// $Id$

//
// CUTS_Log_T
//
template <typename T, typename LOCK>
CUTS_INLINE
CUTS_Log_T <T, LOCK>::CUTS_Log_T (size_t size, bool auto_grow)
: ACE_Array_Base <T> (size),
  used_ (0),
  auto_grow_ (auto_grow)
{

}

//
// ~CUTS_Log_T
//
template <typename T, typename LOCK>
CUTS_INLINE
CUTS_Log_T <T, LOCK>::~CUTS_Log_T (void)
{

}

//
// free_size
//
template <typename T, typename LOCK>
CUTS_INLINE
size_t CUTS_Log_T <T, LOCK>::free_size (void) const
{
  return this->cur_size_ - this->used_;
}

//
// used_size
//
template <typename T, typename LOCK>
CUTS_INLINE
size_t CUTS_Log_T <T, LOCK>::used_size (void) const
{
  return this->used_;
}

//
// reset
//
template <typename T, typename LOCK>
CUTS_INLINE
void CUTS_Log_T <T, LOCK>::reset (void)
{
  this->used_ = 0;
}

//
// lock
//
template <typename T, typename LOCK>
CUTS_INLINE
LOCK & CUTS_Log_T <T, LOCK>::lock (void)
{
  return this->lock_;
}

//
// next_free_record_i
//
template <typename T, typename LOCK>
CUTS_INLINE
T * CUTS_Log_T <T, LOCK>::next_free_record_no_lock (void)
{
  return &(this->array_[this->used_ ++]);
}

//
// used_end
//
template <typename T, typename LOCK>
CUTS_INLINE
typename CUTS_Log_T <T, LOCK>::iterator
CUTS_Log_T <T, LOCK>::used_end (void)
{
  return this->array_ + this->used_;
}

//
// used_end
//
template <typename T, typename LOCK>
CUTS_INLINE
typename CUTS_Log_T <T, LOCK>::const_iterator
CUTS_Log_T <T, LOCK>::used_end (void) const
{
  return this->array_ + this->used_;
}

//
// auto_grow
//
template <typename T, typename LOCK>
CUTS_INLINE
bool CUTS_Log_T <T, LOCK>::auto_grow (void) const
{
  return this->auto_grow_;
}

//
// auto_grow
//
template <typename T, typename LOCK>
CUTS_INLINE
void CUTS_Log_T <T, LOCK>::auto_grow (bool flag) 
{
  this->auto_grow_ = flag;
}

//
// size
//
template <typename T, typename LOCK>
CUTS_INLINE
typename CUTS_Log_T <T, LOCK>::size_type
CUTS_Log_T <T, LOCK>::size (void) const
{
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
  ACE_WRITE_GUARD_RETURN (LOCK, guard, this->lock_, -1);
  return this->ACE_Array_Base <T>::size (new_size);
}
