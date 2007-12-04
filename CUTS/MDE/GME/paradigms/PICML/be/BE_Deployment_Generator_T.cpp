// $Id$

#if !defined (__CUTS_INLINE__)
#include "BE_Deployment_Generator_T.inl"
#endif

#include "BE_algorithm.h"
#include "BE_Generators_T.h"
#include "boost/bind.hpp"

//
// Visit_DeploymentPlan
//
template <typename T>
void CUTS_BE_Deployment_Generator_T <T>::
Visit_DeploymentPlan (const PICML::DeploymentPlan & plan)
{
  if (CUTS_BE_DeploymentPlan_Begin_T <T>::generate (plan))
  {
    typedef std::vector <PICML::NodeReference> NodeReference_Set;
    NodeReference_Set nodes = plan.NodeReference_children ();

    CUTS_BE::visit <T> (nodes,
      boost::bind (&NodeReference_Set::value_type::Accept, _1, boost::ref (*this)));

    CUTS_BE_DeploymentPlan_End_T <T>::generate (plan);
  }
}

//
// Visit_NodeReference
//
template <typename T>
void CUTS_BE_Deployment_Generator_T <T>::
Visit_NodeReference (const PICML::NodeReference & noderef)
{
  PICML::Node node = noderef.ref ();

  if (node != Udm::null)
  {
    // Visit the node that is being referenced.
    CUTS_BE::visit <T> (node,
      boost::bind (&PICML::Node::Accept, _1, boost::ref (*this)));

    // Now, lets get all the instance mappings so we can determine
    // what instances are deployed on this host.
    typedef std::set <PICML::InstanceMapping> InstanceMapping_Set;
    InstanceMapping_Set mapping = noderef.srcInstanceMapping ();

    CUTS_BE::visit <T> (mapping,
      boost::bind (&InstanceMapping_Set::value_type::Accept, _1, boost::ref (*this)));
  }
}

//
// Visit_Node
//
template <typename T>
void CUTS_BE_Deployment_Generator_T <T>::
Visit_Node (const PICML::Node & node)
{
  // Save the <node> as the <curr_node_>.
  this->curr_node_ = node;

  // Generate any information about this node.
  CUTS_BE_Deployment_Node_T <T>::generate (node);
}

//
// Visit_InstanceMapping
//
template <typename T>
void CUTS_BE_Deployment_Generator_T <T>::
Visit_InstanceMapping (const PICML::InstanceMapping & mapping)
{
  PICML::CollocationGroup group = mapping.srcInstanceMapping_end ();

  CUTS_BE::visit <T> (group,
    boost::bind (&PICML::CollocationGroup::Accept, _1, boost::ref (*this)));
}

//
// Visit_CollocationGroup
//
template <typename T>
void CUTS_BE_Deployment_Generator_T <T>::
Visit_CollocationGroup (const PICML::CollocationGroup & group)
{
  typedef std::set <
    PICML::CollocationGroup_Members_Base>
    CollocationGroup_Members_Base_Set;

  // Get all the instances that are in this collocation group.
  CollocationGroup_Members_Base_Set members = group.members ();
  CollocationGroup_Members_Base_Set::iterator iter = members.begin ();

  for ( ; iter != members.end (); iter ++)
  {
    // Right now, we only support reference to component instances. This
    // is necessary because we haven't define the TIOA for partial
    // assemblies.

    if (iter->type () == PICML::ComponentRef::meta)
    {
      PICML::ComponentRef comref = PICML::ComponentRef::Cast (*iter);

      CUTS_BE::visit <T> (comref,
        boost::bind (&PICML::ComponentRef::Accept, _1, boost::ref (*this)));
    }
    else if (iter->type () == PICML::ComponentAssemblyReference::meta)
    {
      PICML::ComponentAssemblyReference car =
        PICML::ComponentAssemblyReference::Cast (*iter);

      CUTS_BE::visit <T> (car,
        boost::bind (&PICML::ComponentAssemblyReference::Accept, _1, boost::ref (*this)));
    }
    else if (iter->type () == PICML::SharedComponentReference::meta)
    {
      PICML::SharedComponentReference scr =
        PICML::SharedComponentReference::Cast (*iter);

      CUTS_BE::visit <T> (scr,
        boost::bind (&PICML::SharedComponentReference::Accept, _1, boost::ref (*this)));
    }
  }
}

//
// Visit_ComponentRef
//
template <typename T>
void CUTS_BE_Deployment_Generator_T <T>::
Visit_ComponentRef (const PICML::ComponentRef & ref)
{
  PICML::Component component = ref.ref ();

  if (component != Udm::null)
    CUTS_BE_Deployment_Location_T <T>::generate (component, this->curr_node_);
}

//
// Visit_ComponentAssemblyReference
//
template <typename T>
void CUTS_BE_Deployment_Generator_T <T>::
Visit_ComponentAssemblyReference (const PICML::ComponentAssemblyReference & car)
{

}

//
// Visit_SharedComponentReference
//
template <typename T>
void CUTS_BE_Deployment_Generator_T <T>::
Visit_SharedComponentReference (const PICML::SharedComponentReference & scr)
{

}
