// $Id$

#include "Tron_Component_Instance_Handler.h"

#if !defined (__CUTS_INLINE__)
#include "Tron_Component_Instance_Handler.inl"
#endif

#include "ace/Env_Value_T.h"

namespace iCCM
{

//
// configure
//
void Tron_Component_Instance_Handler::
configure (const ::Deployment::Properties & config)
{
  // Pass control to the base class. If this method is empty, then it
  // is recommendend that you remove it completely from this class.
  this->base_type::configure (config);

  // NOTE: The Properties passed to this method are those that are
  // attached to a locality manager. In PICML, this would be the Property
  // elements attached to a CollocationGroup.

  // Locate the TronParams property.
  size_t length = config.length ();

  ACE_ERROR ((LM_DEBUG,
              ACE_TEXT ("%T (%t) - %M - configuring tron_component_instance_handler\n")));

  for (size_t i = 0; i < length; ++ i)
  {
//  const char * param = 0;
//  config[i].name >>= param;

  ACE_ERROR ((LM_DEBUG,
              ACE_TEXT ("%T (%t) - %M - found param: %s\n"), config[i].name.in ()));
    if (0 == ACE_OS::strcmp (config[i].name, "TronParams"))
    {
      if (0 != this->spawn_tron_process (config[i]))
        ACE_ERROR ((LM_ERROR,
                    ACE_TEXT("%T (%t) - %M - Tron process failed to start")));
    }
    break;
  }
}

//
// spawn_tron_process
//
int Tron_Component_Instance_Handler::
spawn_tron_process (const ::Deployment::Property & prop)
{
  ACE_ERROR ((LM_DEBUG,
              ACE_TEXT ("%T (%t) - %M - found TronParams\n")));

  // Narrow the property to a char *
  const char * arguments = 0;

  if (!(prop.value >>= arguments))
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - failed extract arguments\n")),
                       -1);

  ACE_ERROR ((LM_DEBUG,
              ACE_TEXT ("%T (%t) - %M - starting tron process with arguments: %s\n"),
              arguments));

  // Get the TRON_ROOT environment variable
  ACE_Env_Value <ACE_CString> TRON_ROOT ("TRON_ROOT", "");
  ACE_CString command = TRON_ROOT;
  command += "/tron -I libiCCM_Tron_Deployment_Handlers.so ";
  command += arguments;

  // Build the process options
  ACE_Process_Options options;
  options.command_line ( command.c_str ());

  // Start the process
  if (ACE_INVALID_PID == this->tron_process_.spawn (options))
    return -1;

  return 0;
}

//
// close
//
void Tron_Component_Instance_Handler::close (void)
{
  // Pass control to the base class. If this method is empty, then it
  // is recommendend that you remove it completely from this class.
  this->base_type::close ();

  // Terminate the tron process
  this->tron_process_.kill ();
  this->tron_process_.wait ();
}

//
// create_Tron_Component_Instance_Handler
//
extern "C"
::DAnCE::InstanceDeploymentHandler_ptr
create_iCCM_Tron_Component_Instance_Handler (void)
{
  iCCM::Tron_Component_Instance_Handler * handler = 0;
  ACE_NEW_RETURN (handler,
                  iCCM::Tron_Component_Instance_Handler (),
                  handler);

  return handler;
}

}
