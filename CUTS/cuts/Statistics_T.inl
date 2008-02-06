// $Id$

//
// CUTS_Statistics_T
//
template <typename T>
CUTS_INLINE
CUTS_Statistics_T <T>::CUTS_Statistics_T (void)
: count_ (0),
  sum_ (CUTS_zero <T>::value ()),
  min_ (CUTS_zero <T>::value ()),
  max_ (CUTS_zero <T>::value ())
{

}

//
// CUTS_Statistics_T
//
template <typename T>
CUTS_INLINE
CUTS_Statistics_T <T>::
CUTS_Statistics_T (const CUTS_Statistics_T <T> & stat)
: count_ (0),
  sum_ (stat.sum_),
  min_ (stat.min_),
  max_ (stat.max_)
{

}

//
// CUTS_Statistics_T
//
template <typename T>
CUTS_INLINE
CUTS_Statistics_T <T>::~CUTS_Statistics_T (void)
{

}

//
// summation
//
template <typename T>
CUTS_INLINE
const T & CUTS_Statistics_T <T>::summation (void) const
{
  return this->sum_;
}

//
// max_value
//
template <typename T>
CUTS_INLINE
const T & CUTS_Statistics_T <T>::max_value (void) const
{
  return this->max_;
}

//
// min_value
//
template <typename T>
CUTS_INLINE
const T & CUTS_Statistics_T <T>::min_value (void) const
{
  return this->min_;
}

//
// avg_value
//
template <typename T>
template <typename T1>
CUTS_INLINE
void CUTS_Statistics_T <T>::avg_value (T1 & value) const
{
  value = this->count_ > 0 ?
    this->sum_ / static_cast <double> (this->count_) :
    CUTS_zero <T>::value ();
}

//
// count
//
template <typename T>
CUTS_INLINE
size_t CUTS_Statistics_T <T>::count (void) const
{
  return this->count_;
}
