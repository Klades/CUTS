// $Id$

#include "OpenSplice_Endpoint.h"

#if !defined (__CUTS_INLINE__)
#include "OpenSplice_Endpoint.inl"
#endif

#include <string>

//
// open
//
int CUTS_OpenSplice_Endpoint::
open (::DDS::DomainParticipant_ptr participant,
      ::DDS::TypeSupport_ptr type_support,
      const char* topic_name)
{
  // First, register the type with the participant.
  ::CORBA::String_var type_name = type_support->get_type_name ();
  return this->open (participant, type_support, type_name.in (), topic_name);
}

//
// open
//
int CUTS_OpenSplice_Endpoint::
open (::DDS::DomainParticipant_ptr participant,
      ::DDS::TypeSupport_ptr type_support,
      const char * type_name,
      const char * topic_name)
{
  ACE_DEBUG ((LM_DEBUG,
              "%T (%t) - %M - registering type %s with the participant\n",
              type_name));

  ::DDS::ReturnCode_t status =
      type_support->register_type (participant, type_name);

  if (::DDS::RETCODE_OK != status)
    {
      ACE_ERROR_RETURN ((LM_ERROR,
                         "%T ($t) - %M - failed to register type %s with participant; "
                         " return code = %d\n",
                         type_name,
                         status),
                        -1);
    }

  // We need to normalize the topic name. Right now, we are only
  // checking for periods (.) in the topic name.
  std::string normalized_topic_name (topic_name);
  
  std::replace (normalized_topic_name.begin (),
                normalized_topic_name.end (),
                '.',
                '_');

  ACE_DEBUG ((LM_DEBUG,
              "%T (%t) - %M - creating topic %s of type %s\n",
              topic_name,
              type_name));

  // Next, we can create the topic for the endpoint.
  this->dds_topic_ = 
    participant->create_topic (normalized_topic_name.c_str (),
			       type_name,
			       TOPIC_QOS_DEFAULT,
			       ::DDS::TopicListener::_nil (),
			       ::DDS::ANY_STATUS);

  if (::CORBA::is_nil (this->dds_topic_.in ()))
    {
      ACE_ERROR_RETURN ((LM_ERROR,
                         "%T (%t) - %M - failed to create topic %s\n",
                         topic_name),
                        -1);
    }

  // Save the participant for later.
  this->participant_ = ::DDS::DomainParticipant::_duplicate (participant);
  return 0;
}

//
// close
//
int CUTS_OpenSplice_Endpoint::close (void)
{
  if (!::CORBA::is_nil (this->participant_.in ()) &&
      !::CORBA::is_nil (this->dds_topic_.in ()))
    {
      this->participant_->delete_topic (this->dds_topic_.in ());
      this->dds_topic_ = ::DDS::Topic::_nil ();
    }

  return 0;
}
