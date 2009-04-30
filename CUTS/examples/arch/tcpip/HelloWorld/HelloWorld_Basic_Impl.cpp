// $Id$

#include "HelloWorld_Basic_Impl.h"
#include "ace/streams.h"
#include "ace/Reactor.h"

HelloWorld_Basic_Impl_Task::
HelloWorld_Basic_Impl_Task (HelloWorld_Basic_Impl * impl)
: impl_ (impl)
{
  this->reactor (new ACE_Reactor ());
}

HelloWorld_Basic_Impl_Task::~HelloWorld_Basic_Impl_Task (void)
{
  ACE_Reactor * reactor = this->reactor ();
  this->reactor (0);

  delete reactor;
}

int HelloWorld_Basic_Impl_Task::activate (void)
{
  ACE_Time_Value interval (2);

  this->reactor ()->schedule_timer (this, 0, interval, interval);
  this->is_active_ = true;

  return ACE_Task_Base::activate ();
}

int HelloWorld_Basic_Impl_Task::deactivate (void)
{
  this->is_active_ = false;
  this->reactor ()->notify (this);
  this->wait ();

  return 0;
}

int HelloWorld_Basic_Impl_Task::svc (void)
{
  this->reactor ()->owner (ACE_OS::thr_self ());

  while (this->is_active_)
    this->reactor ()->handle_events ();

  return 0;
}

int HelloWorld_Basic_Impl_Task::handle_timeout (const ACE_Time_Value & tv, const void *)
{
  ::TCPIP::Message_var ev = new ::TCPIP::Message ();
  ev->message ("This is another message");
  ev->time ().sec = tv.sec ();
  ev->time ().usec = tv.usec ();

  this->impl_->tcpip_handle_message (ev);
  return 0;
}

//
// HelloWorld_Basic_Impl
//
HelloWorld_Basic_Impl::HelloWorld_Basic_Impl (void)
: task_ (this)
{

}

//
// ~HelloWorld_Basic_Impl
//
HelloWorld_Basic_Impl::~HelloWorld_Basic_Impl (void)
{

}

//
// set_session_context
//
void HelloWorld_Basic_Impl::set_session_context (CUTS_TCPIP_Context * ctx)
{
  this->ctx_ = TCPIP::HelloWorld_Context::_narrow (ctx);
}

//
// configuration_complete
//
void HelloWorld_Basic_Impl::configuration_complete (void)
{

}

//
// ccm_activate
//
void HelloWorld_Basic_Impl::ccm_activate (void)
{
  this->task_.activate ();
}

//
// ccm_passivate
//
void HelloWorld_Basic_Impl::ccm_passivate (void)
{
  this->task_.deactivate ();
}

//
// ccm_remove
//
void HelloWorld_Basic_Impl::ccm_remove (void)
{

}

//
// tcpip_handle_message
//
void HelloWorld_Basic_Impl::
tcpip_handle_message (::TCPIP::Message * ev)
{
  std::cout << "message '" << ev->message () << "' received at "
            << ev->time ().sec << "." << ev->time ().usec << std::endl;
}
