// $Id$

//
// CUTS_BE_Impl_Generator_T
//
template <typename CONTEXT>
CUTS_INLINE
CUTS_BE_Impl_Generator_T <CONTEXT>::CUTS_BE_Impl_Generator_T (CONTEXT & context)
: context_ (context)
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
void CUTS_BE_Impl_Generator_T <CONTEXT>::generate (const CHAOS::RootFolder & root)
{
  CHAOS::RootFolder (root).Accept (*this);
}
