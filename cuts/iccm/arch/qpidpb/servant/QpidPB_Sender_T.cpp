// $Id: generate_cpp_class.py 3685 2012-09-26 14:45:04Z dfeiock $

#if !defined (__CUTS_INLINE__)
#include "QpidPB_Sender_T.inl"
#endif  // !defined __CUTS_INLINE__

namespace iCCM
{

//
// activate
//
template <typename EVENT>
void  QpidPB_Sender_T <EVENT>::
activate (qpid::client::Connection & connection,
          const std::string & queue)
{
  using namespace qpid::client;

  ACE_ERROR ((LM_DEBUG,
              ACE_TEXT ("%T (%t) - %M - Activating sender on queue [%s]\n"),
              queue.c_str ()));

  this->session_ = connection.newSession ();
  this->session_.queueDeclare (arg::queue=queue,
                               arg::autoDelete=true);

  this->message_.getDeliveryProperties ().setRoutingKey (queue);
}

//
// passivate
//
template <typename EVENT>
void  QpidPB_Sender_T <EVENT>::passivate (void)
{
  this->session_.close ();
}

//
// send_event
//
template <typename EVENT>
void QpidPB_Sender_T <EVENT>::send_event (EVENT * ev)
{
  using namespace qpid::client;
  downcall_event_type * downcall = dynamic_cast <downcall_event_type *> (ev);

  if (0 != ev)
  {
    downcall->protobuf_event ().SerializeToString (&this->pb_event_stream_);
    this->message_.setData (this->pb_event_stream_);
    this->session_.messageTransfer (arg::content=this->message_);
  }  
}

//
// allocate_event
//
template <typename EVENT>
EVENT * QpidPB_Sender_T <EVENT>::allocate_event (void)
{
  downcall_event_type * ev = 0;
  ACE_NEW_THROW_EX (ev,
                    downcall_event_type (),
                    ::CORBA::NO_MEMORY ());

  return ev;
}

} // namespace iCCM
