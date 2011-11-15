// $Id$

#include "stdafx.h"
#include "Quotas_Domain_Generator.h"

#include "game/Model.h"
#include "game/modelgen.h"

#include "boost/bind.hpp"
#include <functional>
#include <sstream>

//
// Quotas_Domain_Generator
//
Quotas_Domain_Generator::Quotas_Domain_Generator (void)
{

}

//
// ~Quotas_Domain_Generator
//
Quotas_Domain_Generator::~Quotas_Domain_Generator (void)
{

}

//
// generate
//
bool Quotas_Domain_Generator::
generate (GAME::Folder_in folder, const std::string & name, size_t hosts)
{
  using GAME::Mga_t;

  // First create the domain that will contain the hosts.
  static const std::string meta_Domain ("Domain");

  if (GAME::create_if_not <Mga_t> (folder, meta_Domain, this->domain_,
      GAME::contains <Mga_t> (boost::bind (std::equal_to <std::string> (),
                              name,
                              boost::bind (&GAME::Model::impl_type::name,
                                           boost::bind (&GAME::Model::get, _1))))))
  {
    this->domain_->name (name);
  }

  // Right now, we are going to create the specified number of
  // host using a predefined name template (i.e., Host<%n>)
  for (size_t i = 1; i <= hosts; ++ i)
  {
    static const std::string meta_Node ("Node");

    // Construct the name of the host.
    std::ostringstream ostr;
    ostr << meta_Node << i;
    const std::string hostname (ostr.str ());

    // Make sure the host exists in the domain.
    GAME::Model host;
    if (GAME::create_if_not <Mga_t> (this->domain_, meta_Node, host,
        GAME::contains <Mga_t> (boost::bind (std::equal_to <std::string> (),
                                hostname,
                                boost::bind (&GAME::Model::impl_type::name,
                                             boost::bind (&GAME::Model::get, _1))))))
    {
      host->name (name);
    }
  }

  return true;
}

//
// generated_domain
//
GAME::Model Quotas_Domain_Generator::generated_domain (void)
{
  return this->domain_;
}
