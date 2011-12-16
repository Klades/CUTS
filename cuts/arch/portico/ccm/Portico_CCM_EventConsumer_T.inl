// -*- C++ -*-
// Id: CCM_EventConsumer.inl.tmpl 3238 2011-12-07 04:12:45Z hillj Portico_CCM_EventConsumer.inl 2687 2009-06-02 21:20:04Z hillj

//
// Portico_CCM_EventConsumer
//
template <typename SERVANT, typename EVENT>
CUTS_INLINE
Portico_CCM_EventConsumer_T <SERVANT, EVENT>::
Portico_CCM_EventConsumer_T (SERVANT * servant, SERVANT_UPCALL upcall)
: servant_ (servant),
  upcall_ (upcall)
{

}

//
// ~Portico_CCM_EventConsumer
//
template <typename SERVANT, typename EVENT>
CUTS_INLINE
Portico_CCM_EventConsumer_T <SERVANT, EVENT>::
~Portico_CCM_EventConsumer_T (void)
{

}
