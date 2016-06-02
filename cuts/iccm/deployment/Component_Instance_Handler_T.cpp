// $Id$

#include "cuts/iccm/servant/Cookie.h"

#include "dance/DAnCE_Utility.h"

#include "ciao/Base/CIAO_PropertiesC.h"
#include "ciao/Version.h"
#include "ccm/CCM_ObjectC.h"

#include "cuts/iccm/configuration/iCCM_Plugin_Manager.h"
#include "dance/LocalityManager/Scheduler/Plugin_Manager.h"
#include "dance/DAnCE_PropertiesC.h"

#include "ace/ARGV.h"

namespace iCCM
{

template <typename HANDLER, typename ABSTRACT_HANDLER, typename CONTAINER>
Component_Instance_Handler_T <HANDLER, ABSTRACT_HANDLER, CONTAINER>::Component_Instance_Handler_T (void)
{

}

template <typename HANDLER, typename ABSTRACT_HANDLER, typename CONTAINER>
Component_Instance_Handler_T <HANDLER, ABSTRACT_HANDLER, CONTAINER>::~Component_Instance_Handler_T (void)
{

}

template <typename HANDLER, typename ABSTRACT_HANDLER, typename CONTAINER>
::CORBA::StringSeq *
Component_Instance_Handler_T <HANDLER, ABSTRACT_HANDLER, CONTAINER>::dependencies (void)
{
  ::CORBA::StringSeq * retval = 0;
  ACE_NEW_THROW_EX (retval,
                    ::CORBA::StringSeq (0),
                    ::CORBA::NO_MEMORY ());
  return retval;
}

template <typename HANDLER, typename ABSTRACT_HANDLER, typename CONTAINER>
void Component_Instance_Handler_T <HANDLER, ABSTRACT_HANDLER, CONTAINER>::close (void)
{

}

template <typename HANDLER, typename ABSTRACT_HANDLER, typename CONTAINER>
char * Component_Instance_Handler_T <HANDLER, ABSTRACT_HANDLER, CONTAINER>::instance_type (void)
{
  return ::CORBA::string_dup (DAnCE::CCM_COMPONENT);
}

template <typename HANDLER, typename ABSTRACT_HANDLER, typename CONTAINER>
::CORBA::ORB_ptr Component_Instance_Handler_T <HANDLER, ABSTRACT_HANDLER, CONTAINER>::get_orb (void)
{
  return ::CORBA::ORB::_duplicate (this->orb_.in ());
}

template <typename HANDLER, typename ABSTRACT_HANDLER, typename CONTAINER>
Container * Component_Instance_Handler_T <HANDLER, ABSTRACT_HANDLER, CONTAINER>::get_container (void) const
{
  return this->container_.get ();
}

template <typename HANDLER, typename ABSTRACT_HANDLER, typename CONTAINER>
void Component_Instance_Handler_T <HANDLER, ABSTRACT_HANDLER, CONTAINER>::
install_instance (const ::Deployment::DeploymentPlan & plan,
                  ::CORBA::ULong instance_ref,
                  ::CORBA::Any_out instance_reference)
{
  using ::Deployment::InstanceDeploymentDescription;
  using ::Deployment::MonolithicDeploymentDescription;
  using ::Deployment::PlanError;
  using ::Deployment::StartError;

  const InstanceDeploymentDescription & idd = plan.instance[instance_ref];
  const MonolithicDeploymentDescription & mdd = plan.implementation[idd.implementationRef];

  using ::DAnCE::Utility::PROPERTY_MAP;
  PROPERTY_MAP pmap (idd.configProperty.length () + mdd.execParameter.length ());

  // Build a usable property map in the form of a hash map for the
  // properties in the instance and implementation descriptors.
  ::DAnCE::Utility::build_property_map (pmap, mdd.execParameter);
  ::DAnCE::Utility::build_property_map (pmap, idd.configProperty);

  ::CORBA::String_var exec_art,
                      exec_entry,
                      svnt_art,
                      svnt_entry,
                      cont_id;

  using namespace CIAO::Deployment;
  ::CORBA::Any val;
  const char *tmp = 0;

  // We need to locate the entrypoint that is needed to install
  // both the component servant and implementation.
  if (0 == pmap.find (::CIAO::Deployment::SVNT_ENTRYPT, val))
  {
    val >>= tmp;
    svnt_entry = tmp;
  }
  else
  {
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T - %M - failed to locate servant entrypoint for %s\n"),
                mdd.name.in ()));

    throw PlanError (idd.name.in (), "failed to locate servant entrypoint");
  }

  if (0 == pmap.find (::CIAO::Deployment::SVNT_ARTIFACT, val))
  {
    val >>= tmp;
    svnt_art = this->get_implementation (tmp, plan);
  }
  else
  {
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T - %M - failed to locate servant artifact\n")));

    throw PlanError (idd.name.in (), "failed to locate servant artifact");
  }

  if (0 == pmap.find (::CIAO::Deployment::EXEC_ARTIFACT, val))
  {
    val >>= tmp;
    exec_art = this->get_implementation (tmp, plan);
  }
  else
  {
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T - %M - failed to locate executor artifact")
                ACE_TEXT (" for %s\n"),
                mdd.name.in ()));

    throw PlanError (idd.name.in (), "failed to locate executor artifact");
  }

  if (0 == pmap.find (::CIAO::Deployment::COMPONENT_FACTORY, val))
  {
    val >>= tmp;
    exec_entry = tmp;
  }
  else
  {
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T - %M - failed to locate component factory ")
                ACE_TEXT ("for %s\n"),
                mdd.name.in ()));

    throw PlanError (idd.name.in (), "failed to locate component factory\n");
  }

  //if (0 == pmap.find (CONTAINER_ID, val))
  //{
  //  val >>= tmp;
  //  cont_id = tmp;
  //}
  //else
  //{
  //  // Use the default container.
  //  cont_id = "";
  //}

  ::Components::CCMObject_var comp_ref;

  try
  {
    // Install the component. We are going to get back a reference
    // to the installed component.
#if (CIAO_MAJOR_VERSION >= 1 && CIAO_MINOR_VERSION >= 1)
    comp_ref = this->container_->install_component (exec_art,
                                                    exec_entry,
                                                    svnt_art,
                                                    svnt_entry,
                                                    idd.name.in (),
                                                    ACE_DEFAULT_SHLIB_MODE);
#else
    comp_ref = this->container_->install_component (exec_art,
                                                    exec_entry,
                                                    svnt_art,
                                                    svnt_entry,
                                                    idd.name.in ());
#endif

    // Set the attributes for the installed component. This is done
    // by converting the deployment descriptors into a configuration
    // name-value sequence.
    ::Components::ConfigValues attr_config;
    this->create_attribute_configuration (idd.configProperty,
                                          attr_config);

    this->container_->set_attributes (comp_ref.in (), attr_config);
  }
  catch (const ::CORBA::Exception &ex)
  {
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - caught corba exception %s\n"),
                ex._info ().c_str ()));

    throw StartError (idd.name.in (), ex._info ().c_str ());
  }
  catch (...)
  {
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - caught unknown exception\n")));

    throw StartError (idd.name.in (), "unknown C++ exception\n");
  }

  // Make sure that we do have a valid component reference.
  if (::CORBA::is_nil (comp_ref.in ()))
    throw StartError (idd.name.in (), "container provided nil object reference");

  ACE_NEW_THROW_EX (instance_reference,
                    ::CORBA::Any (),
                    ::CORBA::NO_MEMORY ());

  *instance_reference <<= comp_ref;
}

//
// activate_instance
//
template <typename HANDLER, typename ABSTRACT_HANDLER, typename CONTAINER>
void Component_Instance_Handler_T <HANDLER, ABSTRACT_HANDLER, CONTAINER>::
activate_instance (const ::Deployment::DeploymentPlan & ,
                   ::CORBA::ULong ,
                   const ::CORBA::Any & any)
{
  using ::Deployment::StartError;

  ::Components::CCMObject_ptr comp_ref;

  if (!(any >>= comp_ref))
    throw StartError ("activate instance",  "invalid component reference");

  this->container_->activate_component (comp_ref);
}

//
// passivate_instance
//
template <typename HANDLER, typename ABSTRACT_HANDLER, typename CONTAINER>
void Component_Instance_Handler_T <HANDLER, ABSTRACT_HANDLER, CONTAINER>::
passivate_instance (const ::Deployment::DeploymentPlan & ,
                    ::CORBA::ULong index,
                    const ::CORBA::Any & any)
{
  using ::Deployment::StopError;

  ::Components::CCMObject_ptr comp_ref;

  if (!(any >>= comp_ref))
    throw StopError ("passivate instance", "invalid component reference");

  this->container_->passivate_component (comp_ref);

  ACE_UNUSED_ARG (index);
}

//
// remove_instance
//
template <typename HANDLER, typename ABSTRACT_HANDLER, typename CONTAINER>
void Component_Instance_Handler_T <HANDLER, ABSTRACT_HANDLER, CONTAINER>::
remove_instance (const ::Deployment::DeploymentPlan &,
                 ::CORBA::ULong index,
                 const ::CORBA::Any & any_ref)
{
  using ::Deployment::StopError;

  ::Components::CCMObject_ptr comp_ref;

  if (!(any_ref >>= comp_ref))
    throw StopError ("remove instance",  "invalid component reference");

  this->container_->uninstall_component (comp_ref);

  ACE_UNUSED_ARG (index);
}

//
// provide_endpoint_reference
//
template <typename HANDLER, typename ABSTRACT_HANDLER, typename CONTAINER>
void Component_Instance_Handler_T <HANDLER, ABSTRACT_HANDLER, CONTAINER>::
provide_endpoint_reference (const ::Deployment::DeploymentPlan & plan,
                            ::CORBA::ULong index,
                            ::CORBA::Any_out any_out)
{
  using ::Deployment::PlanConnectionDescription;
  using ::Deployment::PlanError;
  using ::Deployment::StartError;

  const PlanConnectionDescription & connection = plan.connection[index];
  ::CORBA::ULong length = connection.internalEndpoint.length ();

  for (::CORBA::ULong i = 0; i < length; ++ i)
  {
    // Get the next internal endpoint in the connection.
    using ::Deployment::PlanSubcomponentPortEndpoint;
    using ::Deployment::InstanceDeploymentDescription;

    const PlanSubcomponentPortEndpoint & ep = connection.internalEndpoint[i];

    if (!ep.provider)
      continue;

    const InstanceDeploymentDescription & idd = plan.instance[ep.instanceRef];

    // Locate the component reference in the container.
    ::CORBA::Object_var obj =
      this->container_->generate_reference (idd.name.in (),
                                            "",
                                            ::CIAO::Container_Types::COMPONENT_t);

    ACE_DEBUG ((LM_DEBUG,
                ACE_TEXT ("%T (%t) - %M - getting provider port %s:%s\n"),
                idd.name.in (),
                ep.portName.in ()));

    ::Components::CCMObject_var comp =
      ::Components::CCMObject::_narrow (obj.in ());

    if (::CORBA::is_nil (comp.in ()))
      throw StartError ("provide_endpoint_reference", "reference is not a component");

    // Finally, locate the correct connection type so that we can
    // return it to the client (or caller).
    switch (ep.kind)
    {
    case ::Deployment::EventConsumer:
      obj = comp->get_consumer (ep.portName.in ());
      break;

    case ::Deployment::Facet:
      obj = comp->provide_facet (ep.portName.in ());
      break;

    default:
      throw PlanError ("provide_endpoint_reference", "invalid connection type");
    }

    // Save the reference.
    ::CORBA::Any * retval = 0;
    ACE_NEW_THROW_EX (retval,
                      ::CORBA::Any (),
                      ::CORBA::NO_MEMORY ());

    any_out = retval;
    *any_out <<= obj;
    return;
  }

  throw PlanError ("provide_endpoint_reference", "provider endpoint not found");
}

//
// connect_instance
//
template <typename HANDLER, typename ABSTRACT_HANDLER, typename CONTAINER>
void Component_Instance_Handler_T <HANDLER, ABSTRACT_HANDLER, CONTAINER>::
connect_instance (const ::Deployment::DeploymentPlan & plan,
                  ::CORBA::ULong index,
                  const ::CORBA::Any & any_ref)
{
  using ::Deployment::PlanConnectionDescription;
  using ::Deployment::PlanError;
  using ::Deployment::StartError;

  const PlanConnectionDescription & connection = plan.connection[index];
  ::CORBA::ULong length = connection.internalEndpoint.length ();

  for (::CORBA::ULong i = 0; i < length; ++ i)
  {
    // Get the next internal endpoint in the connection.
    using ::Deployment::PlanSubcomponentPortEndpoint;
    using ::Deployment::InstanceDeploymentDescription;

    const PlanSubcomponentPortEndpoint & ep = connection.internalEndpoint[i];

    if (ep.provider)
      continue;

    const InstanceDeploymentDescription & idd = plan.instance[ep.instanceRef];

    // Locate the component reference in the container.
    ::CORBA::Object_var obj =
      this->container_->generate_reference (idd.name.in (),
                                            "",
                                            ::CIAO::Container_Types::COMPONENT_t);

    ACE_DEBUG ((LM_DEBUG,
                ACE_TEXT ("%T (%t) - %M - connecting to port %s:%s\n"),
                idd.name.in (),
                ep.portName.in ()));

    ::Components::CCMObject_var comp =
      ::Components::CCMObject::_narrow (obj.in ());

    if (::CORBA::is_nil (comp.in ()))
      throw StartError ("connect_instance", "reference is not a component");

    if (!(any_ref >>= CORBA::Any::to_object (obj)))
      throw StartError ("connect_instance", "failed to extract object");

    if (::CORBA::is_nil (obj.in ()))
      throw StartError ("connect_instance", "any is not an object");

    // Finally, locate the correct connection type so that we can
    // return it to the client (or caller).
    switch (ep.kind)
    {
    case ::Deployment::EventPublisher:
      {
        ACE_DEBUG ((LM_DEBUG,
                    ACE_TEXT ("%T (%t) - %M - connecting an event publisher\n")));

        ::Components::EventConsumerBase_var consumer =
          ::Components::EventConsumerBase::_narrow (obj.in ());

        if (::CORBA::is_nil (consumer.in ()))
        {
          ACE_DEBUG ((LM_DEBUG,
                      ACE_TEXT ("%T (%t) - %M - endpoint <%s> is not an event consumer\n"),
                      ep.portName.in ()));

          throw StartError ("connect_instance", "object is not an EventConsumerBase");
        }

        // Subscribe the consumer the correct port.
        ::Components::Cookie_var cookie = 
          comp->subscribe (ep.portName.in (), consumer);

        // Save this cookie in the components registry.
        this->cookies_[idd.name.in ()].insert (cookie);
      }
      break;

    case ::Deployment::EventEmitter:
      {
        ACE_DEBUG ((LM_DEBUG,
                    ACE_TEXT ("%T (%t) - %M - connecting to an event emitter\n")));

        ::Components::EventConsumerBase_var consumer =
          ::Components::EventConsumerBase::_narrow (obj.in ());

        if (::CORBA::is_nil (consumer.in ()))
          throw StartError ("connect_instance", "object is not an EventConsumerBase");

        // Just connect the emitter to the correct port. This is probably
        // the most simple connection to make.
        comp->connect_consumer (ep.portName.in (), consumer);
      }
      break;

    case ::Deployment::SimplexReceptacle:
      {
        ::CORBA::Object_ptr consumer = ::CORBA::Object::_narrow (obj.in ());
        if (::CORBA::is_nil (consumer))
          throw StartError ("connect_instance", "object is not a CORBA::Object");

        comp->connect (ep.portName.in (), consumer);
      }
      break;

    case ::Deployment::MultiplexReceptacle:
      throw PlanError ("provide_endpoint_reference", "receptacle connections not supports");
      break;

    default:
      ACE_DEBUG ((LM_DEBUG,
                  ACE_TEXT ("%T (%t) - %M - invalid connection type\n")));

      throw PlanError ("provide_endpoint_reference", "invalid connection type");
    }

    return;
  }

  throw PlanError ("provide_endpoint_reference", "provider endpoint not found");
}

//
// disconnect_instance
//
template <typename HANDLER, typename ABSTRACT_HANDLER, typename CONTAINER>
void Component_Instance_Handler_T <HANDLER, ABSTRACT_HANDLER, CONTAINER>::
disconnect_instance (const ::Deployment::DeploymentPlan & p, ::CORBA::ULong index)
{
  ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("%T (%t) - %M - disconnect_instance (%d)\n"),
              index));
  ACE_UNUSED_ARG (p);
}

//
// configure
//
template <typename HANDLER, typename ABSTRACT_HANDLER, typename CONTAINER>
void Component_Instance_Handler_T <HANDLER, ABSTRACT_HANDLER, CONTAINER>::
configure (const ::Deployment::Properties & prop)
{
  using ::Deployment::StartError;

  // Cache the global ORB. We should eventually use different
  // subclasses that determine what ORB to use (e.g., DAnCE vs.
  // the global/default ORB).  We are going to use this to
  // create and activate the handler's POA.
  int argc = 0;
  ACE_ARGV_T <char> tmp_args ("");
  this->orb_ = ::CORBA::ORB_init (argc, tmp_args.argv ());
  ::CORBA::Object_var obj = this->orb_->resolve_initial_references ("RootPOA");

  if (::CORBA::is_nil (obj.in ()))
    throw StartError ("component instance handler", "failed to locate RootPOA");

  this->poa_ = ::PortableServer::POA::_narrow (obj.in ());

  if (::CORBA::is_nil (this->poa_.in ()))
    throw StartError ("component instance handler", "object is not a POA");

  // Finally, register the value types with the ORB.
  this->register_valuetypes (this->orb_.in ());

  // Create the one and only container. We need to pass a reference to
  // the concrete (or subclass) handler. In the new future, we will add
  // support for multiple containers!
  CONTAINER * temp = 0;
  HANDLER * handler = dynamic_cast <HANDLER *> (this);

  ACE_NEW_THROW_EX (temp,
    CONTAINER (handler, this->poa_.in ()),
    ::CORBA::NO_MEMORY ());

  this->container_.reset (temp);

  // Handle properties
  iCCM::PLUGIN_MANAGER::instance ()->handle_properties (prop);

#ifdef REMOVE_IF_WORKS
  auto num_properties = prop.length ();
  for (unsigned int i = 0; i < num_properties; ++i) 
  {
    ::Deployment::Property p = prop[i];
    std::stringstream name;

    name << p.name;

    // Handle CPU Affinity property
    if (name.str () == "edu.vanderbilt.dre.DAnCE.LocalityManager.CPUAffinity")
    {
      // Pull value out of the property
      // We're expecting a string
      const char * aff_str;
      std::stringstream affinity_stream;

      if (p.value >>= aff_str)
      {
        affinity_stream << aff_str;
      }
      else
      {
        // Property was malformed somehow.
        throw std::runtime_error ("CPUAffinity has invalid type (expected string)");
      }

#ifdef ACE_HAS_PTHREADS

      // Setup cpu_set
      cpu_set_t cpuset;
      CPU_ZERO (&cpuset);

      // Setup property value

      int core;
      while (affinity_stream >> core);
      {
        
        CPU_SET (core, &cpuset);
      }

      ACE_hthread_t thread_id = pthread_self();
      ACE_OS::thr_set_affinity (thread_id, sizeof (cpuset), &cpuset);

#endif //ACE_HAS_PTHREADS

#ifdef ACE_WIN32
      HANDLE process = GetCurrentProcess ();
      DWORD_PTR mask = 0;

      int core;
      while (affinity_stream >> core)
      {
        mask |= (1 << (std::stoi (core_string) - 1));
      }

      if (!SetProcessAffinityMask (process, mask))
        throw std::runtime_error ("Could not set CPU affinity");
#endif
    }
  }
#endif
}

//
// instance_configured
//
template <typename HANDLER, typename ABSTRACT_HANDLER, typename CONTAINER>
void Component_Instance_Handler_T <HANDLER, ABSTRACT_HANDLER, CONTAINER>::
instance_configured (const ::Deployment::DeploymentPlan & plan,
                     ::CORBA::ULong index)
{
  using ::Deployment::InstanceDeploymentDescription;
  using ::Deployment::MonolithicDeploymentDescription;
  using ::Deployment::PlanError;
  using ::Deployment::StartError;

  const InstanceDeploymentDescription & idd = plan.instance[index];

  // Get a reference for this object.
  ::CORBA::Object_var obj =
      this->container_->generate_reference (idd.name.in (),
                                            "",
                                            ::CIAO::Container_Types::COMPONENT_t);

  ::Components::CCMObject_var comp =
    ::Components::CCMObject::_narrow (obj.in ());

  if (::CORBA::is_nil (comp.in ()))
    throw StartError ("provide_endpoint_reference", "reference is not a component");

  ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("%T (%t) - %M - notifying %s that configuration ")
              ACE_TEXT ("is complete\n"),
              idd.name.in ()));

  // Invoke the configuration complete method on the component.
  comp->configuration_complete ();

  ACE_DEBUG ((LM_DEBUG,
          ACE_TEXT ("%T (%t) - %M - %s configuration is ready"),
          idd.name.in ()));
}

//
// get_implementation
//
template <typename HANDLER, typename ABSTRACT_HANDLER, typename CONTAINER>
const char *
Component_Instance_Handler_T <HANDLER, ABSTRACT_HANDLER, CONTAINER>::
get_implementation (const char *name, const ::Deployment::DeploymentPlan &plan)
{
  if (name == 0)
    throw ::Deployment::PlanError (name, "no such artifact");

  const ::CORBA::ULong length = plan.artifact.length ();

  for (CORBA::ULong i = 0; i < length; ++ i)
  {
    if (0 == ACE_OS::strcmp (plan.artifact[i].name.in (), name))
    {
      if (plan.artifact[i].location.length () >= 1 &&
          plan.artifact[i].location[0] != 0)
        return plan.artifact[i].location[0].in ();

      ACE_ERROR ((LM_ERROR,
                  ACE_TEXT ("%T - %M - no valid location for artifact %s\n"),
                  name));

      throw ::Deployment::PlanError (name, "invalid location field");
    }
  }

  ACE_ERROR ((LM_ERROR,
              ACE_TEXT ("%T - %M - unable to locate artifact %s\n"),
              name));

  throw ::Deployment::PlanError (name, "artifact non-existant");
}

//
// create_attribute_configuration
//
template <typename HANDLER, typename ABSTRACT_HANDLER, typename CONTAINER>
void Component_Instance_Handler_T <HANDLER, ABSTRACT_HANDLER, CONTAINER>::
create_attribute_configuration (const ::Deployment::Properties &props,
                                ::Components::ConfigValues & values)
{
  ::CORBA::ULong length = props.length ();
  values.length (length);

  for (CORBA::ULong i = 0; i < props.length (); ++ i)
  {
    const ::Deployment::Property & p = props[i];
    ::Components::ConfigValue_var value;

    ACE_NEW_THROW_EX (value,
                      ::OBV_Components::ConfigValue (),
                      ::CORBA::NO_MEMORY ());

    value->name (p.name);
    value->value (p.value);

    values[i] = value;
  }
}

//
// register_valuetypes
//
template <typename HANDLER, typename ABSTRACT_HANDLER, typename CONTAINER>
void Component_Instance_Handler_T <HANDLER, ABSTRACT_HANDLER, CONTAINER>::
register_valuetypes (::CORBA::ORB_ptr orb)
{
  ::CORBA::ValueFactory_var prev;

  prev = orb->register_value_factory (
    Cookie::_tao_obv_static_repository_id (),
    new Cookie_Factory ());

  prev = orb->register_value_factory (
    ::Components::ConfigValue::_tao_obv_static_repository_id (),
    new ::Components::ConfigValue_init ());
}

}
