// $Id$

#include "TCPIP_CCM_Instance_Handler.h"
#include "ace/ARGV.h"

#define CMDLINE_LONG_OPTION(name) "--" ## name

#define CUTS_TCPIP_ENDPOINT               "TCPIPEndpoint"
#define CUTS_TCPIP_ENDPOINT_LONG_OPTION   CMDLINE_LONG_OPTION(CUTS_TCPIP_ENDPOINT)

//
// CUTS_TCPIP_CCM_Instance_Handler
//
CUTS_TCPIP_CCM_Instance_Handler::CUTS_TCPIP_CCM_Instance_Handler (void)
: orb_task_ (tcpip_orb_)
{

}

//
// ~CUTS_TCPIP_CCM_Instance_Handler
//
CUTS_TCPIP_CCM_Instance_Handler::~CUTS_TCPIP_CCM_Instance_Handler (void)
{

}

//
// configure
//
void CUTS_TCPIP_CCM_Instance_Handler::
configure (const ::Deployment::Properties & config)
{
  // First, pass control to the base class.
  base_type::configure (config);

  ACE_ARGV_T <TCHAR> argv_vec;

  // Extract the properties specifically for TCP/IP.
  ::CORBA::ULong length = config.length ();

  for (::CORBA::ULong i = 0; i < length; ++ i)
  {
    const ::Deployment::Property & p = config[i];

    if (0 == ACE_OS::strcmp (p.name.in (), CUTS_TCPIP_ENDPOINT))
    {
      const char * value_str = 0;
      p.value >>= value_str;

      argv_vec.add (CUTS_TCPIP_ENDPOINT_LONG_OPTION);
      argv_vec.add (value_str);
    }
  }

  // Initialize and activate the ORB.
  this->tcpip_orb_.init (argv_vec.argc (), argv_vec.argv ());
  this->orb_task_.activate ();
}


//
// configure
//
void CUTS_TCPIP_CCM_Instance_Handler::close (void)
{
  // Shutdown the TCP/IP ORB.
  this->tcpip_orb_.shutdown ();

  // Pass control to the base class.
  base_type::close ();
}

//
// the_ORB
//
CUTS_TCPIP_ORB & CUTS_TCPIP_CCM_Instance_Handler::the_ORB (void)
{
  return this->tcpip_orb_;
}

//
// create_CUTS_TCPIP_Component_Instance_Handler
//
extern "C"
::DAnCE::InstanceDeploymentHandler_ptr
create_CUTS_TCPIP_Component_Instance_Handler (void)
{
  return new CUTS_TCPIP_CCM_Instance_Handler ();
}
