// $Id$

#include "RTIDDS_ListenerBase.h"

CUTS_RTIDDS_ListenerBase::CUTS_RTIDDS_ListenerBase (void)
{
}

CUTS_RTIDDS_ListenerBase::~CUTS_RTIDDS_ListenerBase (void)
{
}

void CUTS_RTIDDS_ListenerBase::
on_requested_deadline_missed (::DDSDataReader *,
                              const ::DDS_RequestedDeadlineMissedStatus &)
{
}

void
CUTS_RTIDDS_ListenerBase::
on_requested_incompatible_qos (::DDSDataReader *,
                               const ::DDS_RequestedIncompatibleQosStatus &)
{
}

void
CUTS_RTIDDS_ListenerBase::
on_sample_rejected (::DDSDataReader *,
                    const ::DDS_SampleRejectedStatus &)
{
}

void
CUTS_RTIDDS_ListenerBase::
on_liveliness_changed (::DDSDataReader *,
                       const ::DDS_LivelinessChangedStatus &)
{
}

void
CUTS_RTIDDS_ListenerBase::
on_data_available (::DDSDataReader *)
{
}

void
CUTS_RTIDDS_ListenerBase::
on_subscription_matched (::DDSDataReader *,
                         const ::DDS_SubscriptionMatchedStatus &)
{
}

void
CUTS_RTIDDS_ListenerBase::
on_sample_lost (::DDSDataReader *,
                const ::DDS_SampleLostStatus &)
{
}

