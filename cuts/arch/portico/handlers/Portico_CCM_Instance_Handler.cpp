// $Id$

#include "Portico_CCM_Instance_Handler.h"

#if !defined (__CUTS_INLINE__)
#include "Portico_CCM_Instance_Handler.inl"
#endif

//
// configure
//
void Portico_CCM_Instance_Handler::
configure (const ::Deployment::Properties & props)
{
  // First, let the base class do its configuration.
  Portico_CCM_Instance_Handler::base_type::configure (props);

  // Locate the FEDFile and FEDExecution configuration properties.
  std::string fedfile, fedexec;
  size_t length = props.length ();

  for (size_t i = 0; i < length; ++ i)
  {
    if (0 == ACE_OS::strcmp (props[i].name, "FEDFile"))
      props[i].value >>= this->fedinfo_.file_;
    else if (0 == ACE_OS::strcmp (props[i].name, "FEDExecution"))
      props[i].value >>= this->fedinfo_.execution_;
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
void Portico_CCM_Instance_Handler::close (void)
{

}

//
// create_Portico_Component_Instance_Handler
//
extern "C"
::DAnCE::InstanceDeploymentHandler_ptr
create_Portico_CCM_Component_Instance_Handler (void)
{
  Portico_CCM_Instance_Handler * handler = 0;
  ACE_NEW_RETURN (handler,
                  Portico_CCM_Instance_Handler (),
                  handler);

  return handler;
}
