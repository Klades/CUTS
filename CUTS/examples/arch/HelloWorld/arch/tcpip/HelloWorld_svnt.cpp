// $Id$

#include "HelloWorld_svnt.h"
#include "TCPIP_HelloWorldC.h"

#include "cuts/arch/ccm/CCM_Events_T.h"
#include "cuts/arch/tcpip/ccm/TCPIP_CCM_T.h"
#include "cuts/arch/tcpip/TCPIP_Connector.h"
#include "cuts/arch/tcpip/TCPIP_SPEC.h"
#include "cuts/arch/tcpip/TCPIP_Remote_Endpoint.h"
#include "cuts/arch/tcpip/TCPIP_Servant_Manager.h"

HelloWorld_Servant_Context::HelloWorld_Servant_Context (HelloWorld_Servant & parent)
: HelloWorld_Servant_Context_Base (parent)
{
}

HelloWorld_Servant_Context::~HelloWorld_Servant_Context (void)
{
}

//
// push_output_message
//
void HelloWorld_Servant_Context::push_output_message (::Message * ev)
{
  this->output_message_.send_event (ev);
}

//
// endpoint_output_message
//
CUTS_TCPIP_CCM_Remote_Endpoint & HelloWorld_Servant_Context::endpoint_output_message (void)
{
  return this->output_message_;
}

//
// push_handle_message_ex
//
void HelloWorld_Servant_Context::push_handle_message_ex (::Message * ev)
{
  this->handle_message_ex_.send_event (ev);
}

//
// endpoints_handle_message_ex
//
CUTS_TCPIP_CCM_Subscriber_Table & HelloWorld_Servant_Context::endpoints_handle_message_ex (void)
{
  return this->handle_message_ex_;
}

//
// HelloWorld_Servant
//
HelloWorld_Servant::
HelloWorld_Servant (const char * name, executor_type::_ptr_type executor)
: HelloWorld_Servant_Base (name, executor),
  input_message_consumer_ (this, 0)
{
  // Initializing the consumer table.
  this->consumers_.bind ("input_message", &this->input_message_consumer_);

  // Initializing the publishes/emits table.
  this->emits_.bind ("output_message", &this->ctx_->endpoint_output_message ());
  this->publishes_.bind ("handle_message_ex", &this->ctx_->endpoints_handle_message_ex ());

  // Guard the initialization of the virtual table.
  vtable_type::init_guard_type guard (HelloWorld_Servant::table_, 1);

  if (HelloWorld_Servant::table_.is_init ())
    return;

  HelloWorld_Servant::table_[0] = &HelloWorld_Servant::tcpip_input_message;
}

//
// ~HelloWorld_Servant
//
HelloWorld_Servant::~HelloWorld_Servant (void)
{
}

//
// connect_output_message
//
void HelloWorld_Servant::
connect_output_message (::MessageConsumer_ptr)
{
  throw ::CORBA::NO_IMPLEMENT ();
}

//
// disconnect_output_message
//
::MessageConsumer_ptr HelloWorld_Servant::
disconnect_output_message (void)
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
// get_consumer_input_message
//
::MessageConsumer_ptr HelloWorld_Servant::
get_consumer_input_message (void)
{
  throw ::CORBA::NO_IMPLEMENT ();
}

//
// tcpip_input_message
//
int HelloWorld_Servant::
tcpip_input_message (HelloWorld_Servant * svnt, CUTS_TCPIP_InputCDR & stream)
{
  // Extract the ev from the stream.
  CUTS_CCM_Event_T < ::OBV_Message > ev;

  if (!(stream >> *ev.in ()))
  {
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - failed to extract %s from stream\n"),
                       ACE_TEXT ("::Message")),
                      -1);
  }

  // Push the message to the implementation.
  if (svnt->impl_)
    svnt->impl_->push_input_message (ev.in ());

  return 0;
}


//
// attribute setter: message
//
void HelloWorld_Servant::message (const char * message)
{
  if (this->impl_)
    this->impl_->message (message);
  else
    throw ::CORBA::INTERNAL ();
}

//
// attribute getter: message
//
char * HelloWorld_Servant::message (void)
{
  if (this->impl_)
    return this->impl_->message ();
  else
    throw ::CORBA::INTERNAL ();
}

//
// attribute getter: readonly_message
//
char * HelloWorld_Servant::readonly_message (void)
{
  if (this->impl_)
    return this->impl_->readonly_message ();
  else
    throw ::CORBA::INTERNAL ();
}

//
// set_attributes
//
void HelloWorld_Servant::
set_attributes (const ::Components::ConfigValues & config)
{
  const ::CORBA::ULong length = config.length ();

  for (::CORBA::ULong i = 0; i < length; ++ i)
  {
    // get the next configuraton value
    const ::Components::ConfigValue * value = config[i];

    if (0 == ACE_OS::strcmp (value->name (), "message"))
    {
      const char * tmp_value;

      if (!(value->value () >>= tmp_value))
        throw ::Components::InvalidConfiguration ();

      this->message (tmp_value);
    }
  }
}

//
// create_HelloWorld_Servant
//
::PortableServer::Servant 
create_HelloWorld_Servant (const char * name,
                           ::Components::EnterpriseComponent_ptr p)
{
  return ::CUTS_TCPIP::CCM::create_servant <
    ::CIAO_HelloWorld_Impl::HelloWorld_Exec,
    HelloWorld_Servant > (name, p);
}


