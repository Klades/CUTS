// -*- C++ -*-

//=============================================================================
/**
 *  @file       Spring_Deployment_Visitor.h
 *
 *  $Id$
 *
 *  @author     James H. Hill
 */
//=============================================================================

#ifndef _QUOTAS_SPRING_DEPLOYMENT_VISITOR_H_
#define _QUOTAS_SPRING_DEPLOYMENT_VISITOR_H_

#include "PICML/PICML.h"
#include "game/xml/Document.h"

/**
 * @class Quotas_Spring_Deployment_Visitor
 *
 * Implementation of the visitor that generates the Spring XML
 * documents for instantiating Java class (or beans).
 */
class Quotas_Spring_Deployment_Visitor : public PICML::Visitor
{
public:
  /// Default constructor.
  Quotas_Spring_Deployment_Visitor (const std::string & path);

  /// Destructor.
  virtual ~Quotas_Spring_Deployment_Visitor (void);

  virtual void Visit_RootFolder (const PICML::RootFolder & root);

  virtual void Visit_DeploymentPlans (const PICML::DeploymentPlans & plans);

  virtual void Visit_DeploymentPlan (const PICML::DeploymentPlan & plan);

  virtual void Visit_NodeReference (const PICML::NodeReference & node);

  virtual void Visit_InstanceMapping (const PICML::InstanceMapping & mapping);

  virtual void Visit_CollocationGroup (const PICML::CollocationGroup & group);

  virtual void Visit_ComponentInstanceRef (const PICML::ComponentInstanceRef & ref);

  virtual void Visit_ComponentAssemblyReference (const PICML::ComponentAssemblyReference &);

  virtual void Visit_ComponentInstance (const PICML::ComponentInstance & inst);

  virtual void Visit_AttributeInstance (const PICML::AttributeInstance & inst);

  virtual void Visit_RequiredRequestPortInstance (const PICML::RequiredRequestPortInstance & inst);

  virtual void Visit_Invoke (const PICML::Invoke & invoke);

private:
  /// Initialize the object.
  void init (void);

  void init_document (const std::string & root);
  void serialize_xml (const std::string & filename);

  const std::string & path_;

  xercesc::DOMImplementation * impl_;

  xercesc::DOMLSOutput * output_;

  xercesc::DOMLSSerializer * serializer_;

  std::auto_ptr <GAME::Xml::Document> document_;

  std::set <PICML::ComponentInstance> instances_;

  GAME::Xml::Fragment bean_;
};


#endif  // !defined _QUOTAS_SPRING_DEPLOYMENT_VISITOR_H_
