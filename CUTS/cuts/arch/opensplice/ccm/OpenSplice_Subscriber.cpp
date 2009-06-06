// $Id$

#include "OpenSplice_Subscriber.h"

CUTS_OpenSplice_CCM_Subscriber::CUTS_OpenSplice_CCM_Subscriber (void)
{

}

CUTS_OpenSplice_CCM_Subscriber::~CUTS_OpenSplice_CCM_Subscriber (void)
{

}

//
// configure
//
void CUTS_OpenSplice_CCM_Subscriber::
configure (::DDS::DomainParticipant_ptr participant)
{
  this->participant_ = ::DDS::DomainParticipant::_duplicate (participant);
}

//
// connect
//
void CUTS_OpenSplice_CCM_Subscriber::
connect (::Components::EventConsumerBase_ptr p)
{
  // Now, register for the topic. Subscribing an event consumer to
  // will enable a component to register for this topic.
  this->publisher_ =
    this->participant_->create_publisher (PUBLISHER_QOS_DEFAULT,
                                          ::DDS::PublisherListener::_nil (),
                                          ::DDS::ANY_STATUS);

  // The last part is to create a data reader.
  ::DDS::Topic_var topic = this->endpoint_.topic ();

  this->abstract_writer_ =
      this->publisher_->create_datawriter (topic.in (),
                                           DATAWRITER_QOS_DEFAULT,
                                           0,
                                          ::DDS::ANY_STATUS);

  this->consumer_ = p;
}

//
// disconnect
//
::Components::EventConsumerBase_ptr
CUTS_OpenSplice_CCM_Subscriber::disconnect (void)
{
  return this->consumer_._retn ();
}

