#ifndef DSTO_LISTENERBASE_H
#define DSTO_LISTENERBASE_H

#include "dds_dcpsC.h"

#include "DDS_Utilities_export.h"

using namespace DDS;

class DDS_Utilities_Export DSTO_ListenerBase
  : public virtual DataReaderListener
{
public:
  DSTO_ListenerBase (void);
  virtual ~DSTO_ListenerBase (void);

  virtual void
  on_requested_deadline_missed (
    DataReader_ptr reader,
    const RequestedDeadlineMissedStatus & status);

  virtual void
  on_requested_incompatible_qos (
    DataReader_ptr reader,
    const RequestedIncompatibleQosStatus & status);

  virtual void
  on_sample_rejected (
    DataReader_ptr reader,
    const SampleRejectedStatus & status);

  virtual void
  on_liveliness_changed (
    DataReader_ptr reader,
    const LivelinessChangedStatus & status);

  virtual void
  on_data_available (
    DataReader_ptr reader);

  virtual void
  on_subscription_matched (
    DataReader_ptr reader,
    const SubscriptionMatchedStatus & status);

  virtual void
  on_sample_lost (
    DataReader_ptr reader,
    const SampleLostStatus & status);
};

#endif // DSTO_LISTENERBASE_H