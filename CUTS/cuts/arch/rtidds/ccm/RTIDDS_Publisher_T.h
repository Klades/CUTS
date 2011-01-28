// -*- C++ -*-

//=============================================================================
/**
 *  @file       RTIDDS_Publisher.h
 *
 *  $Id$
 *
 *  @author     James H. Hill
 */
//=============================================================================

#ifndef _CUTS_RTIDDS_CCM_PUBLISHER_T_H_
#define _CUTS_RTIDDS_CCM_PUBLISHER_T_H_

#include "cuts/arch/rtidds/RTIDDS_Traits_T.h"
#include "RTIDDS_Publisher.h"
#include "RTIDDS_EventsC.h"

/**
 * @class CUTS_RTIDDS_CCM_Publisher_T
 */
template <typename EVENT>
class CUTS_RTIDDS_CCM_Publisher_T : public CUTS_RTIDDS_CCM_Publisher
{
public:
  /// Type definition for the event traits.
  typedef CUTS_RTIDDS_Traits_T <EVENT> traits_type;

  /// Default constructor.
  CUTS_RTIDDS_CCM_Publisher_T (void);

  /// Destructor.
  virtual ~CUTS_RTIDDS_CCM_Publisher_T (void);

  // Connect an event consumer.
  virtual void connect (::Components::EventConsumerBase_ptr consumer);

  /// Send a CORBA event.
  void send_event (typename traits_type::corba_event_type * ev);

  /// Send a DDS event.
  void send_event (typename traits_type::dds_event_type & ev);

protected:
  /// The writer for this publisher.
  typename traits_type::writer_type * writer_;
};

#if defined (__CUTS_INLINE__)
#include "RTIDDS_Publisher_T.inl"
#endif

#include "RTIDDS_Publisher_T.cpp"

#endif  // !defined _CUTS_RTIDDS_CCM_SUBSCRIBER_T_H_

