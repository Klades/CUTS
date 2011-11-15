// -*- C++ -*-

#ifndef _CUTS_OPENSPLICE_LISTENERBASE_H_
#define _CUTS_OPENSPLICE_LISTENERBASE_H_

#include "dds_dcpsC.h"
#include "OpenSplice_export.h"

class CUTS_OPENSPLICE_Export CUTS_OpenSplice_ListenerBase
: public virtual ::DDS::DataReaderListener
{
 public:
  CUTS_OpenSplice_ListenerBase (void);

  virtual ~CUTS_OpenSplice_ListenerBase (void);
  
  virtual void
    on_requested_deadline_missed (::DDS::DataReader_ptr reader,
				  const ::DDS::RequestedDeadlineMissedStatus & status);
  
  virtual void
    on_requested_incompatible_qos (::DDS::DataReader_ptr reader,
				   const ::DDS::RequestedIncompatibleQosStatus & status);
  
  virtual void
    on_sample_rejected (::DDS::DataReader_ptr reader,
			const ::DDS::SampleRejectedStatus & status);
  
  virtual void
    on_liveliness_changed (::DDS::DataReader_ptr reader,
			   const ::DDS::LivelinessChangedStatus & status);
  
  virtual void
    on_data_available (::DDS::DataReader_ptr reader);
  
  virtual void
    on_subscription_matched (::DDS::DataReader_ptr reader,
			     const ::DDS::SubscriptionMatchedStatus & status);
  
  virtual void
    on_sample_lost (::DDS::DataReader_ptr reader,
		    const ::DDS::SampleLostStatus & status);
};

#endif // _CUTS_OPENSPLICE_LISTENERBASE_H_
