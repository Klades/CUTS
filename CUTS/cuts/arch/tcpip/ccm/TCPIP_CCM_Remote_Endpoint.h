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

#include "ccm/CCM_EventConsumerBaseC.h"
#include "TCPIP_CCM_export.h"

/**
 * @class CUTS_TCPIP_CCM_Remote_Endpoint
 */
class CUTS_TCPIP_CCM_Export CUTS_TCPIP_CCM_Remote_Endpoint
{
public:
  CUTS_TCPIP_CCM_Remote_Endpoint (void);

  virtual ~CUTS_TCPIP_CCM_Remote_Endpoint (void) = 0;

  virtual void connect (::Components::EventConsumerBase_ptr consumer) = 0;

  virtual ::Components::EventConsumerBase_ptr disconnect (void) = 0;
};

#if defined (__CUTS_INLINE__)
#include "TCPIP_CCM_Remote_Endpoint.inl"
#endif

#endif  // !defined _CUTS_TCPIP_CCM_REMOTE_ENDPOINT_H_
