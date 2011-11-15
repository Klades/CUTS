// -*- C++ -*-

#ifndef _CUTS_RTIDDS_CCM_EVENTCONSUMER_H_
#define _CUTS_RTIDDS_CCM_EVENTCONSUMER_H_

#include "cuts/arch/ccm/CCM_EventConsumer.h"
#include "cuts/arch/rtidds/RTIDDS_ListenerBase.h"
#include "cuts/arch/rtidds/RTIDDS_Endpoint.h"
#include "RTIDDS_EventsS.h"
#include "RTIDDS_CCM_export.h"

/**
 * @class CUTS_RTIDDS_CCM_EventConsumer
 */
class CUTS_RTIDDS_CCM_Export CUTS_RTIDDS_CCM_EventConsumer :
  public virtual CUTS_CCM_EventConsumer,
  public virtual ::POA_Components::RTIDDS::EventConsumer,
  public CUTS_RTIDDS_ListenerBase
{
 public:
  /**
   * Initializing contructor.
   */
  CUTS_RTIDDS_CCM_EventConsumer (void);

  /// Destructor.
  virtual ~CUTS_RTIDDS_CCM_EventConsumer (void);

  virtual int configure (::DDSSubscriber * participant,
                         const char * inst,
                         const char * topic_name) = 0;

  /// Close the event consumer.
  virtual int close (void);

  /// Get the topic description for this event consumer.
  virtual ::Components::RTIDDS::TopicDescription * topic_description (void);

protected:
  // Helper method to open the endpoint.
  int open (const char * type_name, const char * topic_name);

  /// Right now, we assume that each consumer is a subscriber. In the
  /// future, we may want to enable shared subscriptions between consumers.
  ::DDSSubscriber * subscriber_;

  /// The abstract reader for the event consumer.
  ::DDSDataReader * abstract_reader_;

  /// The endpoint for this event consumer.
  CUTS_RTIDDS_Endpoint endpoint_;
};

#if defined (__CUTS_INLINE__)
#include "RTIDDS_EventConsumer.inl"
#endif

#endif  // !defined _CUTS_RTIDDS_CCM_EVENTCONSUMER_H_
