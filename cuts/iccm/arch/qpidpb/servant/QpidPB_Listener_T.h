// -*- C++ -*-

//==============================================================================
/**
 *  @file        QpidPB_Listener_T.h
 *
 *  $Id: generate_cpp_class.py 3685 2012-09-26 14:45:04Z dfeiock $
 *
 *  @author      INSERT NAME HERE
 */
//==============================================================================

#ifndef _ICCM_QPIDPB_LISTENER_T_H_
#define _ICCM_QPIDPB_LISTENER_T_H_

#include "QpidPB_Traits_T.h"

#include "qpid/client/MessageListener.h"
#include "qpid/client/Message.h"
#include "qpid/client/SubscriptionManager.h"
#include "qpid/client/Connection.h"
#include "qpid/client/Session.h"

namespace iCCM
{

/**
 * @class QpidPB_Listener_T
 *
 * INSERT CLASS DESCRIPTION HERE
 */
template <typename CONSUMER_T, typename EVENT>
class QpidPB_Listener_T : public qpid::client::MessageListener
{
public:
  typedef QpidPB_Traits_T <EVENT> traits;
  typedef typename traits::protobuf_event_type protobuf_event_type;
  typedef typename traits::upcall_event_type upcall_event_type;

  /// Default constructor.
  QpidPB_Listener_T (CONSUMER_T * consumer);

  /// Destructor.
  virtual ~QpidPB_Listener_T (void);

  /// Start receving events
  virtual void start (qpid::client::Connection & connection,
                      std::string key);

  /// Stop receving events
  virtual void stop (void);

  /// Subscription manager callback for each event
  void received (qpid::client::Message & message);

private:
  CONSUMER_T * consumer_;
  std::string queue_;
  qpid::client::Session session_;
  qpid::client::SubscriptionManager * manager_;
  protobuf_event_type pb_event_;
};

} // namespace iCCM

#if defined (__CUTS_INLINE__)
#include "QpidPB_Listener_T.inl"
#endif  // !defined __CUTS_INLINE__

#include "QpidPB_Listener_T.cpp"

#endif  // _ICCM_QPIDPB_LISTENER_T_H_
