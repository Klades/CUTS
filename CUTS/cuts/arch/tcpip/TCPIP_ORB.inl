// -*- C++ -*-
// $Id$

//
// CUTS_TCPIP_ORB
//
CUTS_INLINE
CUTS_TCPIP_ORB::CUTS_TCPIP_ORB (void)
: listen_addr_ (CUTS_TCPIP_DEFUALT_PORT),
  acceptor_ (obj_mgr_)
{
  CUTS_TCPIP_TRACE ("CUTS_TCPIP_ORB::CUTS_TCPIP_ORB (void)");
}

//
// ~CUTS_TCPIP_ORB
//
CUTS_INLINE
CUTS_TCPIP_ORB::~CUTS_TCPIP_ORB (void)
{
  CUTS_TCPIP_TRACE ("CUTS_TCPIP_ORB::~CUTS_TCPIP_ORB (void)");
}

//
// the_OM
//
CUTS_INLINE
CUTS_TCPIP_Servant_Manager & CUTS_TCPIP_ORB::the_OM (void)
{
  CUTS_TCPIP_TRACE ("CUTS_TCPIP_ORB::the_OM (void)");
  return this->obj_mgr_;
}

//
// shutdown
//
CUTS_INLINE
int CUTS_TCPIP_ORB::shutdown (void)
{
  CUTS_TCPIP_TRACE ("CUTS_TCPIP_ORB::shutdown (void)");
  return this->reactor_->end_reactor_event_loop ();
}

//
// run
//
CUTS_INLINE
int CUTS_TCPIP_ORB::run (void)
{
  CUTS_TCPIP_TRACE ("CUTS_TCPIP_ORB::run (void)");
  return this->reactor_->run_reactor_event_loop ();
}
