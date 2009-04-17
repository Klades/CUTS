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
// parse_args
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
      }

      break;
    }
  }

  // We are going to use a TP_Reactor as the implementation.
  ACE_TP_Reactor * tp_reactor = 0;
  ACE_NEW_THROW_EX (tp_reactor,
                    ACE_TP_Reactor (thrpool_size, true),
                    ACE_bad_alloc ());

  ACE_Auto_Ptr <ACE_Reactor_Impl> ac1 (tp_reactor);

  // Configure the reactor the acceptor.
  ACE_Reactor * reactor = 0;
  ACE_NEW_THROW_EX (reactor, ACE_Reactor (tp_reactor), ACE_bad_alloc ());
  ac1.release ();

  ACE_Auto_Ptr <ACE_Reactor> ac2 (reactor);

  // Open a connection for listening. Make sure we pass the object
  // manager as the argument. The event handler will use it for
  // dispatching received events to objects.
  int retval = this->acceptor_.open (this->listen_addr_, reactor);

  if (0 == retval)
    ac2.release ();

  return retval;
}
