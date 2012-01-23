// -*- C++ -*-

//=============================================================================
/**
 *  @file         OpenSplice_Event_Listener_T.h
 *
 *  $Id$
 *
 *  @author       James H. Hill
 */
//=============================================================================

#ifndef _CUTS_ICCM_OPENSPLICE_EVENT_LISTENER_T_H_
#define _CUTS_ICCM_OPENSPLICE_EVENT_LISTENER_T_H_

#include "OpenSplice_Traits_T.h"

#include "dds_dcpsC.h"

namespace iCCM
{

/**
 * @class OpenSplice_Event_Listener_T
 */
template <typename SERVANT, typename EVENT>
class OpenSplice_Event_Listener_T :
  public ::DDS::DataReaderListener
{
 public:
  /// Type definition of the servant type.
  typedef SERVANT servant_type;

  /// Type definition of the event type.
  typedef EVENT event_type;

  /// Type definition of the event traits.
  typedef OpenSplice_Traits_T <EVENT> traits_type;

  /// Type definition of the reader type.
  typedef typename traits_type::reader_type reader_type;

  /// Type definition of the reader _var type.
  typedef typename traits_type::reader_type_var reader_type_var;

  /// Type definition of the servant callback method.
  typedef void (SERVANT::*DESERIALIZE_METHOD) (EVENT *);

  /**
   * Initializing constructor.
   */
  OpenSplice_Event_Listener_T (SERVANT * servant,
                                        DESERIALIZE_METHOD callback);

  virtual ~OpenSplice_Event_Listener_T (void);

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

private:
  /// Servant that receives the event.
  SERVANT * servant_;

  /// Target method for serializing the event.
  DESERIALIZE_METHOD callback_;
};

}

#include "OpenSplice_Event_Listener_T.cpp"

#endif // _CUTS_ICCM_OPENSPLICE_EVENT_LISTENER_T_H_
