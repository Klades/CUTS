// $Id$

#include "TCPIP_ORB.h"

#if !defined (__CUTS_INLINE__)
#include "TCPIP_ORB.inl"
#endif

#include "ace/CORBA_macros.h"
#include "ace/Get_Opt.h"
#include "ace/Reactor.h"
#include "ace/TP_Reactor.h"
#include <sstream>

//
// init
//
int TCPIP_ORB::init (int argc, char * argv [])
{
  CUTS_TCPIP_TRACE ("TCPIP_ORB::init (int, char * [])");

  // First, parse the command-line arguments.
  const char * optstr = "";
  ACE_Get_Opt get_opt (argc, argv, optstr, 0);

  get_opt.long_option ("TCPIPEndpoint", ACE_Get_Opt::ARG_REQUIRED);
  get_opt.long_option ("TCPIPThreadpoolSize", ACE_Get_Opt::ARG_REQUIRED);

  int opt;
  int thrpool_size = CUTS_TCPIP_DEFAULT_THREADPOOL_SIZE;
  const char * listen_addr = CUTS_TCPIP_DEFAULT_ENDPOINT;

  while ((opt = get_opt ()) != EOF)
  {
    switch (opt)
    {
    case 0:
      if (0 == ACE_OS::strcmp ("TCPIPEndpoint", get_opt.long_option ()))
      {
        listen_addr = get_opt.opt_arg ();
      }
      else if (0 == ACE_OS::strcmp ("TCPIPThreadpoolSize", get_opt.long_option ()))
      {
        std::istringstream istr (get_opt.opt_arg ());
        istr >> thrpool_size;
      }
      break;
    }
  }

  if (-1 == this->listen_addr_.set (listen_addr))
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - failed to convert string to address [%s]\n"),
                       get_opt.opt_arg ()),
                       -1);

  // We are going to use a TP_Reactor as the implementation.
  ACE_Reactor_Impl * reactor_impl = 0;
  ACE_NEW_THROW_EX (reactor_impl,
                    ACE_TP_Reactor (),
                    ACE_bad_alloc ());

  ACE_Auto_Ptr <ACE_Reactor_Impl> auto_clean (reactor_impl);

  // Configure the reactor for the acceptor.
  ACE_Reactor * reactor = 0;
  ACE_NEW_THROW_EX (reactor,
                    ACE_Reactor (reactor_impl),
                    ACE_bad_alloc ());

  this->reactor_.reset (reactor);
  auto_clean.release ();

  ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("%T (%t) - %M - accepting incoming connections; %s:%d\n"),
              this->listen_addr_.get_host_addr (),
              this->listen_addr_.get_port_number ()));

  // Open the acceptoer. This will determine if the specified
  // endpoint is currently in use.
  int retval = this->acceptor_.open (this->listen_addr_, this->reactor_.get ());

  if (0 != retval)
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - failed to open connection; %s:%d\n"),
                this->listen_addr_.get_host_addr (),
                this->listen_addr_.get_port_number ()));

  return retval;
}

