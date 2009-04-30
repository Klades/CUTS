// $Id$

#include "TCPIP_CCM_ComponentServer.h"

#if !defined (__CUTS_INLINE__)
#include "TCPIP_CCM_ComponentServer.inl"
#endif

//
// init
//
int CUTS_TCPIP_CCM_ComponentServer::init (int & argc, char * argv[])
{
  // Instantiate a new ORB.
  this->orb_ = ::CORBA::ORB_init (argc, argv);
  this->task_.reset (this->orb_.in ());

  // Get the RootPOA.
  ::CORBA::Object_var obj = this->orb_->resolve_initial_references ("RootPOA");

  if (CORBA::is_nil (obj.in ()))
    return -1;

  this->root_ = PortableServer::POA::_narrow (obj.in ());

  if (::CORBA::is_nil (this->root_.in ()))
    return -1;

  // Activate the POA manager.
  ::PortableServer::POAManager_var mgr = this->root_->the_POAManager ();
  mgr->activate ();

  return CUTS_TCPIP_ComponentServer::init (argc, argv);
}

//
// activate
//
int CUTS_TCPIP_CCM_ComponentServer::activate (void)
{
  try
  {
    if (0 != this->task_.activate ())
      return -1;

    return CUTS_TCPIP_ComponentServer::activate ();
  }
  catch (const CORBA::Exception & ex)
  {
    ACE_ERROR ((LM_ERROR,
                "%T (%t) - %M - %s\n",
                ex._info ().c_str ()));
  }

  return -1;
}

//
// shutdown
//
int CUTS_TCPIP_CCM_ComponentServer::shutdown (void)
{
  try
  {
    // Shutdown the ORB and wait for task to exit.
    this->orb_->shutdown ();
    this->task_.wait ();

    return CUTS_TCPIP_ComponentServer::shutdown ();
  }
  catch (const CORBA::Exception & ex)
  {
    ACE_ERROR ((LM_ERROR,
                "%T (%t) - %M - %s\n",
                ex._info ().c_str ()));
  }

  return -1;
}

//
// destroy
//
int CUTS_TCPIP_CCM_ComponentServer::destroy (void)
{
  try
  {
    // Destroy the ORB and RootPOA
    this->root_->destroy (0, 0);
    this->orb_->destroy ();

    return CUTS_TCPIP_ComponentServer::destroy ();
  }
  catch (const CORBA::Exception & ex)
  {
    ACE_ERROR ((LM_ERROR,
                "%T (%t) - %M - %s\n",
                ex._info ().c_str ()));
  }

  return -1;
}
