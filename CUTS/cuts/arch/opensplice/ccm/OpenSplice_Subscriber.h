// -*- C++ -*-

#ifndef _CUTS_OPENSPLICE_SUBSCRIBER_H_
#define _CUTS_OPENSPLICE_SUBSCRIBER_H_

#include "OpenSplice_EventsC.h"
#include "cuts/arch/ccm/CCM_Single_Subscriber.h"
#include "cuts/arch/opensplice/OpenSplice_Endpoint.h"
#include "OpenSplice_CCM_export.h"

/**
 * @class CUTS_OpenSplice_CCM_Subscriber
 */
class CUTS_OPENSPLICE_CCM_Export CUTS_OpenSplice_CCM_Subscriber :
  public CUTS_CCM_Single_Subscriber
{
 public:
  CUTS_OpenSplice_CCM_Subscriber (void);

  virtual ~CUTS_OpenSplice_CCM_Subscriber (void);

  virtual void configure (::DDS::Publisher_ptr publisher);

  virtual void connect (::Components::EventConsumerBase_ptr consumer);

  virtual ::Components::EventConsumerBase_ptr disconnect (void);

protected:
  /// The consumer connected to this publisher.
  ::Components::OpenSplice::EventConsumer_var consumer_;

  /// The publisher assigned to this object.
  ::DDS::Publisher_var publisher_;

  /// The writer assigned to this publisher.
  ::DDS::DataWriter_var abstract_writer_;

  /// The underlying endpoint for the publisher.
  CUTS_OpenSplice_Endpoint endpoint_;
};

#endif
