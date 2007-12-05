// $Id$

#include "BE_Deployment_Generator.h"

#if !defined (__CUTS_INLINE__)
#include "BE_Deployment_Generator.inl"
#endif

#include "modelgen.h"
#include "boost/bind.hpp"
#include "Uml.h"

#define COWORKER_DEPLOYMENTPLANS_NAME "CoWorkEr_DeploymentPlans"
//
// Visit_RootFolder
//
void CUTS_BE_Deployment_Generator::
Visit_RootFolder (const PICML::RootFolder & root)
{
  typedef std::vector <PICML::DeploymentPlans> DeploymentPlans_Set;
  DeploymentPlans_Set plans = root.DeploymentPlans_children ();

  // We need to locate the COWORKER_DEPLOYMENTPLANS_NAME folder. If one
  // does not exist, then we need to create one.
  if (Udm::create_if_not (root, this->deployment_plans_,
      Udm::contains (boost::bind (std::equal_to <std::string> (),
                     COWORKER_DEPLOYMENTPLANS_NAME,
                     boost::bind (&DeploymentPlans_Set::value_type::name, _1)))))
  {
    this->deployment_plans_.SetStrValue ("name", COWORKER_DEPLOYMENTPLANS_NAME);
  }

  // We need to visit all the deployment plans in the project.
  std::for_each (plans.begin (),
                 plans.end (),
                 boost::bind (&DeploymentPlans_Set::value_type::Accept,
                              _1, boost::ref (*this)));
}

//
// Visit_DeploymentPlans
//
void CUTS_BE_Deployment_Generator::
Visit_DeploymentPlans (const PICML::DeploymentPlans & folder)
{
  if (std::string (folder.name ()) == COWORKER_DEPLOYMENTPLANS_NAME)
    return;

  // Visit all the deployment plans in this folder. We do not have
  // to worry about any of the plans being CoWorkEr plans since
  // they are all located in a single folder.
  typedef std::vector <PICML::DeploymentPlan> DeploymentPlan_Set;
  DeploymentPlan_Set plans = folder.DeploymentPlan_children ();

  std::for_each (plans.begin (),
                 plans.end (),
                 boost::bind (&DeploymentPlan_Set::value_type::Accept,
                              _1, boost::ref (*this)));
}

//
// Visit_DeploymentPlan
//
void CUTS_BE_Deployment_Generator::
Visit_DeploymentPlan (const PICML::DeploymentPlan & plan)
{
  std::string name = std::string (plan.name ()) + "_CoWorkEr";

  typedef std::vector <PICML::DeploymentPlan> DeploymentPlan_Set;
  DeploymentPlan_Set plans = this->deployment_plans_.DeploymentPlan_children ();

  if (Udm::create_if_not (this->deployment_plans_, this->deployment_plan_,
      Udm::contains (boost::bind (std::equal_to <std::string> (), name,
                     boost::bind (&DeploymentPlan_Set::value_type::name, _1)))))
  {
    this->deployment_plan_.SetStrValue ("name", name);
  }

  // Get all the node references in the current plan. We need to make
  // sure the coworker deployment plan matches on a per-node basis.
  typedef std::vector <PICML::NodeReference> NodeReference_Set;
  NodeReference_Set noderefs = plan.NodeReference_children ();

  std::for_each (noderefs.begin (),
                 noderefs.end (),
                 boost::bind (&NodeReference_Set::value_type::Accept,
                              _1,
                              boost::ref (*this)));
}

//
// Visit_NodeReference
//
void CUTS_BE_Deployment_Generator::
Visit_NodeReference (const PICML::NodeReference & noderef)
{

}
