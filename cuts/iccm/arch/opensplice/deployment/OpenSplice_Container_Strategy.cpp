// $Id$

#include "OpenSplice_Container_Strategy.h"

#if !defined (__CUTS_INLINE__)
#include "OpenSplice_Container_Strategy.inl"
#endif

#include "cuts/iccm/arch/opensplice/servant/OpenSplice_Servant.h"

#include "cuts/iccm/ddsxml/DDS_Participant_File.h"
#include "XSC/utils/XML_Error_Handler.h"

namespace iCCM
{

//
//OpenSplice_Container_Strategy
//
OpenSplice_Container_Strategy::
OpenSplice_Container_Strategy (OpenSplice_Container & container)
  : base_type (container)
{

}

//
// configure_servant
//
void OpenSplice_Container_Strategy::
configure_servant (::PortableServer::Servant servant,
                   const ::Components::ConfigValues & config)
{
  OpenSplice_Servant * ospl_servant = dynamic_cast <OpenSplice_Servant *> (servant);

  if (0 == ospl_servant)
    throw CORBA::INTERNAL ();

  // Locate the DDSParticipantQoS property.
  size_t length = config.length ();
  const char * filename = 0;

  for (size_t i = 0; i < length; ++ i)
  {
    if (0 == ACE_OS::strcmp (config[i]->name (), "ParticipantQoS"))
    {
      config[i]->value () >>= filename;
      break;
    }
  }

  if (0 == filename)
  {
    // Use the default configuration.
    ospl_servant->configure ();
  }
  else
  {
    // Read the contents of the extracted filename.
    iCCM::DDS_Participant_File file;
    XSC::XML::XML_Error_Handler error_handler;
    file->setErrorHandler (&error_handler);

    if (file.read (filename))
    {
      // Extract the contents of the XML document.
      iccm::DomainParticipantQos qos_value;
      file >>= qos_value;

      // Configure the DDS servant.
      ospl_servant->configure (qos_value);
    }
    else
    {
      ACE_ERROR ((LM_ERROR,
                  ACE_TEXT ("%T (%t) - %M - failed to read %s\n"),
                  filename));
    }
  }
}

}
