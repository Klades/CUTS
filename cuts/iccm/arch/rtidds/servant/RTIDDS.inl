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
const RTIDDS::topicqos_type * RTIDDS::topic_qos_default (void)
{
  return &DDS_TOPIC_QOS_DEFAULT;
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
const RTIDDS::datareaderqos_type * RTIDDS::datareader_qos_default (void)
{
  return &DDS_DATAREADER_QOS_DEFAULT;
}

//
// copy_string
//
CUTS_INLINE
void RTIDDS::copy_string (RTIDDS::stringseq_type & dst, const ::iccm::StringSeq & src)
{
  dst.ensure_length (src.count_item (), src.count_item ());

  ::iccm::StringSeq::item_const_iterator
    iter = src.begin_item (), iter_end = src.end_item ();

  for (size_t i = 0; iter != iter_end; ++ iter, ++ i)
    dst[i] = DDS_String_dup((*iter)->c_str ());
}

}
