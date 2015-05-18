// $IdQpidPB_Publisher.cpp 3086 2011-01-22 05:53:51Z hillj $

#include "QpidPB_Publisher.h"

#if !defined (__CUTS_INLINE__)
#include "QpidPB_Publisher.inl"
#endif

namespace iCCM
{

//
// connect
//
void QpidPB_Publisher::
connect (::Components::EventConsumerBase_ptr p)
{
  // Narrow the base consumer to a consumer of our type. This way, we
  // can validate the consumer and make sure we are not working with
  // a consumer type we do not know about.
  ::Components::QpidPB::EventConsumer_var consumer =
    ::Components::QpidPB::EventConsumer::_narrow (p);

  if (::CORBA::is_nil (consumer.in ()))
    throw ::CORBA::INTERNAL ();

  /// Tell the consumer where to connect
  consumer->configure (this->host_.c_str (), this->port_, this->queue_.c_str ());

  // Store the event consumer since all operations above executed
  // correctly and we need to remember the event consumer for the
  // disconnect operation.
  this->consumer_ = ::Components::QpidPB::EventConsumer::_narrow (p);
}

//
// disconnect
//
::Components::EventConsumerBase_ptr
QpidPB_Publisher::disconnect (void)
{
  //===========================================================================
  // INSERT CODE HERE
  //
  // The code you place here should release all resources required for
  // communicating over QpidPB to the contained consumer.
  //===========================================================================

  // Return ownership to the caller. This will allow the caller
  // to gracefully destroy the event consumer.
  return this->consumer_._retn ();
}

//
// activate
//
void QpidPB_Publisher::activate (void)
{
  iCCM::Publisher::activate ();

  ACE_ERROR ((LM_DEBUG,
              ACE_TEXT ("%T (%t) - %M - Opening connection to ")
              ACE_TEXT ("Qpid Broker [%s:%d]\n"),
              this->host_.c_str (),
              this->port_));
  this->connection_.open (this->host_, this->port_);
}

//
// passivate
//
void QpidPB_Publisher::passivate (void)
{
  this->connection_.close ();
  iCCM::Publisher::passivate ();
}

}
