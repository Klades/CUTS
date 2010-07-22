// -*- C++ -*-
// $Id$

//
// CUTS_BE_Preprocessor_Preprocess_Impl_T
//
template <typename CONTEXT>
CUTS_INLINE
bool CUTS_BE_Preprocessor_Preprocess_Impl_T <CONTEXT>::
generate (const PICML::MonolithicImplementation & impl)
{
  return true;
}

//
// CUTS_BE_Preprocessor_WorkerFile_T
//
template <typename CONTEXT>
CUTS_INLINE
void CUTS_BE_Preprocessor_WorkerFile_T <CONTEXT>::
generate (CUTS_BE_Impl_Node * , const PICML::WorkerFile &)
{

}

//
// CUTS_BE_Preprocessor_WorkerLibrary_T
//
template <typename CONTEXT>
CUTS_INLINE
void CUTS_BE_Preprocessor_WorkerLibrary_T <CONTEXT>::
generate (CUTS_BE_Impl_Node *, const PICML::WorkerLibrary &)
{

}

//
// CUTS_BE_Preprocessor_Worker_T
//
template <typename CONTEXT>
void CUTS_BE_Preprocessor_Worker_T <CONTEXT>::
generate (CUTS_BE_Impl_Node *, const PICML::Worker &)
{

}
