// -*- C++ -*-
// $Id$

namespace iCCM
{

//
// DDS_Publisher
//
CUTS_INLINE
template <typename T>
DDS_Publisher <T>::DDS_Publisher (void)
: abs_writer_ (0)
{

}

//
// get_datawriter
//
CUTS_INLINE
template <typename T>
typename DDS_Publisher <T>::datawriter_ptr_type
DDS_Publisher <T>::get_datawriter (void)
{
  return T::_duplicate (this->abs_writer_);
}

//
// is_configured
//
CUTS_INLINE
template <typename T>
bool DDS_Publisher <T>::is_configured (void) const
{
  return !T::_is_nil (this->abs_writer_);
}

//
// connect
//
template <typename T>
CUTS_INLINE
void DDS_Publisher <T>::
connect (::Components::EventConsumerBase_ptr p)
{
  this->consumer_ = ::Components::DDS::EventConsumer::_narrow (p);
}

//
// disconnect
//
template <typename T>
CUTS_INLINE
::Components::EventConsumerBase_ptr DDS_Publisher <T>::disconnect (void)
{
  return this->consumer_._retn ();
}

}
