// $Id$

namespace iCCM
{

//
// TCPIP_Servant_T
//
template <typename T, typename CONTEXT, typename EXECUTOR, typename POA_EXEC>
CUTS_INLINE
TCPIP_Servant_T <T, CONTEXT, EXECUTOR, POA_EXEC>::
TCPIP_Servant_T (T * _this, const char * name, ::PortableServer::POA_ptr port_POA, typename EXECUTOR::_ptr_type executor)
: base_type (_this, name, port_POA, executor)
{
  ACE_ERROR ((LM_ERROR,
              ACE_TEXT ("%T (%t) - %M - constructor for tcpip_servant_t\n")));
}

//
// ~TCPIP_Servant_T
//
template <typename T, typename CONTEXT, typename EXECUTOR, typename POA_EXEC>
CUTS_INLINE
TCPIP_Servant_T <T, CONTEXT, EXECUTOR, POA_EXEC>::~TCPIP_Servant_T (void)
{

}

}
