// $Id: generate_cpp_class.py 3685 2012-09-26 14:45:04Z dfeiock $

#if !defined (__CUTS_INLINE__)
#include "QpidPB_Listener_T.inl"
#endif  // !defined __CUTS_INLINE__

namespace iCCM
{

//
// start
//
template <typename CONSUMER_T, typename EVENT>
void QpidPB_Listener_T <CONSUMER_T, EVENT>::
start (qpid::client::Connection & connection, std::string key)
{
  using namespace qpid::client;
  using namespace qpid::framing;

  this->session_ = connection.newSession ();

  SubscriptionManager * mgr = 0;
  ACE_NEW_THROW_EX (mgr,
                    SubscriptionManager (this->session_),
                    ::CORBA::NO_MEMORY ());
  this->manager_ = mgr;

  // Queues are round-robin for all subscribers.  We need to make sure this
  // event consumer receives all events from the publisher, regardless of
  // if others are listening or not.  Generate a random UUID for our queue
  // name and use the bindingKey to force the broker to copy any events
  // into our queue.
  this->queue_ = ACE_Utils::UUID_GENERATOR::instance ()->generate_UUID ()->to_string ()->c_str ();

  this->session_.queueDeclare (arg::queue=this->queue_,
                               arg::autoDelete=true);
  this->session_.exchangeBind (qpid::client::arg::exchange="amq.topic",
                               qpid::client::arg::queue=this->queue_,
                               qpid::client::arg::bindingKey=key);

  this->manager_->subscribe (*this,
                             this->queue_,
                             SubscriptionSettings (FlowControl::unlimited (),
                                                   ACCEPT_MODE_NONE));
  ACE_ERROR ((LM_DEBUG,
              ACE_TEXT ("%T (%t) - %M - Activating listener on queue [%s:%s]\n"),
              this->queue_.c_str (), key.c_str ()));

  this->manager_->start ();
}

//
// received
//
template <typename CONSUMER_T, typename EVENT>
void QpidPB_Listener_T <CONSUMER_T, EVENT>::
received (qpid::client::Message & message)
{
  // Read the protobuf event
  this->pb_event_.ParseFromString (message.getData ());

  // Wrap the received event in the generated upcall type
  upcall_event_type ev (this->pb_event_);

  // Pass the wrapped event to the consumer
  this->consumer_->push_event (&ev);
}

//
// stop
//
template <typename CONSUMER_T, typename EVENT>
void QpidPB_Listener_T <CONSUMER_T, EVENT>::
stop (void)
{
  ACE_ERROR ((LM_DEBUG,
              ACE_TEXT ("%T (%t) - %M - Passivating listener on queue [%s]\n"),
              this->queue_.c_str ()));

  this->session_.close ();
  delete this->manager_;
  this->manager_ = 0;
}

} // namespace iCCM
