// $Id$

#include "Portico_Component_Instance_Handler.h"

#if !defined (__CUTS_INLINE__)
#include "Portico_Component_Instance_Handler.inl"
#endif

namespace iCCM
{

//
// configure
//
void Portico_Component_Instance_Handler::
configure (const ::Deployment::Properties & config)
{
  // Pass control to the base class. If this method is empty, then it
  // is recommendend that you remove it completely from this class.
  this->base_type::configure (config);

  // NOTE: The Properties passed to this method are those that are
  // attached to a locality manager. In PICML, this would be the Property
  // elements attached to a CollocationGroup.

  // Locate the FEDFile and FEDExecution configuration properties.
  std::string fedfile, fedexec;
  size_t length = config.length ();

  for (size_t i = 0; i < length; ++ i)
  {
    if (0 == ACE_OS::strcmp (config[i].name, "FEDFile"))
      config[i].value >>= this->fedinfo_.file_;
    else if (0 == ACE_OS::strcmp (config[i].name, "FEDExecution"))
      config[i].value >>= this->fedinfo_.execution_;
  }

  if (this->fedinfo_.file_.empty ())
  {
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - FEDFile property not defined in domain\n")));

    throw ::Deployment::StartError ();
  }

  if (this->fedinfo_.execution_.empty ())
  {
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - FEDExecution property not defined in domain\n")));

    throw ::Deployment::StartError ();
  }

  ACE_ERROR ((LM_DEBUG,
              ACE_TEXT ("%T (%t) - %M - using %s execution in %s\n"),
              this->fedinfo_.execution_.c_str (),
              this->fedinfo_.file_.c_str ()));
}


//
// close
//
void Portico_Component_Instance_Handler::close (void)
{
  // Pass control to the base class. If this method is empty, then it
  // is recommendend that you remove it completely from this class.
  this->base_type::close ();
}

//
// create_Portico_Component_Instance_Handler
//
extern "C"
::DAnCE::InstanceDeploymentHandler_ptr
create_iCCM_Portico_Component_Instance_Handler (void)
{
  iCCM::Portico_Component_Instance_Handler * handler = 0;
  ACE_NEW_RETURN (handler,
                  iCCM::Portico_Component_Instance_Handler (),
                  handler);

  return handler;
}

}
