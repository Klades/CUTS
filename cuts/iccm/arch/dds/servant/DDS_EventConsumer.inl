// -*- C++ -*-
// $Id$

namespace iCCM
{

//
// DDS_EventConsumer
//
template <typename T>
CUTS_INLINE
DDS_EventConsumer <T>::DDS_EventConsumer (void)
: subscriber_ (0),
  abs_reader_ (0),
  reader_qos_ (0),
  topic_qos_ (0)
{

}

//
// is_configured
//
template <typename T>
CUTS_INLINE
bool DDS_EventConsumer <T>::is_configured (void) const
{
  return !T::_is_nil (this->subscriber_);
}

//
// is_configured
//
template <typename T>
CUTS_INLINE
typename DDS_EventConsumer <T>::datareader_ptr_type
DDS_EventConsumer <T>::get_datareader (void)
{
  return T::_duplicate (this->abs_reader_);
}

}
