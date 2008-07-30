// $Id$

#include "CAPI_Preprocessor_Handlers.h"
#include "be/BE_Impl_Node.h"
#include "boost/spirit/actor.hpp"
#include <sstream>

//
// CUTS_BE_Preprocessor_Worker_T
//
bool CUTS_BE_Preprocessor_Worker_T <CUTS_BE_Capi>::
handle (CUTS_BE_Impl_Node * node, const PICML::Worker & worker)
{
  std::string import = CUTS_BE_Capi::import (worker);
  node->maplist_["imports"].insert (import);
  return true;
}

//
// CUTS_BE_Preprocessor_WorkerLibrary_T
//
bool CUTS_BE_Preprocessor_WorkerLibrary_T <CUTS_BE_Capi>::
handle (CUTS_BE_Impl_Node * node, const PICML::WorkerLibrary & lib)
{
  std::string location = lib.Location ();
  std::ostringstream jarfile;

  // Get the full path of the JAR file.
  if (!location.empty ())
    jarfile << lib.Location () << "/";

  jarfile << lib.name () << ".jar";

  // Insert the JAR file into the CLASSPATH.
  node->maplist_["classpath"].insert (jarfile.str ());
  return true;
}