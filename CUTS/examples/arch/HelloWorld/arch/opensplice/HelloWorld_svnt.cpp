// $Id$

#include "HelloWorld_svnt.h"
#include "cuts/arch/ccm/CCM_T.h"
#include "cuts/arch/ccm/CCM_Events_T.h"

//
// HelloWorld_Servant_Context
//
HelloWorld_Servant_Context::HelloWorld_Servant_Context (HelloWorld_Servant & parent)
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
// push_output_message
//
void HelloWorld_Servant_Context::
push_output_message (::Message * ev)
{
  this->output_message_.send_event (ev);
}

//
// writer_output_message
//
CUTS_OpenSplice_CCM_Subscriber & HelloWorld_Servant_Context::
writer_output_message (void)
{
  return this->output_message_;
}

//
// push_handle_message_ex
//
void HelloWorld_Servant_Context::
push_handle_message_ex (::Message * ev)
{
  this->handle_message_ex_.send_event (ev);
}

//
// writers_handle_message_ex
//
CUTS_CCM_Subscriber_Table & HelloWorld_Servant_Context::
writers_handle_message_ex (void)
{
  return this->handle_message_ex_;
}

//
// HelloWorld_Servant
//
HelloWorld_Servant::
HelloWorld_Servant (const char * name,
                    ::PortableServer::POA_ptr port_POA,
                    ::CIAO_HelloWorld_Impl::HelloWorld_Exec_ptr executor)
 : HelloWorld_Servant_Base (name, port_POA, executor),
   input_message_consumer_ (this, &HelloWorld_Servant::deserialize_input_message)
{
  this->emits_.bind ("output_message", &this->ctx_->writer_output_message ());
  this->publishes_.bind ("handle_message_ex", &this->ctx_->writers_handle_message_ex ());

  this->consumers_.bind ("input_message", &this->input_message_consumer_);
}

//
// ~HelloWorld_Servant
//
HelloWorld_Servant::~HelloWorld_Servant (void)
{
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
unsubscribe_handle_message_ex(::Components::Cookie *)
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
// deserialize_input_message
//
void HelloWorld_Servant::
deserialize_input_message (HelloWorld_Servant * servant,
                           const ::CUTS_OSPL::Message & dds_event)
{
  // First, extract the ev.
  CUTS_CCM_Event_T < ::OBV_Message > ev;
  *ev.in () <<= dds_event;

  // Now, puch the ev to the implemetation.
  if (servant->impl_)
    servant->impl_->push_input_message (ev.in ());
}

extern "C" ::PortableServer::Servant
create_HelloWorld_Servant (const char * name,
                           ::PortableServer::POA_ptr port_POA,
                           ::Components::EnterpriseComponent_ptr p)
{
  return ::CUTS::CCM::create_servant <
    ::CIAO_HelloWorld_Impl::HelloWorld_Exec,
    ::HelloWorld_Servant > (name, port_POA, p);
}

