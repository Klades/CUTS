// -*- C++ -*-

#ifndef _CUTS_OPENSPLICE_SUBSCRIBER_H_
#define _CUTS_OPENSPLICE_SUBSCRIBER_H_

#include "ccpp_dds_dcps.h"
#include "cuts/arch/ccm/CCM_Single_Subscriber.h"
#include "cuts/arch/opensplice/OpenSplice_Endpoint.h"
#include "OpenSplice_CCM_export.h"
#include "EventsC.h"

/**
 * @class CUTS_OpenSplice_CCM_Subscriber
 */
class CUTS_OPENSPLICE_CCM_Export CUTS_OpenSplice_CCM_Subscriber :
  public CUTS_CCM_Single_Subscriber
{
 public:
  CUTS_OpenSplice_CCM_Subscriber (void);

  virtual ~CUTS_OpenSplice_CCM_Subscriber (void);

  virtual void configure (::DDS::DomainParticipant_ptr participant);

  virtual void connect (::Components::EventConsumerBase_ptr consumer);

  virtual ::Components::EventConsumerBase_ptr disconnect (void);

 protected:
  ::Components::EventConsumerBase_var consumer_;

  ::DDS::DomainParticipant_var participant_;

  ::DDS::Publisher_var publisher_;

  ::DDS::DataWriter_var abstract_writer_;

  CUTS_OpenSplice_Endpoint endpoint_;
};

#endif
