// $Id$

namespace iCCM
{

//
// Tron_EventConsumer_T
//
template <typename SERVANT, typename EVENT>
CUTS_INLINE
Tron_EventConsumer_T <SERVANT, EVENT>::
Tron_EventConsumer_T (SERVANT * servant, CALLBACK_METHOD callback)
: servant_ (servant),
  callback_ (callback)
{

}

//
// ~Tron_EventConsumer_T
//
template <typename SERVANT, typename EVENT>
CUTS_INLINE
Tron_EventConsumer_T <SERVANT, EVENT>::~Tron_EventConsumer_T (void)
{

}

}
