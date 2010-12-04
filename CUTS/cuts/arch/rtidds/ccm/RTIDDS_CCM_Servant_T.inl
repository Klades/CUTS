// -*- C++ -*-
// $Id$

//
// CUTS_RTIDDS_CCM_Servant_T
//
template <typename T, typename CONTEXT, typename EXECUTOR, typename POA_EXEC>
CUTS_INLINE
CUTS_RTIDDS_CCM_Servant_T <T, CONTEXT, EXECUTOR, POA_EXEC>::
CUTS_RTIDDS_CCM_Servant_T (const char * name,
                           ::PortableServer::POA_ptr poa,
                           typename EXECUTOR::_ptr_type executor)
  : base_type (name, poa, executor)
{

}

//
// ~CUTS_RTIDDS_CCM_Servant_T
//
template <typename T, typename CONTEXT, typename EXECUTOR, typename POA_EXEC>
CUTS_INLINE
CUTS_RTIDDS_CCM_Servant_T <T, CONTEXT, EXECUTOR, POA_EXEC>::
~CUTS_RTIDDS_CCM_Servant_T (void)
{

}
