// $Id$

#if !defined (__CUTS_INLINE__)
# include "CCM_Events_T.inl"
#endif

//
// CUTS_CCM_Event_T
//
template <typename EVENT>
CUTS_CCM_Event_T <EVENT>::CUTS_CCM_Event_T (void)
{
  _ptr_type ev = 0;
  ACE_NEW_THROW_EX (ev, EVENT (), ::CORBA::NO_MEMORY ());
  this->event_ = ev;
}

//
// CUTS_CCM_Event_T
//
template <typename EVENT>
CUTS_CCM_Event_T <EVENT>::CUTS_CCM_Event_T (EVENT * ev)
: event_ (ev)
{

}

//
// CUTS_Event_T
//
template <typename EVENTTYPE>
CUTS_Event_T <EVENTTYPE>::CUTS_Event_T (void)
{

}

//
// ~CUTS_Event_T
//
template <typename EVENTTYPE>
CUTS_Event_T <EVENTTYPE>::~CUTS_Event_T (void)
{

}

//
// CUTS_Event_init_T
//
template <typename EVENTTYPE>
CUTS_Event_init_T <EVENTTYPE>::CUTS_Event_init_T (void)
{

}

//
// ~CUTS_Event_init_T
//
template <typename EVENTTYPE>
CUTS_Event_init_T <EVENTTYPE>::~CUTS_Event_init_T (void)
{

}

template <typename EVENTTYPE>
CORBA::ValueBase *
CUTS_Event_init_T <EVENTTYPE>::create_for_unmarshal (void)
{
  CORBA::ValueBase *ret_val = 0;
  ACE_NEW_THROW_EX (ret_val, EVENTTYPE, ::CORBA::NO_MEMORY ());
  return ret_val;
}
