// -*- C++ -*-

//=============================================================================
/**
 *  @file         DDS_Event_Listener_T.h
 *
 *  $Id$
 *
 *  @author       James H. Hill
 */
//=============================================================================

#ifndef _ICCM_DDS_EVENT_LISTENER_T_H_
#define _ICCM_DDS_EVENT_LISTENER_T_H_

namespace iCCM
{

/**
 * @class DDS_Event_Listener_T
 */
template <typename T, typename SERVANT, typename EVENT>
class DDS_Event_Listener_T :
  public T::datareaderlistener_type
{
 public:
  /// Type definition of the servant type.
  typedef SERVANT servant_type;

  /// Type definition of the event type.
  typedef EVENT event_type;

  /// Type definition of the DDS entities.
  typedef typename T::event_traits_type <EVENT>::result_type event_traits_type;
  typedef typename T::datareader_ptr_type datareader_ptr_type;

  /// Type definition of the servant callback method.
  typedef void (SERVANT::*DESERIALIZE_METHOD) (EVENT *);

  /**
   * Initializing constructor.
   */
  DDS_Event_Listener_T (SERVANT * servant,
                        DESERIALIZE_METHOD callback);

  virtual ~DDS_Event_Listener_T (void);

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

#include "DDS_Event_Listener_T.cpp"

#endif // _ICCM_DDS_EVENT_LISTENER_T_H_
