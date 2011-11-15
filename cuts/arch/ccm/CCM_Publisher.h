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

#ifndef _CUTS_CCM_PUBLISHER_H_
#define _CUTS_CCM_PUBLISHER_H_

#include "ccm/CCM_EventConsumerBaseC.h"
#include "CCM_export.h"

/**
 * @class CUTS_CCM_Publisher
 *
 * The interface for all CCM publishers.
 */
class CUTS_CCM_Export CUTS_CCM_Publisher
{
public:
  /// Destructor.
  virtual ~CUTS_CCM_Publisher (void) = 0;

  /**
   * Connect a consumer to this publisher.
   *
   * @param[in]         consumer        The connecting consumer.
   */
  virtual void connect (::Components::EventConsumerBase_ptr consumer) = 0;

  /// Disconnect the currently connected consumer.
  virtual ::Components::EventConsumerBase_ptr disconnect (void) = 0;
};

#if defined (__CUTS_INLINE__)
#include "CCM_Publisher.inl"
#endif

#endif  // !defined _CUTS_TCPIP_CCM_REMOTE_ENDPOINT_H_
