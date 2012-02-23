// $Id$

#if !defined (__CUTS_INLINE__)
#include "DDS_Component_Instance_Handler.inl"
#endif

#include "cuts/iccm/ddsxml/DDS_Domain_File.h"
#include "XSC/utils/XML_Error_Handler.h"

namespace iCCM
{

//
// configure
//
template <typename T>
void DDS_Component_Instance_Handler <T>::
configure (const Deployment::Properties & props)
{
  // First, let the base class do its configuration.
  Component_Instance_Handler_T::configure (props);

  // Locate the DDSDomainQoS property.
  size_t length = props.length ();

  for (size_t i = 0; i < length; ++ i)
  {
    if (0 == ACE_OS::strcmp (props[i].name, "DomainQoS"))
    {
      iccm::DomainParticipantFactoryQos dpf_qos;

      if (this->load_DDSDomainQoS (props[i], dpf_qos))
        this->configure_DDSDomainQoS (dpf_qos);
    }
    break;
  }
}

//
// load_DDSDomainQoS
//
template <typename T>
bool DDS_Component_Instance_Handler <T>::
load_DDSDomainQoS (const ::Deployment::Property & prop, iccm::DomainParticipantFactoryQos & qos)
{
  const char * filename = 0;

  if (!(prop.value >>= filename))
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - failed extract filename\n")),
                       false);

  ACE_ERROR ((LM_DEBUG,
              ACE_TEXT ("%T (%t) - %M - loading domain configuration from %s\n"),
              filename));

  // Read the contents of the extracted filename.
  iCCM::DDS_Domain_File file;
  XSC::XML::XML_Error_Handler error_handler;
  file->setErrorHandler (&error_handler);

  if (!file.read (filename))
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - failed to read file [file=%s]\n"),
                       filename),
                       false);

  // Extract the contents of the XML document.
  iccm::DomainParticipantFactoryQos dpf_qos;
  file >>= dpf_qos;

  return true;
}

}
