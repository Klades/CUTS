// $Id$

#include "Isislab_Emulation_Generator.h"
#include "game/Object.h"
#include <sstream>
#include <iostream>

GME_NAOMI_CREATE_GENERATOR_IMPLEMENT (Isislab_Emulation_Generator);

//
// Isislab_Emulation_Generator
//
Isislab_Emulation_Generator::Isislab_Emulation_Generator (void)
: GME_Naomi_Generator ("ISISlab NS script generator for CUTS")
{

}

//
// ~Isislab_Emulation_Generator
//
Isislab_Emulation_Generator::~Isislab_Emulation_Generator (void)
{

}

//
// run
//
int Isislab_Emulation_Generator::run (const std::string & attr,
                                      const std::string & attr_path,
                                      GME::Object & target)
{
  // First, pass control to the run_i () method. This will invoke the
  // interpreter and generate the deployment plan.
  size_t index = attr_path.find_last_of ("/\\");
  std::string path = attr_path.substr (0, index);
  path += "/models/CUTS";

  int retval = this->run_i (attr,
                            path,
                            target,
                            "CUTS.Interpreter.Isislab.Emulation");

  if (retval == 0)
  {
    // Construct the name of the generated deployment plan.
    std::ostringstream uri;
    uri << "naomi://../models/CUTS/" << target.name () << ".ns";

    // Insert it as a resource.
    GME_Naomi_Resource rc;
    rc.name_ = "emulation";
    rc.uri_ = uri.str ();

    this->resources_.push_back (rc);
  }

  return retval;
}

