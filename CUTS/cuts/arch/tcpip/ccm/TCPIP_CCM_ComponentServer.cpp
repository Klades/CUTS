// $Id$

#include "TCPIP_CCM_ComponentServer.h"

#if !defined (__CUTS_INLINE__)
#include "TCPIP_CCM_ComponentServer.inl"
#endif

//
// activate
//
int CUTS_TCPIP_CCM_ComponentServer::init (int & argc, char * argv[])
{
  // Instantiate a new ORB.
  this->orb_ = ::CORBA::ORB_init (argc, argv);

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

  return 0;
}

//
// svc
//
int CUTS_TCPIP_CCM_ComponentServer::svc (void)
{
  try
  {
    this->orb_->run ();
    return 0;
  }
  catch (const CORBA::Exception & ex)
  {
    ACE_ERROR ((LM_ERROR,
                "%T (%t) - %M - %s\n",
                ex._info ().c_str ()));
  }
  catch (...)
  {

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
    this->orb_->shutdown ();
    return 0;
  }
  catch (const CORBA::Exception & ex)
  {
    ACE_ERROR ((LM_ERROR,
                "%T (%t) - %M - %s\n",
                ex._info ().c_str ()));
  }
}
