// $Id$

//
// CUTS_BE_Impl_Generator_T
//
template <typename CONTEXT>
CUTS_INLINE
CUTS_BE_Impl_Generator_T <CONTEXT>::
CUTS_BE_Impl_Generator_T (CONTEXT & context, CUTS_BE_Preprocessor_T <CONTEXT> & pp)
: context_ (context),
  pp_ (pp)
{

}

//
// ~CUTS_BE_Impl_Generator_T
//
template <typename CONTEXT>
CUTS_INLINE
CUTS_BE_Impl_Generator_T <CONTEXT>::~CUTS_BE_Impl_Generator_T (void)
{

}

//
// generate
//
template <typename CONTEXT>
CUTS_INLINE
void CUTS_BE_Impl_Generator_T <CONTEXT>::generate (const PICML::RootFolder_in root)
{
  root->accept (this);
}
