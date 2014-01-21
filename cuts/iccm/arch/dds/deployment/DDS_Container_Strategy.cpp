// $Id$

#if !defined (__CUTS_INLINE__)
#include "DDS_Container_Strategy.inl"
#endif

#include "cuts/iccm/ddsxml/DDS_Participant_File.h"
#include "XSC/utils/XML_Error_Handler.h"

namespace iCCM
{

//
// DDS_Container_Strategy
//
template <typename T>
DDS_Container_Strategy <T>::
DDS_Container_Strategy (typename T::container_type & container)
: Container_Strategy_T <typename T::container_type> (container)
{

}

//
// configure_servant
//
template <typename T>
void DDS_Container_Strategy <T>::
configure_servant (::PortableServer::Servant servant,
                   const ::Components::ConfigValues & config)
{
  typedef typename T::servant_type servant_type;
  servant_type * dds_servant = dynamic_cast <servant_type *> (servant);

  if (0 == dds_servant)
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

  if (0 != filename)
  {
    ACE_ERROR ((LM_DEBUG,
                ACE_TEXT ("%T (%t) - %M - configuring %s using %s\n"),
                dds_servant->name ().c_str (),
                filename));

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
      dds_servant->configure (qos_value);
    }
    else
    {
      // Unable to read file, use default configuration
      ACE_ERROR ((LM_ERROR,
                  ACE_TEXT ("%T (%t) - %M - failed to read %s, ")
                  ACE_TEXT ("using default configuration"),
                  filename));
      dds_servant->configure ();
    }
  }
  else
  {
    ACE_ERROR ((LM_DEBUG,
                ACE_TEXT ("%T (%t) - %M - using default configuration ")
                ACE_TEXT ("for %s\n"),
                dds_servant->name ().c_str ()));

    // Use the default configuration.
    dds_servant->configure ();
  }
}

}
