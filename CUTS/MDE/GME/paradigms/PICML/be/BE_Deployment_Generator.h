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

private:
  PICML::DeploymentPlans deployment_plans_;

  PICML::DeploymentPlan deployment_plan_;
};

#if defined (__CUTS_INLINE__)
#include "BE_Deployment_Generator.inl"
#endif

#endif  // !defined _CUTS_BE_DEPLOYMENT_GENERATOR_H_
