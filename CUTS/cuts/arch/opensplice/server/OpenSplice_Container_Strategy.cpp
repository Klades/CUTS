// $Id$

#include "OpenSplice_Container_Strategy.h"

#if !defined (__CUTS_INLINE__)
#include "OpenSplice_Container_Strategy.inl"
#endif

#include "OpenSplice_Container.h"
#include "OpenSplice_ComponentServer.h"
#include "cuts/arch/opensplice/ccm/OpenSplice_CCM_Servant.h"

//
// configure_servant
//
void
CUTS_OpenSplice_CCM_Container_Strategy::
configure_servant (::PortableServer::Servant servant,
		   const ::Components::ConfigValues & )
{
  // Convert the servant into an OpenSplice servant.
  CUTS_OpenSplice_CCM_Servant * ospl_servant =
    dynamic_cast <CUTS_OpenSplice_CCM_Servant *> (servant);

  if (0 == ospl_servant)
    return;

  // Get the domain participant factory.
  ::DDS::DomainParticipantFactory_var factory = 
      ::DDS::DomainParticipantFactory::get_instance ();

  // Create a participant on the default domain.
  ACE_DEBUG ((LM_DEBUG,
	      "%T (%t) - %M - creating a participant in the default domain\n"));

  ::DDS::DomainParticipant_var participant = 
      factory->create_participant (0,     /* this is where the domain goes */
				   PARTICIPANT_QOS_DEFAULT,
				   0,
				   ::DDS::ANY_STATUS);

  // Configure the servant.
  ospl_servant->configure (participant.in ());
}

