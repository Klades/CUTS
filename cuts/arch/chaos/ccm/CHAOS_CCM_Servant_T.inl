// -*- C++ -*-
// $Id$

//
// CUTS_CHAOS_CCM_Servant_T
//
template <typename T, typename CONTEXT, typename EXECUTOR, typename POA_EXEC>
CUTS_INLINE
CUTS_CHAOS_CCM_Servant_T <T, CONTEXT, EXECUTOR, POA_EXEC>::
CUTS_CHAOS_CCM_Servant_T (
  const char * name,
  typename EXECUTOR::_ptr_type executor)
 : base_type (name, executor)
{

}

//
// ~CUTS_CHAOS_CCM_Servant_T
//
template <typename T, typename CONTEXT, typename EXECUTOR, typename POA_EXEC>
CUTS_INLINE
CUTS_CHAOS_CCM_Servant_T <T, CONTEXT, EXECUTOR, POA_EXEC>::
~CUTS_CHAOS_CCM_Servant_T (void)
{

}
