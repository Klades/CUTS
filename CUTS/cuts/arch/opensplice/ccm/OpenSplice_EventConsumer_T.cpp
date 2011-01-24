// $Id$

#include "ccpp_dds_dcps.h"
#include "OpenSplice_Event_T.h"

//
// CUTS_OpenSplice_CCM_EventConsumer_T
//
template <typename SERVANT, typename EVENT>
CUTS_OpenSplice_CCM_EventConsumer_T <SERVANT, EVENT>::
CUTS_OpenSplice_CCM_EventConsumer_T (SERVANT * servant, DESERIALIZE_METHOD callback)
: servant_ (servant),
  callback_ (callback)
{

}

//
// ~CUTS_OpenSplice_CCM_EventConsumer_T
//
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
configure (::DDS::Subscriber_ptr subscriber,
           const char * inst,
           const char * topic)
{
  this->subscriber_ = ::DDS::Subscriber::_duplicate (subscriber);

  // First, let's create the fully qualified name of the topic.
  ACE_CString new_topic_name (inst);
  new_topic_name += ".";
  new_topic_name += topic;

  // Register the type for with the participant. This should really
  // be done in the servant's code!!
  typename traits_type::dds_typesupport_type * type_temp = 0;

  ACE_NEW_THROW_EX (type_temp,
                    typename traits_type::dds_typesupport_type (),
                    ::CORBA::NO_MEMORY ());

  typename traits_type::dds_typesupport_var_type type_var (type_temp);

  // Let's go ahead of open this consumer for events.
  int retval = this->open_i (type_var.in (), new_topic_name.c_str ());

  if (0 != retval)
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - failed to open the consumer\n")),
                       -1);

  this->reader_ = reader_type::_narrow (this->abstract_reader_.in ());

  return 0;
}

//
// on_data_available
//
template <typename SERVANT, typename EVENT>
void CUTS_OpenSplice_CCM_EventConsumer_T <SERVANT, EVENT>::
on_data_available (::DDS::DataReader_ptr p)
{
  typename traits_type::dds_event_sequence_type event_seq;
  ::DDS::SampleInfoSeq sample_info;

  // Get the concrete reader from the generic reader.
  reader_var_type reader = reader_type::_narrow (p);

  ::DDS::ReturnCode_t status =
      reader->take (event_seq,
                    sample_info,
                    1,
                    ::DDS::ANY_SAMPLE_STATE,
                    ::DDS::ANY_VIEW_STATE,
                    ::DDS::ANY_INSTANCE_STATE);

  if (status == ::DDS::RETCODE_OK)
  {
    if (0 != this->callback_)
    {
      // Get the length of the sequence.
      int length = event_seq.length ();

      // Make sure we pass each received event to the component servant,
      // and then to the component implementation.
      for (int i = 0; i < length; ++ i)
      {
        // Right now, we are going to derive ourselves from the CORBA
        // object-by-value type since we don't want to implement the remaining
        // pure virtual methods on the concrete classes. :-)
        typedef CUTS_OpenSplice_Upcall_Event_T <typename traits_type::corba_obv_event_type,
                                                typename traits_type::dds_event_type>
                                                upcall_event_t;

        // Wrap the DDS event in the CORBA event, then make the upcall
        // to the component implementation.
        upcall_event_t upcall_event (event_seq[i]);
        (*this->callback_) (this->servant_, &upcall_event);
      }
    }
  }
  else
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - failed to take next event (retcode=%d)\n"),
                status));

  // Return our loan back to the system.
  reader->return_loan (event_seq, sample_info);
}
