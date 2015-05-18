// -*- C++ -*-

//=============================================================================
/**
 *  @file         QpidPB_Publisher_T.h
 *
 *  $IdQpidPB_CCM_Publisher_T.h 3086 2011-01-22 05:53:51Z hillj $
 *
 *  @author       James H. Hill
 */
//=============================================================================

#ifndef _ICCM_QPIDPB_PUBLISHER_T_H_
#define _ICCM_QPIDPB_PUBLISHER_T_H_

#include "QpidPB_Sender_T.h"

#include "QpidPB_EventsC.h"
#include "QpidPB_Publisher.h"

namespace iCCM
{

/**
 * @class QpidPB_Publisher_T
 *
 * Template version of the QpidPB publisher object that is bound to
 * an specific event type.
 */
template <typename EVENT>
class QpidPB_Publisher_T :
  public QpidPB_Publisher
{
public:
  /// Typedef for event type
  typedef EVENT event_type;

  /// Default constructor.
  QpidPB_Publisher_T (void);

  /// Destructor.
  virtual ~QpidPB_Publisher_T (void);

  /// Connect the consumer.
  virtual void connect (::Components::EventConsumerBase_ptr consumer);

  /// Allocate a new event.
  EVENT * allocate_event (void);

  /**
   * Publish a CORBA event. This method will transform the CORBA event
   * to a DDS event before publishing it over the network.
   *
   * @param[in]         ev            The event to send
   */
  void send_event (EVENT * ev);

  virtual void activate (void);
  virtual void passivate (void);

protected:
  QpidPB_Sender_T <EVENT> sender_;
};

}

#if defined (__CUTS_INLINE__)
#include "QpidPB_Publisher_T.inl"
#endif

#include "QpidPB_Publisher_T.cpp"

#endif  // !defined _ICCM_QPIDPB_PUBLISHER_T_H_
