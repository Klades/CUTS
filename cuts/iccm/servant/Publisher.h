// -*- C++ -*-

//=============================================================================
/**
 *  @file         Publisher.h
 *
 *  $Id$
 *
 *  @author       James H. Hill
 */
//=============================================================================

#ifndef _CUTS_ICCM_PUBLISHER_H_
#define _CUTS_ICCM_PUBLISHER_H_

#include "ccm/CCM_EventConsumerBaseC.h"

#include "Servant_export.h"

namespace iCCM
{

/**
 * @class Publisher
 *
 * The interface for all CCM publishers.
 */
class ICCM_SERVANT_Export Publisher
{
public:
  /// Destructor.
  virtual ~Publisher (void) = 0;

  /**
   * Connect a consumer to this publisher.
   *
   * @param[in]         consumer        The connecting consumer.
   */
  virtual void connect (::Components::EventConsumerBase_ptr consumer) = 0;

  /// Disconnect the currently connected consumer.
  virtual ::Components::EventConsumerBase_ptr disconnect (void) = 0;

  /// Method for activating the publisher
  virtual void activate (void);

  /// Method for passivating the publisher
  virtual void passivate (void);
};

}

#if defined (__CUTS_INLINE__)
#include "Publisher.inl"
#endif

#endif  // !defined _CUTS_ICCM_PUBLISHER_H_
