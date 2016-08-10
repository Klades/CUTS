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
  callback_ (callback),
  task_ (servant, callback)
{

}

//
// ~TAO_EventConsumer_T
//
template <typename SERVANT, typename EVENT>
CUTS_INLINE
TAO_EventConsumer_T <SERVANT, EVENT>::~TAO_EventConsumer_T (void)
{
  task_.msg_queue ()->deactivate ();
}

//
// configure_task
//
template <typename SERVANT, typename EVENT>
CUTS_INLINE
void TAO_EventConsumer_T <SERVANT, EVENT>::configure_task (int max_threads, CPU_Mask * mask)
{
  if (max_threads > 0)
  {
    task_.set_max_threads(max_threads);
  }

  if (mask)
  {
    task_.set_cpu_mask(mask);
  }

  task_.open();
}
//
// push_event
//
template <typename SERVANT, typename EVENT>
CUTS_INLINE
void TAO_EventConsumer_T <SERVANT, EVENT>::push_event (EVENT * ev)
{
  CORBA::add_ref (ev);
  task_.putq (ev);
}

}
