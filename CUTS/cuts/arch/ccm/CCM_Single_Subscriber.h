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

#ifndef _CUTS_CCM_SINGLE_SUBSCRIBER_H_
#define _CUTS_CCM_SINGLE_SUBSCRIBER_H_

#include "ccm/CCM_EventConsumerBaseC.h"
#include "CCM_export.h"

/**
 * @class CUTS_TCPIP_CCM_Remote_Endpoint
 */
class CUTS_CCM_Export CUTS_CCM_Single_Subscriber
{
public:
  CUTS_CCM_Single_Subscriber (void);

  virtual ~CUTS_CCM_Single_Subscriber (void) = 0;

  virtual void connect (::Components::EventConsumerBase_ptr consumer) = 0;

  virtual ::Components::EventConsumerBase_ptr disconnect (void) = 0;
};

#if defined (__CUTS_INLINE__)
#include "CCM_Single_Subscriber.inl"
#endif

#endif  // !defined _CUTS_TCPIP_CCM_REMOTE_ENDPOINT_H_
