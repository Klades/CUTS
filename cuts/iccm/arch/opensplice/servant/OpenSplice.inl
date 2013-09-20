// -*- C++ -*-
// $Id$

namespace iCCM
{

//
// get_domainparticipantfactory_instance
//
OpenSplice::domainparticipantfactory_ptr_type
OpenSplice::get_domainparticipantfactory_instance (void)
{
  return ::DDS::DomainParticipantFactory::get_instance ();
}

//
// participant_qos_default
//
CUTS_INLINE
const OpenSplice::domainparticipantqos_type & OpenSplice::domainparticipant_qos_default (void)
{
  return PARTICIPANT_QOS_DEFAULT;
}

//
// publisher_qos_default
//
CUTS_INLINE
const OpenSplice::publisherqos_type & OpenSplice::publisher_qos_default (void)
{
  return PUBLISHER_QOS_DEFAULT;
}

//
// subscriber_qos_default
//
CUTS_INLINE
const OpenSplice::subscriberqos_type & OpenSplice::subscriber_qos_default (void)
{
  return SUBSCRIBER_QOS_DEFAULT;
}

//
// topic_qos_default
//
CUTS_INLINE
const OpenSplice::topicqos_type & OpenSplice::topic_qos_default (void)
{
  return TOPIC_QOS_DEFAULT;
}

//
// datawriter_qos_default
//
CUTS_INLINE
const OpenSplice::datawriterqos_type & OpenSplice::datawriter_qos_default (void)
{
  return DATAWRITER_QOS_USE_TOPIC_QOS;
}

//
// datareader_qos_default
//
CUTS_INLINE
const OpenSplice::datareaderqos_type & OpenSplice::datareader_qos_default (void)
{
  return DATAREADER_QOS_USE_TOPIC_QOS;
}

}
