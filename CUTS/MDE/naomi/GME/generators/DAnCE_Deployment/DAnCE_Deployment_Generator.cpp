// $Id$

#include "DAnCE_Deployment_Generator.h"
#include "gme/Object.h"
#include <sstream>

GME_NAOMI_CREATE_GENERATOR_IMPLEMENT (DAnCE_Deployment_Generator);

//
// DAnCE_Deployment_Generator
//
DAnCE_Deployment_Generator::DAnCE_Deployment_Generator (void)
: GME_Naomi_Generator ("DAnCE deployment plan auto-generated from PICML project")
{

}

//
// ~DAnCE_Deployment_Generator
//
DAnCE_Deployment_Generator::~DAnCE_Deployment_Generator (void)
{

}

//
// run
//
int DAnCE_Deployment_Generator::run (const std::string & attr,
                                     const std::string & attr_path,
                                     GME::Object & target)
{
  // First, pass control to the run_i () method. This will invoke the
  // interpreter and generate the deployment plan.
  int retval = this->run_i (attr,
                            attr_path,
                            target,
                            "MGA.Interpreter.DeploymentPlan");

  if (retval == 0)
  {
    // Construct the name of the generated deployment plan.
    std::ostringstream uri;
    uri << "naomi://" << target.name () << ".cdp";

    // Insert it as a resource.
    GME_Naomi_Resource rc;
    rc.name_ = "deployment";
    rc.uri_ = uri.str ();

    this->resources_.push_back (rc);
  }

  return retval;
}

