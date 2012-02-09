// $Id$

#include "OpenSplice_Component_Instance_Handler.h"

#if !defined (__CUTS_INLINE__)
#include "OpenSplice_Component_Instance_Handler.inl"
#endif

#include "cuts/iccm/ddsxml/DDS_Domain_File.h"
#include "XSC/utils/XML_Error_Handler.h"

//
// operator <<=
//
void operator <<= (DDS::EntityFactoryQosPolicy & qos, const iccm::EntityFactoryQosPolicy & policy)
{
  qos.autoenable_created_entities = policy.autoenable_created_entities ();
}

//
// operator <<=
//
void operator <<= (DDS::DomainParticipantFactoryQos & qos, const iccm::DomainParticipantFactoryQos & policy)
{
  if (policy.entity_factory_p ())
    qos.entity_factory <<= policy.entity_factory ();
}

namespace iCCM
{

//
// configure
//
void OpenSplice_Component_Instance_Handler::
configure (const Deployment::Properties & props)
{
  // First, let the base class do its configuration.
  this->base_type::configure (props);

  // Locate the DDSDomainQoS property.
  size_t length = props.length ();

  for (size_t i = 0; i < length; ++ i)
  {
    if (0 == ACE_OS::strcmp (props[i].name, "DomainQoS"))
    {
      this->configure_DDSDomainQoS (props[i]);
      return;
    }
  }
}

//
// configure_DDSDomainQoS
//
void OpenSplice_Component_Instance_Handler::
configure_DDSDomainQoS (const Deployment::Property & prop)
{
  const char * filename = 0;

  if ((prop.value >>= filename))
  {
    ACE_ERROR ((LM_DEBUG,
                ACE_TEXT ("%T (%t) - %M - loading domain configuration from %s\n"),
                filename));

    // Read the contents of the extracted filename.
    iCCM::DDS_Domain_File file;
    XSC::XML::XML_Error_Handler error_handler;
    file->setErrorHandler (&error_handler);

    if (file.read (filename))
    {
      // Extract the contents of the XML document.
      iccm::DomainParticipantFactoryQos dpf_qos;
      file >>= dpf_qos;

      // Get the current QoS values, update them, and set them.
      ::DDS::DomainParticipantFactory_var dpf =
        ::DDS::DomainParticipantFactory::get_instance ();

      ::DDS::DomainParticipantFactoryQos qos;

      dpf->get_qos (qos);
      qos <<= dpf_qos;
      dpf->set_qos (qos);
    }
    else
    {
      ACE_ERROR ((LM_ERROR,
                  ACE_TEXT ("%T (%t) - %M - failed to read %s\n"),
                  filename));
    }
  }
  else
  {
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - property is not a tk_string\n")));
  }
}

}

//
// create_CUTS_OpenSplice_Component_Instance_Handler
//
extern "C"
::DAnCE::InstanceDeploymentHandler_ptr
create_iCCM_OpenSplice_Component_Instance_Handler (void)
{
  return new iCCM::OpenSplice_Component_Instance_Handler ();
}


