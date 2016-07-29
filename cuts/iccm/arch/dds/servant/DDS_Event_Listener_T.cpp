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
: reader_ (0),
  servant_ (servant),
  callback_ (callback),
  task_ (new task_type (servant, callback))
{
  task_->open();
}

//
// ~DDS_Event_Listener_T
//
template <typename T, typename SERVANT, typename EVENT>
CUTS_INLINE
DDS_Event_Listener_T <T, SERVANT, EVENT>::~DDS_Event_Listener_T (void)
{
  task_->msg_queue ()->deactivate ();
}

//
// configure
//
template <typename T, typename SERVANT, typename EVENT>
CUTS_INLINE
void DDS_Event_Listener_T <T, SERVANT, EVENT>::
configure (typename T::datareader_ptr_type reader)
{
  this->reader_ = T::_duplicate (reader);
}

//
// on_requested_deadline_missed
//
template <typename T, typename SERVANT, typename EVENT>
CUTS_INLINE
void DDS_Event_Listener_T <T, SERVANT, EVENT>::
on_requested_deadline_missed (datareader_ptr_type, const typename T::requesteddeadlinemissedstatus_type &)
{

}

//
// on_requested_incompatible_qos
//
template <typename T, typename SERVANT, typename EVENT>
CUTS_INLINE
void DDS_Event_Listener_T <T, SERVANT, EVENT>::
on_requested_incompatible_qos (datareader_ptr_type, const typename T::requestedincompatibleqosstatus_type &)
{

}

//
// on_sample_rejected
//
template <typename T, typename SERVANT, typename EVENT>
CUTS_INLINE
void DDS_Event_Listener_T <T, SERVANT, EVENT>::
on_sample_rejected (datareader_ptr_type, const typename T::samplerejectedstatus_type &)
{

}

//
// on_liveliness_changed
//
template <typename T, typename SERVANT, typename EVENT>
CUTS_INLINE
void DDS_Event_Listener_T <T, SERVANT, EVENT>::
on_liveliness_changed (datareader_ptr_type, const typename T::livelinesschangedstatus_type &)
{

}

//
// on_data_available
//
template <typename T, typename SERVANT, typename EVENT>
void DDS_Event_Listener_T <T, SERVANT, EVENT>::
on_data_available (datareader_ptr_type data_reader)
{
  ACE_ERROR ((LM_DEBUG,
              ACE_TEXT ("%T (%t) - %M - Data Available\n")));

  typename event_traits_type::dds_event_sequence_type * event_seq = new event_traits_type::dds_event_sequence_type;
  typedef typename T::sampleinfoseq_type sampleinfoseq_type;
  typedef typename T::returncode_type returncode_type;

  // Get the concrete reader from the generic reader.
  typedef typename event_traits_type::reader_var_type typed_reader_var_type;
  typedef typename event_traits_type::reader_type typed_reader_type;

  typed_reader_var_type reader = T::template _reader_cast < typed_reader_type > (data_reader);

  sampleinfoseq_type * sample_info = new sample_info;
  #ifdef ICCM_DDS_USES_POINTERS
  returncode_type status = reader->take (event_seq,
                                         sample_info,
                                         T::LENGTH_UNLIMITED,
                                         T::ANY_SAMPLE_STATE,
                                         T::ANY_VIEW_STATE,
                                         T::ANY_INSTANCE_STATE);
  #else
  returncode_type status = reader->take (*event_seq,
                                         *sample_info,
                                         T::LENGTH_UNLIMITED,
                                         T::ANY_SAMPLE_STATE,
                                         T::ANY_VIEW_STATE,
                                         T::ANY_INSTANCE_STATE);
  #endif

  ACE_ERROR ((LM_DEBUG,
              ACE_TEXT ("%T (%t) - %M - Took Data\n")));

  switch (status)
  {
  case T::RETCODE_OK:
    {
      // Push each event in the sequence to the servant so it can
      // pass it along to the implementation.
      package_type * pkg = new package_type(event_seq, sample_info, reader);
      task_->putq(pkg);
    }
    break;

  case T::RETCODE_NO_DATA:
    // Do nothing...
    break;

  default:
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
on_subscription_matched (datareader_ptr_type, const typename T::subscriptionmatchedstatus_type &)
{

}

//
// on_sample_lost
//
template <typename T, typename SERVANT, typename EVENT>
CUTS_INLINE
void DDS_Event_Listener_T <T, SERVANT, EVENT>::
on_sample_lost (datareader_ptr_type, const typename T::sampleloststatus_type &)
{

}

}
