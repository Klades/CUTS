// $Id$

#if !defined (__CUTS_INLINE__)
#include "BE_Preprocessor_T.inl"
#endif

//
// preprocess
//
template <typename T>
bool CUTS_BE_Preprocessor_T <T>::
preprocess (const PICML::ComponentImplementationContainer & container)
{
  PICML::ComponentImplementationContainer c (container);
  c.Accept (this->impl_graph_);

  return true;
}

//
// preprocess
//
template <typename T>
bool CUTS_BE_Preprocessor_T <T>::preprocess (const PICML::File & file)
{
  PICML::File f (file);
  f.Accept (this->idl_graph_);

  return true;
}

//
// preprocess
//
template <typename T>
bool CUTS_BE_Preprocessor_T <T>::
preprocess (const PICML::File & file, const CUTS_BE_IDL_Node * & node)
{
  this->preprocess (file);
  this->idl_graph_.find (file.name (), node);
  return true;
}
