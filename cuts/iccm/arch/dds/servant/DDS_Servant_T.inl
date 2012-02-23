// -*- C++ -*-
// $Id$

namespace iCCM
{

//
// DDS_Servant_T
//
template <typename TRAIT, typename T, typename CONTEXT, typename EXECUTOR, typename POA_EXEC>
CUTS_INLINE
DDS_Servant_T <TRAIT, T, CONTEXT, EXECUTOR, POA_EXEC>::
DDS_Servant_T (T * _this,
               const char * name,
               ::PortableServer::POA_ptr port_POA,
               typename EXECUTOR::_ptr_type executor)
: base_type (_this, name, port_POA, executor)
{

}

//
// ~DDS_Servant_T
//
template <typename TRAIT, typename T, typename CONTEXT, typename EXECUTOR, typename POA_EXEC>
CUTS_INLINE
DDS_Servant_T <TRAIT, T, CONTEXT, EXECUTOR, POA_EXEC>::~DDS_Servant_T (void)
{

}

}
