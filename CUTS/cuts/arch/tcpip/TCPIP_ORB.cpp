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
int CUTS_TCPIP_ORB::init (int argc, char * argv [])
{
  CUTS_TCPIP_TRACE ("CUTS_TCPIP_ORB::init (int, char * [])");

  // First, parse the command-line arguments.
  ACE_Get_Opt get_opt (argc, argv);

  get_opt.long_option ("TCPIPEndpoint", ACE_Get_Opt::ARG_REQUIRED);
  get_opt.long_option ("TCPIPThreadpoolSize", ACE_Get_Opt::ARG_REQUIRED);

  char opt;
  int thrpool_size = CUTS_TCPIP_DEFAULT_THREADPOOL_SIZE;

  while ((opt = get_opt ()) != EOF)
  {
    switch (opt)
    {
    case 0:
      if (0 == ACE_OS::strcmp ("TCPIPEndpoint", get_opt.long_option ()))
      {
        if (-1 == this->listen_addr_.set (get_opt.opt_arg ()))
          ACE_ERROR_RETURN ((LM_ERROR,
                             "%T (%t) - %M - failed to convert string to address [%s]\n",
                             get_opt.opt_arg ()),
                             -1);
      }
      else if (0 == ACE_OS::strcmp ("TCPIPThreadpoolSize", get_opt.long_option ()))
      {
        std::istringstream istr (get_opt.long_option ());
        istr >> thrpool_size;
      }

      break;
    }
  }

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

  // Open the acceptoer. This will determine if the specified
  // endpoint is currently in use.
  int retval = this->acceptor_.open (this->listen_addr_, this->reactor_.get ());

  return retval;
}

