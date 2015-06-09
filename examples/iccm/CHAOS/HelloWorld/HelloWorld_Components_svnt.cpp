// $Id$

#include "HelloWorld_Components_svnt.h"

HelloReceiver_Context::HelloReceiver_Context (HelloReceiver_Servant & parent)
: HelloReceiver_Context_Base (parent)
{
}

HelloReceiver_Context::~HelloReceiver_Context (void)
{
}

HelloReceiver_Servant::
HelloReceiver_Servant (const char * name,
                       ::PortableServer::POA_ptr poa,
                       ::CIAO_HelloReceiver_Impl::HelloReceiver_Exec_ptr executor)
: HelloReceiver_Servant_Base (this, name, poa, executor),
  greeting_ospl_consumer_ (this, &HelloReceiver_Servant::push_greeting_ospl),
  greeting_ndds_consumer_ (this, &HelloReceiver_Servant::push_greeting_ndds),
  greeting_tcpip_consumer_ (this, &HelloReceiver_Servant::push_greeting_tcpip)
{
  this->consumers_.bind ("greeting_ospl", &this->greeting_ospl_consumer_);
  this->consumers_.bind ("greeting_ndds", &this->greeting_ndds_consumer_);
  this->consumers_.bind ("greeting_tcpip", &this->greeting_tcpip_consumer_);
}

HelloReceiver_Servant::~HelloReceiver_Servant (void)
{
}

void HelloReceiver_Servant::set_attributes (const ::Components::ConfigValues & config)
{
  const ::CORBA::ULong length = config.length ();

  for (::CORBA::ULong i = 0; i < length; ++ i)
  {
    // Get the next configuraton value
    const ::Components::ConfigValue * value = config[i];
  }
}

void HelloReceiver_Servant::push_greeting_ospl (::MessageEvent *ev)
{
  if (0 != this->impl_)
    this->impl_->push_greeting_ospl (ev);
}

void HelloReceiver_Servant::push_greeting_ndds (::MessageEvent *ev)
{
  if (0 != this->impl_)
    this->impl_->push_greeting_ndds (ev);
}

void HelloReceiver_Servant::push_greeting_tcpip (::MessageEvent *ev)
{
  if (0 != this->impl_)
    this->impl_->push_greeting_tcpip (ev);
}

::MessageEventConsumer_ptr HelloReceiver_Servant::get_greeting_ospl_consumer (void)
{
  throw ::CORBA::NO_IMPLEMENT ();
}

::MessageEventConsumer_ptr HelloReceiver_Servant::get_greeting_ndds_consumer (void)
{
  throw ::CORBA::NO_IMPLEMENT ();
}

::MessageEventConsumer_ptr HelloReceiver_Servant::get_greeting_tcpip_consumer (void)
{
  throw ::CORBA::NO_IMPLEMENT ();
}

::PortableServer::Servant
create_HelloReceiver_Servant (const char * name,
                              ::PortableServer::POA_ptr poa,
                              ::Components::EnterpriseComponent_ptr p)
{
  return ::iCCM::create_servant < CIAO_HelloReceiver_Impl::HelloReceiver_Exec, HelloReceiver_Servant > (name, poa, p);
}

HelloSender_Context::HelloSender_Context (HelloSender_Servant & parent)
: HelloSender_Context_Base (parent)
{
}

HelloSender_Context::~HelloSender_Context (void)
{
}

void HelloSender_Context::push_greeting_ospl (::MessageEvent *ev)
{
  this->greeting_ospl_.send_event (ev);
}

void HelloSender_Context::push_greeting_ndds (::MessageEvent *ev)
{
  this->greeting_ndds_.send_event (ev);
}

void HelloSender_Context::push_greeting_tcpip (::MessageEvent *ev)
{
  this->greeting_tcpip_.send_event (ev);
}

::MessageEvent * HelloSender_Context::new_greeting_ospl_event (void)
{
  return this->greeting_ospl_.allocate_event ();
}

::MessageEvent * HelloSender_Context::new_greeting_ndds_event (void)
{
  return this->greeting_ndds_.allocate_event ();
}

::MessageEvent * HelloSender_Context::new_greeting_tcpip_event (void)
{
  return this->greeting_tcpip_.allocate_event ();
}

iCCM::CHAOS_Publisher_Table & HelloSender_Context::get_greeting_ospl_publisher_table (void)
{
  return this->greeting_ospl_;
}

iCCM::CHAOS_Publisher_Table & HelloSender_Context::get_greeting_ndds_publisher_table (void)
{
  return this->greeting_ndds_;
}

iCCM::CHAOS_Publisher_Table & HelloSender_Context::get_greeting_tcpip_publisher_table (void)
{
  return this->greeting_tcpip_;
}

HelloSender_Servant::
HelloSender_Servant (const char * name,
                     ::PortableServer::POA_ptr poa,
                     ::CIAO_HelloSender_Impl::HelloSender_Exec_ptr executor)
: HelloSender_Servant_Base (this, name, poa, executor)
{
  this->publishes_.bind ("greeting_ospl", &this->ctx_->get_greeting_ospl_publisher_table ());
  this->publishes_.bind ("greeting_ndds", &this->ctx_->get_greeting_ndds_publisher_table ());
  this->publishes_.bind ("greeting_tcpip", &this->ctx_->get_greeting_tcpip_publisher_table ());
}

HelloSender_Servant::~HelloSender_Servant (void)
{
}

void HelloSender_Servant::set_attributes (const ::Components::ConfigValues & config)
{
  const ::CORBA::ULong length = config.length ();

  for (::CORBA::ULong i = 0; i < length; ++ i)
  {
    // Get the next configuraton value
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

::Components::Cookie * HelloSender_Servant::subscribe_greeting_ospl (::MessageEventConsumer_ptr)
{
  throw ::CORBA::NO_IMPLEMENT ();
}

::MessageEventConsumer_ptr HelloSender_Servant::unsubscribe_greeting_ospl (::Components::Cookie *)
{
  throw ::CORBA::NO_IMPLEMENT ();
}

::Components::Cookie * HelloSender_Servant::subscribe_greeting_ndds (::MessageEventConsumer_ptr)
{
  throw ::CORBA::NO_IMPLEMENT ();
}

::MessageEventConsumer_ptr HelloSender_Servant::unsubscribe_greeting_ndds (::Components::Cookie *)
{
  throw ::CORBA::NO_IMPLEMENT ();
}

::Components::Cookie * HelloSender_Servant::subscribe_greeting_tcpip (::MessageEventConsumer_ptr)
{
  throw ::CORBA::NO_IMPLEMENT ();
}

::MessageEventConsumer_ptr HelloSender_Servant::unsubscribe_greeting_tcpip (::Components::Cookie *)
{
  throw ::CORBA::NO_IMPLEMENT ();
}

char * HelloSender_Servant::message (void)
{
  if (0 != this->impl_)
    return this->impl_->message ();

  throw ::CORBA::INTERNAL ();
}

void HelloSender_Servant::message (const char * val)
{
  if (0 != this->impl_)
    this->impl_->message (val);
  else
    throw ::CORBA::INTERNAL ();
}

::PortableServer::Servant
create_HelloSender_Servant (const char * name,
                            ::PortableServer::POA_ptr poa,
                            ::Components::EnterpriseComponent_ptr p)
{
  return ::iCCM::create_servant < CIAO_HelloSender_Impl::HelloSender_Exec, HelloSender_Servant > (name, poa, p);
}

