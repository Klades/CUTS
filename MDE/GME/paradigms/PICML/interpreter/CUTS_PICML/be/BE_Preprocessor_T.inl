// $Id$

//
// CUTS_BE_Preprocessor_T
//
template <typename T>
CUTS_INLINE
CUTS_BE_Preprocessor_T <T>::CUTS_BE_Preprocessor_T (void)
{

}

//
// ~CUTS_BE_Preprocessor_T
//
template <typename T>
CUTS_INLINE
CUTS_BE_Preprocessor_T <T>::~CUTS_BE_Preprocessor_T (void)
{

}

//
// stubs
//
template <typename T>
CUTS_INLINE
const CUTS_BE_IDL_Graph & CUTS_BE_Preprocessor_T <T>::stubs (void) const
{
  return this->idl_graph_;
}

//
// stubs
//
template <typename T>
CUTS_INLINE
CUTS_BE_IDL_Graph & CUTS_BE_Preprocessor_T <T>::stubs (void)
{
  return this->idl_graph_;
}

//
// impls
//
template <typename T>
CUTS_INLINE
const CUTS_BE_Impl_Graph & CUTS_BE_Preprocessor_T <T>::impls (void) const
{
  return this->impl_graph_;
}

//
// impls
//
template <typename T>
CUTS_INLINE
CUTS_BE_Impl_Graph & CUTS_BE_Preprocessor_T <T>::impls (void)
{
  return this->impl_graph_;
}

//
// remove
//
template <typename T>
CUTS_INLINE
void CUTS_BE_Preprocessor_T <T>::
remove (const PICML::ComponentImplementationContainer_in container)
{
  this->impl_graph_.remove (container->name ());
}
