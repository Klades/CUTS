// -*- C++ -*-

#ifndef _CUTS_OPENSPLICE_CCM_EVENTCONSUMER_T_H_
#define _CUTS_OPENSPLICE_CCM_EVENTCONSUMER_T_H_

#include "cuts/arch/opensplice/OpenSplice_Traits_T.h"
#include "OpenSplice_EventConsumer.h"

template <typename SERVANT, typename EVENT>
class CUTS_OpenSplice_CCM_EventConsumer_T :
  public CUTS_OpenSplice_CCM_EventConsumer
{
public:
  /// Type definition of the servant type.
  typedef SERVANT servant_type;

  /// Type definition of the event type.
  typedef EVENT event_type;

  typedef void (*deserialize_method) (SERVANT * servant, const EVENT & event);

  CUTS_OpenSplice_CCM_EventConsumer_T (SERVANT * servant, deserialize_method callback);

  virtual ~CUTS_OpenSplice_CCM_EventConsumer_T (void);

  virtual void on_data_available (::DDS::DataReader_ptr reader);

  virtual int configure (::DDS::DomainParticipant_ptr participant,
			 const char * inst,
			 const char * topic);

private:
  /// Servant to pass event.
  SERVANT * servant_;

  /// Method for deserializing an event.
  deserialize_method callback_;

  typename CUTS_OpenSplice_Traits_T <EVENT>::reader_var_type reader_;
};

#include "OpenSplice_EventConsumer_T.cpp"

#endif  // !definef _CUTS_OPENSPLICE_EVENTCONSUMER_T_H_
