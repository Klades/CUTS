// $Id$

#include "TCPIP_HelloWorld_svnt.h"
#include "TCPIP_HelloWorldC.h"
#include "ace/CDR_Stream.h"
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

  void HelloWorld_Servant_Context::
  connect_handle_message (Components::EventConsumerBase_ptr base)
  {
    this->handle_message_.connect (base);
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
      handle_message_ (this, 0)
  {
    // Guard the initializing of the virtual table.
    vtable_type::init_guard_type guard (HelloWorld_Servant::vtable_, 1);

    if (HelloWorld_Servant::vtable_.is_init ())
      return;

    // Initialize the virtual table for the servant.
    HelloWorld_Servant::vtable_[0] = &HelloWorld_Servant::tcpip_handle_message;
  }

  HelloWorld_Servant::~HelloWorld_Servant (void)
  {

  }

  //
  // connect_consumer
  //
  void HelloWorld_Servant::
  connect_consumer (const char * name, ::Components::EventConsumerBase_ptr consumer)
  {
    if (0 == ACE_OS::strcmp (name, ACE_TEXT ("handle_message")))
      this->ctx_->connect_handle_message (consumer);
    else
      throw Components::InvalidName ();
  }

  //
  // connect_handle_message
  //
  void HelloWorld_Servant::connect_handle_message (::MessageConsumer_ptr)
  {
    ACE_DEBUG ((LM_DEBUG,
                "HelloWorld_Servant::connect_handle_message (::MessageConsumer_ptr)\n"));

    throw CORBA::NO_IMPLEMENT ();
  }

  //
  // disconnect_handle_message
  //
  ::MessageConsumer_ptr HelloWorld_Servant::disconnect_handle_message (void)
  {
    ACE_DEBUG ((LM_DEBUG,
                "HelloWorld_Servant::disconnect_handle_message (void)\n"));

    throw CORBA::NO_IMPLEMENT ();
  }

  //
  // disconnect_handle_message
  //
  ::MessageConsumer_ptr HelloWorld_Servant::get_consumer_handle_message (void)
  {
    ACE_DEBUG ((LM_DEBUG,
                "HelloWorld_Servant::get_consumer_handle_message (void)\n"));

    throw CORBA::NO_IMPLEMENT ();
  }

  //
  // tcpip_handle_message
  //
  int HelloWorld_Servant::
  tcpip_handle_message (CUTS_TCPIP_InputCDR & stream)
  {
    ACE_DEBUG ((LM_DEBUG,
                "%T (%t) - %M - received a message on tcpip_handle_message\n"));

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
    if (this->impl_)
      this->impl_->push_handle_message (event);

    return 0;
  }

  //
  // get_consumer
  //
  Components::EventConsumerBase_ptr
  HelloWorld_Servant::get_consumer (const char * name)
  {
    if (0 == ACE_OS::strcmp (name, "handle_message"))
      return this->handle_message_._this ();

    // Failed to locate the connection.
    throw ::Components::InvalidName ();
  }

  //
  // create_HelloWorld_Servant
  //
  ::PortableServer::Servant
  create_HelloWorld_Servant (CUTS_TCPIP_Servant_Manager * svnt_mgr,
                             ::Components::EnterpriseComponent_ptr p)
  {
    // First, convert the pointer to its concrete type.
    ::CIDL_HelloWorld_Impl::HelloWorld_Exec_var executor =
      ::CIDL_HelloWorld_Impl::HelloWorld_Exec::_narrow (p);

    if (::CORBA::is_nil (executor.in ()))
      return 0;

    // Now, create the servant for the executor.
    ::TCPIP::HelloWorld_Servant * servant = 0;

    ACE_NEW_RETURN (servant,
                    ::TCPIP::HelloWorld_Servant (*svnt_mgr, executor.in ()),
                    0);

    return servant;
  }
}
