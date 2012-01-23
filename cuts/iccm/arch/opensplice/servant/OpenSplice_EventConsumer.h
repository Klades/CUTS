// -*- C++ -*-

//=============================================================================
/**
 *  @file         OpenSplice_EventConsumer.h
 *
 *  $Id$
 *
 *  @author       James H. Hill
 */
//=============================================================================

#ifndef _CUTS_OPENSPLICE_CCM_EVENTCONSUMER_H_
#define _CUTS_OPENSPLICE_CCM_EVENTCONSUMER_H_

#include "OpenSplice_EventsS.h"
#include "cuts/iccm/servant/EventConsumer.h"

#include "OpenSplice_svnt_export.h"

#include "ccpp_dds_dcps.h"

namespace iCCM
{

/**
 * @class OpenSplice_EventConsumer
 */
class ICCM_OPENSPLICE_SVNT_Export OpenSplice_EventConsumer :
  public virtual EventConsumer,
  public virtual ::POA_Components::OpenSplice::EventConsumer
{
public:
  /// Default constructor.
  OpenSplice_EventConsumer (void);

  /// Destructor.
  virtual ~OpenSplice_EventConsumer (void);

  virtual void configure (::DDS::Subscriber_ptr subscriber) = 0;

protected:
  /// The parent subscriber.
  ::DDS::Subscriber_ptr subscriber_;

  /// The abstract reader for the event consumer.
  ::DDS::DataReader_var abstract_reader_;
};

}

#if defined (__CUTS_INLINE__)
#include "OpenSplice_EventConsumer.inl"
#endif

#endif  // !defined _CUTS_OPENSPLICE_CCM_EVENTCONSUMER_H_
