// -*- C++ -*-

#ifndef _CUTS_RTIDDS_CCM_SUBSCRIBER_T_H_
#define _CUTS_RTIDDS_CCM_SUBSCRIBER_T_H_

#include "cuts/arch/rtidds/RTIDDS_Traits_T.h"
#include "RTIDDS_Subscriber.h"
#include "RTIDDS_EventsC.h"

/**
 * @class CUTS_RTIDDS_CCM_Subscriber_T
 */
template <typename EVENT>
class CUTS_RTIDDS_CCM_Subscriber_T :
  public CUTS_RTIDDS_CCM_Subscriber
{
public:
  typedef CUTS_RTIDDS_Traits_T <EVENT> traits_type;

  CUTS_RTIDDS_CCM_Subscriber_T (void);

  virtual ~CUTS_RTIDDS_CCM_Subscriber_T (void);

  virtual void connect (::Components::EventConsumerBase_ptr consumer);

  void send_event (typename traits_type::corba_event_type * ev);

  void send_event (typename traits_type::dds_event_type * ev);

protected:
  typename traits_type::writer_type * writer_;
};

#include "RTIDDS_Subscriber_T.cpp"

#endif  // !defined _CUTS_RTIDDS_CCM_SUBSCRIBER_T_H_

