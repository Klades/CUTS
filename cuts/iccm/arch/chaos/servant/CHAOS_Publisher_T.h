// -*- C++ -*-

//=============================================================================
/**
 *  @file         CHAOS_Publisher_T.h
 *
 *  $IdCHAOS_CCM_Publisher_T.h 3086 2011-01-22 05:53:51Z hillj $
 *
 *  @author       James H. Hill
 */
//=============================================================================

#ifndef _ICCM_CHAOS_PUBLISHER_T_H_
#define _ICCM_CHAOS_PUBLISHER_T_H_

#include "CHAOS_EventsC.h"
#include "CHAOS_Publisher.h"

namespace iCCM
{

/**
 * @class CHAOS_Publisher_T
 *
 * Template version of the CHAOS publisher object that is bound to
 * an specific event type.
 */
template <typename EVENT>
class CHAOS_Publisher_T :
  public CHAOS_Publisher
{
public:
  /// Typedef for event type
  typedef EVENT event_type;

  /// Default constructor.
  CHAOS_Publisher_T (void);

  /// Destructor.
  virtual ~CHAOS_Publisher_T (void);

  /// Allocate a new event.
  virtual EVENT * allocate_event (void);

  /**
   * Publish a CORBA event. This method will transform the CORBA event
   * to a DDS event before publishing it over the network.
   *
   * @param[in]         ev            The event to send
   */
  void send_event (EVENT * ev);
};

}

#if defined (__CUTS_INLINE__)
#include "CHAOS_Publisher_T.inl"
#endif

#include "CHAOS_Publisher_T.cpp"

#endif  // !defined _ICCM_CHAOS_PUBLISHER_T_H_
