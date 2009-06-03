// $Id$

#include "OpenSplice_SimpleComponent_svnt.h"
#include "cuts/arch/ccm/CCM_Events_T.h"
//#include "cuts/arch/tcpip/ccm/TCPIP_CCM_T.h"
//#include "cuts/arch/tcpip/TCPIP_Remote_Endpoint.h"

namespace SimpleComponent_Basic_Impl
{
  SimpleComponent_Servant_Context::SimpleComponent_Servant_Context (SimpleComponent_Servant & parent)
  : SimpleComponent_Servant_Context_Base (parent)
  {
  }

  SimpleComponent_Servant_Context::~SimpleComponent_Servant_Context (void)
  {
  }

  void SimpleComponent_Servant_Context::push_handle_message (::Message * ev)
  {
    //this->handle_message_.send_event (ev);
  }

  //CUTS_TCPIP_CCM_Remote_Endpoint & SimpleComponent_Servant_Context::endpoint_handle_message (void)
  //{
  //  //return this->handle_message_;
  //}

  void SimpleComponent_Servant_Context::push_handle_message_ex (::Message * ev)
  {
    //this->handle_message_ex_.send_event (ev);
  }

  //CUTS_TCPIP_CCM_Subscriber_Table & SimpleComponent_Servant_Context::endpoints_handle_message_ex (void)
  //{
  //  return this->handle_message_ex_;
  //}

  /*
  //
  // SimpleComponent_Servant
  //
  SimpleComponent_Servant::
  SimpleComponent_Servant (const char * name,
                           CUTS_TCPIP_Servant_Manager & svnt_mgr,
			   ::CIDL_SimpleComponent_Basic_Impl::SimpleComponent_Exec_ptr executor)
  : SimpleComponent_Servant_Base (name, this, svnt_mgr, executor),
    handle_message_consumer_ (this, 0)
  {
    // Initializing the consumer table.
    //this->consumers_.bind ("handle_message", &this->handle_message_consumer_);

    // Initializing the publishes/emits table.
    //this->emits_.bind ("handle_message", &this->ctx_->endpoint_handle_message ());
    //this->publishes_.bind ("handle_message_ex", &this->ctx_->endpoints_handle_message_ex ());

    // Guard the initialization of the virtual table.
    //vtable_type::init_guard_type guard (SimpleComponent_Servant::vtable_, 1);

    //if (SimpleComponent_Servant::vtable_.is_init ())
    //  return;
  }

  //
  // ~SimpleComponent_Servant
  //
  SimpleComponent_Servant::~SimpleComponent_Servant (void)
  {
  }

  //
  // connect_handle_message
  //
  void SimpleComponent_Servant::
  connect_handle_message (::MessageConsumer_ptr)
  {
    throw ::CORBA::NO_IMPLEMENT ();
  }

  //
  // disconnect_handle_message
  //
  ::MessageConsumer_ptr SimpleComponent_Servant::
  disconnect_handle_message (void)
  {
    throw ::CORBA::NO_IMPLEMENT ();
  }

  //
  // subscribe_handle_message_ex
  //
  ::Components::Cookie * SimpleComponent_Servant::
  subscribe_handle_message_ex (::MessageConsumer_ptr)
  {
    throw ::CORBA::NO_IMPLEMENT ();
  }

  //
  // unsubscribe_handle_message_ex
  //
  ::MessageConsumer_ptr SimpleComponent_Servant::
  unsubscribe_handle_message_ex (::Components::Cookie *)
  {
    throw ::CORBA::NO_IMPLEMENT ();
  }

  //
  // get_consumer_handle_message
  //
  ::MessageConsumer_ptr SimpleComponent_Servant::
  get_consumer_handle_message (void)
  {
    throw ::CORBA::NO_IMPLEMENT ();
  }

  //
  // tcpip_handle_message
  //
  int SimpleComponent_Servant::
  tcpip_handle_message (SimpleComponent_Servant * svnt, CUTS_TCPIP_InputCDR & stream)
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


  void SimpleComponent_Servant::message (const char * message)
  {
    if (this->impl_)
      this->impl_->message (message);
    else
      throw ::CORBA::INTERNAL ();
  }

  char * SimpleComponent_Servant::message (void)
  {
    if (this->impl_)
      return this->impl_->message ();
    else
      throw ::CORBA::INTERNAL ();
  }

  char * SimpleComponent_Servant::readonly_message (void)
  {
    if (this->impl_)
      return this->impl_->readonly_message ();
    else
      throw ::CORBA::INTERNAL ();
  }
}

::PortableServer::Servant
create_SimpleComponent_Servant (const char * name,
                           CUTS_TCPIP_Servant_Manager * svnt_mgr,
                           ::Components::EnterpriseComponent_ptr p)
{
  return ::CUTS_TCPIP::CCM::create_servant <
    ::CIDL_SimpleComponent_Basic_Impl::SimpleComponent_Exec,
    ::TCPIP_SimpleComponent_Basic_Impl::SimpleComponent_Servant > (name, svnt_mgr, p);
}

  */

