// -*- C++ -*-
// $Id$

namespace iCCM
{

//
// get_domainparticipantfactory_instance
//
RTIDDS::domainparticipantfactory_ptr_type
RTIDDS::get_domainparticipantfactory_instance (void)
{
  return ::DDSDomainParticipantFactory::get_instance ();
}

//
// participant_qos_default
//
CUTS_INLINE
const RTIDDS::domainparticipantqos_type & RTIDDS::domainparticipant_qos_default (void)
{
  return DDS_PARTICIPANT_QOS_DEFAULT;
}

//
// publisher_qos_default
//
CUTS_INLINE
const RTIDDS::publisherqos_type & RTIDDS::publisher_qos_default (void)
{
  return DDS_PUBLISHER_QOS_DEFAULT;
}

//
// subscriber_qos_default
//
CUTS_INLINE
const RTIDDS::subscriberqos_type & RTIDDS::subscriber_qos_default (void)
{
  return DDS_SUBSCRIBER_QOS_DEFAULT;
}

//
// topic_qos_default
//
CUTS_INLINE
const RTIDDS::topicqos_type & RTIDDS::topic_qos_default (void)
{
  return DDS_TOPIC_QOS_DEFAULT;
}

//
// datawriter_qos_default
//
CUTS_INLINE
const RTIDDS::datawriterqos_type & RTIDDS::datawriter_qos_default (void)
{
  return DDS_DATAWRITER_QOS_DEFAULT;
}

//
// datareader_qos_default
//
CUTS_INLINE
const RTIDDS::datareaderqos_type & RTIDDS::datareader_qos_default (void)
{
  return DDS_DATAREADER_QOS_DEFAULT;
}

}
