// $Id$

namespace iCCM
{

//
// EventConsumer_T
//
template <typename T, typename SERVANT>
CUTS_INLINE
EventConsumer_T <T, SERVANT>::
EventConsumer_T (SERVANT * servant, callback_method callback)
: servant_ (servant),
  callback_ (callback)
{

}

//
// ~EventConsumer_T
//
template <typename T, typename SERVANT>
CUTS_INLINE
EventConsumer_T <T, SERVANT>::~EventConsumer_T (void)
{

}

}
