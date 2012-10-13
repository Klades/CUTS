// -*- C++ -*-
// $Id$

namespace iCCM
{

//
// OpenSplice_Servant_T
//
template <typename T, typename CONTEXT, typename EXECUTOR, typename POA_EXEC>
CUTS_INLINE
OpenSplice_Servant_T <T, CONTEXT, EXECUTOR, POA_EXEC>::
OpenSplice_Servant_T (T * _this,
                      const char * name,
                      ::PortableServer::POA_ptr port_POA,
                      typename EXECUTOR::_ptr_type executor)
  : DDS_Servant_T <OpenSplice, T, CONTEXT, EXECUTOR, POA_EXEC> (_this, name, port_POA, executor)
{

}

//
// ~OpenSplice_Servant_T
//
template <typename T, typename CONTEXT, typename EXECUTOR, typename POA_EXEC>
CUTS_INLINE
OpenSplice_Servant_T <T, CONTEXT, EXECUTOR, POA_EXEC>::~OpenSplice_Servant_T (void)
{

}

}
