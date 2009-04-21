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
