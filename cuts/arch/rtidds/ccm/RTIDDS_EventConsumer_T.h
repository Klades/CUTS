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
  typedef EVENT event_type;

  typedef CUTS_RTIDDS_Traits_T <EVENT> traits_type;
  typedef typename traits_type::reader_type reader_type;

  typedef void (*UPCALL_METHOD) (SERVANT *, EVENT *);

  CUTS_RTIDDS_CCM_EventConsumer_T (SERVANT * servant, UPCALL_METHOD callback);

  virtual ~CUTS_RTIDDS_CCM_EventConsumer_T (void);

  virtual void on_data_available (::DDSDataReader * reader);

  virtual int configure (::DDSSubscriber * subscriber,
                         const char * inst,
                         const char * topic);

private:
  /// Servant to pass event.
  SERVANT * servant_;

  /// Method for deserializing an event.
  UPCALL_METHOD callback_;

  typename CUTS_RTIDDS_Traits_T <EVENT>::reader_type * reader_;
};

#include "RTIDDS_EventConsumer_T.cpp"

#endif  // !definef _CUTS_RTIDDS_EVENTCONSUMER_T_H_
