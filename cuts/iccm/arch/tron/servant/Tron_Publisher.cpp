// $Id$

#include "Tron_Publisher.h"

#if !defined (__CUTS_INLINE__)
#include "Tron_Publisher.inl"
#endif

namespace iCCM
{

//
// connect
//
void Tron_Publisher::
connect (::Components::EventConsumerBase_ptr p)
{
  // Narrow the base consumer to a consumer of our type. This way, we
  // can validate the consumer and make sure we are not working with
  // a consumer type we do not know about.
  ::Components::Tron::EventConsumer_var consumer =
    ::Components::Tron::EventConsumer::_narrow (p);

  if (::CORBA::is_nil (consumer.in ()))
    throw ::CORBA::INTERNAL ();

  //===========================================================================
  // INSERT CODE HERE
  //
  // The code that you place here should use the <consumer> object
  // to extract information for establishing a connection and sending
  // data to this consumer event point via Tron architecture.
  //===========================================================================

  // Store the event consumer since all operations above executed
  // correctly and we need to remember the event consumer for the
  // disconnect operation.
  this->consumer_ = ::Components::Tron::EventConsumer::_narrow (p);
}

//
// disconnect
//
::Components::EventConsumerBase_ptr
Tron_Publisher::disconnect (void)
{
  //===========================================================================
  // INSERT CODE HERE
  //
  // The code you place here should release all resources required for
  // communicating over Tron to the contained consumer.
  //===========================================================================

  // Return ownership to the caller. This will allow the caller
  // to gracefully destroy the event consumer.
  return this->consumer_._retn ();
}

//
// register_channel
//
void Tron_Publisher::
register_channel (Reporter * reporter, const ACE_CString & name)
{
  this->channel_ = reporter->getOutputEncoding (reporter, name.c_str ());
  this->reporter_ = reporter;

  ACE_ERROR ((LM_DEBUG,
              ACE_TEXT ("%T (%t) - %M - Got reporter for Publisher [%s, %d]\n"),
              name.c_str (),
              this->channel_));
}

}
