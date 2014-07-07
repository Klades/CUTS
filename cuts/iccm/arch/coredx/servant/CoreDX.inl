// -*- C++ -*-
// $Id$

namespace iCCM
{

//
// get_domainparticipantfactory_instance
//
CoreDX::domainparticipantfactory_ptr_type
CoreDX::get_domainparticipantfactory_instance (void)
{
  return ::DDS::DomainParticipantFactory::get_instance ();
}

//
// participant_qos_default
//
CUTS_INLINE
const CoreDX::domainparticipantqos_type & CoreDX::domainparticipant_qos_default (void)
{
  return ::DDS::PARTICIPANT_QOS_DEFAULT;
}

//
// publisher_qos_default
//
CUTS_INLINE
const CoreDX::publisherqos_type & CoreDX::publisher_qos_default (void)
{
  return ::DDS::PUBLISHER_QOS_DEFAULT;
}

//
// subscriber_qos_default
//
CUTS_INLINE
const CoreDX::subscriberqos_type & CoreDX::subscriber_qos_default (void)
{
  return ::DDS::SUBSCRIBER_QOS_DEFAULT;
}

//
// topic_qos_default
//
CUTS_INLINE
const CoreDX::topicqos_type * CoreDX::topic_qos_default (void)
{
  return &::DDS::TOPIC_QOS_DEFAULT;
}

//
// datawriter_qos_default
//
CUTS_INLINE
const CoreDX::datawriterqos_type & CoreDX::datawriter_qos_default (void)
{
  return ::DDS::DATAWRITER_QOS_DEFAULT;
}

//
// datareader_qos_default
//
CUTS_INLINE
const CoreDX::datareaderqos_type * CoreDX::datareader_qos_default (void)
{
  return &::DDS::DATAREADER_QOS_DEFAULT;
}

//
// copy_string
//
CUTS_INLINE
void CoreDX::copy_string (CoreDX::stringseq_type & dst, const ::iccm::StringSeq & src)
{
  dst.resize (src.count_item ());

  ::iccm::StringSeq::item_const_iterator
    iter = src.begin_item (), iter_end = src.end_item ();

  for (size_t i = 0; iter != iter_end; ++ iter, ++ i)
    dst[i] = ACE_OS::strdup ((*iter)->c_str ());
}

}
