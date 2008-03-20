// $Id$

#include "BE_Assembly_Generator.h"

#if !defined (__CUTS_INLINE__)
#include "BE_Assembly_Generator.inl"
#endif

#include "BE_Assembly_Generator_Preprocessor.h"
#include "BE_Position.h"
#include "BE_Scope_Manager.h"
#include "CoWorkEr_Cache.h"
#include "BE_CUTS_Project.h"
#include "modelgen.h"

// BOOST headers
#include "boost/bind.hpp"

// UDM headers
#include "Uml.h"

static const char *
COWORKER_COMPONENTIMPLEMENTATIONS = "CoWorkEr_ComponentImplementations";

//
// Visit_RootFolder
//
void CUTS_BE_Assembly_Generator::
Visit_RootFolder (const PICML::RootFolder & folder)
{
  // Preprocess to project and determine if we need to generate 
  // any CUTS assemblies.
  CUTS_BE_Assembly_Generator_Preprocessor preprocessor (this->build_list_);
  PICML::RootFolder (folder).Accept (preprocessor);

  if (this->build_list_.empty ())
    return;

  // We need to locate the <CoWorkEr_ComponentImplementations> folder
  // or create one since this is where all the <CoWorkErs> will be
  // placed.

  typedef std::vector <PICML::ComponentImplementations> Folder_Set;
  Folder_Set folders = folder.ComponentImplementations_children ();

  if (Udm::contains (
      boost::bind (std::equal_to <std::string> (),
                   COWORKER_COMPONENTIMPLEMENTATIONS,
                   boost::bind (&PICML::ComponentImplementations::name,
                                _1))) (folder, this->target_folder_))
  {
    // Now that we have found the target folder, we need to process
    // the assemblies in the build order derived by the preprocessor.
    std::for_each (this->build_list_.begin (),
                   this->build_list_.end (),
                   boost::bind (&build_list_type::value_type::Accept,
                                _1,
                                boost::ref (*this)));
  }
  else
  {
    // The user needs to run the CoWorkEr generator first.
  }
}

//
// Visit_ComponentImplementations
//
void CUTS_BE_Assembly_Generator::
Visit_ComponentImplementations (const PICML::ComponentImplementations & folder)
{
  // We need to ignore all folders that contain the CUTS_ and 
  // CoWorkEr_.
  std::string name = folder.name ();

  if (name.find ("CUTS_") == std::string::npos &&
      name.find ("CoWorkEr_") == std::string::npos)
  {
    typedef std::vector <PICML::ComponentImplementationContainer> Container_Set;
    Container_Set containers = folder.ComponentImplementationContainer_children ();

    std::for_each (containers.begin (),
                   containers.end (),
                   boost::bind (&Container_Set::value_type::Accept,
                                _1,
                                boost::ref (*this)));
  }
}

//
// Visit_ComponentImplementations
//
void CUTS_BE_Assembly_Generator::
Visit_ComponentImplementationContainer (
  const PICML::ComponentImplementationContainer & container)
{
  std::string path = container.getPath2 (".", false);

  // Validate this parent folder is not a prexisting CUTS or CoWorker
  // container. We ignore these since they are not user defined
  PICML::ComponentImplementations folder = 
    PICML::ComponentImplementations::Cast (container.parent ());

  std::string name = folder.name ();

  if (name.find ("CUTS_") == std::string::npos &&
      name.find ("CoWorkEr_") == std::string::npos)
  {
    // Validate the contain exist in the target folder.
    typedef std::vector <PICML::ComponentImplementationContainer> Container_Set;

    Container_Set containers = 
      this->target_folder_.ComponentImplementationContainer_children ();

    name = std::string (container.name ()) + "_CoWorkEr";

    // We need to find the "target" container for this container.
    if (Udm::create_if_not (this->target_folder_, this->target_container_,
        Udm::contains (boost::bind (std::equal_to <std::string> (),
                       name,
                       boost::bind (&PICML::ComponentImplementationContainer::name,
                                    _1)))))
    {
      this->target_container_.SetStrValue ("name", name);
    }
  }
  else
  {
    // Reset the container.
    this->target_container_ = 
      PICML::ComponentImplementationContainer::Cast (Udm::null);
  }
}

//
// Visit_ComponentImplementation
//
void CUTS_BE_Assembly_Generator::
Visit_ComponentImplementation (const PICML::ComponentImplementation & impl)
{
  if (impl.type () == PICML::ComponentAssembly::meta)
  {
    PICML::MgaObject parent = impl.parent ();
    std::string name = std::string (parent.name ()) + "_CoWorkEr";

    // We need to find the "target" container for this container.
    if (Udm::create_if_not (this->target_folder_, this->target_container_,
        Udm::contains (boost::bind (std::equal_to <std::string> (),
                       name,
                       boost::bind (&PICML::ComponentImplementationContainer::name,
                                    _1)))))
    {
      this->target_container_.SetStrValue ("name", name);
    }

    // We can now visit the assembly to create the proxies.
    PICML::ComponentAssembly assembly = PICML::ComponentAssembly::Cast (impl);
    assembly.Accept (*this);
  }
}

//
// Visit_ComponentAssembly
//
void CUTS_BE_Assembly_Generator::
Visit_ComponentAssembly (const PICML::ComponentAssembly & assembly)
{
  if (!assembly.isInstance ())
  {
    // We are generating a proxy assembly for an actual assembly.
    PICML::ComponentImplementationContainer parent =
      PICML::ComponentImplementationContainer::Cast (assembly.parent ());

    // Visit the containers parent to validate it has been created
    // in the target folder.
    parent.Accept (*this);

    if (this->target_container_ == Udm::null)
      return;

    // Validate that the container contains a CoWorkEr assembly for this
    // assembly.
    std::string name = assembly.name ();

    if (Udm::create_if_not (this->target_container_, this->target_assembly_,
        Udm::contains (boost::bind (std::equal_to <std::string> (),
                       name,
                       boost::bind (&PICML::ComponentAssembly::name, _1)))))
    {
      this->target_assembly_.SetStrValue ("name", name);
    }

    // Set the position of the assembly.
    this->target_assembly_.position () = assembly.position ();

    // Save the component assemblies to their respective maps 
    // for later usage.
    std::string path = assembly.getPath2 (".");
    this->assembly_map_.insert (std::make_pair (path, this->target_assembly_));

    // Visit all the component assemblies in this assembly. We need to 
    // create instances of each component assembly.
    typedef std::vector <PICML::ComponentAssembly> ComponentAssembly_Set;
    ComponentAssembly_Set assemblies = assembly.ComponentAssembly_children ();

    std::for_each (assemblies.begin (),
                   assemblies.end (),
                   boost::bind (&ComponentAssembly_Set::value_type::Accept,
                                _1,
                                boost::ref (*this)));

    // Visit all the components in the assembly.
    typedef std::vector <PICML::Component> Component_Set;
    Component_Set components = assembly.Component_children ();

    std::for_each (components.begin (),
                   components.end (),
                   boost::bind (&Component_Set::value_type::Accept,
                                _1,
                                boost::ref (*this)));

    // Create all the port delegations of this component assembly.
    typedef std::vector <PICML::EventSinkDelegate> EventSinkDelegate_set;
    EventSinkDelegate_set sink_delegates = assembly.EventSinkDelegate_children ();

    std::for_each (sink_delegates.begin (),
                   sink_delegates.end (),
                   boost::bind (&EventSinkDelegate_set::value_type::Accept,
                                _1,
                                boost::ref (*this)));

    // Create all the port delegations of this component assembly.
    typedef std::vector <PICML::EventSourceDelegate> EventSourceDelegate_set;
    EventSourceDelegate_set src_delegates = assembly.EventSourceDelegate_children ();

    std::for_each (src_delegates.begin (),
                   src_delegates.end (),
                   boost::bind (&EventSourceDelegate_set::value_type::Accept,
                                _1,
                                boost::ref (*this)));

    // Visit all the emit connections in the assembly.
    typedef std::vector <PICML::emit> emit_Set;
    emit_Set emits = assembly.emit_children ();

    std::for_each (emits.begin (),
                   emits.end (),
                   boost::bind (&emit_Set::value_type::Accept,
                                _1,
                                boost::ref (*this)));

    // Visit all the <publish> connections in the <assembly>.
    typedef std::vector <PICML::publish> publish_Set;
    publish_Set publishes = assembly.publish_kind_children ();

    std::for_each (publishes.begin (),
                   publishes.end (),
                   boost::bind (&publish_Set::value_type::Accept,
                                _1,
                                boost::ref (*this)));

    // Visit all the <invokes> connections in the <assembly>.
    typedef std::vector <PICML::invoke> invoke_Set;
    invoke_Set invokes = assembly.invoke_kind_children ();

    std::for_each (invokes.begin (),
                   invokes.end (),
                   boost::bind (&invoke_Set::value_type::Accept,
                                _1,
                                boost::ref (*this)));
  }
  else
  {
    // We are handling an instance in a component assembly, which
    // is contained in another component assembly.
    PICML::ComponentAssembly assembly_type = 
      PICML::ComponentAssembly (assembly).Archetype ();

    // Get the CoWorkEr assembly type for the assembly instance.
    std::string path = assembly_type.getPath2 (".");
    PICML::ComponentAssembly coworker_assembly_type = this->assembly_map_[path];

    // Create an instance of the CoWorkEr assembly.
    PICML::ComponentAssembly assembly_instance;
    std::string name = assembly.name ();

    if (Udm::create_instance_if_not (
          this->target_assembly_,
          coworker_assembly_type, 
          assembly_instance,
          Udm::contains (boost::bind (std::equal_to <std::string> (),
                          name,
                          boost::bind (&PICML::ComponentAssembly::name,
                                      _1)))))
    {
      assembly_instance.SetStrValue ("name", name);
    }

    // Update the position of the assembly instance.
    if (std::string (assembly_instance.position ()) !=
        std::string (assembly.position ()))
    {
      assembly_instance.position () = assembly.position ();
    }

    // Save the corresponding coworker instance for this assembly.
    path = assembly.getPath2 ("."); 
    this->assembly_instance_map_.insert (std::make_pair (path, assembly_instance));
  }
}

//
// Visit_Component
//
void CUTS_BE_Assembly_Generator::
Visit_Component (const PICML::Component & component)
{
  // Get the interface type of this component.
  PICML::Component proxy_type;
  PICML::Component interface_type =
    PICML::Component::Cast (component.archetype ());

  if (this->locate_proxy_type (interface_type, proxy_type))
  {
    // We should first search for an instance of the specified type
    // that has the same name. If we can't find it, when we should
    // create one.

    PICML::Component proxy_component;
    std::string name = component.name ();

    if (Udm::create_instance_if_not (this->target_assembly_,
        proxy_type, proxy_component,
        Udm::contains (boost::bind (std::logical_and <bool> (),
          boost::bind (std::equal_to <std::string> (),
                       name,
                       boost::bind (&PICML::Component::name, _1)),
          boost::bind (std::equal_to <Udm::Object> (),
                       proxy_type,
                       boost::bind (&Udm::Object::archetype, _1))))))
    {
      // Update the <proxy> so that it matches its <component>. We however,
      // are going to move the <proxy_component> down some to make space
      // for the <cuts_proxy_impl> property.
      proxy_component.name () = component.name ();

      //CUTS_BE_Position pos;
      //pos << component;
      //pos.translate (0, 50);
      //pos >> proxy_component;
    }

    // Update the position of the generated component.
    if (std::string (proxy_component.position ()) != 
        std::string (component.position ()))
    {
      proxy_component.position () = component.position ();
    }

    // Locate the <cuts_proxy_impl> attribute. This is need to configure
    // the proxy to load the correct implementation.
    typedef std::vector <PICML::Attribute> Attribute_Set;
    Attribute_Set attributes = proxy_component.Attribute_kind_children ();

    PICML::Attribute attribute;
    PICML::Property property;
    std::string propval;

    if (Udm::contains (boost::bind (std::equal_to <std::string> (),
                       "cuts_proxy_impl",
                       boost::bind (&PICML::Attribute::name,
                                    _1))) (proxy_component, attribute))
    {
      if (this->create_attribute_property (attribute,
                                           this->target_assembly_,
                                           property))
      {
        // Create the property value for cuts_proxy_impl.
        this->locate_executor_entry_point (interface_type);
        propval = this->artifact_name_ + ":" + this->entry_point_;

        if (std::string (property.DataValue ()) != propval)
          property.DataValue () = propval;
      }
    }

    // Save the proxy by name for later usage.
    this->proxy_map_.insert (
      std::make_pair (proxy_component.name (), proxy_component));

    // We need to make sure their is a property set for the
    // name of the proxy.
    if (Udm::contains (boost::bind (std::equal_to <std::string> (),
                       "cuts_name",
                       boost::bind (&PICML::Attribute::name,
                                    _1))) (proxy_component, attribute))
    {
      if (this->create_attribute_property (attribute,
                                           this->target_assembly_,
                                           property))
      {
        this->generate_scoped_instance_name (component, propval);

        if (std::string (property.DataValue ()) != propval)
          property.DataValue () = propval;
      }
    }
  }
}

//
// Visit_OutEventPort
//
void CUTS_BE_Assembly_Generator::
Visit_OutEventPort (const PICML::OutEventPort & outevent)
{
  // Get the parent of the <inevent>. This could be a component
  // or an component assembly. Ideally, we should be ask for the 
  // ComponentImplementation, which could be an component or an 
  // assembly.
  Udm::Object parent = outevent.parent ();
  Uml::Class type = parent.type ();

  if (type == PICML::Component::meta)
  {
    // Get the parent of the <outevent>.
    PICML::Component component =
      PICML::Component::Cast (outevent.parent ());

    // Get the proxy that has the same name as <component>.
    PICML::Component proxy_component = this->proxy_map_[component.name ()];

    // Get all the output ports for the <proxy_component>.
    // Get all the input ports for the <proxy_component>.
    if (!Udm::contains (boost::bind (std::equal_to <std::string> (),
                        outevent.name (),
                        boost::bind (&PICML::OutEventPort::name,
                                    _1))) (proxy_component,
                                           this->target_outevent_))
    {
      this->target_outevent_ = PICML::OutEventPort::Cast (Udm::null);
    }
  }
  else if (type == PICML::ComponentAssembly::meta)
  {
    // Get the assembly parent of the InEventPort.
    PICML::ComponentAssembly assembly =
      PICML::ComponentAssembly::Cast (parent).Archetype ();

    // Locate the coworker for this assembly.
    std::string path = assembly.getPath2 (".");
    PICML::ComponentAssembly coworker_assembly = this->assembly_map_[path];

    // Get all the input ports for the <proxy_component>.
    if (!Udm::contains (boost::bind (std::equal_to <std::string> (),
                        outevent.name (),
                        boost::bind (&PICML::OutEventPort::name,
                                     _1))) (coworker_assembly,
                                            this->target_outevent_))
    {
      this->target_outevent_ = PICML::OutEventPort::Cast (Udm::null);
    }
  }
  else
  {
    // We have an unknown type.
  }
}

//
// Visit_InEventPort
//
void CUTS_BE_Assembly_Generator::
Visit_InEventPort (const PICML::InEventPort & inevent)
{
  // Get the parent of the <inevent>. This could be a component
  // or an component assembly. Ideally, we should be ask for the 
  // ComponentImplementation, which could be an component or an 
  // assembly.
  Udm::Object parent = inevent.parent ();
  Uml::Class type = parent.type ();

  if (type == PICML::Component::meta)
  {
    // Get the proxy that has the same name as <component>.
    PICML::Component component = PICML::Component::Cast (parent);
    PICML::Component proxy_component = this->proxy_map_[component.name ()];

    // Get all the input ports for the <proxy_component>.
    if (!Udm::contains (boost::bind (std::equal_to <std::string> (),
                        inevent.name (),
                        boost::bind (&PICML::InEventPort::name,
                                    _1))) (proxy_component,
                                           this->target_inevent_))
    {
      this->target_inevent_ = PICML::InEventPort::Cast (Udm::null);
    }
  }
  else if (type == PICML::ComponentAssembly::meta)
  {
    PICML::ComponentAssembly assembly = 
      PICML::ComponentAssembly::Cast (parent);

    // Get the name of the port of interest.
    std::string name = inevent.name ();

    // If the parent assembly is not an instance, then we are 
    // creating a port on the assembly. Otherwise, we are connection
    // to an exposed port of the assembly.
    if (!parent.isInstance ())
    {
      // Get all the InEventPort elements of the assembly.
      typedef std::vector <PICML::InEventPort> InEventPort_set;
      InEventPort_set inevents = assembly.InEventPort_children ();

      if (Udm::create_if_not (this->target_assembly_, this->target_inevent_,
          Udm::contains (boost::bind (std::equal_to <std::string> (),
                         name,
                         boost::bind (&PICML::InEventPort::name, _1)))))
      {
        this->target_inevent_.SetStrValue ("name", name);
      }

      // Validate the event type if correct.
      if (PICML::Event (this->target_inevent_.ref ()) != 
          PICML::Event (inevent.ref ()))
      {
        this->target_inevent_.ref () = inevent.ref ();
      }

      // Update the position of the port.
      if (std::string (this->target_inevent_.position ()) != 
          std::string (inevent.position ()))
      {
        this->target_inevent_.position () = inevent.position ();
      }

      // Validate the attributes of the port.
    }
    else
    {
      // Locate the coworker assembly for this assembly instance.
      std::string path = assembly.getPath2 (".");

      PICML::ComponentAssembly coworker_assembly = 
        this->assembly_instance_map_[path];

      // Get all the input ports for the <proxy_component>.
      if (!Udm::contains (boost::bind (std::equal_to <std::string> (),
          name, boost::bind (&PICML::InEventPort::name, _1))) (
            coworker_assembly, this->target_inevent_))
      {
        this->target_inevent_ = PICML::InEventPort::Cast (Udm::null);
      }
    }
  }
  else
  {
    // We have an unknown type.
  }
}

//
// Visit_ProvidedRequestPort
//
void CUTS_BE_Assembly_Generator::
Visit_ProvidedRequestPort (const PICML::ProvidedRequestPort & facet)
{
  // Get the parent of the <inevent>. This could be a component
  // or an component assembly. Ideally, we should be ask for the 
  // ComponentImplementation, which could be an component or an 
  // assembly.
  Udm::Object parent = facet.parent ();
  Uml::Class type = parent.type ();

  if (type == PICML::Component::meta)
  {
    // Get the parent of the <inevent>.
    PICML::Component component = PICML::Component::Cast (parent);

    // Get the proxy that has the same name as <component>.
    PICML::Component proxy_component = this->proxy_map_[component.name ()];

    // Get all the input ports for the <proxy_component>.
    if (!Udm::contains (boost::bind (std::equal_to <std::string> (),
                        facet.name (),
                        boost::bind (&PICML::ProvidedRequestPort::name,
                                    _1))) (proxy_component,
                                            this->target_facet_))
    {
      this->target_facet_ = PICML::ProvidedRequestPort::Cast (Udm::null);
    }
  }
  else if (type == PICML::ComponentAssembly::meta)
  {
    // Get the assembly parent of the InEventPort.
    PICML::ComponentAssembly assembly =
      PICML::ComponentAssembly::Cast (parent).Archetype ();

    // Locate the coworker for this assembly.
    std::string path = assembly.getPath2 (".");
    PICML::ComponentAssembly coworker_assembly = this->assembly_map_[path];

    // Get all the input ports for the <proxy_component>.
    if (!Udm::contains (boost::bind (std::equal_to <std::string> (),
                        facet.name (),
                        boost::bind (&PICML::ProvidedRequestPort::name,
                                     _1))) (coworker_assembly,
                                            this->target_receptacle_))
    {
      this->target_facet_ = PICML::ProvidedRequestPort::Cast (Udm::null);
    }
  }
  else
  {
    // We have an unknown type.
  }
}

//
// Visit_RequiredRequestPort
//
void CUTS_BE_Assembly_Generator::
Visit_RequiredRequestPort (const PICML::RequiredRequestPort & receptacle)
{
  // Get the parent of the <inevent>. This could be a component
  // or an component assembly. Ideally, we should be ask for the 
  // ComponentImplementation, which could be an component or an 
  // assembly.
  Udm::Object parent = receptacle.parent ();
  Uml::Class type = parent.type ();

  if (type == PICML::Component::meta)
  {
    // Get the parent of the <inevent>.
    PICML::Component component =
      PICML::Component::Cast (receptacle.parent ());

    // Get the proxy that has the same name as <component>.
    PICML::Component proxy_component = this->proxy_map_[component.name ()];

    // Get all the input ports for the <proxy_component>.
    if (!Udm::contains (boost::bind (std::equal_to <std::string> (),
                        receptacle.name (),
                        boost::bind (&PICML::ProvidedRequestPort::name,
                                    _1))) (proxy_component,
                                           this->target_receptacle_))
    {
      this->target_receptacle_ = PICML::RequiredRequestPort::Cast (Udm::null);
    }
  }
  else if (type == PICML::ComponentAssembly::meta)
  {
    // Get the assembly parent of the InEventPort.
    PICML::ComponentAssembly assembly =
      PICML::ComponentAssembly::Cast (parent).Archetype ();

    // Locate the coworker for this assembly.
    std::string path = assembly.getPath2 (".");
    PICML::ComponentAssembly coworker_assembly = this->assembly_map_[path];

    // Get all the input ports for the <proxy_component>.
    if (!Udm::contains (boost::bind (std::equal_to <std::string> (),
                        receptacle.name (),
                        boost::bind (&PICML::RequiredRequestPort::name,
                                     _1))) (coworker_assembly,
                                            this->target_receptacle_))
    {
      this->target_receptacle_ = PICML::RequiredRequestPort::Cast (Udm::null);
    }
  }
  else
  {
    // We have an unknown type.
  }
}

//
// Visit_publish
//
void CUTS_BE_Assembly_Generator::
Visit_publish (const PICML::publish & publish)
{
  // Locate the correct output port on the proxy.
  PICML::OutEventPort outevent = publish.srcpublish_end ();
  outevent.Accept (*this);

  if (this->target_outevent_ != Udm::null)
  {
    PICML::publish target_publish;

    // We only need to create a publish connection if one does not
    // already exist. We are not concerned with shared components at
    // this moment.
    if (Udm::create_if_not (this->target_assembly_, target_publish,
        Udm::contains (boost::bind (std::equal_to <PICML::OutEventPort> (),
                       this->target_outevent_,
                       boost::bind (&PICML::publish::srcpublish_end, _1)))))
    {
      // Create a new publish connector and attach it to the newly
      // created connection object.
      this->target_connector_ =
        PICML::PublishConnector::Create (this->target_assembly_);

      target_publish.srcpublish_end () = this->target_outevent_;
      target_publish.dstpublish_end () = this->target_connector_;
    }
    else
    {
      this->target_connector_ = target_publish.dstpublish_end ();
    }

    // Make sure the location of the connector in the CoWorkEr
    // assembly is in the same location as its counterpart.
    PICML::PublishConnector connector = publish.dstpublish_end ();
    connector.Accept (*this);
  }
}

//
// Visit_emit
//
void CUTS_BE_Assembly_Generator::
Visit_emit (const PICML::emit & emit)
{
  // Visit the <InEventPort> for this connection.
  PICML::InEventPort inevent = emit.dstemit_end ();
  inevent.Accept (*this);

  // Visit the <OutEventPort> for this connection.
  PICML::OutEventPort outevent = emit.srcemit_end ();
  outevent.Accept (*this);

  if (this->target_inevent_ != Udm::null &&
      this->target_outevent_ != Udm::null)
  {
    // We need to create a emits connection in the target assembly
    // if we are not able to find an existing one for the target
    // in and out event ports.
    PICML::emit target_emit;

    if (Udm::create_if_not (this->target_assembly_, target_emit,
        Udm::contains (boost::bind (std::logical_and <bool> (),
            boost::bind (std::equal_to <PICML::OutEventPort> (),
                         this->target_outevent_,
                         boost::bind (&PICML::emit::srcemit_end, _1)),
            boost::bind (std::equal_to <PICML::InEventPort> (),
                         this->target_inevent_,
                         boost::bind (&PICML::emit::dstemit_end, _1))))))
    {
      target_emit.srcemit_end () = this->target_outevent_;
      target_emit.dstemit_end () = this->target_inevent_;
    }
  }
}

//
// Visit_emit
//
void CUTS_BE_Assembly_Generator::
Visit_invoke (const PICML::invoke & invoke)
{
  // Visit the <InEventPort> for this connection.
  PICML::ProvidedRequestPort facet = invoke.dstinvoke_end ();
  facet.Accept (*this);

  // Visit the <OutEventPort> for this connection.
  PICML::RequiredRequestPort receptacle = invoke.srcinvoke_end ();
  receptacle.Accept (*this);

  if (this->target_facet_ != Udm::null && 
      this->target_receptacle_  != Udm::null)
  {
    // We need to create a emits connection in the target assembly
    // if we are not able to find an existing one for the target
    // in and out event ports.
    PICML::invoke target_invoke;

    if (Udm::create_if_not (this->target_assembly_, target_invoke,
        Udm::contains (boost::bind (std::logical_and <bool> (),
            boost::bind (std::equal_to <PICML::RequiredRequestPort> (),
                         this->target_receptacle_,
                         boost::bind (&PICML::invoke::srcinvoke_end, _1)),
            boost::bind (std::equal_to <PICML::ProvidedRequestPort> (),
                         this->target_facet_,
                         boost::bind (&PICML::invoke::dstinvoke_end, _1))))))
    {
      target_invoke.srcinvoke_end () = this->target_receptacle_;
      target_invoke.dstinvoke_end () = this->target_facet_;
    }
  }
}

//
// Visit_PublishConnector
//
void CUTS_BE_Assembly_Generator::
Visit_PublishConnector (const PICML::PublishConnector & connector)
{
  if (this->target_connector_ == Udm::null)
    return;

  // Make sure the connector in the coworker assembly is in the
  // correct location.
  this->target_connector_.position () = connector.position ();

  // We need to make sure the connector in the regular assembly
  // has all its outgoing connections in the coworker assembly.
  typedef std::set <PICML::deliverTo> deliverTo_Set;
  deliverTo_Set delivers = connector.dstdeliverTo ();

  std::for_each (delivers.begin (),
                 delivers.end (),
                 boost::bind (&deliverTo_Set::value_type::Accept,
                              _1,
                              boost::ref (*this)));
}

//
// Visit_deliverTo
//
void CUTS_BE_Assembly_Generator::
Visit_deliverTo (const PICML::deliverTo & deliverTo)
{
  // This will locate the correct input port on the proxy component.
  PICML::InEventPort inevent = deliverTo.dstdeliverTo_end ();
  inevent.Accept (*this);

  if (this->target_inevent_ != Udm::null)
  {
    PICML::deliverTo target_deliverTo;

    // We need to verify that we have a deliverTo connection in the
    // proxy assembly, such that is source is the <target_connector_>
    // and its destination is the <target_inevent_>.
    if (Udm::create_if_not (this->target_assembly_, target_deliverTo,
        Udm::contains (boost::bind (std::logical_and <bool> (),
          boost::bind (std::equal_to <PICML::PublishConnector> (),
                       this->target_connector_,
                       boost::bind (&PICML::deliverTo::srcdeliverTo_end, _1)),
          boost::bind (std::equal_to <PICML::InEventPort> (),
                       this->target_inevent_,
                       boost::bind (&PICML::deliverTo::dstdeliverTo_end, _1))))))
    {
      target_deliverTo.srcdeliverTo_end () = this->target_connector_;
      target_deliverTo.dstdeliverTo_end () = this->target_inevent_;
    }
  }
}

//
// locate_proxy
//
bool CUTS_BE_Assembly_Generator::
locate_proxy (const PICML::Component & component, PICML::Component & proxy)
{
  typedef std::vector <PICML::Component> Component_Set;
  Component_Set proxies = this->target_assembly_.Component_children ();

  // Locate the proxy component by its name.
  return Udm::contains (boost::bind (std::equal_to <std::string> (),
                        component.name (),
                        boost::bind (&PICML::Component::name,
                                     _1))) (this->target_assembly_, proxy);
}

//
// locate_proxy_type
//
bool CUTS_BE_Assembly_Generator::
locate_proxy_type (const PICML::Component & component,
                   PICML::Component & proxy)
{
  Proxy_Type_Map::
    const_iterator entry = this->proxy_type_map_.find (component);

  if (entry != this->proxy_type_map_.end ())
  {
    proxy = entry->second;
    return true;
  }

  // Locate the "proxy" that supports this interface. This mean we
  // have to search all the component's that are derived from this
  // component to locate the CoWorkEr proxy.

  typedef std::set <PICML::Component> Component_Set;
  Component_Set tmpset = Udm::DerivedAttr <PICML::Component> (component.__impl ());

  if (Udm::contains (
      boost::bind (&CUTS_CoWorkEr_Cache::is_coworker, _1)) (tmpset, proxy))
  {
    this->proxy_type_map_.insert (std::make_pair (component, proxy));
    return true;
  }
  else
    return false;
}

//
// locate_executor_entry_point
//
bool CUTS_BE_Assembly_Generator::
locate_executor_entry_point (const PICML::Component & component)
{
  // Erase the previous values.
  this->artifact_name_.clear ();
  this->entry_point_.clear ();

  // First, we need to locate the component implementation container
  // that contains a monolithic implementation for this component.
  typedef std::set <PICML::ComponentRef> ComponentRef_Set;
  ComponentRef_Set refs = component.referedbyComponentRef ();

  for (ComponentRef_Set::iterator iter = refs.begin ();
       iter != refs.end ();
       iter ++)
  {
    // Get the monolithic implementation in this container and visit
    // it. We need to locate the executor artifact.
    PICML::Implements implements = iter->srcImplements ();

    if (implements != Udm::null)
    {
      implements.Accept (*this);
      break;
    }
  }

  return !(this->artifact_name_.empty () || this->entry_point_.empty ());
}

//
// Visit_Implements
//
void CUTS_BE_Assembly_Generator::
Visit_Implements (const PICML::Implements & implements)
{
  PICML::MonolithicImplementation monoimpl =
    PICML::MonolithicImplementation::Cast (implements.srcImplements_end ());

  monoimpl.Accept (*this);
}

//
// Visit_MonolithicImplementation
//
void CUTS_BE_Assembly_Generator::
Visit_MonolithicImplementation (const PICML::MonolithicImplementation & monoimpl)
{
  typedef std::set <PICML::MonolithprimaryArtifact> primaryArtifact_Set;
  primaryArtifact_Set primaries = monoimpl.dstMonolithprimaryArtifact ();

  std::for_each (primaries.begin (),
                 primaries.end (),
                 boost::bind (&primaryArtifact_Set::value_type::Accept,
                              _1,
                              boost::ref (*this)));
}

//
// Visit_MonolithprimaryArtifact
//
void CUTS_BE_Assembly_Generator::
Visit_MonolithprimaryArtifact (const PICML::MonolithprimaryArtifact & primary)
{
  PICML::ImplementationArtifactReference ref =
    primary.dstMonolithprimaryArtifact_end ();

  PICML::ImplementationArtifact artifact = ref.ref ();

  if (artifact != Udm::null)
    artifact.Accept (*this);
}

//
// Visit_ImplementationArtifact
//
void CUTS_BE_Assembly_Generator::
Visit_ImplementationArtifact (const PICML::ImplementationArtifact & artifact)
{
  // Determine if this is the CIAO executor artifact. The artifact
  // will end in _exec.
  std::string name = artifact.name ();

  if (name.rfind ("_exec") == (name.length () - 5))
  {
    this->artifact_name_ = artifact.location ();

    typedef std::set <PICML::ArtifactExecParameter> ExecParameter_Set;
    ExecParameter_Set params = artifact.dstArtifactExecParameter ();

    std::for_each (params.begin (),
                   params.end (),
                   boost::bind (&ExecParameter_Set::value_type::Accept,
                                _1,
                                boost::ref (*this)));
  }
}

//
// Visit_ArtifactExecParameter
//
void CUTS_BE_Assembly_Generator::
Visit_ArtifactExecParameter (const PICML::ArtifactExecParameter & param)
{
  PICML::Property property = param.dstArtifactExecParameter_end ();

  if ((std::string) property.name () == "entryPoint")
    this->entry_point_ = property.DataValue ();
}

//
// create_attribute_property
//
bool CUTS_BE_Assembly_Generator::
create_attribute_property (const PICML::ReadonlyAttribute & attr,
                           const Udm::Object & parent,
                           PICML::Property & property)
{
  // Get the connection from the cuts_proxy_impl its property. If
  // we cannot find it, then we need to create one and attach it to
  // the connection.
  PICML::AttributeValue attrval = attr.dstAttributeValue ();

  if (attrval == Udm::null)
  {
    attrval = PICML::AttributeValue::Create (parent);
    attrval.srcAttributeValue_end () = attr;
  }

  // Get the property that is connected to the attribute value. If we
  // cannot find one, then we need to create one and attach it to
  // the connection.
  property = attrval.dstAttributeValue_end ();

  if (property == Udm::null)
  {
    // Create the new property and connect it with the attribute
    // value connection.
    property = PICML::Property::Create (parent);
    attrval.dstAttributeValue_end () = property;
  }

  if (std::string (property.name ()) != std::string (attr.name ()))
    property.name () = attr.name ();

  // We need to get the target attribute data type. We want to
  // reference the same data object in the property. This will
  // make life a LOT simplier.
  PICML::AttributeMember attr_member = attr.AttributeMember_child ();

  if (attr_member == Udm::null)
    return false;

  try
  {
    // Let's see what kind of member type we have in this attribute.
    PICML::MemberType member_type = attr_member.ref ();

    if (member_type == Udm::null)
      return false;

    PICML::PredefinedType target_type = 
      PICML::PredefinedType::Cast (member_type);

    if (target_type == Udm::null)
      return false;

    // Now that we have the predefined type of the attribute, we need
    // to validate the property containing a data type element.
    PICML::DataType datatype = property.DataType_child ();

    if (datatype == Udm::null)
      datatype = PICML::DataType::Create (property);

    // Make sure the name of the data type and the actual reference
    // to the predefined type is of <type>.
    if (std::string (datatype.name ()) != std::string (target_type.name ()))
      datatype.name () = target_type.name ();

    PICML::PredefinedType curr_type =
      PICML::PredefinedType::Cast (datatype.ref ());

    if (curr_type != target_type)
      datatype.ref () = target_type;

    return true;
  }
  catch (udm_exception & )
  {

  }

  return false;
}

//
// generate_scoped_instance_name
//
void CUTS_BE_Assembly_Generator::
generate_scoped_instance_name (const PICML::Component & component,
                               std::string & name)
{
  // Initialize the scoped name for the component instance.
  name = component.name ();
  PICML::MgaObject parent = component.parent ();

  do
  {
    name.insert (0, ".").insert (0, parent.name ());
    parent = PICML::MgaObject::Cast (parent.parent ());
  } while (parent.type () != PICML::ComponentImplementationContainer::meta);
}

//
// Visit_EventSourceDelegate
//
void CUTS_BE_Assembly_Generator::
Visit_EventSourceDelegate (const PICML::EventSourceDelegate & delegate)
{
  
}

//
// Visit_EventSinkDelegate
//
void CUTS_BE_Assembly_Generator::
Visit_EventSinkDelegate (const PICML::EventSinkDelegate & delegate)
{
  // Get the endpoints of the connection.
  PICML::InEventPort src = delegate.srcEventSinkDelegate_end ();
  PICML::InEventPort dst = delegate.dstEventSinkDelegate_end ();

  // Determine which of the ports is in this assembly. This is 
  // a really horrible design decision!!! The <src> port is in this
  // assembly. The <dst> port is the actual port on a component
  // or assembly.

  Udm::Object parent =
    delegate.parent (), src_parent = src.parent ();
  PICML::InEventPort tmp_port;

  if (src_parent == parent)
  {
    // The delegate port is the source.
    // 1. Create the delegation port in this assembly.
    std::string name = src.name ();

    // We only need to create a publish connection if one does not
    // already exist. We are not concerned with shared components at
    // this moment.
    if (Udm::create_if_not (this->target_assembly_, tmp_port,
        Udm::contains (boost::bind (std::equal_to <std::string> (),
                       name,
                       boost::bind (&PICML::InEventPort::name, _1)))))
    {
      tmp_port.SetStrValue ("name", name);
    }

    if (std::string (tmp_port.position ()) != 
        std::string (src.position ()))
    {
      tmp_port.position () = src.position ();
    }

    // 2. Get the target delegation port. It can be either in a
    // component or the assembly. Let the visitor function resolve
    // that for us.
    dst.Accept (*this);

    if (tmp_port == Udm::null || this->target_inevent_ == Udm::null)
      return;

    PICML::EventSinkDelegate target_delegate;

    if (Udm::create_if_not (this->target_assembly_, target_delegate,
        Udm::contains (boost::bind (std::logical_and <bool> (),
          boost::bind (std::equal_to <PICML::InEventPort> (),
                       tmp_port,
                       boost::bind (&PICML::EventSinkDelegate::srcEventSinkDelegate_end, _1)),
          boost::bind (std::equal_to <PICML::InEventPort> (),
                       this->target_inevent_,
                       boost::bind (&PICML::EventSinkDelegate::dstEventSinkDelegate_end, _1))))))
    {
      target_delegate.srcEventSinkDelegate_end () = tmp_port;
      target_delegate.dstEventSinkDelegate_end () = this->target_inevent_;
    }
  }
  else
  {
    // The delegate port is the destination.
    // 1. Create the delegation port in this assembly.
    std::string name = dst.name ();

    // We only need to create a publish connection if one does not
    // already exist. We are not concerned with shared components at
    // this moment.
    if (Udm::create_if_not (this->target_assembly_, tmp_port,
        Udm::contains (boost::bind (std::equal_to <std::string> (),
                       name,
                       boost::bind (&PICML::InEventPort::name, _1)))))
    {
      tmp_port.SetStrValue ("name", name);
    }

    if (std::string (tmp_port.position ()) != 
        std::string (dst.position ()))
    {
      tmp_port.position () = dst.position ();
    }

    // 2. Get the target delegation port. It can be either in a
    // component or the assembly. Let the visitor function resolve
    // that for us.
    src.Accept (*this);

    if (tmp_port == Udm::null || this->target_inevent_ == Udm::null)
      return;

    PICML::EventSinkDelegate target_delegate;

    if (Udm::create_if_not (this->target_assembly_, target_delegate,
        Udm::contains (boost::bind (std::logical_and <bool> (),
          boost::bind (std::equal_to <PICML::InEventPort> (),
                       this->target_inevent_,
                       boost::bind (&PICML::EventSinkDelegate::srcEventSinkDelegate_end, _1)),
          boost::bind (std::equal_to <PICML::InEventPort> (),
                       tmp_port,
                       boost::bind (&PICML::EventSinkDelegate::dstEventSinkDelegate_end, _1))))))
    {
      target_delegate.srcEventSinkDelegate_end () = this->target_inevent_;
      target_delegate.dstEventSinkDelegate_end () = tmp_port;
    }
  }
}
