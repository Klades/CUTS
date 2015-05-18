// -*- C++ -*-

//==============================================================================
/**
 *  @file        QpidPB_Sender_T.h
 *
 *  $Id: generate_cpp_class.py 3685 2012-09-26 14:45:04Z dfeiock $
 *
 *  @author      INSERT NAME HERE
 */
//==============================================================================

#ifndef _ICCM_QPIDPB_SENDER_T_H_
#define _ICCM_QPIDPB_SENDER_T_H_

#include "qpid/client/Session.h"
#include "qpid/client/Message.h"
#include "qpid/client/Connection.h"

namespace iCCM
{

/**
 * @class QpidPB_Sender_T
 *
 * INSERT CLASS DESCRIPTION HERE
 */
template <typename EVENT>
class QpidPB_Sender_T
{
public:
  typedef QpidPB_Traits_T <EVENT> traits;
  typedef typename traits::protobuf_event_type protobuf_event_type;
  typedef typename traits::downcall_event_type downcall_event_type;

  /// Default constructor.
  QpidPB_Sender_T (void);

  /// Destructor.
  ~QpidPB_Sender_T (void);

  virtual void activate (qpid::client::Connection & connection,
                         const std::string & queue);

  virtual void passivate (void);

  virtual EVENT * allocate_event (void);
  virtual void send_event (EVENT * ev);

private:
  qpid::client::Session session_;
  qpid::client::Message message_;
  std::string pb_event_stream_;
};

} // namespace iCCM

#if defined (__CUTS_INLINE__)
#include "QpidPB_Sender_T.inl"
#endif  // !defined __CUTS_INLINE__

#include "QpidPB_Sender_T.cpp"

#endif  // _ICCM_QPIDPB_SENDER_T_H_
