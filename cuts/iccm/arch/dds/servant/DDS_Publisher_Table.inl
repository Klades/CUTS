// -*- C++ -*-

namespace iCCM
{

//
// DDS_Publisher_Table
//
template <typename T>
CUTS_INLINE
DDS_Publisher_Table <T>::DDS_Publisher_Table (void)
: abs_writer_ (0)
{

}

//
// get_datawriter
//
template <typename T>
CUTS_INLINE
typename DDS_Publisher_Table <T>::datawriter_ptr_type
DDS_Publisher_Table <T>::get_datawriter (void)
{
  return T::_duplicate (this->abs_writer_);
}

//
// is_configured
//
template <typename T>
CUTS_INLINE
bool DDS_Publisher_Table <T>::is_configured (void) const
{
  return !T::_is_nil (this->abs_writer_);
}

//
// configure
//
template <typename T>
CUTS_INLINE
void DDS_Publisher_Table <T>::
configure (publisher_ptr_type publisher, topic_ptr_type topic)
{
  this->abs_writer_ =
    publisher->create_datawriter (topic,
                                  T::datawriter_qos_default (),
                                  0,
                                  T::STATUS_MASK_NONE);
}

}
