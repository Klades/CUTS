namespace iCCM
{
  template <typename SERVANT, typename EVENT, typename PACKAGE>
  DDS_EventConsumer_Task_T<SERVANT, EVENT, PACKAGE>::DDS_EventConsumer_Task_T (
      SERVANT * servant, DESERIALIZE_METHOD callback, int max_threads)
  : EventConsumer_Task_Base_T<PACKAGE>(max_threads)
  , servant_(servant)
  , callback_(callback)
  {
  }

  template <typename SERVANT, typename EVENT, typename PACKAGE>
  DDS_EventConsumer_Task_T<SERVANT, EVENT, PACKAGE::DDS_EventConsumer_Task_T (
      SERVANT * servant, DESERIALIZE_METHOD callback, CPU_Mask * mask, int max_threads)
  : EventConsumer_Task_Base_T<PACKAGE>(max_threads, mask)
  , servant_(servant)
  , callback_(callback)
  {
  }

  template <typename SERVANT, typename EVENT, typename PACKAGE>
  DDS_EventConsumer_Task_T<SERVANT, EVENT, PACKAGE>::~DDS_EventConsumer_Task_T (void)
  {
  }

  template <typename SERVANT, typename EVENT, typename PACKAGE>
  DDS_EventConsumer_Task_T<SERVANT, EVENT, PACKAGE>::svc (void)
  {
    typedef PACKAGE::event_seq event_seq;

    if (this->setting_affinity_) 
    {
      this->set_affinity();
    }
  
    PACKAGE * pkg;
    
    while (getq(pkg) != -1) 
    {
      event_seq * events = pkg->get();
#ifdef ICCM_DDS_SEQ_USES_SIZE
      const size_t length = events.size ();
#else
      const size_t length = events.length ();
#endif
      ACE_ERROR ((LM_DEBUG, ACE_TEXT ("%T (%t) - %M - Got Size\n")));

      for (size_t i = 0; i < length; ++i)
      {
#ifdef ICCM_DDS_USES_POINTERS
        typename pkg::upcall_event_type upcall_event (*events[i]);
#else
        typename pkg::upcall_event_type upcall_event (events[i]);
#endif
        ACE_ERROR ((LM_DEBUG,
              ACE_TEXT ("%T (%t) - %M - Making upcall to [%02x:%02x]\n"), this->servant_, this->callback_));
        ACE_ERROR ((LLM_DEBUG,
              ACE_TEXT ("%T (%t) - %M - Upcall event type is [%s] at [0x%02x]\n"), typeid (upcall_event).name(), &upcall_event));
        (this->servant_->*this->callback_) (&upcall_event);
      }
      delete pkg;
  }
}
