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

#include "DDS_EventConsumer_Task_T.h"
#include "EventPackage.h"

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
  typedef typename T::template event_traits_type <EVENT>::result_type event_traits_type;
  typedef typename T::datareader_ptr_type datareader_ptr_type;
  typedef typename T::topic_ptr_type topic_ptr_type;
  typedef typename T::datareaderqos_type datareaderqos_type;

  /// Type definition of the servant callback method.
  typedef void (SERVANT::*DESERIALIZE_METHOD) (EVENT *);

  /**
   * Initializing constructor.
   */
  DDS_Event_Listener_T (SERVANT * servant,
                        DESERIALIZE_METHOD callback);

  virtual ~DDS_Event_Listener_T (void);

  void configure (typename T::datareader_ptr_type reader);

  virtual void
    on_requested_deadline_missed (
      datareader_ptr_type reader,
      const typename T::requesteddeadlinemissedstatus_type & status);

  virtual void
    on_requested_incompatible_qos (
      datareader_ptr_type reader,
      const typename T::requestedincompatibleqosstatus_type & status);

  virtual void
    on_sample_rejected (
      datareader_ptr_type reader,
      const typename T::samplerejectedstatus_type & status);

  virtual void
    on_liveliness_changed (
      datareader_ptr_type reader,
      const typename T::livelinesschangedstatus_type & status);

  virtual void
    on_data_available (datareader_ptr_type reader);

  virtual void
    on_subscription_matched (
      datareader_ptr_type reader,
      const typename T::subscriptionmatchedstatus_type & status);

  virtual void
    on_sample_lost (
      datareader_ptr_type reader,
      const typename T::sampleloststatus_type & status);

private:
  // Typedef for EventPackage
  typedef EventPackage<event_traits_type,
          typename T::sampleinfoseq_type sampleinfoseq_type> package_type;

  // Typedef for the task
  typedef DDS_EventConsumer_Task_T<SERVANT, EVENT, package_type> task_type;

  /// Reader assigned to this listener.
  typename T::datareader_var_type reader_;

  /// Servant that receives the event.
  SERVANT * servant_;

  /// Target method for serializing the event.
  DESERIALIZE_METHOD callback_;

  task_type * task_;
};

}

#include "DDS_Event_Listener_T.cpp"

#endif // _ICCM_DDS_EVENT_LISTENER_T_H_
