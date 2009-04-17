// -*- C++ -*-

//=============================================================================
/**
 *  @file         TCPIP_Acceptor.h
 *
 *  $Id$
 *
 *  @author       James H. Hill
 */
//=============================================================================

#ifndef _CUTS_TCPIP_ACCEPTOR_T_H_
#define _CUTS_TCPIP_ACCEPTOR_T_H_

#include "ace/SOCK_Acceptor.h"
#include "TCPIP_export.h"

/**
 * @class CUTS_TCPIP_Acceptor_T
 */
template <typename SVC_HANDLER>
class CUTS_TCPIP_Acceptor_T :
  public ACE_Acceptor <SVC_HANDLER, ACE_SOCK_Acceptor>
{
public:
  CUTS_TCPIP_Acceptor_T (const CUTS_TCPIP_Servant_Manager & obj_mgr);

  virtual ~CUTS_TCPIP_Acceptor_T (void);

protected:
  virtual int make_svc_handler (SVC_HANDLER *& sh);

private:
  /// The object manager for the acceptor.
  const CUTS_TCPIP_Servant_Manager & obj_mgr_;
};

#if defined (__CUTS_INLINE__)
#include "TCPIP_Acceptor_T.inl"
#endif

#include "TCPIP_Acceptor_T.cpp"

#endif  // !defined _CUTS_TCPIP_ACCEPTOR_T_H_
