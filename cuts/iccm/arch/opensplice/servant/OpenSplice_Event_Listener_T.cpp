// $Id$

namespace iCCM
{

//
// OpenSplice_Event_Listener_T
//
template <typename SERVANT, typename EVENT>
OpenSplice_Event_Listener_T <SERVANT, EVENT>::
OpenSplice_Event_Listener_T (SERVANT * servant, DESERIALIZE_METHOD callback)
: servant_ (servant),
  callback_ (callback)
{
}

//
// ~OpenSplice_Event_Listener_T
//
template <typename SERVANT, typename EVENT>
OpenSplice_Event_Listener_T <SERVANT, EVENT>::
~OpenSplice_Event_Listener_T (void)
{
}

//
// on_requested_deadline_missed
//
template <typename SERVANT, typename EVENT>
void OpenSplice_Event_Listener_T <SERVANT, EVENT>::
on_requested_deadline_missed (::DDS::DataReader_ptr abstract_reader,
                              const ::DDS::RequestedDeadlineMissedStatus &)
{
}

//
// on_requested_incompatible_qos
//
template <typename SERVANT, typename EVENT>
void OpenSplice_Event_Listener_T <SERVANT, EVENT>::
on_requested_incompatible_qos (::DDS::DataReader_ptr,
                               const ::DDS::RequestedIncompatibleQosStatus &)
{
}

//
// on_sample_rejected
//
template <typename SERVANT, typename EVENT>
void OpenSplice_Event_Listener_T <SERVANT, EVENT>::
on_sample_rejected (::DDS::DataReader_ptr,
                    const ::DDS::SampleRejectedStatus &)
{
}

//
// on_liveliness_changed
//
template <typename SERVANT, typename EVENT>
void OpenSplice_Event_Listener_T <SERVANT, EVENT>::
on_liveliness_changed (::DDS::DataReader_ptr,
                       const ::DDS::LivelinessChangedStatus &)
{
}

//
// on_data_available
//
template <typename SERVANT, typename EVENT>
void OpenSplice_Event_Listener_T <SERVANT, EVENT>::
on_data_available (::DDS::DataReader_ptr abstract_reader)
{
  typename traits_type::dds_event_sequence_type event_seq;
  ::DDS::SampleInfoSeq sample_info;

  // Get the concrete reader from the generic reader.
  reader_type_var reader = reader_type::_narrow (abstract_reader);
  ::DDS::ReturnCode_t status = reader->take (event_seq,
                                             sample_info,
                                             1,
                                             ::DDS::ANY_SAMPLE_STATE,
                                             ::DDS::ANY_VIEW_STATE,
                                             ::DDS::ANY_INSTANCE_STATE);

  if (status == ::DDS::RETCODE_OK)
  {
    if (0 != this->callback_)
    {
      // Push each event in the sequence to the servant so it can
      // pass it along to the implementation.
      size_t length = event_seq.length ();

      for (size_t i = 0; i < length; ++ i)
      {
        typename traits_type::upcall_event_type upcall_event (event_seq[i]);
        (this->servant_->*this->callback_) (&upcall_event);
      }
    }
    else
    {
      ACE_ERROR ((LM_CRITICAL,
                  ACE_TEXT ("%T (%t) - %M - callback is not set!!\n")));
    }

    // Return our loan back to the system.
    reader->return_loan (event_seq, sample_info);
  }
  else
  {
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - failed to take next event [retcode=%d]\n"),
                status));
  }
}

//
// on_subscription_matched
//
template <typename SERVANT, typename EVENT>
void OpenSplice_Event_Listener_T <SERVANT, EVENT>::
on_subscription_matched (::DDS::DataReader_ptr,
                         const ::DDS::SubscriptionMatchedStatus &)
{
}

//
// on_sample_lost
//
template <typename SERVANT, typename EVENT>
void OpenSplice_Event_Listener_T <SERVANT, EVENT>::
on_sample_lost (::DDS::DataReader_ptr,
                const ::DDS::SampleLostStatus &)
{
}

}
