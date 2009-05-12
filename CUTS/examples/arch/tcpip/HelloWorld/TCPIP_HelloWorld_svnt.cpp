// $Id$

#include "TCPIP_HelloWorld_svnt.h"
#include "TCPIP_HelloWorldC.h"
#include "ace/CDR_Stream.h"
#include "cuts/arch/tcpip/ccm/TCPIP_CCM_T.h"
#include "cuts/arch/tcpip/TCPIP_Connector.h"
#include "cuts/arch/tcpip/TCPIP_SPEC.h"
#include "cuts/arch/tcpip/TCPIP_Remote_Endpoint.h"
#include "cuts/arch/tcpip/TCPIP_Servant_Manager.h"

namespace TCPIP
{
  //
  // HelloWorld_Servant_Context
  //
  HelloWorld_Servant_Context::
  HelloWorld_Servant_Context (::TCPIP::HelloWorld_Servant & parent)
  : HelloWorld_Servant_Context_Base (parent)
  {

  }

  //
  // ~HelloWorld_Servant_Context
  //
  HelloWorld_Servant_Context::~HelloWorld_Servant_Context (void)
  {

  }

  //
  // endpoint_handle_message
  //
  CUTS_TCPIP_CCM_Remote_Endpoint &
  HelloWorld_Servant_Context::endpoint_handle_message (void)
  {
    return this->handle_message_;
  }

  //
  // tcpip_handle_message
  //
  void HelloWorld_Servant_Context::push_handle_message (::Message * ev)
  {
    if (this->handle_message_.is_connected ())
      this->handle_message_.send_event (ev);
  }

  //
  // HelloWorld_Servant
  //
  HelloWorld_Servant::
  HelloWorld_Servant (CUTS_TCPIP_Servant_Manager & svnt_mgr,
                      ::CIDL_HelloWorld_Impl::HelloWorld_Exec_ptr executor)
    : HelloWorld_Servant_Base (this, svnt_mgr, executor),
      handle_message_consumer_ (this, 0)
  {
    do
    {
      // Guard the initialization of the virtual table.
      vtable_type::init_guard_type guard (HelloWorld_Servant::vtable_, 1);

      if (HelloWorld_Servant::vtable_.is_init ())
        continue;

      HelloWorld_Servant::vtable_[0] = &HelloWorld_Servant::tcpip_handle_message;
    } while (0);

    // Initialize the endpoint map.
    this->endpoints_.bind ("handle_message", &this->ctx_->endpoint_handle_message ());

    if (1 != this->endpoints_.current_size ())
      throw ::CORBA::INTERNAL ();

    // Initialize the consumer table.
    this->consumers_.bind ("handle_message", &this->handle_message_consumer_);
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
  void HelloWorld_Servant::connect_handle_message (::MessageConsumer_ptr)
  {
    throw ::CORBA::NO_IMPLEMENT ();
  }

  //
  // disconnect_handle_message
  //
  ::MessageConsumer_ptr HelloWorld_Servant::disconnect_handle_message (void)
  {
    throw ::CORBA::NO_IMPLEMENT ();
  }

  //
  // disconnect_handle_message
  //
  ::MessageConsumer_ptr HelloWorld_Servant::get_consumer_handle_message (void)
  {
    throw ::CORBA::NO_IMPLEMENT ();
  }

  //
  // tcpip_handle_message
  //
  int HelloWorld_Servant::
  tcpip_handle_message (HelloWorld_Servant * svnt, CUTS_TCPIP_InputCDR & stream)
  {
    // Store the event in a smart pointer for reference counting.
    ::Message * temp = 0;
    ACE_NEW_RETURN (temp, ::OBV_Message (), -1);
    ::Message_var event (temp);

    // Extract the contents of the message.
    if (!(stream >> *event))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to extract %s from stream\n"),
                         ACE_TEXT ("::TCPIP::Message")),
                         -1);

    // Push the message to the implementation.
    if (svnt->impl_)
      svnt->impl_->push_handle_message (event);

    return 0;
  }

  //
  // create_HelloWorld_Servant
  //
  ::PortableServer::Servant
  create_HelloWorld_Servant (CUTS_TCPIP_Servant_Manager * svnt_mgr,
                             ::Components::EnterpriseComponent_ptr p)
  {
    return ::CUTS_TCPIP::CCM::create_servant <::CIDL_HelloWorld_Impl::HelloWorld_Exec,
                                              ::TCPIP::HelloWorld_Servant> (svnt_mgr, p);
  }
}
