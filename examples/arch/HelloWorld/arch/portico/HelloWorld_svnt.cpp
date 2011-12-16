// $Id$

#include "HelloWorld_svnt.h"
#include "cuts/arch/ccm/CCM_T.h"
#include "cuts/arch/ccm/CCM_Events_T.h"

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

//
// HelloSender_Servant_Context
//
HelloSender_Servant_Context::
HelloSender_Servant_Context (HelloSender_Servant & parent)
: HelloSender_Servant_Context_Base (parent)
{
}

//
// ~HelloSender_Servant_Context
//
HelloSender_Servant_Context::~HelloSender_Servant_Context (void)
{
}

//
// push_greeting_event
//
Message * HelloSender_Servant_Context::push_greeting_event (void)
{
  return this->greeting_.allocate_event ();
}

//
// push_output_message
//
void HelloSender_Servant_Context::push_greeting (::Message * ev)
{
  this->greeting_.send_event (ev);
}

//
// publisher_output_message
//
Portico_CCM_Publisher_Table &
HelloSender_Servant_Context::publisher_greeting (void)
{
  return this->greeting_;
}

//
// advance_time
//
void HelloSender_Servant_Context::advance_time (::CORBA::Double amount)
{
  this->svnt_.advance_time (amount);
}

//
// tick
//
void HelloSender_Servant_Context::tick (void)
{
  this->svnt_.rti_ambassador ().tick ();
}

//
// HelloSender_Servant
//
HelloSender_Servant::
HelloSender_Servant (const char * name,
                    ::PortableServer::POA_ptr poa,
                    ::CIAO_HelloSender_Impl::HelloSender_Exec_ptr executor)
 : HelloSender_Servant_Base (this, name, poa, executor)
{
  this->publishes_.bind ("greeting", &this->ctx_->publisher_greeting ());
}

//
// ~HelloSender_Servant
//
HelloSender_Servant::~HelloSender_Servant (void)
{
}

//
// attribute setter: message
//
void HelloSender_Servant::message (const char * message)
{
  if (this->impl_)
    this->impl_->message (message);
  else
    throw ::CORBA::INTERNAL ();
}

//
// attribute getter: message
//
char * HelloSender_Servant::message (void)
{
  if (this->impl_)
    return this->impl_->message ();
  else
    throw ::CORBA::INTERNAL ();
}

//
// set_attributes
//
void HelloSender_Servant::
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

////
//// connect_output_message
////
//void HelloSender_Servant::
//connect_output_message (::MessageConsumer_ptr consumer)
//{
//  this->ctx_->publisher_output_message ().connect (consumer);
//}
//
////
//// disconnect_output_message
////
//::MessageConsumer_ptr
//HelloSender_Servant::disconnect_output_message (void)
//{
//  ::Components::EventConsumerBase_var consumer_base =
//    this->ctx_->publisher_output_message ().disconnect ();
//
//  ::MessageConsumer_var consumer = ::MessageConsumer::_narrow (consumer_base.in ());
//  return consumer._retn ();
//}

//
// subscribe_handle_message_ex
//
::Components::Cookie * HelloSender_Servant::
subscribe_greeting (::MessageConsumer_ptr consumer)
{
  return this->ctx_->publisher_greeting ().subscribe (consumer);
}

//
// unsubscribe_handle_message_ex
//
::MessageConsumer_ptr HelloSender_Servant::
unsubscribe_greeting (::Components::Cookie * c)
{
  ::Components::EventConsumerBase_var consumer_base =
    this->ctx_->publisher_greeting ().unsubscribe (c);

  ::MessageConsumer_var consumer = ::MessageConsumer::_narrow (consumer_base.in ());
  return consumer._retn ();
}

////
//// get_consumer_input_message
////
//::MessageConsumer_ptr HelloSender_Servant::
//get_consumer_input_message (void)
//{
//  throw ::CORBA::NO_IMPLEMENT ();
//}

////
//// push_input_message
////
//void HelloSender_Servant::push_input_message (::Message * ev)
//{
//  if (0 != this->impl_)
//    this->impl_->push_input_message (ev);
//}

//
// create_HelloSender_Servant
//
extern "C" ::PortableServer::Servant
create_HelloSender_Servant (const char * name,
                            ::PortableServer::POA_ptr poa,
                            ::Components::EnterpriseComponent_ptr p)
{
  return ::CUTS::CCM::create_servant <
    ::CIAO_HelloSender_Impl::HelloSender_Exec,
    ::HelloSender_Servant > (name, poa, p);
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

//
// HelloReceiver_Servant_Context
//
HelloReceiver_Servant_Context::
HelloReceiver_Servant_Context (HelloReceiver_Servant & parent)
: HelloReceiver_Servant_Context_Base (parent)
{
}

//
// ~HelloReceiver_Servant_Context
//
HelloReceiver_Servant_Context::~HelloReceiver_Servant_Context (void)
{
}

//
// tick
//
void HelloReceiver_Servant_Context::tick (void)
{
  this->svnt_.rti_ambassador ().tick ();
}

//
// HelloReceiver_Servant
//
HelloReceiver_Servant::
HelloReceiver_Servant (const char * name,
                       ::PortableServer::POA_ptr poa,
                       ::CIAO_HelloReceiver_Impl::HelloReceiver_Exec_ptr executor)
: HelloReceiver_Servant_Base (this, name, poa, executor),
  greeting_consumer_ (this, &HelloReceiver_Servant::push_greeting)
{
  this->consumers_.bind ("greeting", &this->greeting_consumer_);
}

//
// ~HelloReceiver_Servant
//
HelloReceiver_Servant::~HelloReceiver_Servant (void)
{
}

//
// get_consumer_greeting
//
::MessageConsumer_ptr HelloReceiver_Servant::
get_consumer_greeting (void)
{
  throw ::CORBA::NO_IMPLEMENT ();
}

//
// push_greeting
//
void HelloReceiver_Servant::push_greeting (::Message * ev)
{
  if (0 != this->impl_)
    this->impl_->push_greeting (ev);
}

//
// create_HelloReceiver_Servant
//
extern "C" ::PortableServer::Servant
create_HelloReceiver_Servant (const char * name,
                              ::PortableServer::POA_ptr poa,
                              ::Components::EnterpriseComponent_ptr p)
{
  return ::CUTS::CCM::create_servant <
    ::CIAO_HelloReceiver_Impl::HelloReceiver_Exec,
    ::HelloReceiver_Servant > (name, poa, p);
}
