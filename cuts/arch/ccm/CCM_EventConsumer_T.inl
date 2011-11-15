// $Id$

//
// CUTS_CCM_EventConsumer_T
//
template <typename T, typename SERVANT>
CUTS_INLINE
CUTS_CCM_EventConsumer_T <T, SERVANT>::
CUTS_CCM_EventConsumer_T (SERVANT * servant, upcall_method_type upcall)
: servant_ (servant),
  upcall_ (upcall)
{

}

//
// ~CUTS_CCM_EventConsumer_T
//
template <typename T, typename SERVANT>
CUTS_INLINE
CUTS_CCM_EventConsumer_T <T, SERVANT>::~CUTS_CCM_EventConsumer_T (void)
{

}

//
// push_event
//
template <typename T, typename SERVANT>
CUTS_INLINE
void CUTS_CCM_EventConsumer_T <T, SERVANT>::push_event (T * ev)
{
  if (0 != this->servant_)
    (*this->upcall_) (this->servant_, ev);
}
