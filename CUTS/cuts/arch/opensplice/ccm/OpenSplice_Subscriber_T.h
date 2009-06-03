// -*- C++ -*-

#ifndef _CUTS_OPENSPLICE_CCM_SUBSCRIBER_T_H_
#define _CUTS_OPENSPLICE_CCM_SUBSCRIBER_T_H_

#include "cuts/arch/opensplice/OpenSplice_Traits_T.h"
//#include "dds_dcpsC.h"
#include "OpenSplice_Subscriber.h"
#include "EventsC.h"

/**
 * @class CUTS_OpenSplice_CCM_Subscriber_T
 */
template <typename EVENT>
class CUTS_OpenSplice_CCM_Subscriber_T :
  public CUTS_OpenSplice_CCM_Subscriber
{
public:
  typedef CUTS_OpenSplice_Traits_T <EVENT> traits_type;

  CUTS_OpenSplice_CCM_Subscriber_T (::DDS::DomainParticipant_ptr participant);

  virtual ~CUTS_OpenSplice_CCM_Subscriber_T (void);

  virtual void connect (::Components::EventConsumerBase_ptr consumer);
  
  virtual ::Components::EventConsumerBase_ptr disconnect (void);

  void send_event (typename traits_type::corba_event_type * ev);

protected:
  typename traits_type::writer_var_type writer_;

  ::Components::OpenSplice::EventConsumer_var consumer_;

  ::DDS::DomainParticipant_var participant_;

  ::DDS::Topic_var dds_topic_;

  ::DDS::Publisher_var publisher_;
};

#include "OpenSplice_Subscriber_T.cpp"

#endif  // !defined _CUTS_OPENSPLICE_CCM_SUBSCRIBER_T_H_

