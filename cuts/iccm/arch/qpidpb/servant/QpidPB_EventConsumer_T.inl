// $IdQpidPB_EventConsumer_T.cpp 3289 2012-02-10 03:05:18Z hillj $

namespace iCCM
{

//
// QpidPB_EventConsumer_T
//
template <typename SERVANT, typename EVENT>
CUTS_INLINE
QpidPB_EventConsumer_T <SERVANT, EVENT>::
QpidPB_EventConsumer_T (SERVANT * servant, CALLBACK_METHOD callback)
: servant_ (servant),
  callback_ (callback),
  listener_ (0)
{
      ACE_ERROR ((LM_ERROR,
                  ACE_TEXT ("EventConsumer_T ctor called")));
}

//
// ~QpidPB_EventConsumer_T
//
template <typename SERVANT, typename EVENT>
CUTS_INLINE
QpidPB_EventConsumer_T <SERVANT, EVENT>::~QpidPB_EventConsumer_T (void)
{

}

//
// push_event
//
template <typename SERVANT, typename EVENT>
CUTS_INLINE
void
QpidPB_EventConsumer_T <SERVANT, EVENT>::push_event (EVENT * ev)
{
  if (this->servant_ !=0)
    (*this->servant_.*this->callback_) (ev);
}


}
