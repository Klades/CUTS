// -*- C++ -*-

#ifndef _CUTS_OPENSPLICE_CCM_EVENTCONSUMER_T_H_
#define _CUTS_OPENSPLICE_CCM_EVENTCONSUMER_T_H_

#include "OpenSplice_EventConsumer.h"

template <typename SERVANT, typename T, typename EVENT_SEQ>
class CUTS_OpenSplice_CCM_EventConsumer_T :
  public CUTS_OpenSplice_CCM_EventConsumer
{
public:
  /// Type definition of the servant type.
  typedef SERVANT servant_type;

  typedef T reader_type;

  /// Type definition of the event type.
  typedef EVENT_SEQ event_seq_type;

  typedef typename event_seq_type::value_type event_type;

  typedef void (*deserialize_method) (SERVANT * servant, const event_type & event);

  CUTS_OpenSplice_CCM_EventConsumer_T (SERVANT * servant, deserialize_method callback);

  virtual ~CUTS_OpenSplice_CCM_EventConsumer_T (void);

  virtual void on_data_available (::DDS::DataReader_ptr reader);

private:
  /// Servant to pass event.
  SERVANT * servant_;

  /// Method for deserializing an event.
  deserialize_method callback_;
};

#include "OpenSplice_EventConsumer_T.cpp"

#endif  // !definef _CUTS_OPENSPLICE_EVENTCONSUMER_T_H_
