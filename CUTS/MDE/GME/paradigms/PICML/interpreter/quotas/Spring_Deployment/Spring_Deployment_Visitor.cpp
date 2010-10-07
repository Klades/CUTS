// $Id$

#include "stdafx.h"
#include "Spring_Deployment_Visitor.h"

#include "game/xml/Document.h"

#include "Utils/UDM/visit.h"
#include "Utils/UDM/Abstract_Type_Dispatcher_T.h"

#include "PIM/PICML/utils/udm/functional.h"

#include "xercesc/framework/LocalFileFormatTarget.hpp"

static GAME::Xml::String SPRING_NS ("http://www.springframework.org/schema/beans");

class CollocationGroupMember_Dispatcher :
  public UDM_Abstract_Type_Dispatcher_T <PICML::Visitor>
{
public:
  CollocationGroupMember_Dispatcher (void)
  {
    this->insert <PICML::ComponentInstanceRef> ();
  }
};

//
// Quotas_Spring_Deployment_Visitor
//
Quotas_Spring_Deployment_Visitor::
Quotas_Spring_Deployment_Visitor (const std::string & path)
: path_ (path),
  impl_ (0),
  output_ (0),
  serializer_ (0)
{
  this->init ();
}

//
// ~Quotas_Spring_Deployment_Visitor
//
Quotas_Spring_Deployment_Visitor::~Quotas_Spring_Deployment_Visitor (void)
{
  if (this->output_)
    this->output_->release ();

  if (this->serializer_)
    this->serializer_->release ();
}

//
// init
//
void Quotas_Spring_Deployment_Visitor::init (void)
{
  using namespace xercesc;

  // Get the LS DOM implementation
  this->impl_ = DOMImplementationRegistry::getDOMImplementation (L"LS");
  this->document_.reset (new GAME::Xml::Document (this->impl_));

  this->serializer_ = ((DOMImplementationLS*)impl_)->createLSSerializer ();
  this->output_ = ((DOMImplementationLS*)this->impl_)->createLSOutput ();

  // Set features if the serializer supports the feature/mode
  if (this->serializer_->getDomConfig ()->canSetParameter (XMLUni::fgDOMWRTDiscardDefaultContent, true))
    this->serializer_->getDomConfig ()->setParameter (XMLUni::fgDOMWRTDiscardDefaultContent, true);

  if (this->serializer_->getDomConfig ()->canSetParameter (XMLUni::fgDOMWRTFormatPrettyPrint, true))
    this->serializer_->getDomConfig ()->setParameter (XMLUni::fgDOMWRTFormatPrettyPrint, true);

  if (this->serializer_->getDomConfig ()->canSetParameter (XMLUni::fgDOMWRTBOM, false))
    this->serializer_->getDomConfig ()->setParameter (XMLUni::fgDOMWRTBOM, false);
}


//
// Visit_RootFolder
//
void Quotas_Spring_Deployment_Visitor::
Visit_RootFolder (const PICML::RootFolder & root)
{
  Udm::visit_all <PICML::DeploymentPlans> (root, *this);
}

//
// Visit_DeploymentPlans
//
void Quotas_Spring_Deployment_Visitor::
Visit_DeploymentPlans (const PICML::DeploymentPlans & plans)
{
  Udm::visit_all <PICML::DeploymentPlan> (plans, *this);
}

//
// Visit_DeploymentPlan
//
void Quotas_Spring_Deployment_Visitor::
Visit_DeploymentPlan (const PICML::DeploymentPlan & plan)
{
  Udm::visit_all <PICML::NodeReference> (plan, *this);
}


//
// Visit_NodeReference
//
void Quotas_Spring_Deployment_Visitor::
Visit_NodeReference (const PICML::NodeReference & node)
{
  std::set <PICML::InstanceMapping> mapping = node.srcInstanceMapping ();
  Udm::visit_all (mapping, *this);
}

//
// Visit_InstanceMapping
//
void Quotas_Spring_Deployment_Visitor::
Visit_InstanceMapping (const PICML::InstanceMapping & mapping)
{
  PICML::CollocationGroup group = mapping.srcInstanceMapping_end ();
  group.Accept (*this);
}

//
// Visit_CollocationGroup
//
void Quotas_Spring_Deployment_Visitor::
Visit_CollocationGroup (const PICML::CollocationGroup & group)
{
  using GAME::Xml::String;

  // Create a new XML document.
  this->document_->create (SPRING_NS, String ("beans"));   // served with butter sauce. ;-)

  // Initialize the document.
  GAME::Xml::Fragment & root = this->document_->root ();
  root->setAttributeNS (String ("http://www.w3.org/2000/xmlns/"),
                        String ("xmlns:xsi"),
                        String ("http://www.w3.org/2001/XMLSchema-instance"));

  root->setAttribute (String ("xsi:schemaLocation"),
                      String ("http://www.springframework.org/schema/beans http://www.springframework.org/schema/beans/spring-beans-2.5.xsd"));

  // Visit the remaining elements to build the document.
  CollocationGroupMember_Dispatcher cgm_dispatcher;
  std::set <PICML::CollocationGroupMember> members = group.members ();
  std::for_each (members.begin (),
                 members.end (),
                 boost::bind (&CollocationGroupMember_Dispatcher::dispatch,
                              boost::ref (cgm_dispatcher),
                              boost::ref (*this),
                              _1));

  // Write the document.
  std::string filename (this->path_);
  filename += "/" + std::string (group.name ()) + ".pdd";
  this->serialize_xml (filename);

  // Close the document.
  this->document_->close ();
  this->instances_.clear ();
}

//
// Visit_ComponentInstanceRef
//
void Quotas_Spring_Deployment_Visitor::
Visit_ComponentInstanceRef (const PICML::ComponentInstanceRef & ref)
{
  using GAME::Xml::Fragment;
  using GAME::Xml::String;

  PICML::ComponentInstance inst = ref.ref ();

  if (inst != Udm::null)
    inst.Accept (*this);
}

//
// serialize_xml
//
void Quotas_Spring_Deployment_Visitor::serialize_xml (const std::string & filename)
{
  xercesc::LocalFileFormatTarget target (filename.c_str ());
  this->output_->setByteStream (&target);
  this->serializer_->write (this->document_->impl (), this->output_);
}

//
// Visit_ComponentInstance
//
void Quotas_Spring_Deployment_Visitor::
Visit_ComponentInstance (const PICML::ComponentInstance & inst)
{
  using GAME::Xml::Fragment;
  using GAME::Xml::String;

  // Create a new bean element.
  Fragment & root = this->document_->root ();
  this->bean_ = root.create_element (SPRING_NS, String ("bean"));

  // Set the id of the new bean.
  std::string id ("_");
  id.append (inst.UUID ());

  this->bean_->setAttribute (String ("id"), String (id));

  // Get the component type for the implementation. This will be used
  // to generate the class attribute on the bean.
  PICML::ComponentInstanceType inst_type = inst.ComponentInstanceType_child ();
  PICML::MonolithicImplementation impl = inst_type.ref ();

  const std::string implname (impl.name ());

  if (implname.find ("_ComponentWrapper") != std::string::npos)
  {
    std::vector <PICML::ProvidedRequestPortInstance> facets =
      inst.ProvidedRequestPortInstance_kind_children ();

    // There should be only one provided port in an component
    // wrapper. Get it and find its class type.
    PICML::ProvidedRequestPortInstance facet_inst = facets.front ();
    PICML::ProvidedRequestPort facet = facet_inst.ref ();
    PICML::Object obj = PICML::Object::Cast (facet.ref ());

    const std::string fq_type = PICML::utils::fq_type (obj, ".");
    this->bean_->setAttribute (String ("class"), String (fq_type));
  }
  else
  {
    this->bean_->setAttribute (String ("class"), String (impl.name ()));

    // Finally, visit the connections between the components. This
    // will result in specifying the dependency <property> elements.
    Udm::visit_all <PICML::RequiredRequestPortInstance> (inst, *this);
  }

  // Now, let's visit each of the configuration properties for this
  // component instance. This will result in specifying all the
  // <property> tags for an element.
  Udm::visit_all <PICML::AttributeInstance> (inst, *this);
}

//
// Visit_AttributeInstance
//
void Quotas_Spring_Deployment_Visitor::
Visit_AttributeInstance (const PICML::AttributeInstance & inst)
{
  PICML::AttributeValue av = inst.dstAttributeValue ();
  if (av == Udm::null)
    return;

  using GAME::Xml::Fragment;
  using GAME::Xml::String;

  // Right now, we are only supporting simple types. So, just write
  // the property and the property's value.
  PICML::Property prop = av.dstAttributeValue_end ();

  if (prop.type () == PICML::SimpleProperty::meta)
  {
    PICML::SimpleProperty simple = PICML::SimpleProperty::Cast (prop);

    Fragment xml_property = this->bean_.create_element (SPRING_NS, String ("property"));
    xml_property->setAttribute (String ("name"), String (prop.name ()));
    xml_property.create_simple_content (SPRING_NS, String ("value"), String (simple.Value ()));
  }
}

//
// Visit_ProvidedRequestPortInstance
//
void Quotas_Spring_Deployment_Visitor::
Visit_RequiredRequestPortInstance (const PICML::RequiredRequestPortInstance & inst)
{
  std::set <PICML::Invoke> invokes = inst.dstinvoke ();

  std::for_each (invokes.begin (),
                 invokes.end (),
                 boost::bind (&PICML::Invoke::Accept,
                              _1,
                              boost::ref (*this)));
}

//
// Visit_Invoke
//
void Quotas_Spring_Deployment_Visitor::Visit_Invoke (const PICML::Invoke & invoke)
{
  using GAME::Xml::Fragment;
  using GAME::Xml::String;

  PICML::RequiredRequestPortEnd endpoint = invoke.srcinvoke_end ();

  // Create the property for the connection.
  Fragment xml_property = this->bean_.create_element (SPRING_NS, String ("property"));

  std::string endpoint_name (endpoint.name ());
  endpoint_name[0] = ::tolower (endpoint_name[0]);
  xml_property->setAttribute (String ("name"), String (endpoint_name));

  PICML::ProvidedRequestPortEnd request = invoke.dstinvoke_end ();
  PICML::ComponentInstance instance = PICML::ComponentInstance::Cast (request.parent ());

  std::string uuid ("_");
  uuid += instance.UUID ();

  Fragment ref_fragment = xml_property.create_element (SPRING_NS, String ("ref"));
  ref_fragment->setAttribute (String ("bean"), String (uuid));
}
