// $Id$

namespace iCCM
{

//
// OpenSplice_EventConsumer_T
//
template <typename SERVANT, typename EVENT>
OpenSplice_EventConsumer_T <SERVANT, EVENT>::
OpenSplice_EventConsumer_T (SERVANT * servant, DESERIALIZE_METHOD callback)
: DDS_EventConsumer_T <OpenSplice, SERVANT, EVENT> (servant, callback)
{

}

//
// ~OpenSplice_EventConsumer_T
//
template <typename SERVANT, typename EVENT>
OpenSplice_EventConsumer_T <SERVANT, EVENT>::~OpenSplice_EventConsumer_T (void)
{

}

}
