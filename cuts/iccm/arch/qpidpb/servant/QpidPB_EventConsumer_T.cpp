// $Id$

#if !defined (__CUTS_INLINE__)
#include "QpidPB_EventConsumer_T.inl"
#endif

namespace iCCM
{

template <typename SERVANT, typename EVENT>
void QpidPB_EventConsumer_T <SERVANT, EVENT>::activate (void)
{
  // Establish the connection
  ACE_ERROR ((LM_DEBUG,
              ACE_TEXT ("%T (%t) - %M - Opening connection to ")
              ACE_TEXT ("Qpid Broker [%s:%d]\n"),
              this->host_,
              this->port_));
  this->connection_.open (this->host_, this->port_);

  typedef QpidPB_Listener_T <self_type, EVENT> listener_type;
  listener_type * listener = 0;
  ACE_NEW_THROW_EX (listener,
                    listener_type (this),
                    ::CORBA::NO_MEMORY ());
  this->listener_ = listener;

  this->listener_->start (this->connection_, this->queue_);
}

template <typename SERVANT, typename EVENT>
void QpidPB_EventConsumer_T <SERVANT, EVENT>::passivate (void)
{
  // Stop events and subscriptions, disconnect from the qpid broker
  this->listener_->stop ();
  delete this->listener_;
  this->listener_ = 0;

  this->connection_.close ();
}

}
