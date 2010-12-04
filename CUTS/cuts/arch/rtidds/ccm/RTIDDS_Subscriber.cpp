// $Id$

#include "RTIDDS_Subscriber.h"

//
// CUTS_RTIDDS_CCM_Subscriber
//
CUTS_RTIDDS_CCM_Subscriber::CUTS_RTIDDS_CCM_Subscriber (void)
: participant_ (0),
  publisher_ (0),
  abstract_writer_ (0)
{

}

//
// ~CUTS_RTIDDS_CCM_Subscriber
//
CUTS_RTIDDS_CCM_Subscriber::~CUTS_RTIDDS_CCM_Subscriber (void)
{
  this->disconnect ();
}

//
// configure
//
void CUTS_RTIDDS_CCM_Subscriber::
configure (::DDSDomainParticipant * participant)
{
  this->participant_ = participant;
}

//
// connect
//
void CUTS_RTIDDS_CCM_Subscriber::
connect (::Components::EventConsumerBase_ptr p)
{
  // Now, register for the topic. Subscribing an event consumer to
  // will enable a component to register for this topic.
  this->publisher_ =
    this->participant_->create_publisher (DDS_PUBLISHER_QOS_DEFAULT,
                                          0,
                                          DDS_STATUS_MASK_NONE);

  // The last part is to create a data reader.
  ::DDSTopic * topic = this->endpoint_.topic ();

  this->abstract_writer_ =
      this->publisher_->create_datawriter (topic,
                                           DDS_DATAWRITER_QOS_DEFAULT,
                                           0,
                                           DDS_STATUS_MASK_NONE);

  this->consumer_ = p;
}

//
// disconnect
//
::Components::EventConsumerBase_ptr
CUTS_RTIDDS_CCM_Subscriber::disconnect (void)
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

  if (0 != this->publisher_)
  {
    retcode = this->participant_->delete_publisher (this->publisher_);

    if (retcode == DDS_RETCODE_OK)
      this->publisher_ = 0;
    else

      ACE_ERROR ((LM_ERROR,
                  ACE_TEXT ("%T (%t) - %M - failed to delete publisher\n")));
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

