// -*- C++ -*-
// $Id$

//
// CUTS_OpenSplice_CCM_Servant_T
//
template <typename T, typename CONTEXT, typename EXECUTOR, typename POA_EXEC>
CUTS_INLINE
CUTS_OpenSplice_CCM_Servant_T <T, CONTEXT, EXECUTOR, POA_EXEC>::
CUTS_OpenSplice_CCM_Servant_T (const char * name,
			       typename EXECUTOR::_ptr_type executor,
			       ::DDS::DomainParticipant_ptr participant)
  : base_type (name, executor)
{
  this->participant (participant);
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
