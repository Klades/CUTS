// $Id$

#include "stdafx.h"
#include "Quotas_Deployment_Generator.h"
#include "game/modelgen.h"
#include "game/Reference.h"
#include "game/Connection.h"
#include "game/Set.h"

#include "boost/bind.hpp"
#include <functional>
#include <sstream>

//
// Quotas_Deployment_Generator
//
Quotas_Deployment_Generator::
Quotas_Deployment_Generator (void)
{

}

//
// ~Quotas_Deployment_Generator
//
Quotas_Deployment_Generator::~Quotas_Deployment_Generator (void)
{

}

//
// generate
//
bool Quotas_Deployment_Generator::
generate (GAME::Folder_in folder,
          const std::string & name,
          const GAME::Model & domain,
          const GAME::Model & assembly,
          GAME::Model & deployment)
{
  using GAME::Mga_t;

  GAME::Transaction t (folder->project ());

  // First, create the deployment plan container.
  static const std::string meta_DeploymentPlan ("DeploymentPlan");
  if (GAME::create_if_not <Mga_t> (folder, meta_DeploymentPlan, deployment,
      GAME::contains <Mga_t> (boost::bind (std::equal_to <std::string> (),
                              name,
                              boost::bind (&GAME::Model::impl_type::name,
                                           boost::bind (&GAME::Model::get, _1))))))
  {
    deployment->name (name);
  }

  std::vector <GAME::Model> nodes;
  if (0 == domain->children ("Node", nodes))
    return true;

  // There should only be 1 node in the collection right now.
  GAME::Reference node_ref;
  static const std::string meta_NodeReference ("NodeReference");

  if (GAME::create_if_not <Mga_t> (deployment, meta_NodeReference, node_ref,
      GAME::contains <Mga_t> (boost::bind (std::equal_to <GAME::FCO> (),
                              nodes[0],
                              boost::bind (&GAME::Reference::impl_type::refers_to,
                                           boost::bind (&GAME::Reference::get, _1))))))
  {
    node_ref->refers_to (nodes[0]);
  }

  // Commit the current transaction. This will force the add-on
  // to generate its elements.
  t.flush ();

  std::vector <GAME::Connection> conns;
  if (0 == node_ref.in_connections ("InstanceMapping", conns))
    return false;

  GAME::Set collocation = GAME::Set::_narrow (conns[0].src ());

  GAME::Reference asm_ref;
  static const std::string meta_ComponentAssemblyReference ("ComponentAssemblyReference");
  if (GAME::create_if_not <Mga_t> (deployment, meta_ComponentAssemblyReference, asm_ref,
      GAME::contains <Mga_t> (boost::bind (std::equal_to <GAME::FCO> (),
                              assembly,
                              boost::bind (&GAME::Reference::impl_type::refers_to,
                                           boost::bind (&GAME::Reference::get, _1)))))
  {
    asm_ref->refers_to (assembly);
  }

  asm_ref->name (assembly->name ());

  // Deployment the assembly to the collocation group.
  collocation->insert (asm_ref);

  t.commit ();

  return true;
}
