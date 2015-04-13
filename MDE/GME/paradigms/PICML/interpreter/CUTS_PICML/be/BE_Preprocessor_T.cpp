// $Id$

#if !defined (__CUTS_INLINE__)
#include "BE_Preprocessor_T.inl"
#endif

#include "BE_IDL_Graph_Builder.h"
#include "BE_Impl_Graph_Builder_T.h"

//
// preprocess
//
template <typename T>
bool CUTS_BE_Preprocessor_T <T>::
preprocess (const PICML::ComponentImplementationContainer_in container)
{
  // Build the implementation dependency graph.
  CUTS_BE_Impl_Graph_Builder_T <T> builder (this->impl_graph_, this->idl_graph_);
  container->accept (&builder);

  return true;
}

//
// preprocess
//
template <typename T>
bool CUTS_BE_Preprocessor_T <T>::preprocess (const PICML::File_in file)
{
  CUTS_BE_IDL_Graph_Builder builder (this->idl_graph_);
  file->accept (builder);

  return true;
}

//
// preprocess
//
template <typename T>
bool CUTS_BE_Preprocessor_T <T>::
preprocess (const PICML::File_in file, const CUTS_BE_IDL_Node * & node)
{
  this->preprocess (file);
  this->idl_graph_.find (file->name (), node);
  return true;
}
