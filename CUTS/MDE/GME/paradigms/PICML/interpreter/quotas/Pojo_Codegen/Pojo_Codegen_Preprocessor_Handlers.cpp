// $Id$

#include "stdafx.h"
#include "Pojo_Codegen_Preprocessor_Handlers.h"

#if !defined (__CUTS_INLINE__)
#include "Pojo_Codegen_Preprocessor_Handlers.inl"
#endif

#include "be/BE_Impl_Node.h"

//
// CUTS_BE_Preprocessor_Preprocess_Impl_T
//
bool CUTS_BE_Preprocessor_Preprocess_Impl_T <Quotas::Pojo::Codegen::Context>::
generate (const PICML::MonolithicImplementation & impl)
{
  const std::string name (impl.name ());
  return name.find ("_ComponentFacadeImpl") == std::string::npos;
}

//
// CUTS_BE_Preprocessor_Worker_T
//
void CUTS_BE_Preprocessor_Worker_T <Quotas::Pojo::Codegen::Context>::
generate (CUTS_BE_Impl_Node * node, const PICML::Worker & worker)
{
  std::string import = CUTS_BE_Java::import (worker);
  node->maplist_["imports"].insert (import);
}

//
// CUTS_BE_Preprocessor_WorkerLibrary_T
//
void CUTS_BE_Preprocessor_WorkerLibrary_T <Quotas::Pojo::Codegen::Context>::
generate (CUTS_BE_Impl_Node * node, const PICML::WorkerLibrary & lib)
{
  std::string classpath = lib.Location ();

  // Get the full path of the JAR file.
  if (!classpath.empty ())
    classpath += "/";

  classpath += std::string (lib.name ()) + ".jar";

  // Insert the JAR file into the CLASSPATH.
  node->maplist_["classpath"].insert (classpath);
}
