// $Id$

#include "TCPIP_HelloWorld_svnt.h"
#include "cuts/arch/ccm/CCM_Events_T.h"
#include "cuts/arch/tcpip/ccm/TCPIP_CCM_T.h"
#include "cuts/arch/tcpip/TCPIP_Connector.h"
#include "cuts/arch/tcpip/TCPIP_SPEC.h"
#include "cuts/arch/tcpip/TCPIP_Remote_Endpoint.h"
#include "cuts/arch/tcpip/TCPIP_Servant_Manager.h"

namespace TCPIP_HelloWorld_Basic_Impl
{
  HelloWorld_Servant_Context::HelloWorld_Servant_Context (HelloWorld_Servant & parent)
  : HelloWorld_Servant_Context_Base (parent)
  {
  }

  HelloWorld_Servant_Context::~HelloWorld_Servant_Context (void)
  {
  }

  void HelloWorld_Servant_Context::push_handle_message (::Message * ev)
  {
    this->handle_message_.send_event (ev);
  }

  CUTS_TCPIP_CCM_Remote_Endpoint & HelloWorld_Servant_Context::endpoint_handle_message (void)
  {
    return this->handle_message_;
  }

  void HelloWorld_Servant_Context::push_handle_message_ex (::Message * ev)
  {
    this->handle_message_ex_.send_event (ev);
  }

  CUTS_TCPIP_CCM_Subscriber_Table & HelloWorld_Servant_Context::endpoints_handle_message_ex (void)
  {
    return this->handle_message_ex_;
  }

  //
  // HelloWorld_Servant
  //
  HelloWorld_Servant::
  HelloWorld_Servant (const char * name,
                      ::CIDL_HelloWorld_Basic_Impl::HelloWorld_Exec_ptr executor)
  : HelloWorld_Servant_Base (this, name, executor),
    handle_message_consumer_ (this, 0)
  {
    // Initializing the consumer table.
    this->consumers_.bind ("handle_message", &this->handle_message_consumer_);

    // Initializing the publishes/emits table.
    this->emits_.bind ("handle_message", &this->ctx_->endpoint_handle_message ());
    this->publishes_.bind ("handle_message_ex", &this->ctx_->endpoints_handle_message_ex ());

    // Guard the initialization of the virtual table.
    vtable_type::init_guard_type guard (HelloWorld_Servant::table_, 1);

    if (HelloWorld_Servant::table_.is_init ())
      return;

    HelloWorld_Servant::table_[0] = &HelloWorld_Servant::tcpip_handle_message;
  }

  //
  // ~HelloWorld_Servant
  //
  HelloWorld_Servant::~HelloWorld_Servant (void)
  {
  }

  //
  // connect_handle_message
  //
  void HelloWorld_Servant::
  connect_handle_message (::MessageConsumer_ptr)
  {
    throw ::CORBA::NO_IMPLEMENT ();
  }

  //
  // disconnect_handle_message
  //
  ::MessageConsumer_ptr HelloWorld_Servant::
  disconnect_handle_message (void)
  {
    throw ::CORBA::NO_IMPLEMENT ();
  }

  //
  // subscribe_handle_message_ex
  //
  ::Components::Cookie * HelloWorld_Servant::
  subscribe_handle_message_ex (::MessageConsumer_ptr)
  {
    throw ::CORBA::NO_IMPLEMENT ();
  }

  //
  // unsubscribe_handle_message_ex
  //
  ::MessageConsumer_ptr HelloWorld_Servant::
  unsubscribe_handle_message_ex (::Components::Cookie *)
  {
    throw ::CORBA::NO_IMPLEMENT ();
  }

  //
  // get_consumer_handle_message
  //
  ::MessageConsumer_ptr HelloWorld_Servant::
  get_consumer_handle_message (void)
  {
    throw ::CORBA::NO_IMPLEMENT ();
  }

  //
  // tcpip_handle_message
  //
  int HelloWorld_Servant::
  tcpip_handle_message (HelloWorld_Servant * svnt, CUTS_TCPIP_InputCDR & stream)
  {
    // Extract the event from the stream.
    CUTS_CCM_Event_T < ::OBV_Message > event;

    if (!(stream >> *event.in ()))
    {
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to extract %s from stream\n"),
                         ACE_TEXT ("::Message")),
                        -1);
    }

    // Push the message to the implementation.
    if (svnt->impl_)
      svnt->impl_->push_handle_message (event.in ());

    return 0;
  }


  void HelloWorld_Servant::message (const char * message)
  {
    if (this->impl_)
      this->impl_->message (message);
    else
      throw ::CORBA::INTERNAL ();
  }

  char * HelloWorld_Servant::message (void)
  {
    if (this->impl_)
      return this->impl_->message ();
    else
      throw ::CORBA::INTERNAL ();
  }

  char * HelloWorld_Servant::readonly_message (void)
  {
    if (this->impl_)
      return this->impl_->readonly_message ();
    else
      throw ::CORBA::INTERNAL ();
  }
}

::PortableServer::Servant
create_HelloWorld_Servant (const char * name,
                           ::Components::EnterpriseComponent_ptr p)
{
  return ::CUTS_TCPIP::CCM::create_servant <
    ::CIDL_HelloWorld_Basic_Impl::HelloWorld_Exec,
    ::TCPIP_HelloWorld_Basic_Impl::HelloWorld_Servant > (name, p);
}


