// $Id$

#include "HelloWorld_svnt.h"

#if !defined (__CUTS_INLINE__)
#include "HelloWorld_svnt.inl"
#endif

#include "TCPIP_HelloWorldC.h"
#include "ace/CDR_Stream.h"
#include "cuts/arch/tcpip/TCPIP_Connector.h"
#include "cuts/arch/tcpip/TCPIP_SPEC.h"
#include "cuts/arch/tcpip/TCPIP_Remote_Endpoint.h"

namespace TCPIP
{
  //
  // HelloWorld_Servant_Context
  //
  HelloWorld_Servant_Context::HelloWorld_Servant_Context (void)
  {

  }

  //
  // ~HelloWorld_Servant_Context
  //
  HelloWorld_Servant_Context::~HelloWorld_Servant_Context (void)
  {

  }

  void HelloWorld_Servant_Context::
  connect_handle_message (Components::EventConsumerBase_ptr base)
  {
    // Narrow the object to a TCPIP EventConsumerBase object.
    Components::TCPIP::EventConsumerBase_var consumer =
      Components::TCPIP::EventConsumerBase::_narrow (base);

    if (CORBA::is_nil (consumer.in ()))
      throw Components::InvalidConnection ();

    // Get the remote endpoint from the consumer.
    Components::TCPIP::Endpoint_var endpoint = consumer->remote_endpoint ();

    int retval = this->handle_message_.connect (endpoint->address.in (),
                                                endpoint->UUID.in () ,
                                                endpoint->event);

    if (0 != retval)
      throw Components::InvalidConnection ();
  }

  //
  // tcpip_handle_message
  //
  void HelloWorld_Servant_Context::tcpip_handle_message (TCPIP::Message * ev)
  {
    if (this->handle_message_.is_connected ())
      this->handle_message_.send_event (ev);
  }

  //
  // HelloWorld_Servant
  //
  HelloWorld_Servant::
  HelloWorld_Servant (CUTS_TCPIP_Component * impl)
    : HelloWorld_Servant_Base (this, impl)
  {
    // Guard the initializing of the virtual table.
    vtable_type::init_guard_type guard (HelloWorld_Servant::vtable_, 1);

    if (HelloWorld_Servant::vtable_.is_init ())
      return;

    // Initialize the virtual table for the servant.
    HelloWorld_Servant::vtable_[0] = &HelloWorld_Servant::tcpip_handle_message;
  }

  //
  // tcpip_handle_message
  //
  int HelloWorld_Servant::
  tcpip_handle_message (ACE_InputCDR & stream)
  {
    ACE_DEBUG ((LM_DEBUG,
                "%T (%t) - %M - received a message on tcpip_handle_message\n"));

    // Store the event in a smart pointer for reference counting.
    ::TCPIP::Message_var event;
    ACE_NEW_RETURN (event, ::TCPIP::Message (), -1);

    // Extract the contents of the message.
    if (!(stream >> *event))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to extract %s from stream\n"),
                         ACE_TEXT ("::TCPIP::Message")),
                         -1);

    // Push the message to the implementation.
    if (this->impl_)
      this->impl_->tcpip_handle_message (event);

    return 0;
  }

  //
  // get_consumer
  //
  Components::EventConsumerBase_ptr
  HelloWorld_Servant::get_consumer (const char * name)
  {
    if (0 == ACE_OS::strcmp (name, "handle_message"))
    {
      if (0 != this->handle_message_.get ())
        return this->handle_message_->_this ();

      CUTS_TCPIP_CCM_EventConsumer * consumer = 0;

      ACE_NEW_THROW_EX (consumer,
                        CUTS_TCPIP_CCM_EventConsumer (this, 0),
                        CORBA::NO_MEMORY ());

      this->handle_message_.reset (consumer);
      return this->handle_message_->_this ();
    }

    // Failed to locate the connection.
    throw ::Components::InvalidName ();
  }

  //
  // connect_consumer
  //
  void HelloWorld_Servant::
  connect_consumer (const char * name, Components::EventConsumerBase_ptr consumer)
  {
    if (0 == ACE_OS::strcmp (name, "handle_message"))
      this->ctx_->connect_handle_message (consumer);
    else
      throw Components::InvalidName ();
  }
}
