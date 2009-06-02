// -*- C++ -*-

//=============================================================================
/**
 *  @file         TCPIP_CCM_Remote_Endpoint.h
 *
 *  $Id$
 *
 *  @author       James H. Hill
 */
//=============================================================================

#ifndef _CUTS_TCPIP_CCM_REMOTE_ENDPOINT_H_
#define _CUTS_TCPIP_CCM_REMOTE_ENDPOINT_H_

#include "cuts/arch/ccm/CCM_Single_Subscriber.h"
#include "TCPIP_CCM_export.h"

/**
 * @class CUTS_TCPIP_CCM_Remote_Endpoint
 */
class CUTS_TCPIP_CCM_Export CUTS_TCPIP_CCM_Remote_Endpoint :
  public CUTS_CCM_Single_Subscriber
{
public:
  CUTS_TCPIP_CCM_Remote_Endpoint (void);

  virtual ~CUTS_TCPIP_CCM_Remote_Endpoint (void) = 0;

private:
  CUTS_TCPIP_CCM_Remote_Endpoint (const CUTS_TCPIP_CCM_Remote_Endpoint &);
  const CUTS_TCPIP_CCM_Remote_Endpoint & operator = (const CUTS_TCPIP_CCM_Remote_Endpoint &);
};

#if defined (__CUTS_INLINE__)
#include "TCPIP_CCM_Remote_Endpoint.inl"
#endif

#endif  // !defined _CUTS_TCPIP_CCM_REMOTE_ENDPOINT_H_
