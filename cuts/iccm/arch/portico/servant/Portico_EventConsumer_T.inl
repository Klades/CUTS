// $Id$

namespace iCCM
{

//
// Portico_EventConsumer_T
//
template <typename SERVANT, typename EVENT>
CUTS_INLINE
Portico_EventConsumer_T <SERVANT, EVENT>::
Portico_EventConsumer_T (SERVANT * servant, CALLBACK_METHOD callback)
: servant_ (servant),
  callback_ (callback)
{

}

//
// ~Portico_EventConsumer_T
//
template <typename SERVANT, typename EVENT>
CUTS_INLINE
Portico_EventConsumer_T <SERVANT, EVENT>::~Portico_EventConsumer_T (void)
{

}

}
