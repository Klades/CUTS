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

//
// push_ciao_event
//
template <typename T, typename SERVANT>
CUTS_INLINE
void CUTS_CCM_EventConsumer_T <T, SERVANT>::
ciao_push_event (::Components::EventBase * ev,
                 const char * ,
                 ::CORBA::TypeCode_ptr)
{
  this->push_event (ev);
}

//
// ciao_is_substitutable
//
template <typename T, typename SERVANT>
CUTS_INLINE
::CORBA::Boolean CUTS_CCM_EventConsumer_T <T, SERVANT>::
ciao_is_substitutable (const char *)
{
  throw ::CORBA::NO_IMPLEMENT ();
}
