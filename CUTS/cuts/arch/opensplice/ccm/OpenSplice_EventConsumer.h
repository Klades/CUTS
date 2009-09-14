// -*- C++ -*-

#ifndef _CUTS_OPENSPLICE_CCM_EVENTCONSUMER_H_
#define _CUTS_OPENSPLICE_CCM_EVENTCONSUMER_H_

#include "OpenSplice_EventsS.h"
#include "cuts/arch/ccm/CCM_EventConsumer.h"
#include "cuts/arch/opensplice/OpenSplice_ListenerBase.h"
#include "cuts/arch/opensplice/OpenSplice_Endpoint.h"
#include "OpenSplice_CCM_export.h"

/**
 * @class CUTS_OpenSplice_CCM_EventConsumer
 */
class CUTS_OPENSPLICE_CCM_Export CUTS_OpenSplice_CCM_EventConsumer :
  public virtual CUTS_CCM_EventConsumer,
  public virtual ::POA_Components::OpenSplice::EventConsumer,
  public CUTS_OpenSplice_ListenerBase,
  public CUTS_OpenSplice_Endpoint
{
 public:
  /**
   * Initializing contructor.
   */
  CUTS_OpenSplice_CCM_EventConsumer (void);

  /// Destructor.
  virtual ~CUTS_OpenSplice_CCM_EventConsumer (void);

  virtual int configure (::DDS::DomainParticipant_ptr participant,
       const char * inst,
       const char * topic_name) = 0;

  virtual int open (::DDS::DomainParticipant_ptr participant,
        ::DDS::TypeSupport_ptr type_support,
        const char * topic_name);

  /// Close the event consumer.
  virtual int close (void);

  /// Get the topic description for this event consumer.
  virtual ::Components::OpenSplice::TopicDescription * topic_description (void);

 protected:
  /// Right now, we assume that each consumer is a subscriber. In the
  /// future, we may want to enable shared subscriptions between consumers.
  ::DDS::Subscriber_var subscriber_;

  /// The abstract reader for the event consumer.
  ::DDS::DataReader_var abstract_reader_;
};

#if defined (__CUTS_INLINE__)
#include "OpenSplice_EventConsumer.inl"
#endif

#endif  // !defined _CUTS_OPENSPLICE_CCM_EVENTCONSUMER_H_
