// $Id$

#include "RTIDDS_Servant.h"

#if !defined (__CUTS_INLINE__)
#include "RTIDDS_Servant.inl"
#endif

//
// remove
//
::DDSDomainParticipant * CUTS_RTIDDS_Servant::remove_participant (void)
{
  if (0 != this->subscriber_)
  {
    // Delete the subscriber.
    this->participant_->delete_subscriber (this->subscriber_);
    this->subscriber_ = 0;
  }

  if (0 != this->publisher_)
  {
    // Delete the publisher.
    this->participant_->delete_publisher (this->publisher_);
    this->publisher_ = 0;
  }

  // Return the participant to the caller.
  ::DDSDomainParticipant * participant = this->participant_;
  this->participant_ = 0;

  return participant;
}
