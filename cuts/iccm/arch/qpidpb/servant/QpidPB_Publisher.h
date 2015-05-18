// -*- C++ -*-

//=============================================================================
/**
 *  @file         QpidPB_Publisher.h
 *
 *  $Id$
 *
 *  Code generated by iCCM skeleton project generator that is include
 *  in the CUTS (http://cuts.cs.iupui.edu) and developed by:
 *
 *      Software Engineering & Distributed System (SEDS) Group
 *      Indiana Univesity-Purdue University Indianapolis
 *      Indianapolis, IN 46202
 */
//=============================================================================

#ifndef _ICCM_QPIDPB_PUBLISHER_H_
#define _ICCM_QPIDPB_PUBLISHER_H_

#include "cuts/iccm/servant/Publisher.h"

#include "qpid/client/Connection.h"

#include "QpidPB_EventsC.h"
#include "QpidPB_svnt_export.h"

namespace iCCM
{

/**
 * @class QpidPB_Publisher
 *
 * The base class for all QpidPB publishers that are integrated into
 * the iCCM architecture. In essence, this class is an adapter class that
 * allows a QpidPB publisher to integrate with the iCCM architecture.
 */
class ICCM_QPIDPB_SVNT_Export QpidPB_Publisher :
  public Publisher
{
public:
  /// Default constructor.
  QpidPB_Publisher (void);

  /// Destructor.
  virtual ~QpidPB_Publisher (void);

  /**
   * Connect an event consumer to this publisher. This reference should
   * be narrowed to a ::Components::QpidPB::EventConsumer object.
   *
   * @param[in]           consumer          Referene to event consumer.
   */
  virtual void connect (::Components::EventConsumerBase_ptr consumer);

  /// Disconnect the consumer.
  virtual ::Components::EventConsumerBase_ptr disconnect (void);

  virtual void activate (void);
  virtual void passivate (void);

  virtual void configure_broker (const std::string & host, int port);

protected:
  /// The consumer connected to this publisher.
  ::Components::QpidPB::EventConsumer_var consumer_;

  /// The qpid broker information
  std::string host_;
  int port_;
  std::string queue_;

  /// The qpid connection
  qpid::client::Connection connection_;
};

}

#if defined (__CUTS_INLINE__)
#include "QpidPB_Publisher.inl"
#endif

#endif  // !defined _ICCM_QPIDPB_PUBLISHER_H_
