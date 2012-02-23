// -*- C++ -*-
// $Id$

namespace iCCM
{

//
// DDS_EventConsumer_T
//
template <typename T, typename SERVANT, typename EVENT>
CUTS_INLINE
DDS_EventConsumer_T <T, SERVANT, EVENT>::
DDS_EventConsumer_T (SERVANT * servant, DESERIALIZE_METHOD callback)
: servant_ (servant),
  callback_ (callback)
{

}

//
// ~DDS_EventConsumer_T
//
template <typename T, typename SERVANT, typename EVENT>
CUTS_INLINE
DDS_EventConsumer_T <T, SERVANT, EVENT>::~DDS_EventConsumer_T (void)
{

}
}
