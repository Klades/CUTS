// -*- C++ -*-
// $Id$

//
// CUTS_OpenSplice_CCM_Servant_T
//
template <typename T, typename CONTEXT, typename EXECUTOR, typename POA_EXEC>
CUTS_INLINE
CUTS_OpenSplice_CCM_Servant_T <T, CONTEXT, EXECUTOR, POA_EXEC>::
CUTS_OpenSplice_CCM_Servant_T (const char * name,
                               ::PortableServer::POA_ptr port_POA,
                               typename EXECUTOR::_ptr_type executor)
  : base_type (name, port_POA, executor)
{

}

//
// ~CUTS_OpenSplice_CCM_Servant_T
//
template <typename T, typename CONTEXT, typename EXECUTOR, typename POA_EXEC>
CUTS_INLINE
CUTS_OpenSplice_CCM_Servant_T <T, CONTEXT, EXECUTOR, POA_EXEC>::
~CUTS_OpenSplice_CCM_Servant_T (void)
{

}
