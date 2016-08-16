// $Id$

//
// CUTS_CCM_EventConsumer_T
//
template <typename T, typename SERVANT>
CUTS_INLINE
CUTS_CCM_EventConsumer_T <T, SERVANT>::
CUTS_CCM_EventConsumer_T (SERVANT * servant, upcall_method_type upcall)
: servant_ (servant),
  upcall_ (upcall),
  task_ (new Consumer_Task<T, SERVANT>(servant, upcall))
{
  task_->open ();
}

//
// ~CUTS_CCM_EventConsumer_T
//
template <typename T, typename SERVANT>
CUTS_INLINE
CUTS_CCM_EventConsumer_T <T, SERVANT>::~CUTS_CCM_EventConsumer_T (void)
{
  task_->msg_queue ()->deactivate ();
  task_->wait ();
}

//
// push_event
//
template <typename T, typename SERVANT>
CUTS_INLINE
void CUTS_CCM_EventConsumer_T <T, SERVANT>::push_event (T * ev)
{
  ACE_Message_Block * msg = new ACE_Message_Block (reinterpret_cast<char*>(ev));
  task_->put (msg);
}
