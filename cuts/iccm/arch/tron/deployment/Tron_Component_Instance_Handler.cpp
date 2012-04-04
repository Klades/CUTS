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

  // Start the TestAdapterCallback
  this->activate_test_adapter_callback ();

  // NOTE: The Properties passed to this method are those that are
  // attached to a locality manager. In PICML, this would be the Property
  // elements attached to a CollocationGroup.

  // Locate the TronParams property.
  size_t length = config.length ();

  ACE_ERROR ((LM_DEBUG,
              ACE_TEXT ("%T (%t) - %M - configuring tron_component_instance_handler\n")));

  for (size_t i = 0; i < length; ++ i)
  {
    if (0 == ACE_OS::strcmp (config[i].name, "TronParams"))
    {
      if (0 != this->spawn_tron_process (config[i]))
        ACE_ERROR ((LM_ERROR,
                    ACE_TEXT("%T (%t) - %M - Tron process failed to start")));
    }
    break;
  }

  // Statically spawn the tron process for now
  if (0 != this->spawn_static_tron_process ())
    return;

  // Wait for Tron to set the test adapter on the callback
  // Use the Tron_ORB_Initializer to prevent ORB deadlocks
  ::CORBA::ORB_var orb = this->get_orb ();
  Tron_ORB_Initializer orb_init (orb.in ());
  orb_init.activate ();

  this->tac_.wait_for_set_test_adapter ();

  orb_init.deactivate ();
  orb_init.wait ();
}

//
// activate_test_adapter_callback
//
void Tron_Component_Instance_Handler::activate_test_adapter_callback (void)
{
  // Get a reference to the <RootPOA>
  ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("%T (%t) - %M - %N:%l resolving RootPOA\n")));

  ::CORBA::ORB_var orb = this->get_orb ();

  ::CORBA::Object_var obj = orb->resolve_initial_references ("RootPOA");
  ::PortableServer::POA_var root_poa = ::PortableServer::POA::_narrow (obj.in ());

  this->tac_mgr_.activate (root_poa.in ());
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
  options.command_line (command.c_str ());

  // Start the process
  if (ACE_INVALID_PID == this->tron_process_.spawn (options))
    return -1;

  return 0;
}

//
// spawn_static_tron_process
//
int Tron_Component_Instance_Handler::
spawn_static_tron_process (void)
{
  // Get the IOR for the TestAdapterCallback
  ::CORBA::ORB_var orb = this->get_orb ();

  ::CORBA::Object_var obj = this->tac_mgr_.get_reference ();
  ::Tron::TestAdapterCallback_var tac = ::Tron::TestAdapterCallback::_narrow (obj.in ());

  ACE_CString ior = orb->object_to_string (tac.in ());

  // Get the TRON_ROOT environment variable
  ACE_Env_Value <ACE_CString> TRON_ROOT ("TRON_ROOT", "");
  ACE_CString command = TRON_ROOT;
  command += "/tron -I libiCCM_Tron_Deployment_Handlers.so -v 10 button.xml ";
  command += "-- -ORBInitRef TestAdapterCallback=" + ior;

  // Build the process options
  ACE_Process_Options options;
  options.command_line (command.c_str ());

  // Start the process
  if (ACE_INVALID_PID == this->tron_process_.spawn (options))
    return -1;

  return 0;
}

//
// install_instance
//
void Tron_Component_Instance_Handler::
install_instance (const ::Deployment::DeploymentPlan & plan,
                  ::CORBA::ULong instanceRef,
                  ::CORBA::Any_out instance_reference)
{
  this->instance_count_++;
  this->base_type::install_instance (plan, instanceRef, instance_reference);
}

//
// activate_instance
//
void Tron_Component_Instance_Handler::
activate_instance (const ::Deployment::DeploymentPlan & plan,
                   ::CORBA::ULong index,
                   const ::CORBA::Any & comp)
{
  ACE_ERROR ((LM_DEBUG,
              ACE_TEXT ("%T (%t) - %M - starting activate_instance [%d, %d]\n"),
              this->init_complete_,
              this->instance_count_.value ()));

  if (!this->init_complete_)
  {
    // Tell the test adapter that initialization is complete
    Tron::TestAdapter_var ta = this->tac_.get_test_adapter ();

    ta->initialization_complete ();
    this->init_complete_ = true;
  }

  if (0 == --this->instance_count_)
  {
    // Tell the test adapter that configuration is complete
    Tron::TestAdapter_var ta = this->tac_.get_test_adapter ();

    ta->activate_complete ();
  }


  this->base_type::activate_instance (plan, index, comp);
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
