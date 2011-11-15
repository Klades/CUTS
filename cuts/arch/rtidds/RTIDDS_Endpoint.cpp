// $Id$

#include "RTIDDS_Endpoint.h"

#if !defined (__CUTS_INLINE__)
#include "RTIDDS_Endpoint.inl"
#endif

#include "ace/Log_Msg.h"
#include <string>

//
// open
//
int CUTS_RTIDDS_Endpoint::
open (::DDSDomainParticipant * participant,
      const char * type_name,
      const char * topic_name)
{
  // First, let's search for the topic just in case this endpoint
  // is part of a loopback connection.
  DDS_Duration_t duration;
  duration.sec = 0;
  duration.nanosec = 0;

  this->dds_topic_ = participant->find_topic (topic_name, duration);

  if (0 == this->dds_topic_)
  {
    this->dds_topic_ =
      participant->create_topic (topic_name,
                                 type_name,
                                 DDS_TOPIC_QOS_DEFAULT,
                                 0,
                                 DDS_STATUS_MASK_NONE);

    if (0 == this->dds_topic_)
      ACE_ERROR_RETURN ((LM_ERROR,
                         "%T (%t) - %M - failed to create topic %s\n",
                         topic_name),
                        -1);
  }

  // Save the participant for later.
  this->participant_ = participant;
  return 0;
}

//
// close
//
int CUTS_RTIDDS_Endpoint::close (void)
{
  if (0 != this->participant_ && 0 != this->dds_topic_)
  {
    this->participant_->delete_topic (this->dds_topic_);
    this->dds_topic_ = 0;
  }

  return 0;
}
