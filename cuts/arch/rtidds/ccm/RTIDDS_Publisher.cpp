// $Id$

#include "RTIDDS_Publisher.h"

#if !defined (__CUTS_INLINE__)
#include "RTIDDS_Publisher.inl"
#endif

//
// connect
//
void CUTS_RTIDDS_CCM_Publisher::
connect (::Components::EventConsumerBase_ptr p)
{
  if (0 == this->publisher_)
    return;

  // The last part is to create a data reader.
  ::DDSTopic * topic = this->endpoint_.topic ();

  this->abstract_writer_ =
      this->publisher_->create_datawriter (topic,
                                           DDS_DATAWRITER_QOS_DEFAULT,
                                           0,
                                           DDS_STATUS_MASK_NONE);

  this->consumer_ = ::Components::RTIDDS::EventConsumer::_narrow (p);
}

//
// disconnect
//
::Components::EventConsumerBase_ptr
CUTS_RTIDDS_CCM_Publisher::disconnect (void)
{
  // Delete the data write for this subscriber.
  DDS_ReturnCode_t retcode;

  if (0 != this->abstract_writer_)
  {
    retcode = this->publisher_->delete_datawriter (this->abstract_writer_);

    if (retcode == DDS_RETCODE_OK)
      this->abstract_writer_ = 0;
    else
      ACE_ERROR ((LM_ERROR,
                  ACE_TEXT ("%T (%t) - %M - failed to delete data writer\n")));
  }

  if (this->endpoint_.is_open ())
  {
    // First, make sure we close the endpoint.
    if (0 != this->endpoint_.close ())
      ACE_ERROR ((LM_ERROR,
                  ACE_TEXT ("%T (%t) - %M - failed to close subscriber endpoint\n")));
  }

  return this->consumer_._retn ();
}

