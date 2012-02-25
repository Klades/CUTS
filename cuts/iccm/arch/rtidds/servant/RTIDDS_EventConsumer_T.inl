// $Id$

namespace iCCM
{

//
// RTIDDS_EventConsumer_T
//
template <typename SERVANT, typename EVENT>
CUTS_INLINE
RTIDDS_EventConsumer_T <SERVANT, EVENT>::
RTIDDS_EventConsumer_T (SERVANT * servant, DESERIALIZE_METHOD callback)
: DDS_EventConsumer_T (servant, callback)
{

}

//
// ~RTIDDS_EventConsumer_T
//
template <typename SERVANT, typename EVENT>
CUTS_INLINE
RTIDDS_EventConsumer_T <SERVANT, EVENT>::~RTIDDS_EventConsumer_T (void)
{

}

}
