// $Id$

#include "TCPIP_Component_Instance_Handler.h"

#if !defined (__CUTS_INLINE__)
#include "TCPIP_Component_Instance_Handler.inl"
#endif

namespace iCCM
{

//
// configure
//
void TCPIP_Component_Instance_Handler::
configure (const ::Deployment::Properties & config)
{
  ACE_ERROR ((LM_DEBUG,
              ACE_TEXT ("%T (%t) - %M - configuring instance handler\n")));
  // Pass control to the base class. If this method is empty, then it
  // is recommendend that you remove it completely from this class.
  this->base_type::configure (config);

  ACE_ARGV_T <ACE_TCHAR> argv_vec;

  // Extract the properties specifically for TCP/IP.
  ::CORBA::ULong length = config.length ();

  for (::CORBA::ULong i = 0; i < length; ++ i)
  {
    const ::Deployment::Property & p = config[i];

    if (0 == ACE_OS::strcmp (p.name.in (), "TCPIPEndpoint"))
    {
      const char * value_str = 0;
      p.value >>= value_str;

      argv_vec.add ("--TCPIPEndpoint");
      argv_vec.add (value_str);
    }
  }

  ACE_ERROR ((LM_DEBUG,
              ACE_TEXT ("%T (%t) - %M - initializing the tcpip orb\n")));
  // Initialize and activate the ORB.
  this->tcpip_orb_.init (argv_vec.argc (), argv_vec.argv ());
  ACE_ERROR ((LM_DEBUG,
              ACE_TEXT ("%T (%t) - %M - activating the tcpip orb\n")));
  this->orb_task_.activate ();
  ACE_ERROR ((LM_DEBUG,
              ACE_TEXT ("%T (%t) - %M - finished configure on the instance handler\n")));
}


//
// close
//
void TCPIP_Component_Instance_Handler::close (void)
{
  ACE_ERROR ((LM_DEBUG,
              ACE_TEXT ("%T (%t) - %M - closing the instance handler\n")));
  // Shutdown the TCP/IP ORB.
  this->tcpip_orb_.shutdown ();

  ACE_ERROR ((LM_DEBUG,
              ACE_TEXT ("%T (%t) - %M - tcpip orb is shutdown\n")));
  // Pass control to the base class. If this method is empty, then it
  // is recommendend that you remove it completely from this class.
  this->base_type::close ();
}

//
// the_ORB
//
TCPIP_ORB & TCPIP_Component_Instance_Handler::the_ORB (void)
{
  return this->tcpip_orb_;
}

}

//
// create_TCPIP_Component_Instance_Handler
//
extern "C"
::DAnCE::InstanceDeploymentHandler_ptr
create_iCCM_TCPIP_Component_Instance_Handler (void)
{
  iCCM::TCPIP_Component_Instance_Handler * handler = 0;
  ACE_NEW_RETURN (handler,
                  iCCM::TCPIP_Component_Instance_Handler (),
                  handler);

  return handler;
}