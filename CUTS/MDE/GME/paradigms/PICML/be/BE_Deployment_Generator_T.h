// -*- C++ -*-

//=============================================================================
/**
 * @file        BE_Deployment_Generator_T.h
 *
 * Generic parser logic for the deployment model.
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _CUTS_BE_DEPLOYMENT_GENERATOR_T_H_
#define _CUTS_BE_DEPLOYMENT_GENERATOR_T_H_

#include "PICML/PICML.h"
#include "cuts/config.h"

//=============================================================================
/**
 * @class CUTS_BE_Deployment_Generator_T
 *
 * Generic parser logic for deployment plan models.
 */
//=============================================================================

template <typename T>
class CUTS_BE_Deployment_Generator_T : public PICML::Visitor
{
public:
  /// Default constructor.
  CUTS_BE_Deployment_Generator_T (void);

  /// Destructor.
  virtual ~CUTS_BE_Deployment_Generator_T (void);

  virtual void Visit_DeploymentPlan (
    const PICML::DeploymentPlan & );

  virtual void Visit_NodeReference (
    const PICML::NodeReference & );

  virtual void Visit_Node (
    const PICML::Node & );

  virtual void Visit_InstanceMapping (
    const PICML::InstanceMapping & );

  virtual void Visit_CollocationGroup (
    const PICML::CollocationGroup & group);

  virtual void Visit_ComponentRef (
    const PICML::ComponentRef & ref);

  virtual void Visit_ComponentAssemblyReference (
    const PICML::ComponentAssemblyReference & car);

  virtual void Visit_SharedComponentReference (
    const PICML::SharedComponentReference & scr);

private:
  /// The current node being generated.
  PICML::Node curr_node_;
};

#if defined (__CUTS_INLINE__)
#include "BE_Deployment_Generator_T.inl"
#endif

#include "BE_Deployment_Generator_T.cpp"

#endif
