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
 * @class CUTS_TCPIP_CCM_Subscriber
 */
class CUTS_TCPIP_CCM_Export CUTS_TCPIP_CCM_Subscriber :
  public CUTS_CCM_Single_Subscriber
{
public:
  /// Default constructor.
  CUTS_TCPIP_CCM_Subscriber (void);

  /// Destructor.
  virtual ~CUTS_TCPIP_CCM_Subscriber (void);

private:
  CUTS_TCPIP_CCM_Subscriber (const CUTS_TCPIP_CCM_Subscriber &);
  const CUTS_TCPIP_CCM_Subscriber & operator = (const CUTS_TCPIP_CCM_Subscriber &);
};

#if defined (__CUTS_INLINE__)
#include "TCPIP_CCM_Remote_Endpoint.inl"
#endif

#endif  // !defined _CUTS_TCPIP_CCM_REMOTE_ENDPOINT_H_
