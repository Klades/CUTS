// $Id$

#include "OpenSplice_ListenerBase.h"

CUTS_OpenSplice_ListenerBase::CUTS_OpenSplice_ListenerBase (void)
{
}

CUTS_OpenSplice_ListenerBase::~CUTS_OpenSplice_ListenerBase (void)
{
}

void CUTS_OpenSplice_ListenerBase::
on_requested_deadline_missed (::DDS::DataReader_ptr,
			      const ::DDS::RequestedDeadlineMissedStatus &)
{
}

void
CUTS_OpenSplice_ListenerBase::
on_requested_incompatible_qos (::DDS::DataReader_ptr,
			       const ::DDS::RequestedIncompatibleQosStatus &)
{
}

void
CUTS_OpenSplice_ListenerBase::
on_sample_rejected (::DDS::DataReader_ptr,
		    const ::DDS::SampleRejectedStatus &)
{
}

void
CUTS_OpenSplice_ListenerBase::
on_liveliness_changed (::DDS::DataReader_ptr,
		       const ::DDS::LivelinessChangedStatus &)
{
}

void
CUTS_OpenSplice_ListenerBase::
on_data_available (::DDS::DataReader_ptr)
{
}

void
CUTS_OpenSplice_ListenerBase::
on_subscription_matched (::DDS::DataReader_ptr,
			 const ::DDS::SubscriptionMatchedStatus &)
{
}

void
CUTS_OpenSplice_ListenerBase::
on_sample_lost (::DDS::DataReader_ptr,
		const ::DDS::SampleLostStatus &)
{
}

