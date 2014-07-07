// $Id$

#if !defined (__CUTS_INLINE__)
#include "DDS_Publisher.inl"
#endif

namespace iCCM
{

//
// ~DDS_Publisher
//
template <typename T>
DDS_Publisher <T>::~DDS_Publisher (void)
{
  if (!T::_is_nil (this->abs_writer_))
  {
    typedef typename T::publisher_var_type publisher_var_type;
    typedef typename T::returncode_type returncode_type;

    // Destroy the data writer owned by this event producer.
    publisher_var_type publisher = this->abs_writer_->get_publisher ();
    returncode_type retcode = publisher->delete_datawriter (this->abs_writer_);

    if (retcode != 0)
      ACE_ERROR ((LM_ERROR,
                  ACE_TEXT ("%T (%t) - %M - failed to delete data writer [retcode = %d]\n"),
                  retcode));
  }
}

//
// configure
//
template <typename T>
void DDS_Publisher <T>::
configure (publisher_ptr_type publisher, const datawriterqos_type & datawriter_qos, topic_ptr_type topic)
{
  this->abs_writer_ =
    publisher->create_datawriter (topic,
                                  datawriter_qos,
                                  0,
                                  T::STATUS_MASK_NONE);

  if (T::_is_nil (this->abs_writer_))
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - failed to create abstract ")
                ACE_TEXT ("reader for topic <%s>\n"),
                topic->get_name ()));
}

}
