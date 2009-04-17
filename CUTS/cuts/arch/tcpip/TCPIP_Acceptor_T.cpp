// $Id$

#if !defined (__CUTS_INLINE__)
#include "TCPIP_Acceptor_T.cpp"
#endif

template <typename SVC_HANDLER>
int
CUTS_TCPIP_Acceptor_T <SVC_HANDLER>::make_svc_handler (SVC_HANDLER * &sh)
{
  CUTS_TCPIP_TRACE ("CUTS_TCPIP_Acceptor_T <SVC_HANDLER>::make_svc_handler (SVC_HANDLER * &)");

  if (sh == 0)
    ACE_NEW_RETURN (sh,
                    SVC_HANDLER (this->obj_mgr_),
                    -1);

  // Set the reactor of the newly created <SVC_HANDLER> to the same
  // reactor that this <ACE_Acceptor> is using.
  sh->reactor (this->reactor ());

  return 0;
}
