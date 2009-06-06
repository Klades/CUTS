// -*- C++ -*-

#ifndef _CUTS_OPENSPLICE_CCM_SUBSCRIBER_T_H_
#define _CUTS_OPENSPLICE_CCM_SUBSCRIBER_T_H_

#include "cuts/arch/opensplice/OpenSplice_Traits_T.h"
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

  CUTS_OpenSplice_CCM_Subscriber_T (void);

  virtual ~CUTS_OpenSplice_CCM_Subscriber_T (void);

  virtual void connect (::Components::EventConsumerBase_ptr consumer);

  void send_event (typename traits_type::corba_event_type * ev);

  void send_event (typename traits_type::dds_event_type & ev);

protected:
  typename traits_type::writer_var_type writer_;
};

#include "OpenSplice_Subscriber_T.cpp"

#endif  // !defined _CUTS_OPENSPLICE_CCM_SUBSCRIBER_T_H_

