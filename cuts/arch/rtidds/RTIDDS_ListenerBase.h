// -*- C++ -*-

#ifndef _CUTS_RTIDDS_LISTENERBASE_H_
#define _CUTS_RTIDDS_LISTENERBASE_H_

#include "ndds/ndds_cpp.h"
#include "RTIDDS_export.h"

class CUTS_RTIDDS_Export CUTS_RTIDDS_ListenerBase
: public virtual ::DDSDataReaderListener
{
 public:
  CUTS_RTIDDS_ListenerBase (void);

  virtual ~CUTS_RTIDDS_ListenerBase (void);

  virtual void
    on_requested_deadline_missed (
    ::DDSDataReader * reader,
    const ::DDS_RequestedDeadlineMissedStatus & status);

  virtual void
    on_requested_incompatible_qos (
    ::DDSDataReader * reader,
    const ::DDS_RequestedIncompatibleQosStatus & status);

  virtual void
    on_sample_rejected (
    ::DDSDataReader * reader,
    const ::DDS_SampleRejectedStatus & status);

  virtual void
    on_liveliness_changed (
    ::DDSDataReader * reader,
    const ::DDS_LivelinessChangedStatus & status);

  virtual void
    on_data_available (::DDSDataReader * reader);

  virtual void
    on_subscription_matched (
    ::DDSDataReader * reader,
    const ::DDS_SubscriptionMatchedStatus & status);

  virtual void
    on_sample_lost (
    ::DDSDataReader * reader,
    const ::DDS_SampleLostStatus & status);
};

#endif // _CUTS_RTIDDS_LISTENERBASE_H_
