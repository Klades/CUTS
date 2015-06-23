// $Id$

#if !defined (__CUTS_INLINE__)
#include "QpidPB_EventConsumer_T.inl"
#endif

namespace iCCM
{

//
// configure
//
template <typename SERVANT, typename EVENT>
void QpidPB_EventConsumer_T <SERVANT, EVENT>::
configure (const char * host, int port, const char * queue)
{
  this->host_ = host;
  this->port_ = port;

  listener_type * listener = 0;

  if (0 != this->listeners_.find (queue, listener))
  {
    // This is a new queue, allocate a new listener
    ACE_ERROR ((LM_DEBUG,
                ACE_TEXT ("%T (%t) - %M - Allocating listener for queue [%s]\n"),
                queue));

    ACE_NEW_THROW_EX (listener,
                      listener_type (this),
                      ::CORBA::NO_MEMORY ());
    this->listeners_.bind (queue, listener);
  }
}

template <typename SERVANT, typename EVENT>
void QpidPB_EventConsumer_T <SERVANT, EVENT>::activate (void)
{
  // Establish the connection
  ACE_ERROR ((LM_DEBUG,
              ACE_TEXT ("%T (%t) - %M - Opening connection to ")
              ACE_TEXT ("Qpid Broker [%s:%d]\n"),
              this->host_.c_str (),
              this->port_));
  this->connection_.open (this->host_, this->port_);

  // Start our listeners
  typename listeners_map_type::ITERATOR end = this->listeners_.end ();
  for (typename listeners_map_type::ITERATOR it = this->listeners_.begin (); it != end; ++it)
    (*it).item ()->start (this->connection_, (*it).key ().c_str ());
}

template <typename SERVANT, typename EVENT>
void QpidPB_EventConsumer_T <SERVANT, EVENT>::passivate (void)
{
  // Stop our listeners
  typename listeners_map_type::ITERATOR end = this->listeners_.end ();
  for (typename listeners_map_type::ITERATOR it = this->listeners_.begin (); it != end; ++it)
    (*it).item ()->stop ();

  // Disconnect from the qpid broker
  this->connection_.close ();
  iCCM::EventConsumer::passivate ();
}

}
