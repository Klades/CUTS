// $Id$

#include "BE_Deployment_Generator.h"

#if !defined (__CUTS_INLINE__)
#include "BE_Deployment_Generator.inl"
#endif

#include "modelgen.h"
#include "boost/bind.hpp"
#include "Uml.h"

#define COWORKER_DEPLOYMENTPLANS_NAME "CoWorkEr_DeploymentPlans"
#define COWORKER_IMPLEMENTATIONS_NAME "CoWorkEr_ComponentImplementations"

//
// Visit_RootFolder
//
void CUTS_BE_Deployment_Generator::
Visit_RootFolder (const PICML::RootFolder & root)
{
  // We can only generate a deployment plan we have already generated
  // all the component implementations. Or, at least have a folder
  // that would contain the coworker component implementations.
  if (Udm::find (root, this->implementations_,
      boost::bind (std::equal_to <std::string> (),
                   COWORKER_IMPLEMENTATIONS_NAME,
                   boost::bind (&PICML::ComponentImplementations::name, _1))))
  {
    typedef std::set <PICML::DeploymentPlans> DeploymentPlans_Set;
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
  // Get the actual node in the deployment.
  PICML::Node node = noderef.ref ();

  // We need to make sure the coworker deployment plan has a
  // node reference of the same type.
  if (Udm::create_if_not (this->deployment_plan_, this->noderef_,
      Udm::contains (boost::bind (std::equal_to <PICML::Node> (),
                     node,
                     boost::bind (&PICML::NodeReference::ref, _1)))))
  {
    this->noderef_.ref () = node;
  }

  // Make sure the name and location of the node reference are
  // the same in both plans.
  if (std::string (this->noderef_.name ()) != std::string (noderef.name ()))
    this->noderef_.name () = noderef.name ();

  if (std::string (this->noderef_.position ()) != std::string (noderef.position ()))
    this->noderef_.position () = noderef.position ();

  // Lastly, make sure in map all the groups to a node.
  typedef std::set <PICML::InstanceMapping> InstanceMapping_Set;
  InstanceMapping_Set mapping = noderef.srcInstanceMapping ();

  std::for_each (mapping.begin (),
                 mapping.end (),
                 boost::bind (&InstanceMapping_Set::value_type::Accept,
                              _1,
                              boost::ref (*this)));
}

//
// Visit_InstanceMapping
//
void CUTS_BE_Deployment_Generator::
Visit_InstanceMapping (const PICML::InstanceMapping & mapping)
{
  PICML::CollocationGroup group = mapping.srcInstanceMapping_end ();
  group.Accept (*this);

  // Finally, make sure the deployment contains a connection that
  // maps the collocation group to the node.
  PICML::InstanceMapping target_mapping;

  if (Udm::create_if_not (this->deployment_plan_, target_mapping,
      Udm::contains (boost::bind (std::logical_and <bool> (),
        boost::bind (std::equal_to <PICML::CollocationGroup> (),
                     this->group_,
                     boost::bind (&PICML::InstanceMapping::srcInstanceMapping_end, _1)),
        boost::bind (std::equal_to <PICML::NodeReference> (),
                     this->noderef_,
                     boost::bind (&PICML::InstanceMapping::dstInstanceMapping_end, _1))))))
  {
    target_mapping.srcInstanceMapping_end () = this->group_;
    target_mapping.dstInstanceMapping_end () = this->noderef_;
  }
}

//
// Visit_CollocationGroup
//
void CUTS_BE_Deployment_Generator::
Visit_CollocationGroup (const PICML::CollocationGroup & group)
{
  std::string name = group.name ();

  // Verify we have a collocation group with the same name
  // as <group>. If not, we need to create one.
  if (Udm::create_if_not (this->deployment_plan_, this->group_,
      Udm::contains (boost::bind (std::equal_to <std::string> (),
                     name,
                     boost::bind (&PICML::CollocationGroup::name, _1)))))
  {
    this->group_.name () = name;
  }

  // Get all the members currently in the group. We are going to use this
  // to determine if we need to add members, or not.
  this->members_ = this->group_.members ();

  // Update the position only if we don't match our counterpart.
  if (std::string (this->group_.position ()) != std::string (group.position ()))
    this->group_.position () = group.position ();

  // Make sure this group has all the correct instances.
  typedef std::set <PICML::CollocationGroupMember> CollocationGroup_Members_Set;
  CollocationGroup_Members_Set members = group.members ();

  std::for_each (members.begin (),
                 members.end (),
                 boost::bind (&CUTS_BE_Deployment_Generator::
                               Visit_CollocationGroupMember,
                               this, _1));
}

//
// Visit_CollocationGroupMember
//
void CUTS_BE_Deployment_Generator::
Visit_CollocationGroupMember (
  const PICML::CollocationGroupMember & member)
{
  if (member.type () == PICML::ComponentRef::meta)
  {
    PICML::ComponentRef ref = PICML::ComponentRef::Cast (member);
    ref.Accept (*this);
  }
  else if (member.type () == PICML::SharedComponentReference::meta)
  {
    PICML::SharedComponentReference ref =
      PICML::SharedComponentReference::Cast (member);

    ref.Accept (*this);
  }
  else if (member.type () == PICML::ComponentRef::meta)
  {
    PICML::ComponentAssemblyReference ref =
      PICML::ComponentAssemblyReference::Cast (member);

    ref.Accept (*this);
  }
}

//
// Visit_ComponentRef
//
void CUTS_BE_Deployment_Generator::
Visit_ComponentRef (const PICML::ComponentRef & ref)
{
  // Get the component being referenced and gets its exact
  // location.
  PICML::Component component = ref.ref ();

  if (component != Udm::null)
    component.Accept (*this);

  // There is not need to continue if we have not path. This should
  // never really happen. This check is just here for safety.
  if (this->path_.empty ())
    return;

  PICML::MgaObject parent;
  PICML::ComponentImplementationContainer container;
  std::string name = this->path_.top ();

  if (Udm::find (this->implementations_, container,
      boost::bind (std::equal_to <std::string> (),
                   name,
                   boost::bind (&PICML::ComponentImplementationContainer::name,
                                _1))))
  {
    this->path_.pop ();
    parent = container;

    while (!this->path_.empty ())
    {
      // Get the next name in the path.
      name = this->path_.top ();

      // Locate the object w/ this name in the parent. We are also
      // going to store the located object in the parent.
      if (!Udm::find (parent, parent,
          boost::bind (std::equal_to <std::string> (),
                       name,
                       boost::bind (&PICML::MgaObject::name, _1))))
      {
        break;
      }

      this->path_.pop ();
    }
  }

  if (this->path_.empty ())
  {
    // Convert the located item into a component.
    PICML::Component component = PICML::Component::Cast (parent);

    // Let's see if the target deployment plan has an reference
    // to the found component instance.
    typedef std::vector <PICML::ComponentRef> ComponentRef_Set;
    ComponentRef_Set comrefs = this->deployment_plan_.ComponentRef_kind_children ();

    PICML::ComponentRef target_ref;

    if (Udm::create_if_not (this->deployment_plan_, target_ref,
        Udm::contains (boost::bind (std::equal_to <PICML::Component> (),
                       component,
                       boost::bind (&PICML::ComponentRef::ref, _1)))))
    {
      target_ref.ref () = component;
    }

    // Make sure the name's match.
    if (std::string (target_ref.name ()) != std::string (ref.name ()))
      target_ref.name () = ref.name ();

    if (std::string (target_ref.position ()) != std::string (ref.position ()))
      target_ref.position () = ref.position ();

    // Let's see if this reference is a member of the current
    // collocation group. If not, then we definitely need to
    // add it. :)
    if (this->members_.find (target_ref) == this->members_.end ())
      this->group_.members () += target_ref;
  }
}

//
// Visit_Component
//
void CUTS_BE_Deployment_Generator::
Visit_Component (const PICML::Component & component)
{
  // Get the location of this component in its really assembly. We
  // are going to store the path so we can try to locate it in the
  // coworker assembly.
  this->path_.push (component.name ());
  PICML::MgaObject parent = component.parent ();

  do {
    this->path_.push (parent.name ());
    parent = PICML::MgaObject::Cast (parent.parent ());
  } while (parent.type () != PICML::ComponentImplementationContainer::meta);

  // Right now, the container has a _CoWorkEr appended to its
  // real name.
  this->path_.push (parent.name ());
  this->path_.top () += "_CoWorkEr";
}
