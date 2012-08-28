// $Id$

namespace iCCM
{

//
// TAO_EventConsumer_T
//
template <typename SERVANT, typename EVENT>
CUTS_INLINE
TAO_EventConsumer_T <SERVANT, EVENT>::
TAO_EventConsumer_T (SERVANT * servant, CALLBACK_METHOD callback)
: servant_ (servant),
  callback_ (callback)
{

}

//
// ~TAO_EventConsumer_T
//
template <typename SERVANT, typename EVENT>
CUTS_INLINE
TAO_EventConsumer_T <SERVANT, EVENT>::~TAO_EventConsumer_T (void)
{

}

//
// push_event
//
template <typename SERVANT, typename EVENT>
CUTS_INLINE
void TAO_EventConsumer_T <SERVANT, EVENT>::push_event (EVENT * ev)
{
  if (0 != this->servant_)
    (*this->servant_.*this->callback_) (ev);
}

}
