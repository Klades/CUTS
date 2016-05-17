// $IdCHAOS_EventConsumer_T.cpp 3289 2012-02-10 03:05:18Z hillj $

namespace iCCM
{

template <typename SERVANT, typename EVENT>
CUTS_INLINE
CHAOS_EventConsumer_T <SERVANT, EVENT>::
CHAOS_EventConsumer_T (SERVANT * servant, CALLBACK_METHOD callback)
: servant_ (servant),
  callback_ (callback)
{

}

template <typename SERVANT, typename EVENT>
CUTS_INLINE
CHAOS_EventConsumer_T <SERVANT, EVENT>::~CHAOS_EventConsumer_T (void)
{

}

}
