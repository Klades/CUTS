// $Id$

namespace iCCM
{

//
// DDS_Event_Listener_T
//
template <typename T, typename SERVANT, typename EVENT>
CUTS_INLINE
DDS_Event_Listener_T <T, SERVANT, EVENT>::
DDS_Event_Listener_T (SERVANT * servant, DESERIALIZE_METHOD callback)
: servant_ (servant),
  callback_ (callback)
{
}

//
// ~DDS_Event_Listener_T
//
template <typename T, typename SERVANT, typename EVENT>
CUTS_INLINE
DDS_Event_Listener_T <T, SERVANT, EVENT>::~DDS_Event_Listener_T (void)
{
}

//
// on_requested_deadline_missed
//
template <typename T, typename SERVANT, typename EVENT>
CUTS_INLINE
void DDS_Event_Listener_T <T, SERVANT, EVENT>::
on_requested_deadline_missed (::DDS::DataReader_ptr, const ::DDS::RequestedDeadlineMissedStatus &)
{
}

//
// on_requested_incompatible_qos
//
template <typename T, typename SERVANT, typename EVENT>
CUTS_INLINE
void DDS_Event_Listener_T <T, SERVANT, EVENT>::
on_requested_incompatible_qos (::DDS::DataReader_ptr, const ::DDS::RequestedIncompatibleQosStatus &)
{
}

//
// on_sample_rejected
//
template <typename T, typename SERVANT, typename EVENT>
CUTS_INLINE
void DDS_Event_Listener_T <T, SERVANT, EVENT>::
on_sample_rejected (::DDS::DataReader_ptr, const ::DDS::SampleRejectedStatus &)
{
}

//
// on_liveliness_changed
//
template <typename T, typename SERVANT, typename EVENT>
CUTS_INLINE
void DDS_Event_Listener_T <T, SERVANT, EVENT>::
on_liveliness_changed (::DDS::DataReader_ptr, const ::DDS::LivelinessChangedStatus &)
{
}

//
// on_data_available
//
template <typename T, typename SERVANT, typename EVENT>
void DDS_Event_Listener_T <T, SERVANT, EVENT>::
on_data_available (::DDS::DataReader_ptr data_reader)
{
  typename event_traits_type::dds_event_sequence_type event_seq;
  typedef typename T::sampleinfoseq_type sampleinfoseq_type;
  typedef typename T::returncode_type returncode_type;

  // Get the concrete reader from the generic reader.
  typedef typename event_traits_type::reader_var_type typed_reader_var_type;
  typedef typename event_traits_type::reader_type typed_reader_type;

  typed_reader_var_type reader = T::_reader_cast <typed_reader_type> (data_reader);

  sampleinfoseq_type sample_info;
  returncode_type status = reader->take (event_seq,
                                         sample_info,
                                         1,
                                         T::ANY_SAMPLE_STATE,
                                         T::ANY_VIEW_STATE,
                                         T::ANY_INSTANCE_STATE);

  if (0 == status)
  {
    if (0 != this->callback_)
    {
      // Push each event in the sequence to the servant so it can
      // pass it along to the implementation.
      size_t length = event_seq.length ();

      for (size_t i = 0; i < length; ++ i)
      {
        typename event_traits_type::upcall_event_type upcall_event (event_seq[i]);
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
template <typename T, typename SERVANT, typename EVENT>
CUTS_INLINE
void DDS_Event_Listener_T <T, SERVANT, EVENT>::
on_subscription_matched (::DDS::DataReader_ptr, const ::DDS::SubscriptionMatchedStatus &)
{
}

//
// on_sample_lost
//
template <typename T, typename SERVANT, typename EVENT>
CUTS_INLINE
void DDS_Event_Listener_T <T, SERVANT, EVENT>::
on_sample_lost (::DDS::DataReader_ptr, const ::DDS::SampleLostStatus &)
{
}

}
