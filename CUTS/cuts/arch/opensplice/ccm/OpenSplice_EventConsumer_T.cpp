// $Id$

#include "cuts/arch/opensplice/OpenSplice_Traits_T.h"
#include "ccpp_dds_dcps.h"

template <typename SERVANT, typename EVENT>
CUTS_OpenSplice_CCM_EventConsumer_T <SERVANT, EVENT>::
CUTS_OpenSplice_CCM_EventConsumer_T (SERVANT * servant, deserialize_method callback)
  : servant_ (servant),
    callback_ (callback)
{

}

template <typename SERVANT, typename EVENT>
CUTS_OpenSplice_CCM_EventConsumer_T <SERVANT, EVENT>::
~CUTS_OpenSplice_CCM_EventConsumer_T (void)
{

}

//
// configure
//
template <typename SERVANT, typename EVENT>
int CUTS_OpenSplice_CCM_EventConsumer_T <SERVANT, EVENT>::
configure (::DDS::DomainParticipant_ptr participant,
	   const char * inst,
	   const char * topic)
{
  // First, let's create the fully qualified name of the topic.                                                                                                           
  ACE_CString new_topic_name (inst);
  new_topic_name += ".";
  new_topic_name += topic;

  // Then, create the topic for the event.

  // Now, register for the topic. Subscribing an event consumer to                                                                                                                
  // will enable a component to register for this topic.
  this->subscriber_ = participant->create_subscriber (SUBSCRIBER_QOS_DEFAULT,
                                                      ::DDS::SubscriberListener::_nil (),
                                                      ::DDS::ANY_STATUS);

  // Finally, save the name of the topic.
  this->topic_ = new_topic_name;
  return 0;
}

//
// on_data_available
//
template <typename SERVANT, typename EVENT>
void CUTS_OpenSplice_CCM_EventConsumer_T <SERVANT, EVENT>::
on_data_available (::DDS::DataReader_ptr p)
{
  typename CUTS_OpenSplice_Traits_T <EVENT>::dds_event_sequence_type event_seq;
  ::DDS::SampleInfoSeq sample_info;

  // Get the concrete reader from the generic reader.
  typename CUTS_OpenSplice_Traits_T <EVENT>::reader_var_type reader = 
    CUTS_OpenSplice_Traits_T <EVENT>::reader_type::_narrow (p);

  ::DDS::ReturnCode_t status =
      reader->take (event_seq,
		    sample_info,
		    1,
		    ::DDS::ANY_SAMPLE_STATE,
		    ::DDS::ANY_VIEW_STATE,
		    ::DDS::ANY_INSTANCE_STATE);

  // We should check the return code here!!

  if (0 != this->callback_)
    (*this->callback_) (this->servant_, event_seq[0]);
}
