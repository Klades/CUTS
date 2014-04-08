// $Id$

namespace iCCM
{

//
// CoreDX_EventConsumer_T
//
template <typename SERVANT, typename EVENT>
CUTS_INLINE
CoreDX_EventConsumer_T <SERVANT, EVENT>::
CoreDX_EventConsumer_T (SERVANT * servant, CALLBACK_METHOD callback)
: DDS_EventConsumer_T <CoreDX, SERVANT, EVENT> (servant, callback)
{

}

//
// ~CoreDX_EventConsumer_T
//
template <typename SERVANT, typename EVENT>
CUTS_INLINE
CoreDX_EventConsumer_T <SERVANT, EVENT>::~CoreDX_EventConsumer_T (void)
{

}

}
