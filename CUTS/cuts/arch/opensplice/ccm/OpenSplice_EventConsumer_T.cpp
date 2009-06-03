// $Id$

template <typename SERVANT, typename T, typename EVENT_SEQ>
CUTS_OpenSplice_CCM_EventConsumer_T <SERVANT, T, EVENT_SEQ>::
CUTS_OpenSplice_CCM_EventConsumer_T (SERVANT * servant, deserialize_method callback)
  : servant_ (servant),
    callback_ (callback)
{

}

template <typename SERVANT, typename T, typename EVENT_SEQ>
CUTS_OpenSplice_CCM_EventConsumer_T <SERVANT, T, EVENT_SEQ>::
~CUTS_OpenSplice_CCM_EventConsumer_T (void)
{

}

//
// on_data_available
//
template <typename SERVANT, typename T, typename EVENT_SEQ>
void CUTS_OpenSplice_CCM_EventConsumer_T <SERVANT, T, EVENT_SEQ>::
on_data_available (::DDS::DataReader_ptr p)
{
  EVENT_SEQ event_seq;
  ::DDS::SampleInfoSeq sample_info;

  // Get the concrete reader from the generic reader.
  typename T::_var_type reader = T::_narrow (p);

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
