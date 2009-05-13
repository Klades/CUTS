#include "DSTO_ListenerBase.h"

namespace CUTS_DDS
{
  DSTO_ListenerBase::DSTO_ListenerBase (void)
  {
  }

  DSTO_ListenerBase::~DSTO_ListenerBase (void)
  {
  }

  void
  DSTO_ListenerBase::on_requested_deadline_missed (
    DataReader_ptr,
    const RequestedDeadlineMissedStatus &)
  {
  }

  void
  DSTO_ListenerBase::on_requested_incompatible_qos (
    DataReader_ptr,
    const RequestedIncompatibleQosStatus &)
  {
  }

  void
  DSTO_ListenerBase::on_sample_rejected (
    DataReader_ptr,
    const SampleRejectedStatus &)
  {
  }

  void
  DSTO_ListenerBase::on_liveliness_changed (
    DataReader_ptr,
    const LivelinessChangedStatus &)
  {
  }

  void
  DSTO_ListenerBase::on_data_available (
    DataReader_ptr)
  {
  }

  void
  DSTO_ListenerBase::on_subscription_matched (
    DataReader_ptr,
    const SubscriptionMatchedStatus &)
  {
  }

  void
  DSTO_ListenerBase::on_sample_lost (
    DataReader_ptr,
    const SampleLostStatus &)
  {
  }
}

