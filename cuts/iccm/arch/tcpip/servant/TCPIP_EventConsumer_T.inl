// $Id$

namespace iCCM
{

//
// TCPIP_EventConsumer_T
//
template <typename SERVANT, typename EVENT>
CUTS_INLINE
TCPIP_EventConsumer_T <SERVANT, EVENT>::
TCPIP_EventConsumer_T (SERVANT * servant, long event_id)
: servant_ (servant),
  event_id_ (event_id)
{

}

//
// ~TCPIP_EventConsumer_T
//
template <typename SERVANT, typename EVENT>
CUTS_INLINE
TCPIP_EventConsumer_T <SERVANT, EVENT>::~TCPIP_EventConsumer_T (void)
{

}

}
