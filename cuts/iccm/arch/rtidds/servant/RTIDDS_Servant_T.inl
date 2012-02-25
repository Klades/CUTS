// $Id$

namespace iCCM
{

//
// RTIDDS_Servant_T
//
template <typename T, typename CONTEXT, typename EXECUTOR, typename POA_EXEC>
CUTS_INLINE
RTIDDS_Servant_T <T, CONTEXT, EXECUTOR, POA_EXEC>::
RTIDDS_Servant_T (T * _this, const char * name, ::PortableServer::POA_ptr port_POA, typename EXECUTOR::_ptr_type executor)
: DDS_Servant_T (_this, name, port_POA, executor)
{

}

//
// ~RTIDDS_Servant_T
//
template <typename T, typename CONTEXT, typename EXECUTOR, typename POA_EXEC>
CUTS_INLINE
RTIDDS_Servant_T <T, CONTEXT, EXECUTOR, POA_EXEC>::~RTIDDS_Servant_T (void)
{

}

}
