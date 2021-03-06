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
  // Start the TestAdapterCallback
  this->activate_test_adapter_callback ();

  // NOTE: The Properties passed to this method are those that are
  // attached to a locality manager. In PICML, this would be the Property
  // elements attached to a CollocationGroup.

  // Locate the TronParams and TronAdapterParams properties.
  size_t length = config.length ();
  const char * tron_params = 0;
  const char * tron_adapter_params = 0;

  for (size_t i = 0; i < length; ++ i)
  {
    if (0 == ACE_OS::strcmp (config[i].name, "TronParams"))
    {
      if (!(config[i].value >>= tron_params))
        ACE_ERROR ((LM_ERROR,
                    ACE_TEXT ("%T (%t) - %M - failed extract arguments\n")));
    }

    if (0 == ACE_OS::strcmp (config[i].name, "TronAdapterParams"))
    {
      if (!(config[i].value >>= tron_adapter_params))
        ACE_ERROR ((LM_ERROR,
                    ACE_TEXT ("%T (%t) - %M - failed extract arguments\n")));
    }
  }

  if (0 != this->spawn_tron_process (tron_params, tron_adapter_params))
      ACE_ERROR ((LM_ERROR,
                  ACE_TEXT ("%T (%t) - %M - failed to spawn tron process\n")));

  // Wait for Tron to set the test adapter on the callback
  // Use the Tron_ORB_Initializer to prevent ORB deadlocks
  ::CORBA::ORB_var orb = DAnCE::PLUGIN_MANAGER::instance ()->get_orb ();
  Tron_ORB_Initializer orb_init (orb.in ());
  orb_init.activate ();

  this->tac_.wait_for_set_test_adapter ();

  orb_init.deactivate ();
  orb_init.wait ();

  // Pass control to the Proxy
  Tron::TestAdapter_var ta = this->tac_.get_test_adapter ();
  ta->configure (config);
}

//
// activate_test_adapter_callback
//
void Tron_Component_Instance_Handler::activate_test_adapter_callback (void)
{
  // Get a reference to the <RootPOA>
  ::CORBA::ORB_var orb = DAnCE::PLUGIN_MANAGER::instance ()->get_orb ();

  ::CORBA::Object_var obj = orb->resolve_initial_references ("RootPOA");
  ::PortableServer::POA_var root_poa = ::PortableServer::POA::_narrow (obj.in ());

  this->tac_mgr_.activate (root_poa.in ());

  ACE_ERROR ((LM_ERROR,
              ACE_TEXT("%T (%t) - %M - activated TestAdapterCallback\n")));
}

//
// spawn_tron_process
//
int Tron_Component_Instance_Handler::
spawn_tron_process (const char * tron_params, const char * adapter_params)
{
  ACE_ERROR ((LM_DEBUG,
              ACE_TEXT ("%T (%t) - %M - starting tron process with arguments: [%s, %s]\n"),
              tron_params,
              adapter_params));

  // Get the IOR for the TestAdapterCallback
  ::CORBA::ORB_var orb = DAnCE::PLUGIN_MANAGER::instance ()->get_orb ();

  ::CORBA::Object_var obj = this->tac_mgr_.get_reference ();
  ::Tron::TestAdapterCallback_var tac = ::Tron::TestAdapterCallback::_narrow (obj.in ());

  ACE_CString ior = orb->object_to_string (tac.in ());

  // Get the TRON_ROOT environment variable
  ACE_Env_Value <ACE_CString> TRON_ROOT ("TRON_ROOT", "");
  ACE_CString command = TRON_ROOT;
  command += "/tron -I libiCCM_Tron_Deployment_Handlers.so ";
  command += tron_params;
  command += " -- ";
  command += adapter_params;
  command += " -ORBInitRef TestAdapterCallback=" + ior;

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
  // Pass control to the proxy
  Tron::TestAdapter_var ta = this->tac_.get_test_adapter ();
  ta->install_instance (plan, instanceRef, instance_reference);

  ++ this->instance_count_;
}

//
// activate_instance
//
void Tron_Component_Instance_Handler::
activate_instance (const ::Deployment::DeploymentPlan & plan,
                   ::CORBA::ULong index,
                   const ::CORBA::Any & comp)
{
  if (!this->init_complete_)
  {
    // Tell the test adapter that initialization is complete
    Tron::TestAdapter_var ta = this->tac_.get_test_adapter ();

    ta->initialization_complete ();
    this->init_complete_ = true;
  }

  // Pass control to the proxy.
  Tron::TestAdapter_var ta = this->tac_.get_test_adapter ();
  ta->activate_instance (plan, index, comp);

  if (0 == --this->instance_count_)
  {
    // Tell the test adapter that configuration is complete
    Tron::TestAdapter_var ta = this->tac_.get_test_adapter ();
    ta->activate_complete ();
  }
}

//
// close
//
void Tron_Component_Instance_Handler::close (void)
{
  // Pass control to the proxy.
  Tron::TestAdapter_var ta = this->tac_.get_test_adapter ();
  ta->close ();

  ACE_ERROR ((LM_ERROR,
              ACE_TEXT("%T (%t) - %M - terminating tron process")));

  // Terminate the tron process
  this->tron_process_.kill ();
  this->tron_process_.wait ();
}

//
// passivate_instance
//
void Tron_Component_Instance_Handler::
passivate_instance (const ::Deployment::DeploymentPlan & plan,
                    ::CORBA::ULong index,
                    const ::CORBA::Any & comp)
{
  // Pass control to the proxy
  Tron::TestAdapter_var ta = this->tac_.get_test_adapter ();
  ta->passivate_instance (plan, index, comp);

}

//
// remove_instance
//
void Tron_Component_Instance_Handler::
remove_instance (const ::Deployment::DeploymentPlan & plan,
                 ::CORBA::ULong index,
                 const ::CORBA::Any & comp)
{
  // Pass control to the proxy
  Tron::TestAdapter_var ta = this->tac_.get_test_adapter ();
  ta->remove_instance (plan, index, comp);
}

//
// provide_endpoint_reference
//
void Tron_Component_Instance_Handler::
provide_endpoint_reference (const ::Deployment::DeploymentPlan & plan,
                            ::CORBA::ULong index,
                            const ::CORBA::Any_out comp)
{
  // Pass control to the proxy
  Tron::TestAdapter_var ta = this->tac_.get_test_adapter ();
  ta->provide_endpoint_reference (plan, index, comp);
}

//
// connect_instance
//
void Tron_Component_Instance_Handler::
connect_instance (const ::Deployment::DeploymentPlan & plan,
                  ::CORBA::ULong index,
                  const ::CORBA::Any & comp)
{
  // Pass control to the proxy
  Tron::TestAdapter_var ta = this->tac_.get_test_adapter ();
  ta->connect_instance (plan, index, comp);
}

//
// disconnect_instance
//
void Tron_Component_Instance_Handler::
disconnect_instance (const ::Deployment::DeploymentPlan & plan,
                     ::CORBA::ULong connectionRef)
{
  // Pass control to the proxy
  Tron::TestAdapter_var ta = this->tac_.get_test_adapter ();
  ta->disconnect_instance (plan, connectionRef);
}

//
// instance_configured
//
void Tron_Component_Instance_Handler::
instance_configured (const ::Deployment::DeploymentPlan & plan,
                     ::CORBA::ULong index)
{
  // Pass control to the proxy
  Tron::TestAdapter_var ta = this->tac_.get_test_adapter ();
  ta->instance_configured (plan, index);
}

//
// instance_type
//
char * Tron_Component_Instance_Handler::
instance_type (void)
{
  // Pass control to the proxy
  Tron::TestAdapter_var ta = this->tac_.get_test_adapter ();
  return ta->instance_type ();
}

//
// dependencies
//
::CORBA::StringSeq * Tron_Component_Instance_Handler::
dependencies (void)
{
  // Pass control to the proxy
  Tron::TestAdapter_var ta = this->tac_.get_test_adapter ();
  return ta->dependencies ();
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
