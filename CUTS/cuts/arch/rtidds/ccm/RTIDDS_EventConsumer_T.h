// -*- C++ -*-

#ifndef _CUTS_RTIDDS_CCM_EVENTCONSUMER_T_H_
#define _CUTS_RTIDDS_CCM_EVENTCONSUMER_T_H_

#include "cuts/arch/rtidds/RTIDDS_Traits_T.h"
#include "RTIDDS_EventConsumer.h"

template <typename SERVANT, typename EVENT>
class CUTS_RTIDDS_CCM_EventConsumer_T :
  public CUTS_RTIDDS_CCM_EventConsumer
{
public:
  /// Type definition of the servant type.
  typedef SERVANT servant_type;

  /// Type definition of the event type.
  typedef EVENT event_type;

  typedef void (*deserialize_method) (SERVANT * servant, const EVENT & event);

  CUTS_RTIDDS_CCM_EventConsumer_T (SERVANT * servant, deserialize_method callback);

  virtual ~CUTS_RTIDDS_CCM_EventConsumer_T (void);

  virtual void on_data_available (::DDSDataReader * reader);

  virtual int configure (::DDSDomainParticipant * participant,
                         const char * inst,
                         const char * topic);

private:
  /// Servant to pass event.
  SERVANT * servant_;

  /// Method for deserializing an event.
  deserialize_method callback_;

  typename CUTS_RTIDDS_Traits_T <EVENT>::reader_type * reader_;
};

#include "RTIDDS_EventConsumer_T.cpp"

#endif  // !definef _CUTS_RTIDDS_EVENTCONSUMER_T_H_
