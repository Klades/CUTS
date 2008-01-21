// $Id$

#if !defined (__CUTS_INLINE__)
#include "Statistics_T.inl"
#endif  /* defined __CUTS_INLINE__ */

//
// operator +=
//
template <typename T>
const CUTS_Statistics_T <T> &
CUTS_Statistics_T <T>::operator = (const CUTS_Statistics_T <T> & rhs)
{
  this->count_ = rhs.count_;
  this->min_ = rhs.min_;
  this->max_ = rhs.max_;
  this->sum_ = rhs.sum_;

  return *this;
}

//
// operator +=
//
template <typename T>
const CUTS_Statistics_T <T> &
CUTS_Statistics_T <T>::operator += (const T & rhs)
{
  if (this->count_!= 0)
  {
    // Update the min and max values if necessary.
    if (rhs > this->max_)
      this->max_ = rhs;
    else if (rhs < this->min_)
      this->min_ = rhs;
  }
  else
  {
    // This is the first-time value.
    this->max_ = rhs;
    this->min_ = rhs;
  }

  // Update the summation value.
  this->sum_ += rhs;
  ++ this->count_;

  return *this;
}

//
// reset
//
template <typename T>
void CUTS_Statistics_T <T>::reset (void)
{
  this->count_ = 0;
  this->min_ = CUTS_zero <T>::value ();
  this->max_ = CUTS_zero <T>::value ();
  this->sum_ = CUTS_zero <T>::value ();
}
