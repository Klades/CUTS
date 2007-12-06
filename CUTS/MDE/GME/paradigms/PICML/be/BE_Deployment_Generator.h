// -*- C++ -*-

//=============================================================================
/**
 * @file        BE_Deployment_Generator.h
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _CUTS_BE_DEPLOYMENT_GENERATOR_H_
#define _CUTS_BE_DEPLOYMENT_GENERATOR_H_

#include "cuts/config.h"
#include "PICML/PICML.h"
#include <stack>
#include "BE_export.h"

//=============================================================================
/**
 * @class CUTS_BE_Deployment_Generator
 */
//=============================================================================

class CUTS_BE_Export CUTS_BE_Deployment_Generator : public PICML::Visitor
{
public:
  /// Default constructor.
  CUTS_BE_Deployment_Generator (void);

  /// Destructor.
  virtual ~CUTS_BE_Deployment_Generator (void);

  virtual void Visit_RootFolder (
    const PICML::RootFolder & root);

  virtual void Visit_DeploymentPlans (
    const PICML::DeploymentPlans & plans);

  virtual void Visit_DeploymentPlan (
    const PICML::DeploymentPlan & plan);

  virtual void Visit_NodeReference (
    const PICML::NodeReference & noderef);

  virtual void Visit_InstanceMapping (
    const PICML::InstanceMapping & mapping);

  virtual void Visit_CollocationGroup (
    const PICML::CollocationGroup & group);

  virtual void Visit_ComponentRef (
    const PICML::ComponentRef & ref);

  virtual void Visit_Component (
    const PICML::Component & component);

private:
  void Visit_CollocationGroup_Members_Base (
    const PICML::CollocationGroup_Members_Base & member);

  PICML::ComponentImplementations implementations_;

  PICML::DeploymentPlans deployment_plans_;

  PICML::DeploymentPlan deployment_plan_;

  PICML::NodeReference noderef_;

  PICML::CollocationGroup group_;

  std::set <PICML::CollocationGroup_Members_Base> members_;

  std::stack <std::string> path_;
};

#if defined (__CUTS_INLINE__)
#include "BE_Deployment_Generator.inl"
#endif

#endif  // !defined _CUTS_BE_DEPLOYMENT_GENERATOR_H_
