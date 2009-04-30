// $Id$

#include "HelloWorld_Basic_Impl.h"
#include "ace/streams.h"

//
// HelloWorld_Basic_Impl
//
HelloWorld_Basic_Impl::HelloWorld_Basic_Impl (void)
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

}

//
// ccm_passivate
//
void HelloWorld_Basic_Impl::ccm_passivate (void)
{

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
  std::cout << "received message ["
            << ev->message () << "] at "
            << ev->time ().sec << "."
            << ev->time ().usec << std::endl;
}
