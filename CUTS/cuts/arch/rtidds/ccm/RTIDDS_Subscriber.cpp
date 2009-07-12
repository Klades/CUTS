// $Id$

#include "RTIDDS_Subscriber.h"

CUTS_RTIDDS_CCM_Subscriber::CUTS_RTIDDS_CCM_Subscriber (void)
{

}

CUTS_RTIDDS_CCM_Subscriber::~CUTS_RTIDDS_CCM_Subscriber (void)
{

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
  return this->consumer_._retn ();
}

