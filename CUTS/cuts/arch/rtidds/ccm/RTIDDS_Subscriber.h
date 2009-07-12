// -*- C++ -*-

#ifndef _CUTS_RTIDDS_SUBSCRIBER_H_
#define _CUTS_RTIDDS_SUBSCRIBER_H_

#include "ndds/ndds_cpp.h"
#include "cuts/arch/ccm/CCM_Single_Subscriber.h"
#include "cuts/arch/rtidds/RTIDDS_Endpoint.h"
#include "RTIDDS_EventsC.h"
#include "RTIDDS_CCM_export.h"

/**
 * @class CUTS_RTIDDS_CCM_Subscriber
 */
class CUTS_RTIDDS_CCM_Export CUTS_RTIDDS_CCM_Subscriber :
  public CUTS_CCM_Single_Subscriber
{
 public:
  CUTS_RTIDDS_CCM_Subscriber (void);

  virtual ~CUTS_RTIDDS_CCM_Subscriber (void);

  virtual void configure (::DDSDomainParticipant * participant);

  virtual void connect (::Components::EventConsumerBase_ptr consumer);

  virtual ::Components::EventConsumerBase_ptr disconnect (void);

 protected:
  ::Components::EventConsumerBase_var consumer_;

  ::DDSDomainParticipant * participant_;

  ::DDSPublisher * publisher_;

  ::DDSDataWriter * abstract_writer_;

  CUTS_RTIDDS_Endpoint endpoint_;
};

#endif
