// -*- C++ -*-
// $Id$

//
// CUTS_CCM_Component_T
//
template <typename T, typename CTX>
CUTS_INLINE
CUTS_CCM_Component_T <T, CTX>::CUTS_CCM_Component_T (void)
{

}

//
// ~CUTS_CCM_Component_T
//
template <typename T, typename CTX>
CUTS_INLINE
CUTS_CCM_Component_T <T, CTX>::~CUTS_CCM_Component_T (void)
{

}

//
// ccm_activate
//
template <typename T, typename CTX>
CUTS_INLINE
void CUTS_CCM_Component_T <T, CTX>::ccm_activate (void)
{
  CUTS_Component::activate ();
}

//
// ciao_preactivate
//
template <typename T, typename CTX>
CUTS_INLINE
void CUTS_CCM_Component_T <T, CTX>::ciao_preactivate (void)
{

}

//
// ciao_postactivate
//
template <typename T, typename CTX>
CUTS_INLINE
void CUTS_CCM_Component_T <T, CTX>::ciao_postactivate (void)
{

}

//
// ccm_passivate
//
template <typename T, typename CTX>
CUTS_INLINE
void CUTS_CCM_Component_T <T, CTX>::ccm_passivate (void)
{
  CUTS_Component::deactivate ();
}

//
// ccm_remove
//
template <typename T, typename CTX>
CUTS_INLINE
void CUTS_CCM_Component_T <T, CTX>::ccm_remove (void)
{

}
