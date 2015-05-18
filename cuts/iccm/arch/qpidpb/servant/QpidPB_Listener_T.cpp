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
start (qpid::client::Connection & connection, std::string queue)
{
  using namespace qpid::client;
  using namespace qpid::framing;

  this->queue_ = queue;

  this->session_ = connection.newSession ();

  SubscriptionManager * mgr = 0;
  ACE_NEW_THROW_EX (mgr,
                    SubscriptionManager (this->session_),
                    ::CORBA::NO_MEMORY ());
  this->manager_ = mgr;

  this->session_.queueDeclare (arg::queue=queue,
                               arg::autoDelete=true);

  this->manager_->subscribe (*this,
                            this->queue_,
                            SubscriptionSettings (FlowControl::unlimited (),
                                                  ACCEPT_MODE_NONE));
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
  this->manager_->cancel (this->queue_);
  this->session_.close ();
  delete this->manager_;
  this->manager_ = 0;
}

} // namespace iCCM
